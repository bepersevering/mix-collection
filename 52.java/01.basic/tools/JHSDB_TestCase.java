package tools;

public class JHSDB_TestCase {
  static class Test {
    static ObjectHolder staticObj = new ObjectHolder();
    ObjectHolder instanceHolder = new ObjectHolder();

    void foo() {
      ObjectHolder localObj = new ObjectHolder();
      System.out.println("done");
    }
  }

  private static class ObjectHolder {

  }

  public static void main(String[] args) {
    Test test = new JHSDB_TestCase.Test();
    test.foo();
  }
}


