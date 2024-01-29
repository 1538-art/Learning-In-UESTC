#pragma once

void loginUser(User users[MAX_USERS]);

void registerUser(User users[MAX_USERS]);

//打卡考勤
void clock_in(User* use);

//查询打卡记录
void clock_record();