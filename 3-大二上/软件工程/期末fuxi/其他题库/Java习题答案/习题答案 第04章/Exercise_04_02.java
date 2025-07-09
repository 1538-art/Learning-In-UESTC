/*
���һ����Poker���ⲿ���һ����Card���ڲ��ࡣ
��	Poker���ж���˽�г�Ա��ɫ���顢���������Լ�һ���Ƶ��������ԣ��ṩ���췽��(��������ʼ��һ���Ƶ�����)�����ϴ�Ʒ���shuffle��Math.random()��ȡ[0, 1)֮������������ȡ[n, m)֮����������ʽ��Math.random()*(m-n) + n���ͷ��Ʒ���deal��
��	Card���ж��廨ɫ�͵������ԣ��ṩ��ӡ��Ϣ������
��	��������ಢ��main()�����У�����һ����Poker���󣬲�����shuffle()����ϴ�ơ����Ʒ���deal()��

*/

class Poker {
	//��ɫ
	String[] suits = {"����", "����", "÷��", "����"};
	String[] ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	//����һ����
	private Card[] cards = new Card[52];
	
	//����һ���ƣ��ɻ�ɫ�͵�������
	class Card {
		private String suite;	//��ɫ
		private String rank;	//����
		
		public Card(String suite, String rank) {
			super();
			this.suite = suite;
			this.rank = rank;
		}
		public String toString() {
			return suite + " " +rank;
		}
	}
	
	//����һ����
	public Poker() {
		for (int i = 0; i < suits.length; i++) {
			for (int j = 0; j < ranks.length; j++) {
				cards[i * 13 + j] = new Card(suits[i], ranks[j]);
			}
		}
	}
	
	//���ϴ��
	public void shuffle() {
		for (int i = 0; i < cards.length; i++) {
			//Math.random()��ȡ[0, 1)֮��������
			//��ȡ[n, m)֮����������ʽ��Math.random()*(m-n) + n
			int index = (int) (Math.random() * cards.length);
			//�����������Ԫ��
			Card tmp = cards[i];
			cards[i] = cards[index];
			cards[index] = tmp;
		}
	}
	//����
	public void deal() {
		for (int i = 0; i < 52; i++) {
			System.out.print(cards[i] + "\t");
			if ((i+1) % 13 == 0)
				System.out.println();
		}
	}
}

public class Exercise_04_02 {
	public static void main(String[] args) {
		Poker obj = new Poker();
		obj.shuffle();
		obj.deal();
	}
}