//利用程序读取“test.txt”文件内容并打印到控制台。
import java.io.*;
public class Exercise_9_02 {
	public static void main(String[] args) {
		FileInputStream fis = null;
		try {
			// 创建文件输入流对象
			fis = new FileInputStream("D:/test.txt");
			int n = 512; 		// 设定读取的字节数
			byte buffer[] = new byte[n];
			// 读取输入流
			while ((fis.read(buffer, 0, n) != -1) && (n > 0)) {
				System.out.print(new String(buffer));
			}
		} catch (Exception e) {
			System.out.println(e);
		} finally {
			try {
				fis.close(); 	// 关闭输入流
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}