/*
1.	编写一个Circle圆类，提供默认构造方法和创建指定半径的构造方法。创建一个InvalidRadiusException异常类，当如果半径为负，则setRadius()方法抛出一个InvalidRadiusException的对象
*/
public class Exercise_06_01 {
	public static void main(String[] args) {
		try {
			new Circle(10);
			new Circle(-2);
			new Circle(0);
		} catch (Exception e) {
			System.out.println(e);
		}
	}
}