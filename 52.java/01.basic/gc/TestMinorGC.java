public class TestMinorGC {
  private static final int _1MB = 1024 * 1024;

  /**
   * VM参数:-verbose:gc -Xms20M -Xmx20M -Xmn10M -XX:+PrintGCDetails
   * -XX:SurvivorRatio=8
   *
   */
  public static void testAllocation1() {
    byte[] allication1, allication2, allication3, allication4;
    allication1 = new byte[2 * _1MB];
    allication2 = new byte[2 * _1MB];
    allication3 = new byte[2 * _1MB];
    allication4 = new byte[4 * _1MB]; // 出现一次MinorGC
  }

  // VM参数:
  // -verbose:gc -Xms20M -Xmx20M -Xmn10M -XX:+PrintGCDetails -XX:SurvivorRatio=8
  // -XX:MaxTenuringThreshold=15 -XX:+PrintTenuringDistribution
  public static void testAllocation2() {
    byte[] allication1, allication2, allication3, allication4;
    allication1 = new byte[_1MB / 4];
    allication2 = new byte[_1MB / 4];
    allication3 = new byte[4 * _1MB];
    allication4 = new byte[4 * _1MB];
    allication4 = null;
    // allication4 = new byte[4 * _1MB];
  }

  // java -verbose:gc -Xms20M -Xmx20M -Xmn10M -XX:+PrintGCDetails
  // -XX:SurvivorRatio=8 TestMinorGC
  public static void main(String[] args) {
    // testAllocation1();
    testAllocation2();
  }
}