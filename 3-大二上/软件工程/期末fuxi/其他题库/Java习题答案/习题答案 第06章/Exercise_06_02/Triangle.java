
public class Triangle {

	private double side1;
	private double side2;
	private double side3;

	public Triangle() {
		
	}
	public Triangle(double side1, double side2, double side3) throws IllegalTriangleException {
		super();
		this.setSide(side1, side2, side3);
	}

	double getArea() {
		double p = (side1 + side2 + side3) / 2;
		return Math.sqrt(p * (p - side1) * (p - side2) * (p - side3));
	}

	double getPerimeter() {
		return side1 + side2 + side3;
	}

	// 判断是否是个三角形
	public boolean isTriangle() {
		//任意两边和大于第三边
		if (side1 + side2 > side3 && side1 + side3 > side2 && side2 + side3 > side1)
			return true;
		return false;
	}
	
	public void setSide(double side1, double side2, double side3) throws IllegalTriangleException {
		this.side1 = side1;
		this.side2 = side2;
		this.side3 = side3;
		if (!isTriangle())
			throw new IllegalTriangleException(side1, side2, side3);
	}

	public double getSide1() {
		return side1;
	}

	public double getSide2() {
		return side2;
	}

	public double getSide3() {
		return side3;
	}

	public String toString() {
		return "Triangle [side1=" + side1 + ", side2=" + side2 + ", side3=" + side3 + "]";
	}
}
