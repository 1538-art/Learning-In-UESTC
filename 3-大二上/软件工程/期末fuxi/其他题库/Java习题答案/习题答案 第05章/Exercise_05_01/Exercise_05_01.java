/*
设计一个名为Geometric的几何图形的抽象类，该类包括：
?	二个名为color、filled的属性分别表示图形颜色和是否填充
?	一个无参的构造方法。
?	一个能创建指定颜色和填充值的构造方法。
?	一个名为getArea()的抽象方法返回图形的面积。
?	一个名为getPerimeter()的抽象方法方法返图形的周长
?	一个名为toString()方法的方法返回圆的字符串描述。
②	设计一个名为Circle的圆类来实现Geometric类，该类包括：
?	一个名为radius的double属性表示半径。
?	一个无参构造方法创建圆。
?	一个能创建指定radius的圆的构造方法。
?	radius的访问器方法。
?	一个名为getArea()的方法返回该圆的面积。
?	一个名为getPerimeter()的方法返回圆的周长。
?	一个名为toString()的方法返回该圆的字符串描述。
③	设计一个名为Rectangle的矩形类来实现Geometric类，提供属性表示矩形的边。
?	二个名为side1、side2的double属性表示矩形的二条边。
?	一个无参构造方法创建矩形。
?	一个能创建指定side1和side2的圆的构造方法。
?	side1和side2的访问器方法。
?	一个名为getArea()的方法返回该矩形的面积。
?	一个名为getPerimeter()的方法返回该矩形的周长。
?	一个名为toString()的方法返回该矩形的字符串描述。
④	设计一个名为Triangle的三角形类来实现Geometric类，该类包括：
?	三个名为side1、side2和side3的double属性表示三角形的三条边。
?	一个无参构造方法创三角形。
?	一个能创建指定side1、side2和side3的矩形的构造方法。
?	side1、side2和side3的访问器方法。
?	一个名为getArea()的方法返回该三角形的面积。
?	一个名为getPerimeter()的方法返回该三角型的周长。
?	一个名为isTriangle()的方法判断三边是否能构成三角形。
?	一个名为toString()的方法返回该傻逼较小的字符串描述。
⑤	编写测试类，测试图形的面积和周长。

*/
public class Exercise_05_01 {
	public static void say(Geometric o) {
		if (null == o)
			return;
		System.out.println(o);
		System.out.println("面积：" + o.getArea());
		System.out.println("周长：" + o.getPerimeter());
		System.out.println("颜色：" + o.getColor());
		System.out.println("填充：" + o.isFilled());
	}
	public static void main(String[] args) {
		say(new Circle(10));
		say(new Rectangle(10, 10));
		say(new Triangle(3, 4, 5));
	}
}