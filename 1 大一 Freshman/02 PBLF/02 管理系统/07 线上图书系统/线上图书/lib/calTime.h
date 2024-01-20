#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "network.h"

#ifndef CALTIME_H
#define CALTIME_H

// 将日期字符串解析为tm结构体
struct tm parseDate(const char *dateString)
{
    struct tm tm_date = {0};
    sscanf(dateString, "%d-%d-%d", &tm_date.tm_year, &tm_date.tm_mon, &tm_date.tm_mday);
    tm_date.tm_year -= 1900;
    tm_date.tm_mon -= 1;
    return tm_date;
}

// 获取当前时间
void getCurrentDate(char *buffer)
{
    time_t current_time;
    struct tm *time_info;

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(buffer, 11, "%Y-%m-%d", time_info);
}

// 计算日期差
int dateDifference(const char *startDateString, const char *endDateString)
{
    struct tm start_date = parseDate(startDateString);
    struct tm end_date = parseDate(endDateString);

    time_t start_time = mktime(&start_date);
    time_t end_time = mktime(&end_date);

    return (int)difftime(end_time, start_time) / (60 * 60 * 24);
}

// 计算未来一定天数后的日期
void calculateFutureDate(const char *startDateString, int days, char *futureDateString)
{
    struct tm start_date = parseDate(startDateString);

    time_t start_time = mktime(&start_date);
    time_t future_time = start_time + days * 24 * 60 * 60;

    struct tm future_date = *localtime(&future_time);

    sprintf(futureDateString, "%d-%02d-%02d", future_date.tm_year + 1900, future_date.tm_mon + 1, future_date.tm_mday);
}

#endif