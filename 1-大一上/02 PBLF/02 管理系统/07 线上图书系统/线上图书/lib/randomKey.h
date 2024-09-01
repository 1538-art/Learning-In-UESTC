#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

#ifndef KEY_H
#define KEY_H

char *generateKey()
{
    // 声明一个GUID结构体
    GUID guid;

    // 生成GUID
    CoCreateGuid(&guid);

    // 将GUID转换为字符串表示
    wchar_t guidStr[40]; // 38个字符表示GUID，再加上一个字符串结束符'\0'
    StringFromGUID2(&guid, guidStr, sizeof(guidStr) / sizeof(guidStr[0]));

    // 将宽字符字符串转换为多字节字符串
    char mbGuidStr[40];
    WideCharToMultiByte(CP_UTF8, 0, guidStr, -1, mbGuidStr, sizeof(mbGuidStr), NULL, NULL);

    // 打印生成的GUID多字节字符串
    FILE *fp = fopen("info/key.txt", "w");
    fprintf(fp, "%s", mbGuidStr);
    fclose(fp);

    char *key = (char *)malloc(sizeof(mbGuidStr));
    strcpy(key, mbGuidStr);
    return key;
}

#endif