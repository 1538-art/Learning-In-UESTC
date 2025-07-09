import java.util.HashMap;
import java.util.Map;

//编写程序计算字符数组中每个字符出现次数。
public class Exercise_03_02 {
    public static void main(String[] args) {
        String str = "abcabdabc";
        //计算给定字符串中每个字符出现的次数
        findCharCount(str);
        //计算给定字符串在 目标字符串中的次数
        findCount(str, "ab");
    }
    //计算给定字符串中每个字符出现的次数
    public static void findCharCount(String str) {
        Map<Character,Integer> map = new HashMap<>();
        for(int i=0;i<str.length();i++) {
            char ch = str.charAt(i);
            //判断map容器中是否包含key
            if(map.containsKey(ch)) {
                //如果集合中已经存在
                Integer count = map.get(ch);
                count += 1;
                //重新存入
                map.put(ch, count);
            }else {
                map.put(ch,1);
            }
        }
        for (Character key : map.keySet()) {
            Integer value = map.get(key);
            System.out.println(key+" 出现了 "+value+" 次");
        }
    }
    //计算字符串在给定字符串出现的次数
    public static void findCount(String src,String des) {
        int index = 0;
        int count = 0;
        while((index = src.indexOf(des, index)) != -1) {
            count++;
            index = index + des.length();
        }
        System.out.println(des+"出现了 "+count+" 次");
    }
}
