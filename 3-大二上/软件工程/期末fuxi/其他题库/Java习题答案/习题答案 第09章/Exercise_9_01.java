//���ó�����D�����½�һ���ı��ļ���test.txt�������ó������ļ���д�롰ǧ��IT��������
import java.io.*;
public class Exercise_9_01 {
	public static void main(String[] args) {
		FileOutputStream fos = null;
		String str = "ǧ��IT����";
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