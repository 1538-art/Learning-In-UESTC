
public class Circle extends Geometric {

	private final double PI = 3.14;
	private double radius;
	
	
	public Circle() {
	}

	public Circle(String color, boolean filled) {
		super(color, filled);
	}

	public Circle(double radius) {
		super();
		setRadius(radius);
	}
	double getArea() {
		return PI * radius * radius;
	}

	double getPerimeter() {
		return 2 * PI * radius;
	}

	public double getRadius() {
		return radius;
	}

	public void setRadius(double radius) {
		if (radius >= 0)
			this.radius = radius;
	}

	public String toString() {
		return "Circle [radius=" + radius + "]";
	}
}
