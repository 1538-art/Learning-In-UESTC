import java.text.*;
import java.util.Date;
public class Exercise_07_03 {
	public static void main(String[] args) {
		String date1 = "1990/1/1"; 			// 开始“三天打渔两天晒网”的日期
		String date2 = "2016/1/1"; 			// 结束的日期
		long day = getDay(date1, date2);	// 传入值计算时间差
		if ((day + 1) % 5 == 0 || (day + 1) % 5 == 4) {
			System.out.println(date2 + "是晒网日");
		} else {
			System.out.println(date2 + "是打渔日");
		}
	}
	public static long getDay(String time1, String time2) {
		long dayDistance = 0;
		SimpleDateFormat ft = new SimpleDateFormat("yyyy/MM/dd");
		try {
			Date date1 = ft.parse(time1);
			Date date2 = ft.parse(time2);
			dayDistance = date2.getTime() - date1.getTime();
			dayDistance = dayDistance / 1000 / 60 / 60 / 24;
		} catch (ParseException e) {
			e.printStackTrace();
		}
		return dayDistance;
	}
}