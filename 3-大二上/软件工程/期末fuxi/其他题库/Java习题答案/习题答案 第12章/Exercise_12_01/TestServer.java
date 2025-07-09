import java.io.*;
import java.net.*;
public class TestServer {
	public static void main(String[] args) {
		ServerSocket server = null; 			// �����׽���
		Socket socket1 = null;
		InputStream is = null; 					// ����������
		InputStreamReader isr = null; 			// ת����
		BufferedReader bufReader = null; 		// ������
		OutputStream os = null; 				// ���������
		OutputStreamWriter osw = null; 			// ת����
		BufferedWriter bufWriter = null; 		// ������
		try {
			server = new ServerSocket(9999); 	// ���������ڶ˿ں�9999��
			socket1 = server.accept(); 			// accept�����ᵼ�³�������,
			System.out.println(socket1);
			is = socket1.getInputStream();
			isr = new InputStreamReader(is);
			bufReader = new BufferedReader(isr);
			String line = bufReader.readLine();
			System.out.println(line);
			os = socket1.getOutputStream();
			osw = new OutputStreamWriter(os);
			bufWriter = new BufferedWriter(osw);
			bufWriter.write("���յ��������Ϣ,�����!!");
			bufWriter.newLine();
			bufWriter.flush();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				bufReader.close();
			} catch (Exception e2) {
			}
			try {
				bufWriter.close();
			} catch (Exception e2) {
			}
			try {
				socket1.close();
			} catch (Exception e2) {
			}
			try {
				server.close();
			} catch (Exception e2) {
			}
		}
	}
}