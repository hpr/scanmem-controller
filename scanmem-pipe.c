#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h> 

#define PARENT_READ read_pipe[0]
#define PARENT_WRITE write_pipe[1]
#define CHILD_WRITE read_pipe[1]
#define CHILD_READ write_pipe[0]

#define BUFSIZE 256

#include "ScanmemController.h"

int read_pipe[2];
int write_pipe[2];

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  char response[BUFSIZE] = "";

  pipe(read_pipe);
  pipe(write_pipe);

  pid_t parent = getpid();
  pid_t pid = fork();
  if (pid == -1) {
    printf("failed to fork\n");
  } else if (pid > 0) {
    // parent: need to give child nativeLibraryDir so he can dlopen libscanmem.so
    close(CHILD_READ);
    close(CHILD_WRITE);

    printf("in the parent\n");

    // write(PARENT_WRITE, "test", 4);
    fd_set readfds;
    struct timeval tv = { .tv_sec = 10, .tv_usec = 0 };
    FD_ZERO(&readfds);
    FD_SET(PARENT_READ, &readfds);
    select(PARENT_READ + 1, &readfds, NULL, NULL, &tv);

    if (FD_ISSET(PARENT_READ, &readfds)) {
      read(PARENT_READ, response, BUFSIZE-1); // should read "test" which was written by the child to stdout
      response[BUFSIZE-1] = '\0';
      close(PARENT_READ);
      close(PARENT_WRITE);
      fprintf(stderr, "in parent | message received: %s\n", response);
    }
  } else if (pid == 0) {
    printf("in the child\n");
    // child
    close(PARENT_READ);
    close(PARENT_WRITE);

    dup2(CHILD_READ, STDIN_FILENO);
    dup2(CHILD_WRITE, STDOUT_FILENO);
    close(CHILD_READ);
    close(CHILD_WRITE);

    execlp("./scanmem-controller", "./scanmem-controller", NULL);
    perror("exec failed\n");
  }

  return JNI_VERSION_1_6;
}

JNIEXPORT jstring JNICALL Java_ScanmemController_sm_1get_1version(JNIEnv* env, jclass obj) {
  char* cmd = "sm_get_version";
  write(PARENT_WRITE, cmd, sizeof(cmd));
  // todo: read & return version
  return (*env)->NewStringUTF(env, "version");
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {
  // sm_cleanup();
  // dlclose(libscanmem);
}