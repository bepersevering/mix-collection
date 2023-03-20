public class Singleton1 {  
	private Singleton1() {
	}  
	private static class LazyHolder {
		static final Singleton1 INSTANCE = new Singleton1();
	}

	public static Singleton1 getInstance() {
		return LazyHolder.INSTANCE;
	}
}

