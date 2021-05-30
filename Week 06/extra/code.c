/* Play noughts and crosses (tic-tac-toe) between two human players. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <time.h>

struct encrypt { char origin[101], after[102]; };
typedef struct encrypt encrypt;

struct decrypt { char origin[102], after[101]; };
typedef struct decrypt decrypt;

struct code {
    int order;
    char conv[5][101];
};
typedef struct code code;

void enCheck(int random, int i, encrypt *e) {
    if(e->origin[i] >= 'a' && e->origin[i] <= 'z') {
        if((e->origin[i] + random) > 'z') e->after[i+1] = 'a' + (random - 'z' + e->origin[i]);
        else e->after[i+1] = e->origin[i] + random;
    }
    else e->after[i+1] = e->origin[i];
}

void deCheck(int i, decrypt *d, code *c) {
    int a = d->origin[0] - '0';
    if(d->origin[i] >= 'a' && d->origin[i] <= 'z') {
        if((d->origin[i] - c->conv[a][i]) < 'a') d->after[i-1] = 'z' - (c->conv[a][i] - d->origin[i] + 'a');
        else d->after[i-1] = d->origin[i] - c->conv[a][i];
    }
    else d->after[i-1] = d->origin[i];
}

void enConv(encrypt *e, code *c) {
    int random;
    int len = strlen(e->origin);
    e->after[0] = c->order;
    c->conv[c->order][0] = c->order;
    for(int i = 0; i < len; i++) {
        srand(time(NULL));
        random = (rand() % 25) + 1;
        c->conv[c->order][i+1] = random;
        enCheck(random, i, e);  
    }
}

void deConv(decrypt *d, code *c) {
    int len = strlen(d->origin);
    for(int i = 1; i < len; i++) {
        deCheck(i, d, c);
    }
}

void enPrint(encrypt *e, code *c) {
    printf("Conversion is done.\n");
    printf("The code is: ");
    int len = strlen(e->origin) + 1;
    printf("%d", e->after[0]);
    for(int i = 1; i < len; i++) printf("%c", e->after[i]);
    printf("\n");
}

void dePrint(decrypt *d, code *c) {
    printf("Conversion is done.\n");
    printf("The sentence is: ");
    int len = strlen(d->origin) - 1;
    for(int i = 0; i < len; i++) printf("%c", d->after[i]);
    printf("\n");
}

void dec(code *c) {
    decrypt *d = malloc(sizeof(decrypt));
    printf("Please write code for decrypt(maximum 101 characters): ");
    fgets(d->origin, sizeof(d->origin), stdin);
    deConv(d, c);
    dePrint(d, c);
    free(d);
}

void enc(code *c) {
    encrypt *e = malloc(sizeof(encrypt));
    printf("Please write a sentence for encrypt(maximum 100 characters): ");
    fgets(e->origin, sizeof(e->origin), stdin);
    enConv(e, c);
    enPrint(e, c);
    dec(c);
    free(e);
}

int main(int n, char *args[n]) {
    if (n == 1) {
        code *c = malloc(sizeof(code));
        c->order = 0;
        enc(c);
        free(c);
    }
    else {
        fprintf(stderr, "Use: ./code   for encrypt\n");
        exit(1);
    }
    return 0;
}
