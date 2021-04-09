class ScanmemController {
  static {
    //System.loadLibrary("scanmem-controller");
    System.load("/home/habs/rn/scanmem-controller/scanmem-controller.so");
  }
  private static native String s_get_version();
  public static void main(String args[]) {
    try {
      System.out.println(s_get_version());
    } catch(UnsatisfiedLinkError e) {
      System.out.println(e.getMessage());
      throw e;
    }
  }
}