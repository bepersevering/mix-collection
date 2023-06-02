// Run with
// java -XX:+PrintGC -XX:+DoEscapeAnalysis EscapeTest

import java.util.ArrayList;
import java.util.function.Consumer;

public class EscapeTest {

  public static void forEach(ArrayList<Object> list, Consumer<Object> f) {
    for (Object obj : list) {
      f.accept(obj);
    }
  }

  public static void main(String[] args) {
    ArrayList<Object> list = new ArrayList<>();
    for (int i = 0; i < 100; i++) {
      list.add(i);
    }

    for (int i = 0; i < 400_000_00; i++) {
      forEach(list, obj -> {});
    }
  }
}