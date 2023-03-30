import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.invoke.MethodType;

public class Foo2 {

    public void bar(Object o) {

    }

    public static void main(String[] args) throws Throwable {
		MethodHandles.Lookup l = MethodHandles.lookup();
        MethodType t = MethodType.methodType(void.class, Object.class);
        MethodHandle mh = l.findVirtual(Foo2.class, "bar", t);
		
		Foo2 foo = new Foo2();
		Object object = new Object();
        long current = System.currentTimeMillis();
        for (int i = 1; i < 2_000_000_000; i++) {
            if (i % 100_000_000 == 0) {
                long temp = System.currentTimeMillis();
                System.out.println(temp - current);
                current = temp;
            }
            mh.invokeExact(foo, object);
        }

    }
}

