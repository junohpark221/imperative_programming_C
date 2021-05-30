/* Custom versions of standard string functions. */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

bool digit(char c) {
    return '0' <= c && c <= '9';
}

bool valid(const char scores[]) {
    int n = strlen(scores);
    int m = 0;
    while(m < n) {
        if(scores[0] == '0') break;
        if(! digit(scores[m])) break;
        else m++;
    }
    return m == n;
}

void print(const char scores[]) {
    if(scores[0] == "false") printf("Invalid");
    int len = strlen(scores);
    for(int i = 0 ; i < len ; i++) {
        if(i != 0) printf(" ");
        printf("%c", scores[i]);
    }
}

char org(const char scores[]) {
    int len = strlen(scores), tmp, j;
    char new_scores[len];
    strcpy(new_scores, scores);
    for(int i = 0; i < len - 1; i++) {
        for(j = i+1; j < len; j++) {
            if(new_scores[i] < new_scores[j]) {
                tmp = new_scores[i];
                new_scores[i] = new_scores[j];
                new_scores[j] = tmp;
            }
        }
    }
    print(new_scores);
}

void arr(int n, const char scores[]) {
    int len = n - 1, m = 0;
    char new_scores[len];
    char inv[1] = ("false");
    for(int i = 0 ; i < len ; n++) {
        new_scores[i] = scores[i+1];
    }
    for(int j = 0 ; j < len ; n++) {
        if(valid(new_scores)) m++;
    }
    if(m == len) org(new_scores);
    else print(inv);
}

int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if(n == 1) fprintf(stderr, "Use e.g.: ./rank 3 4 5\n");
    else {
        arr(n, args);
    }
    return 0;
}
