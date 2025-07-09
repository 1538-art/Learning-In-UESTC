import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
public class Exercise_08_02 {
	public static void main(String[] args) {
		Map<String, Integer> map = new HashMap<String, Integer>();
		map.put("AA", 100);
		map.put("BB", 80);
		map.put("CC", 90);
		map.put("DD", 90);
		map.put("EE", 93);
		map.put("WW", 93);
		map.put("HH", 95);
		map.put("DD", 90);
		// 通过.entrySet()的方法把Map类型的转化为Set集合
		Set<Entry<String, Integer>> entrySet = map.entrySet();
		// 把Set集合转化为List集合
		List<Entry<String, Integer>> list = new ArrayList<Map.Entry<String, Integer>>(
				entrySet);
		// 通过Collections.sort排序
		Collections.sort(list, new Comparator<Entry<String, Integer>>() {
			public int compare(Entry<String, Integer> o1,
					Entry<String, Integer> o2) {
				return o2.getValue() - o1.getValue();
			}
		});
		for (int i = 0; i < 3; i++) {
			System.out.println(list.get(i).getKey());
		}
	}
}