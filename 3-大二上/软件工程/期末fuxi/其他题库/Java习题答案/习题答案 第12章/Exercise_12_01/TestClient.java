import java.io.*;
import java.net.*;
public class TestClient {
	public static void main(String[] args) {
		Socket socket2 = null;
		OutputStream os = null;
		OutputStreamWriter osw = null;
		BufferedWriter bufWriter = null;
		InputStream is = null;
		InputStreamReader isr = null;
		BufferedReader bufReader = null;
		try {
			socket2 = new Socket("127.0.0.1", 9999); 	// 创建Socket对象的过程,就是发起请求的过程,
			System.out.println(socket2);
			os = socket2.getOutputStream(); 			// 获取输出流对象
			osw = new OutputStreamWriter(os);
			bufWriter = new BufferedWriter(osw);
			bufWriter.write("千锋IT教育");
			bufWriter.newLine();
			bufWriter.flush(); 							// 把数据刷入网线
			is = socket2.getInputStream();
			isr = new InputStreamReader(is);
			bufReader = new BufferedReader(isr);
			String line = bufReader.readLine();
			System.out.println(line);
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				bufWriter.close();
			} catch (Exception e2) {
			}
			try {
				bufReader.close();
			} catch (Exception e2) {
			}
			try {
				socket2.close();
			} catch (Exception e2) {
			}
		}
	}
}