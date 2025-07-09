//利用转换流复制“test.txt”为“my.txt”。
import java.io.*;
public class Exercise_9_03 {
	public static void main(String[] args) {
		InputStreamReader isr = null;
		OutputStreamWriter osw = null;
		try {
			// 创建字节输入流
			FileInputStream fis = new FileInputStream("D:/test.txt");
			// 将字节输入流转换为字符输入流
			isr = new InputStreamReader(fis);
			// 创建字节输出流
			FileOutputStream fos = new FileOutputStream("D:/my.txt");
			// 将字节输出流转换成字符输出流
			osw = new OutputStreamWriter(fos);
			int str;
			while ((str = isr.read()) != -1) {
				osw.write(str);
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (osw != null) {
				try {
					osw.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
				if (isr != null) {
					try {
						isr.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}
		}
	}
}