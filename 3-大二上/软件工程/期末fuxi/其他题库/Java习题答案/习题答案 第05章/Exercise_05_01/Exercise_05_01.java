/*
���һ����ΪGeometric�ļ���ͼ�εĳ����࣬���������
?	������Ϊcolor��filled�����Էֱ��ʾͼ����ɫ���Ƿ����
?	һ���޲εĹ��췽����
?	һ���ܴ���ָ����ɫ�����ֵ�Ĺ��췽����
?	һ����ΪgetArea()�ĳ��󷽷�����ͼ�ε������
?	һ����ΪgetPerimeter()�ĳ��󷽷�������ͼ�ε��ܳ�
?	һ����ΪtoString()�����ķ�������Բ���ַ���������
��	���һ����ΪCircle��Բ����ʵ��Geometric�࣬���������
?	һ����Ϊradius��double���Ա�ʾ�뾶��
?	һ���޲ι��췽������Բ��
?	һ���ܴ���ָ��radius��Բ�Ĺ��췽����
?	radius�ķ�����������
?	һ����ΪgetArea()�ķ������ظ�Բ�������
?	һ����ΪgetPerimeter()�ķ�������Բ���ܳ���
?	һ����ΪtoString()�ķ������ظ�Բ���ַ���������
��	���һ����ΪRectangle�ľ�������ʵ��Geometric�࣬�ṩ���Ա�ʾ���εıߡ�
?	������Ϊside1��side2��double���Ա�ʾ���εĶ����ߡ�
?	һ���޲ι��췽���������Ρ�
?	һ���ܴ���ָ��side1��side2��Բ�Ĺ��췽����
?	side1��side2�ķ�����������
?	һ����ΪgetArea()�ķ������ظþ��ε������
?	һ����ΪgetPerimeter()�ķ������ظþ��ε��ܳ���
?	һ����ΪtoString()�ķ������ظþ��ε��ַ���������
��	���һ����ΪTriangle������������ʵ��Geometric�࣬���������
?	������Ϊside1��side2��side3��double���Ա�ʾ�����ε������ߡ�
?	һ���޲ι��췽���������Ρ�
?	һ���ܴ���ָ��side1��side2��side3�ľ��εĹ��췽����
?	side1��side2��side3�ķ�����������
?	һ����ΪgetArea()�ķ������ظ������ε������
?	һ����ΪgetPerimeter()�ķ������ظ������͵��ܳ���
?	һ����ΪisTriangle()�ķ����ж������Ƿ��ܹ��������Ρ�
?	һ����ΪtoString()�ķ������ظ�ɵ�ƽ�С���ַ���������
��	��д�����࣬����ͼ�ε�������ܳ���

*/
public class Exercise_05_01 {
	public static void say(Geometric o) {
		if (null == o)
			return;
		System.out.println(o);
		System.out.println("�����" + o.getArea());
		System.out.println("�ܳ���" + o.getPerimeter());
		System.out.println("��ɫ��" + o.getColor());
		System.out.println("��䣺" + o.isFilled());
	}
	public static void main(String[] args) {
		say(new Circle(10));
		say(new Rectangle(10, 10));
		say(new Triangle(3, 4, 5));
	}
}