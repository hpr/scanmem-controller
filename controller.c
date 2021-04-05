#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdbool.h>
 
// ./configure CFLAGS=-fPIC CXXFLAGS=-fPIC
// make
// gcc -shared *.o -o libscanmem.so

int main() {
  void *scanmemlib;
  bool (*sm_init)(void);
  void (*sm_set_backend)(void);
  void (*sm_backend_exec_cmd)(const char *);
  unsigned long (*sm_get_num_matches)(void);
  void (*sm_cleanup)(void);
  const char *(*sm_get_version)(void);
 
  scanmemlib = dlopen("./libscanmem.so.1.0.0", RTLD_LAZY);
  if (scanmemlib != NULL) {
    sm_init = dlsym(scanmemlib, "sm_init");
    sm_set_backend = dlsym(scanmemlib, "sm_set_backend");
    sm_backend_exec_cmd = dlsym(scanmemlib, "sm_backend_exec_cmd");
    sm_cleanup = dlsym(scanmemlib, "sm_cleanup");
    sm_get_version = dlsym(scanmemlib, "sm_get_version");
    sm_get_num_matches = dlsym(scanmemlib, "sm_get_num_matches");

    sm_set_backend();
    sm_init();

    printf("version %s\n", sm_get_version());

    sm_backend_exec_cmd("pid 32183");
    sm_backend_exec_cmd("18");
    sm_backend_exec_cmd("list");

    sm_cleanup();
    dlclose(scanmemlib);
  } else {
    printf("could not read library\n");
  }
  return EXIT_SUCCESS;
}