public class FinalizeEscapeGC {
	public static FinalizeEscapeGC SAVE_HOOK = null;

	public void isAlive() {
		System.out.println("yes, i am still alive. ");
	}

	@Override
	protected void finalize() throws Throwable {
		super.finalize();
		System.out.println("Finalize method executed!");
	}
}
