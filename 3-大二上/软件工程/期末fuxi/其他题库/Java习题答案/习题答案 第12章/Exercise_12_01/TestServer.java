import java.io.*;
import java.net.*;
public class TestServer {
	public static void main(String[] args) {
		ServerSocket server = null; 			// 服务套接字
		Socket socket1 = null;
		InputStream is = null; 					// 网络输入流
		InputStreamReader isr = null; 			// 转换流
		BufferedReader bufReader = null; 		// 缓冲流
		OutputStream os = null; 				// 网络输出流
		OutputStreamWriter osw = null; 			// 转换流
		BufferedWriter bufWriter = null; 		// 缓冲流
		try {
			server = new ServerSocket(9999); 	// 服务器绑定在端口号9999上
			socket1 = server.accept(); 			// accept方法会导致程序阻塞,
			System.out.println(socket1);
			is = socket1.getInputStream();
			isr = new InputStreamReader(is);
			bufReader = new BufferedReader(isr);
			String line = bufReader.readLine();
			System.out.println(line);
			os = socket1.getOutputStream();
			osw = new OutputStreamWriter(os);
			bufWriter = new BufferedWriter(osw);
			bufWriter.write("我收到了你的消息,请放心!!");
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