import java.net.*;
public class TestSend {
	public static void main(String[] args) throws Exception {
		DatagramSocket ds = new DatagramSocket();
		byte[] data = "����IT����".getBytes();
		DatagramPacket dp = new DatagramPacket(data, 0, data.length,
				InetAddress.getByName("127.0.0.1"), 8088);
		ds.send(dp); 	// �����ݰ����͸�Ӳ��
		ds.close();
	}
}