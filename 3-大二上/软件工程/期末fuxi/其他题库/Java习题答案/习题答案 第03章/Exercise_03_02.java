import java.util.HashMap;
import java.util.Map;

//��д��������ַ�������ÿ���ַ����ִ�����
public class Exercise_03_02 {
    public static void main(String[] args) {
        String str = "abcabdabc";
        //��������ַ�����ÿ���ַ����ֵĴ���
        findCharCount(str);
        //��������ַ����� Ŀ���ַ����еĴ���
        findCount(str, "ab");
    }
    //��������ַ�����ÿ���ַ����ֵĴ���
    public static void findCharCount(String str) {
        Map<Character,Integer> map = new HashMap<>();
        for(int i=0;i<str.length();i++) {
            char ch = str.charAt(i);
            //�ж�map�������Ƿ����key
            if(map.containsKey(ch)) {
                //����������Ѿ�����
                Integer count = map.get(ch);
                count += 1;
                //���´���
                map.put(ch, count);
            }else {
                map.put(ch,1);
            }
        }
        for (Character key : map.keySet()) {
            Integer value = map.get(key);
            System.out.println(key+" ������ "+value+" ��");
        }
    }
    //�����ַ����ڸ����ַ������ֵĴ���
    public static void findCount(String src,String des) {
        int index = 0;
        int count = 0;
        while((index = src.indexOf(des, index)) != -1) {
            count++;
            index = index + des.length();
        }
        System.out.println(des+"������ "+count+" ��");
    }
}
