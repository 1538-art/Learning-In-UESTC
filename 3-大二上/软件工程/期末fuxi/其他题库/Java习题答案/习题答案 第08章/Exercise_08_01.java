import java.util.*;
public class Exercise_08_01 {
	public static void main(String[] args) {
		List<Integer> list = new ArrayList<Integer>();
		Scanner input = new Scanner(System.in);
		for (int i = 0; i < 10; i++) {
			System.out.println("请输入第" + (i + 1) + "个整数：");
			int d = input.nextInt();
			list.add(d);
		}
		Collections.sort(list);
		Collections.reverse(list);
		System.out.println(list);
	}
}