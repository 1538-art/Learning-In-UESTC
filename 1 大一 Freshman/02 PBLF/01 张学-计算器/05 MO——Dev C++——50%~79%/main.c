/*
������򲻷��ϴ��ͳ���Ҫ��5����������ϣ��ɶ��Բû�����ó�����������
���ܵĽ�����壺
    ֻ�����˺�������֮ǰ��֪ʶ����˱Ƚϸ��ӵ�����
    ˼·����
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LENGTH 500

double AddAndSubtract1(char **p);
/*���ڴ���ӷ��ͼ����ĺ��������ڲ������ƶ�ָ��
 *�����������������p�ĵ�ַ������������p
 *����ֵ�����ս��
 */
double MultiplyAndDivide2(char **p);
/*���ڴ���˷��ͳ����ĺ��������ڲ������ƶ�ָ��
 *�������������������p
 *����ֵ���м���
 */
double Rower3(char **p);
/*���ڴ���˷��ĺ��������ڲ������ƶ�ָ��
 *�������������������p
 *����ֵ���м���
 */
double Bracket4(char **p);
/*���ڴ���Բ���ŵĺ��������ڲ������ƶ�ָ��
 *�������������������p
 *����ֵ�������ڽ��
 */
double Transform5(char **p);
/*���ڴ������ֵĺ���,����ǰ���������ַ�ת��Ϊ�����ͣ����ڲ������ƶ�ָ��
 *�������������������p�ĵ�ַ
 *����ֵ���м���
 */

double Transform5(char **p) {
    // ʹ��strtod�������ַ���ת��Ϊ�������������ַ���ָ����ǰ�ƶ�
    double result = strtod(*p, p);
    return result;
}

double Bracket4(char **p) {
    // �����ǰ�ַ���'('�����������ڵı��ʽ
    if (**p == '(') {
        (*p)++;  //����'('�ַ�
        double result = AddAndSubtract1(p);
        (*p)++;  //����')'�ַ�
        return result;
    } else {
        // ���򣬴�������
        return Transform5(p);
    }
}

double Rower3(char **p) {
    double result = Bracket4(p);
    // �����ǰ�ַ���'^'������˷�����
    if (**p == '^') {
        (*p)++;
        result = pow(result, Bracket4(p));
    }
    return result;
}

double MultiplyAndDivide2(char **p) {    //�����s����������&s
    double result = Rower3(p);
    // �����ǰ�ַ���'*'��'/'������˷����������
    while (**p == '*' || **p == '/') {
        if (*(*p)++ == '*') {
            result *= Bracket4(p);
        } else {
            result /= Bracket4(p);
        }
    }
    return result;
}

double AddAndSubtract1(char **p) {
    double result = MultiplyAndDivide2(p);
    // �����ǰ�ַ���'+'��'-'������ӷ����������
    while (**p == '+' || **p == '-') {
        if (*(*p)++ == '+') {
            result += MultiplyAndDivide2(p);
        } else {
            result -= MultiplyAndDivide2(p);
        }
    }
    return result;
}

int main() {
    char buffer[LENGTH];
    // �ӱ�׼�����ȡÿ�б��ʽ����������
    printf("����һ�б��ʽ������Enter����������\n");
    while (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') {
        char *p = buffer;
        printf("%.10g\n", AddAndSubtract1(&p));
        printf("������һ�б��ʽ������Enter����������\n");
    }
    printf("�ټ�");
    return 0;
}
/*by MO
**2023/11/20
*/
