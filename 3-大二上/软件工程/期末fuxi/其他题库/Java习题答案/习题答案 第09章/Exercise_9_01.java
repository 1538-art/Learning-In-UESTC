//利用程序在D盘下新建一个文本文件“test.txt”，利用程序在文件中写入“千锋IT教育”。
import java.io.*;
public class Exercise_9_01 {
	public static void main(String[] args) {
		FileOutputStream fos = null;
		String str = "千锋IT教育";
		try {
			fos = new FileOutputStream("D:/test.txt");
			fos.write(str.getBytes());
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				fos.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}