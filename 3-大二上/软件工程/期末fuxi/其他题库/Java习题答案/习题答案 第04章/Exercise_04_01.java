/*
	���һ���û���User�����еı������û���������ͼ�¼�û������ı�����������Ĺ��췽�����޲Ρ�Ϊ�û�����ֵ��Ϊ�û��������븳ֵ������ȡ����������ķ����ͷ�������Ϣ�ķ�����
*/
class User {
	public static int count;		//��¼�û�����
	private String name;			//�û���
	private String pwd;			//����
	
	//�޲ι��캯��
	public User() {
	}
	//��ʼ���û������캯��
	public User(String name) {
		this.name = name;
	}
	//��ʼ���û��������빹�캯��
	public User(String name, String pwd) {
		this.name = name;
		this.pwd = pwd;
	}
	public String getPwd() {
		return pwd;
	}
	public void setPwd(String pwd) {
		this.pwd = pwd;
	}
	public String getInfo() {
		return "User [name=" + name + "]";
	}
}
public class Exercise_04_01 {
	public static void main(String[] args) {
		User u = new User("����");
		u.setPwd("123");
		String str = u.getInfo();
		System.out.println(str);
	}
}