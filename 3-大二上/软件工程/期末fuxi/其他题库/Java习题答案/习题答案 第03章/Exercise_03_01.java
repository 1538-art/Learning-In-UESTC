//��д���������������������Լ������С������

import java.util.Scanner;

public class Exercise_03_01 {
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("�������һ������");
        int n = sc.nextInt();
        System.out.println("������ڶ�������");
        int m = sc.nextInt();
        max_min(n,m);
    }
    //�����Լ������С������
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
       System.out.println("���Լ��Ϊ"+yshu);
       System.out.println("��С������Ϊ"+bshu);

   }
}