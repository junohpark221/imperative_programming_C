/* Calculate a grade from a mark. */
#include <stdio.h>
#include <stdlib.h>

int distinct(int max, int other1, int other2) {
    if (max * max == (other1 * other1) + (other2 * other2)) return 1;
    else return 0;
}

int compare(const char arr1[], const char arr2[], const char arr3[]) {
    int num1 = atoi(arr1);
    int num2 = atoi(arr2);
    int num3 = atoi(arr3);
    int max;
    int val;
    if (num1 > 0 && num2 > 0 && num3 > 0) {
        if (num1 > num2) {
            max = num1;
            if (num1 > num3) {
                max = num1;
                val = distinct(max, num2, num3);
            }
            else {
                max = num3;
                val = distinct(max, num1, num2);
            }
        }
        else {
            max = num2;
            if (num2 > num3) {
                max = num2;
                val = distinct(max, num1, num3);
            }
            else {
                max = num3;
                val = distinct(max, num1, num2);
            }
        }
        return val;
    }
    else {
        return -1;
    }
}

void print(num) {
    if (num == 1) printf("The triangle with these three sides is right triangle.\n");
    else if (num == 0) printf("The triangle with these three sides is not right triangle.\n");
    else printf("The value of the side is wrong.\n");
}

int main(int n, char *arrs[n]) {
    setbuf(stdout, NULL);
    if (n == 4) {
        int value = compare(arrs[1], arrs[2], arrs[3]);
        print(value);
    }
    else {
        fprintf(stderr, "Please use the function through these ways.\n");
        fprintf(stderr, "./pythagoras  or ./pythagoras 'l' 'm' 'n'\n");
        fprintf(stderr, "(l m n are natural numbers.)\n");
        return 1;
    }
    return 0;
}
