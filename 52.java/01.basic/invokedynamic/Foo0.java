
import java.lang.invoke.*;

public class Foo0 {
  public static void bar(Object o) {
    new Exception().printStackTrace();
  }

  public static void main(String[] args) throws Throwable {
    MethodHandles.Lookup l = MethodHandles.lookup();
    MethodType t = MethodType.methodType(void.class, Object.class);
    MethodHandle mh = l.findStatic(Foo0.class, "bar", t);
    mh.invokeExact(new Object());
  }
}
