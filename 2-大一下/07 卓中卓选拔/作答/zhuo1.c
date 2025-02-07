/*12位整数编码
用12位的存储空间表示整数，一般只能有212=4096个数字。现采用如下编码方式:
用8位表示一个常数immed 8，用4位表示该常数要进行移位操作的移位数 rotate imm
最终这12位表示的数值是: immed 8 循环右移 rotate imm*2 位后所得到的值
示例: 0x3fc可以由8位常数0xff循环右移30位得到，是常数表达式
示例: 0x1fe，虽然可以由0xff循环右移31位得到，但是移动的位数不是偶数，因此不符合该编码方式
如果只考虑正整数，请编写程序
0
该程序从标准输入读取一个非负32位十进制整数 K
如果 K 可以采用此编码方式，则输出 -1，程序结束
0
如果不行，该程序将试着找出两个离 K 最近的两个数 m 和 n，要求:
0
m 比K 小，且 m 及 K-m 都可以采用上述编码;
n比K大，且n 及 K-n 都可以采用上述编码
如果 m 和n 都找到，则输出 K，m 和 n，格式如下:
K,m,n
即输出的三个数用英文逗号隔开，
否则输出 -2。*/


#include <stdio.h>
#include <stdint.h>

// 判断 num 是否可以由 immed_8 循环右移 rotate_imm*2 位后得到
int is_encoded_number(uint32_t num) {
    for (int rotate_imm = 0; rotate_imm < 16; rotate_imm++) {
        uint32_t shifted_num = (num << (rotate_imm * 2)) | (num >> (32 - rotate_imm * 2));
        shifted_num &= 0xFFFFFFFF; // 保证数值在 32 位内
        if (shifted_num <= 0xFF) {
            return 1; // 可以表示
        }
    }
    return 0; // 不可以表示
}

// 寻找离 k 最近的符合要求的 m 和 n
int find_closest_encoded_numbers(uint32_t k, uint32_t* lower_m, uint32_t* upper_n) {
    // 找 m < k
    for (int32_t m = k - 1; m >= 0; m--) {
        if (is_encoded_number(m) && is_encoded_number(k - m)) {
            *lower_m = m;
            break;
        }
    }

    // 找 n > k
    for (uint32_t n = k + 1; n < 4294967295; n++) {
        if (is_encoded_number(n) && is_encoded_number(n - k)) {
            *upper_n = n;
            break;
        }
    }

    if (*lower_m != -1 && *upper_n != -1) {
        return 1; // 找到
    } else {
        return 0; // 没找到
    }
}

int main() {
    uint32_t k;
    if (scanf("%u", &k) != 1) {
        return 1; // 输入错误
    }

    if (is_encoded_number(k)) {
        printf("-1\n");
    } else {
        uint32_t lower_m = -1, upper_n = -1;
        if (find_closest_encoded_numbers(k, &lower_m, &upper_n)) {
            printf("%u,%u,%u\n", k, lower_m, upper_n);
        } else {
            printf("-2\n");
        }
    }

    return 0;
}

