//编写方法返回两个整数的最大公约数和最小公倍数

import java.util.Scanner;

public class Exercise_03_01 {
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入第一个整数");
        int n = sc.nextInt();
        System.out.println("请输入第二个整数");
        int m = sc.nextInt();
        max_min(n,m);
    }
    //求最大公约数和最小公倍数
   private static void max_min(int m,int n)
   {
       int temp = 1;
       int yshu=1;
       int bshu=m*n;
       if(n<m)
       {
           temp = n;
           n=m;
           m=temp;
       }
       while (m!=0)
       {
           temp=n%m;
           n=m;
           m=temp;
       }
       yshu=n;
       bshu/=n;
       System.out.println("最大公约数为"+yshu);
       System.out.println("最小公倍数为"+bshu);

   }
}