/*
	设计一个用户类User，类中的变量有用户名、密码和记录用户数量的变量，定义类的构造方法（无参、为用户名赋值、为用户名和密码赋值）、获取和设置密码的方法和返回类信息的方法。
*/
class User {
	public static int count;		//记录用户数量
	private String name;			//用户名
	private String pwd;			//密码
	
	//无参构造函数
	public User() {
	}
	//初始化用户名构造函数
	public User(String name) {
		this.name = name;
	}
	//初始化用户名和密码构造函数
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
		User u = new User("张三");
		u.setPwd("123");
		String str = u.getInfo();
		System.out.println(str);
	}
}