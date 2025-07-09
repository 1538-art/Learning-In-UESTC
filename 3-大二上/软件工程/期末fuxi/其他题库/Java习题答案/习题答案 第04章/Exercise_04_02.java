/*
设计一副牌Poker的外部类和一张牌Card的内部类。
①	Poker类中定义私有成员花色数组、点数数组以及一副牌的数组属性，提供构造方法(创建并初始化一副牌的数组)、随机洗牌方法shuffle（Math.random()获取[0, 1)之间的随机数；获取[n, m)之间的随机数公式：Math.random()*(m-n) + n）和发牌方法deal。
②	Card类中定义花色和点数属性，提供打印信息方法。
③	定义测试类并在main()方法中，创建一副牌Poker对象，并调用shuffle()进行洗牌、发牌方法deal()。

*/

class Poker {
	//花色
	String[] suits = {"黑桃", "红桃", "梅花", "方块"};
	String[] ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	//定义一副牌
	private Card[] cards = new Card[52];
	
	//定义一张牌，由花色和点数构成
	class Card {
		private String suite;	//花色
		private String rank;	//点数
		
		public Card(String suite, String rank) {
			super();
			this.suite = suite;
			this.rank = rank;
		}
		public String toString() {
			return suite + " " +rank;
		}
	}
	
	//创建一副牌
	public Poker() {
		for (int i = 0; i < suits.length; i++) {
			for (int j = 0; j < ranks.length; j++) {
				cards[i * 13 + j] = new Card(suits[i], ranks[j]);
			}
		}
	}
	
	//随机洗牌
	public void shuffle() {
		for (int i = 0; i < cards.length; i++) {
			//Math.random()获取[0, 1)之间的随机数
			//获取[n, m)之间的随机数公式：Math.random()*(m-n) + n
			int index = (int) (Math.random() * cards.length);
			//随机交换数组元素
			Card tmp = cards[i];
			cards[i] = cards[index];
			cards[index] = tmp;
		}
	}
	//发牌
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