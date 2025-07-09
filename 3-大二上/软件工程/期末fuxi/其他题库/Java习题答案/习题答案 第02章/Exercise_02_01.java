//编写程序实现1!+2!+3!+…20!的和
public class Exercise_02_01 {
	public static void main(String[] args) {
		int sum = 0;
		int tmp;
		for (int i = 1; i <= 20; i++) {
			tmp = 1;
			for (int j = 1; j <= i; j++) {
				tmp *= j;
			}
			sum += tmp;
		}
		System.out.println(sum);
	}
}
