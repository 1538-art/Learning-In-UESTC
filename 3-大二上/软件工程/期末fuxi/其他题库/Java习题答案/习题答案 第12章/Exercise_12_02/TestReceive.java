import java.net.*;
public class TestReceive {
	public static void main(String[] args) throws Exception {
		// �󶨶˿�
		DatagramSocket ds = new DatagramSocket(8088);
		byte[] buf = new byte[1024];
		DatagramPacket dp = new DatagramPacket(buf, buf.length);
		// ��������
		ds.receive(dp); 	// ���յ������ݱ�����DatagramPacket������
		String string = new String(buf, 0, dp.getLength());
		System.out.println(string);
		ds.close();
	}
}