/*
2.	编写一个Triangle三角形类，在三角形中，任意两边之和总大于第三边。创建一个IllegalTriangleException异常类，在Triangle类的构造方法中，如果创建的三角形的边违反了这一规则，则抛出一个IllegalTriangleException对象
*/
public class Exercise_06_02 {
	public static void main(String[] args) {
		try {
			new Triangle(3, 4, 5);
			new Triangle(-3, 4, 5);
			new Triangle(0, 0, 0);
		} catch (Exception e) {
			System.out.println(e);
		}
	}
}