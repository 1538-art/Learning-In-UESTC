//���ó����ȡ��test.txt���ļ����ݲ���ӡ������̨��
import java.io.*;
public class Exercise_9_02 {
	public static void main(String[] args) {
		FileInputStream fis = null;
		try {
			// �����ļ�����������
			fis = new FileInputStream("D:/test.txt");
			int n = 512; 		// �趨��ȡ���ֽ���
			byte buffer[] = new byte[n];
			// ��ȡ������
			while ((fis.read(buffer, 0, n) != -1) && (n > 0)) {
				System.out.print(new String(buffer));
			}
		} catch (Exception e) {
			System.out.println(e);
		} finally {
			try {
				fis.close(); 	// �ر�������
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}