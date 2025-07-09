public class Exercise_11_02 {
	public static void main(String[] args) {
		MyThread t1 = new MyThread("Thread-1", (int) (Math.random() * 100));
		MyThread t2 = new MyThread("Thread-2", (int) (Math.random() * 100));
		MyThread t3 = new MyThread("Thread-3", (int) (Math.random() * 100));
		t1.start();
		t2.start();
		t3.start();
	}
}
class MyThread extends Thread {
	private String whoAmI;
	private int delay;
	public MyThread(String s, int d) {
		whoAmI = s;
		delay = d;
	}
	public void run() {
		try {
			sleep(delay);
		} catch (InterruptedException ie) {
		}
		System.out.println("Hello!I am " + whoAmI + ",I sleep " + delay
				+ " milliseconds");
	}
}