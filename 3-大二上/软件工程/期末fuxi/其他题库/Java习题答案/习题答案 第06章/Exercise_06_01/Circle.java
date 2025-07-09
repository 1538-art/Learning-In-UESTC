
public class Circle  {

	private final double PI = 3.14;
	private double radius;
	
	
	public Circle() {
	}

	public Circle(double radius) throws InvalidRadiusException {
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

	public void setRadius(double radius) throws InvalidRadiusException {
		if (radius < 0)
			throw new InvalidRadiusException(radius);
		this.radius = radius;
	}

	public String toString() {
		return "Circle [radius=" + radius + "]";
	}
}
