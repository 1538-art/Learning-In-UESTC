
public class Triangle extends Geometric {

	private double side1;
	private double side2;
	private double side3;

	public Triangle() {
		super();
	}

	public Triangle(String color, boolean filled) {
		super(color, filled);
	}

	public Triangle(double side1, double side2, double side3) {
		super();
		setSide1(side1);
		setSide2(side2);
		setSide3(side3);
	}

	double getArea() {
		if (!isTriangle()) 
			return 0;
		double p = (side1 + side2 + side3) / 2;
		return Math.sqrt(p * (p - side1) * (p - side2) * (p - side3));
	}

	double getPerimeter() {
		if (!isTriangle()) 
			return 0;
		return side1 + side2 + side3;
	}

	// 判断是否是个三角形
	public boolean isTriangle() {
		//任意两边和大于第三边
		if (side1 + side2 > side3 && side1 + side3 > side2 && side2 + side3 > side1)
			return true;
		return false;
	}

	public double getSide1() {
		return side1;
	}

	public void setSide1(double side1) {
		if (side1 >= 0)
			this.side1 = side1;
	}

	public double getSide2() {
		return side2;
	}

	public void setSide2(double side2) {
		if (side2 >= 0)
			this.side2 = side2;
	}

	public double getSide3() {
		return side3;
	}

	public void setSide3(double side3) {
		if (side3 >= 0)
			this.side3 = side3;
	}

	public String toString() {
		return "Triangle [side1=" + side1 + ", side2=" + side2 + ", side3=" + side3 + "]";
	}
}
