/* Classify a triangle according to the integer lengths of its sides. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

enum { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday, Invalid };

bool digit(char c) {
    return '0' <= c && c <= '9';
}

bool valid(const char date[]) {
    int n = strlen(date);
    int m = 0;
    while(m < n) {
        if(date[0] == '0') break;
        if(! digit(date[m])) break;
        else m++;
    }
    return m == n;
}

int convertDay(const char date[]) {
    long m;
    if(valid(date)) m = atol(date);
    else m = -1;
    if(m > 31 || m < 1) m = -1;
    return m;
}

int convertMonth(const char date[]) {
    long m;
    if(valid(date)) m = atol(date);
    else m = -1;
    if(m > 12 || m < 1) m = -1;
    return m;
}

int monthLength(int month) {
    int n, newMonth = 0;
    char monthDay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    for(n = 0; n < month; n++) {
        newMonth = newMonth + monthDay[n];
    }
    newMonth = newMonth - monthDay[month - 1];
    return newMonth;
}

int calculate(int day, int month) {
    int newMonth = monthLength(month);
    int all = day + newMonth;
    if(all % 7 == 1) return Monday;
    else if(all % 7 == 2) return Tuesday;
    else if(all % 7 == 3) return Wednesday;
    else if(all % 7 == 4) return Thursday;
    else if(all % 7 == 5) return Friday;
    else if(all % 7 == 6) return Saturday;
    else return Sunday;
}

int check(int day, int month) {
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        if(day <= 31 && day > 0) return calculate(day, month);
        else return Invalid;
    }
    else if(month == 4 || month == 6 || month == 9 || month == 11) {
        if(day <= 30 && day > 0) return calculate(day, month);
        else return Invalid;
    }
    else if(month == 2) {
        if(day <= 28 && day > 0) return calculate(day, month);
        else return Invalid;
    }
    if(month <= 0 || day <= 0) return Invalid;
    else return calculate(day, month);
}

void assert(int line, bool b) {
    if (b) return;
    printf("The test on line %d fails.\n", line);
    exit(1);
}

void print(int day) {
    if(day == Monday) printf("Monday\n");
    else if(day == Tuesday) printf("Tuesday\n");
    else if(day == Wednesday) printf("Wednesday\n");
    else if(day == Thursday) printf("Thursday\n");
    else if(day == Friday) printf("Friday\n");
    else if(day == Saturday) printf("Saturday\n");
    else if(day == Sunday) printf("Sunday\n");
    else if(day == Invalid) printf("Invalid\n");
}

void checkConstants() {
    assert(__LINE__, Monday==0 && Tuesday==1 && Wednesday==2 && Thursday==3);
    assert(__LINE__, Friday==4 && Saturday==5 && Sunday==6 && Invalid==7);
}

void testConvertDay() {
    assert(__LINE__, convertDay("1") == 1);
    assert(__LINE__, convertDay("2") == 2);
    assert(__LINE__, convertDay("30") == 30);
    assert(__LINE__, convertDay("31") == 31);
    assert(__LINE__, convertDay("32") == -1);
    assert(__LINE__, convertDay("33") == -1);
    assert(__LINE__, convertDay("0") == -1);
    assert(__LINE__, convertDay("x") == -1);
    assert(__LINE__, convertDay("7z1") == -1);
    assert(__LINE__, convertDay("24.06") == -1);
    assert(__LINE__, convertDay("08") == -1);
}

void testConvertMonth() {
    assert(__LINE__, convertMonth("1") == 1);
    assert(__LINE__, convertMonth("2") == 2);
    assert(__LINE__, convertMonth("11") == 11);
    assert(__LINE__, convertMonth("12") == 12);
    assert(__LINE__, convertMonth("13") == -1);
    assert(__LINE__, convertMonth("14") == -1);
    assert(__LINE__, convertMonth("0") == -1);
    assert(__LINE__, convertMonth("x") == -1);
    assert(__LINE__, convertMonth("7z1") == -1);
    assert(__LINE__, convertMonth("24.06") == -1);
    assert(__LINE__, convertMonth("08") == -1);
}

void testMonday() {
    assert(__LINE__, check(15, 1) == Monday);
    assert(__LINE__, check(19, 2) == Monday);
    assert(__LINE__, check(2, 4) == Monday);
}

void testTuesday() {
    assert(__LINE__, check(20, 3) == Tuesday);
    assert(__LINE__, check(6, 2) == Tuesday);
    assert(__LINE__, check(26, 6) == Tuesday);
}

void testWednesday() {
    assert(__LINE__, check(30, 5) == Wednesday);
    assert(__LINE__, check(21, 2) == Wednesday);
    assert(__LINE__, check(5, 9) == Wednesday);
}

void testThursday() {
    assert(__LINE__, check(12, 7) == Thursday);
    assert(__LINE__, check(15, 2) == Thursday);
    assert(__LINE__, check(1, 11) == Thursday);
}

void testFriday() {
    assert(__LINE__, check(31, 8) == Friday);
    assert(__LINE__, check(2, 2) == Friday);
    assert(__LINE__, check(8, 6) == Friday);
}

void testSaturday() {
    assert(__LINE__, check(27, 10) == Saturday);
    assert(__LINE__, check(17, 2) == Saturday);
    assert(__LINE__, check(1, 9) == Saturday);
}

void testSunday() {
    assert(__LINE__, check(2, 12) == Sunday);
    assert(__LINE__, check(11, 2) == Sunday);
    assert(__LINE__, check(22, 4) == Sunday);
}
void test() {
    checkConstants();
    testConvertDay();
    testConvertMonth();
    testMonday();
    testTuesday();
    testWednesday();
    testThursday();
    testFriday();
    testSaturday();
    testSunday();
    printf("All tests passed\n");
}

int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if(n == 1) test();
    else if (n == 3) {
        int day = convertDay(args[1]), month = convertMonth(args[2]);
        int value = check(day, month);
        print(value);
    }
    else {
        fprintf(stderr, "Use like this way : \n");
        fprintf(stderr, "./daycal [Day] [Month]\n");
        fprintf(stderr, "Do not write the numbers starting with '0'\n");
        return 1;
    }
    return 0;
}
