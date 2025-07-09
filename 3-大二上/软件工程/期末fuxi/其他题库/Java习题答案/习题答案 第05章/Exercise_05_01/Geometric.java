
public abstract class Geometric {
	private String color;	//颜色
	private boolean filled;	//是否填充
	
	//默认构造方法
	public Geometric() {
	}
	//带颜色和填充值的构造方法
	public Geometric(String color, boolean filled) {
		super();
		this.color = color;
		this.filled = filled;
	}
	//获取面积
	abstract double getArea();
	//获取周长
	abstract double getPerimeter();
	
	public String getColor() {
		return color;
	}
	
	public void setColor(String color) {
		this.color = color;
	}
	
	public boolean isFilled() {
		return filled;
	}
	
	public void setFilled(boolean filled) {
		this.filled = filled;
	}
	
	public String toString() {
		return "Geometric [color=" + color + ", filled=" + filled + "]";
	}
}
