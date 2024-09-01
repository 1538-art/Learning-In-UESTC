#pragma once

void schedule_control(char* username, int* n, char name[NUM_GUARDS][5]);

void saveScheduleToFile(int* n, char name[7][5]);

void loadSchedule(int(*guards)[NUM_DAYS], char** guard_names);

void changeSchedule(char name[NUM_GUARDS][5], int* n);

void push();

void printSchedule(int* n);