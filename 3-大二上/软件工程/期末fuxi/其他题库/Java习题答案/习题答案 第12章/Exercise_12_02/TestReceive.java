import java.net.*;
public class TestReceive {
	public static void main(String[] args) throws Exception {
		// 绑定端口
		DatagramSocket ds = new DatagramSocket(8088);
		byte[] buf = new byte[1024];
		DatagramPacket dp = new DatagramPacket(buf, buf.length);
		// 接收数据
		ds.receive(dp); 	// 接收到的数据保存在DatagramPacket对象中
		String string = new String(buf, 0, dp.getLength());
		System.out.println(string);
		ds.close();
	}
}