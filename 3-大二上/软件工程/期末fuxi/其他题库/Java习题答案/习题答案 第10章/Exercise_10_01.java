package com.qianfeng.java7;

import java.awt.*;
import javax.swing.*;
public class Exercise_10_01 {
	public static void main(String[] args) {
		new Exercise_11_01().display();
	}
	JButton b1, b2, b3, b4, b5;
	JFrame frame; 											// ����
	public void display() {
		frame = new JFrame("JFrame����");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		b1 = new JButton("��");
		b2 = new JButton("��");
		b3 = new JButton("��");
		b4 = new JButton("��");
		b5 = new JButton("��");
		BorderLayout borderLayout = new BorderLayout();
		Container contentPane = frame.getContentPane(); 	// ����
		contentPane.setLayout(borderLayout);
		contentPane.add(b1, BorderLayout.EAST);
		contentPane.add(b2, BorderLayout.WEST);
		contentPane.add(b3, BorderLayout.SOUTH);
		contentPane.add(b4, BorderLayout.NORTH);
		contentPane.add(b5, BorderLayout.CENTER);
		contentPane.setSize(200, 100);
		frame.pack();
		frame.setVisible(true);
	}
}
