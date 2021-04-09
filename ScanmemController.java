class ScanmemController {
  static {
    //System.loadLibrary("scanmem-controller");
    System.load("/home/habs/rn/scanmem-controller/scanmem-controller.so");
  }
  private static native String sm_get_version();
  private static native boolean sm_init();
  private static native void sm_set_backend();
  private static native void sm_cleanup();
  private static native void sm_backend_exec_cmd(String cmd);

  public static void main(String args[]) {
    System.out.println(sm_get_version());

    sm_backend_exec_cmd("pid 32813");
  }
}