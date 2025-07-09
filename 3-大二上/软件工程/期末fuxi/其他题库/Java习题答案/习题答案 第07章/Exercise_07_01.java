public class Exercise_07_01 {
	public static void main(String[] args) {
		String str = "abcdefg";
		StringBuffer reverse = Exercise_08_01.reverseString1(str, 1, 4);
		System.out.println(reverse);
	}
	public static StringBuffer reverseString1(String str, int start, int end) {
		StringBuffer sb = new StringBuffer(str.substring(0, start));
		for (int i = end; i >= start; i--) {
			char c = str.charAt(i);
			sb.append(c);
		}
		sb.append(str.substring(end + 1));
		return sb;
	}
}