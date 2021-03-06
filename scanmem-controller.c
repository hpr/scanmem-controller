#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdbool.h>

#include <sys/select.h>
#include <string.h>

void* libscanmem;
const char* (*sm_get_version)(void);
bool (*sm_init)(void);
void (*sm_set_backend)(void);
unsigned long (*sm_get_num_matches)(void);
void (*sm_backend_exec_cmd)(const char*);
void (*sm_cleanup)(void);

// JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
//   libscanmem = dlopen("./libscanmem.so.1.0.0", RTLD_LAZY);
//   if (libscanmem == NULL) printf("%s", dlerror());
//   sm_get_version = dlsym(libscanmem, "sm_get_version");
//   sm_init = dlsym(libscanmem, "sm_init");
//   sm_set_backend = dlsym(libscanmem, "sm_set_backend");
//   sm_backend_exec_cmd = dlsym(libscanmem, "sm_backend_exec_cmd");
//   sm_cleanup = dlsym(libscanmem, "sm_cleanup");
//   sm_get_num_matches = dlsym(libscanmem, "sm_get_num_matches");

//   sm_init();
//   sm_set_backend();

//   return JNI_VERSION_1_6;
// }

// JNIEXPORT jstring JNICALL Java_ScanmemController_sm_1get_1version(JNIEnv* env, jclass obj) {
//   return (*env)->NewStringUTF(env, sm_get_version());
// }

// JNIEXPORT jboolean JNICALL Java_ScanmemController_sm_1init(JNIEnv* env, jclass obj) {
//   return sm_init();
// }

// JNIEXPORT void JNICALL Java_ScanmemController_sm_1set_1backend(JNIEnv* env, jclass obj) {
//   sm_set_backend();
// }

// JNIEXPORT void JNICALL Java_ScanmemController_sm_1cleanup(JNIEnv* env, jclass obj) {
//   sm_cleanup();
// }

// JNIEXPORT void JNICALL Java_ScanmemController_sm_1backend_1exec_1cmd(JNIEnv* env, jclass obj, jstring cmd) {
//   sm_backend_exec_cmd((*env)->GetStringUTFChars(env, cmd, 0));
// }

// JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {
//   sm_cleanup();
//   dlclose(libscanmem);
// }

const char* get_version() {
  return sm_get_version();
}

int main() {
  libscanmem = dlopen("./libscanmem.so.1.0.0", RTLD_LAZY);
  if (libscanmem == NULL) printf("%s", dlerror());
  sm_get_version = dlsym(libscanmem, "sm_get_version");
  char* cmd;
  fd_set fds;
  while (strcmp(cmd, "exit") != 0) {
    // select to read from stdin
  }
  printf("backwards");
  dlclose(libscanmem);
}