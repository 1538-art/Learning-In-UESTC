/*
1.	��дһ��CircleԲ�࣬�ṩĬ�Ϲ��췽���ʹ���ָ���뾶�Ĺ��췽��������һ��InvalidRadiusException�쳣�࣬������뾶Ϊ������setRadius()�����׳�һ��InvalidRadiusException�Ķ���
*/
public class Exercise_06_01 {
	public static void main(String[] args) {
		try {
			new Circle(10);
			new Circle(-2);
			new Circle(0);
		} catch (Exception e) {
			System.out.println(e);
		}
	}
}