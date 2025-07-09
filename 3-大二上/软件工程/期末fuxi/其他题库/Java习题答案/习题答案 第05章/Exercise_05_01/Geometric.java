
public abstract class Geometric {
	private String color;	//��ɫ
	private boolean filled;	//�Ƿ����
	
	//Ĭ�Ϲ��췽��
	public Geometric() {
	}
	//����ɫ�����ֵ�Ĺ��췽��
	public Geometric(String color, boolean filled) {
		super();
		this.color = color;
		this.filled = filled;
	}
	//��ȡ���
	abstract double getArea();
	//��ȡ�ܳ�
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
