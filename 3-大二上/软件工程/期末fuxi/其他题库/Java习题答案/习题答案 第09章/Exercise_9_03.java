//����ת�������ơ�test.txt��Ϊ��my.txt����
import java.io.*;
public class Exercise_9_03 {
	public static void main(String[] args) {
		InputStreamReader isr = null;
		OutputStreamWriter osw = null;
		try {
			// �����ֽ�������
			FileInputStream fis = new FileInputStream("D:/test.txt");
			// ���ֽ�������ת��Ϊ�ַ�������
			isr = new InputStreamReader(fis);
			// �����ֽ������
			FileOutputStream fos = new FileOutputStream("D:/my.txt");
			// ���ֽ������ת�����ַ������
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