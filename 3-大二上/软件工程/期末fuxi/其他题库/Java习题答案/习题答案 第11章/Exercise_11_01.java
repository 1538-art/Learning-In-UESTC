public class Exercise_11_01 extends Thread {
	int k = 1;
	public static void main(String[] args) {
		Exercise_07_01 t1 = new Exercise_07_01();
		Exercise_07_01 t2 = new Exercise_07_01();
		t1.k = 1;
		t2.k = 2;
		t1.start();
		t2.start();
	}
	public void run() {
		int i = k;
		while (i < 10) {
			System.out.println(Thread.currentThread().getName() + "-----" + i);
			i += 2;
		}
		System.out.println(Thread.currentThread().getName() + " end");
	}
}