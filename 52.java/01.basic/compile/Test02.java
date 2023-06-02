import java.lang.Math;

public class Test02 {

    public static int foo(boolean f, int in) {
        int v;
        if (f) {
            v = in;
        } else {
            v = (int)Math.sin(in);
        }

        if (v == in) {
            return 0;
        } else {
            return (int)Math.cos(v);
        }
    }

}
