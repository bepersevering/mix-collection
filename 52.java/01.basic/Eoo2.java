import sun.misc.Unsafe;

import java.lang.reflect.Field;

public class Eoo2 {

    static boolean boolValue = true;

    public static void main(String[] args) throws NoSuchFieldException, IllegalAccessException {
        // boolValue = true; // 将这个true替换为2或者3，再看看打印结果
        long offset = getUnsafe().staticFieldOffset(Eoo2.class.getDeclaredField("boolValue"));

        if (boolValue) System.out.println("Hello, Java!");
        if (boolValue == true) System.out.println("Hello, JVM!");
        System.out.println("putBoolean");
        getUnsafe().putBoolean(Eoo2.class, offset, false);
        if (boolValue) System.out.println("Hello, Java!");
        if (boolValue == true) System.out.println("Hello, JVM!");
        System.out.println("putByte 2");
        getUnsafe().putByte(Eoo2.class, offset, (byte) 2);
        if (boolValue) System.out.println("Hello, Java!");
        if (boolValue == true) System.out.println("Hello, JVM!");
        System.out.println("putByte 3");
        getUnsafe().putByte(Eoo2.class, offset, (byte) 3);
        if (boolValue) System.out.println("Hello, Java!");
        if (boolValue == true) System.out.println("Hello, JVM!");
    }

    public static Unsafe getUnsafe() throws NoSuchFieldException, IllegalAccessException {
        Field f = Unsafe.class.getDeclaredField("theUnsafe");
        f.setAccessible(true);
        return (Unsafe) f.get(null);
    }

}
