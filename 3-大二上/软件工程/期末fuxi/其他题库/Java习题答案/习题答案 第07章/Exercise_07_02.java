public class Exercise_07_02 {
	public static void main(String[] args) {
		String str = "   abc  ccd  ";
		String trim = Exercise_08_02.myTrim(str);
		System.out.println("[" + trim + "]");
	}
	public static String myTrim(String str) {
		int start = 0;
		int end = str.length() - 1;
		while (start < end && str.charAt(start) == ' ') {
			start++;
		}
		while (start < end && str.charAt(end) == ' ') {
			end--;
		}
		return str.substring(start, end + 1);
	}
}