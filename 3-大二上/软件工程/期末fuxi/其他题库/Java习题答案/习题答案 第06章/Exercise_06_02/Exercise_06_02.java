/*
2.	��дһ��Triangle�������࣬���������У���������֮���ܴ��ڵ����ߡ�����һ��IllegalTriangleException�쳣�࣬��Triangle��Ĺ��췽���У���������������εı�Υ������һ�������׳�һ��IllegalTriangleException����
*/
public class Exercise_06_02 {
	public static void main(String[] args) {
		try {
			new Triangle(3, 4, 5);
			new Triangle(-3, 4, 5);
			new Triangle(0, 0, 0);
		} catch (Exception e) {
			System.out.println(e);
		}
	}
}