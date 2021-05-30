#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

struct lineS { int x0; int y0; int x1; int y1; int pen; };
typedef struct lineS lineS;

int decide(int n){
    if(n >= 0 && n <= 31) return n;
    else if(n >= 32 && n <= 63) return n - 64;
    else if(n >= 64 && n <= 95) return (n - 64) + 1000;
    else if(n >= 96 && n <= 127) return (n - 128) + 1000;
    else if(n >= 128 && n <= 159) return (n - 128) + 2000;
    else if(n >= 160 && n <= 191) return (n - 192) + 2000;
    else if(n >= 192 && n <= 223) return 3000;
    else return 3000;
}

int toDeci(char *tmp){
    int n = 0;
    for(int a = 0; a < 2; a++){
        int b = 0;
        if(tmp[a] >= 97 && tmp[a] <= 102) b = tmp[a] - (97 - 10);
        if(tmp[a] >= 48 && tmp[a] <= 57) b = tmp[a] - 48;
        n *= 16;
        n += b;
    }
    return decide(n);
}

void drawLine(display *d, lineS *l, int n){
    if(n == -1) end(d);
    else if(l->pen % 2 == 0){
        if(n >= -32 && n <= 31) l->x0 += n;
        else if(n >= 968 && n <= 1031) l->y0 += (n - 1000);
        else l->pen += 1;
        l->x1 = l->x0;
        l->y1 = l->y0;
    }
    else{
        if(n >= -32 && n <= 31){
            l->x1 += n;
        }
        else if(n >= 968 && n <= 1031){
            l->y1 += (n - 1000);
            line(d, l->x0, l->y0, l->x1, l->y1);
            l->x0 = l->x1;
            l->y0 = l->y1;
        }
        else l->pen += 1;
    }
}

void lineMain(display *d, unsigned char *b, int len){
    char tmp[3];
    lineS *l = malloc(sizeof(lineS));
    *l = (lineS) { 0, 0, 0 };
    for(int a = 0; a < len; a++){
        sprintf(tmp, "%x", b[a]);
        if(strlen(tmp) == 1){
            tmp[1] = tmp[0];
            tmp[0] = '0';
        }
        int n = toDeci(tmp);
        drawLine(d, l, n);
    }
//-----------------------------------------------------------------------------------------
    unsigned char test = (b[0] << 6) | b[1];
    char test2[20];
    unsigned int p = (test & 0xFFFF);
    sprintf(test2, "%x", test);
    printf("%s\n", test2);
    int test3[10];
    test3[0] = 1000;
    printf("%d\n", test3[0]);
//--------------------------------------------------------------------------------------------
    drawLine(d, l, -1);
    free(l);
}

int readBi(char *file, char *mode, unsigned char *b, display *d){
    FILE *p = fopen(file, mode);
    if(p == NULL){
        printf("Error occurs! Can`t open %s.\n", file);
        exit(1);
    }
    b[0] = fgetc(p);
    int n = 1;
    while(! feof(p)){
        b[n] = fgetc(p);
        n++;
    }
    fclose(p);
    return n;
}

void findDraw(char *file, display *d, unsigned char *b, int len){
    if(strcmp(file, "lines") == 0 || strcmp(file, "lines.sketch") == 0) lineMain(d, b, len);
    else if(strcmp(file, "square") == 0 || strcmp(file, "square.sketch") == 0) lineMain(d, b, len);
    else if(strcmp(file, "oxo") == 0 || strcmp(file, "oxo.sketch") == 0) lineMain(d, b, len);
    else if(strcmp(file, "diag") == 0 || strcmp(file, "diag.sketch") == 0) lineMain(d, b, len);
    else if(strcmp(file, "cross") == 0 || strcmp(file, "cross.sketch") == 0) lineMain(d, b, len);
}

int main(int n, char *args[n]){
    if(n != 2){
        fprintf(stdout, "Use    ./sketch filename.sketch\n");
        exit(1);
    }
    display *d = newDisplay(args[1], 200, 200);
    unsigned char b[200];
    int len = readBi(args[1], "rb", b, d) - 1;
    findDraw(args[1], d, b, len);
    free(d);
}
