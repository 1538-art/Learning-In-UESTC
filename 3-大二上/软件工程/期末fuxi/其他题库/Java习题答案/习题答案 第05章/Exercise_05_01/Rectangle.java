
public class Rectangle extends Geometric {
	
	private double side1;
	private double side2;
	
	public Rectangle() {
		super();
	}

	public Rectangle(String color, boolean filled) {
		super(color, filled);
	}

	public Rectangle(double side1, double side2) {
		super();
		setSide1(side1);
		setSide2(side2);
	}

	double getArea() {
		return side1 * side2;
	}

	double getPerimeter() {
		return 2 * (side1 + side2);
	}

	public double getSide1() {
		return side1;
	}

	public void setSide1(double side1) {
		if (side1 >=0 )
			this.side1 = side1;
	}

	public double getSide2() {
		return side2;
	}

	public void setSide2(double side2) {
		if (side2 >=0 )
			this.side2 = side2;
	}

	public String toString() {
		return "Rectangle [side1=" + side1 + ", side2=" + side2 + "]";
	}
}
