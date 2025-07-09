import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
public class Exercise_10_02 extends JFrame {
	public static void main(String[] args) {
		new Exercise_11_02();
	}
	private JPanel pane = null;
	private JPanel p = null;
	private CardLayout card = null;
	private JButton button_1 = null;
	private JButton button_2 = null;
	private JButton b1 = null, b2 = null, b3 = null;
	private JPanel p1 = null, p2 = null, p3 = null;
	public Exercise02() {
		super("JFrame窗口");
		try {
			UIManager
					.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		// 创建新卡片布局
		card = new CardLayout(5, 5);
		pane = new JPanel(card);
		p = new JPanel();
		button_1 = new JButton("< 上一张");
		button_2 = new JButton("下一张  >");
		b1 = new JButton("1");
		b2 = new JButton("2");
		b3 = new JButton("3");
		b1.setMargin(new Insets(2, 2, 2, 2));
		b2.setMargin(new Insets(2, 2, 2, 2));
		b3.setMargin(new Insets(2, 2, 2, 2));
		p.add(button_1);
		p.add(b1);
		p.add(b2);
		p.add(b3);
		p.add(button_2);
		p1 = new JPanel();
		p2 = new JPanel();
		p3 = new JPanel();
		p1.setBackground(Color.RED);
		p2.setBackground(Color.BLUE);
		p3.setBackground(Color.GREEN);
		p1.add(new JLabel("红"));
		p2.add(new JLabel("蓝"));
		p3.add(new JLabel("绿"));
		pane.add(p1, "p1");
		pane.add(p2, "p2");
		pane.add(p3, "p3");
		// 翻转卡片布局动作
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				card.previous(pane);
			}
		});
		button_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				card.next(pane);
			}
		});
		b1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				card.show(pane, "p1");
			}
		});
		b2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				card.show(pane, "p2");
			}
		});
		b3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				card.show(pane, "p3");
			}
		});
		this.getContentPane().add(pane);
		this.getContentPane().add(p, BorderLayout.SOUTH);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(300, 200);
		this.setVisible(true);
	}
}