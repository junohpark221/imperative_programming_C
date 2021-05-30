#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

struct lineS { int x0; int y0; int x1; int y1; int pen; unsigned int pr; int pau; };
typedef struct lineS lineS;

int decide(int n){
    if(n >= 0 && n <= 31) return n;
    else if(n >= 32 && n <= 63) return n - 64;
    else if(n >= 64 && n <= 95) return (n - 64) + 1000;
    else if(n >= 96 && n <= 127) return (n - 128) + 1000;
    else if(n >= 128 && n <= 159) return (n - 128) + 2000;
    else if(n >= 160 && n <= 191) return (n - 192) + 2000;
    else if(n >= 192 && n <= 223) return n + 2808;
    else return 10000;
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

void st1Draw(display *d, lineS *l, int n){
    if(l->pen % 2 == 0){
        if(n >= -32 && n <= 31) l->x0 += n;
        else if(n >= 968 && n <= 1031) l->y0 += (n - 1000);
        else l->pen += 1;
        l->x1 = l->x0;
        l->y1 = l->y0;
    }
    else{
        if(n >= -32 && n <= 31) l->x1 += n;
        else if(n >= 968 && n <= 1031){
            l->y1 += (n - 1000);
            line(d, l->x0, l->y0, l->x1, l->y1);
            l->x0 = l->x1;
            l->y0 = l->y1;
        }
        else l->pen += 1;
    }
}

void st1Main(display *d, unsigned char *b, int len){
    char tmp[3];
    lineS *l = malloc(sizeof(lineS));
    *l = (lineS) { 0, 0, 0, 0, 0, 0, 0 };
    for(int a = 0; a < len; a++){
        sprintf(tmp, "%x", b[a]);
        if(strlen(tmp) == 1){
            tmp[1] = tmp[0];
            tmp[0] = '0';
        }
        int n = toDeci(tmp);
        st1Draw(d, l, n);
    }
    end(d);
    free(l);
}

void st2Rp(display *d, lineS *l, int n, unsigned char *b, int a){
    if(l->pr == 0){
        if(n >= 1968 && n <= 2031){
            unsigned char tmp1 = b[a] << 2;
            tmp1 = tmp1 >> 2;
            l->pr = tmp1;
        }
        else if(n == 3000) l->pen += 1;
        else if(n == 3001) pause(d, l->pau);
        else if(n == 3002) clear(d);
        else if(n == 3003) key(d);
        else if(n == 3004) colour(d, (l->pr & 0xFFFF));
    }
    else{
        if(n >= 1968 && n <= 2031){
            unsigned char tmp1 = b[a] << 2;
            tmp1 = tmp1 >> 2;
            l->pr = (l->pr << 6) | tmp1;
        }
        else if(n == 3000) l->pen += 1;
        else if(n == 3001){
            l->pau = l->pr;
            pause(d, l->pau);
            l->pr = 0;
        }
        else if(n == 3002) clear(d);
        else if(n == 3003) key(d);
        else if(n == 3004) {colour(d, l->pr); l->pr = '\0';}
    }
}

void st2PenOn(display *d, lineS *l, int n, unsigned char *b, int a){
    if(l->pr == 0){
        if(n >= -32 && n <= 31) l->x1 += n;
        else if(n >= 968 && n <= 1031){
            l->y1 += (n - 1000);
            line(d, l->x0, l->y0, l->x1, l->y1);
            l->x0 = l->x1;
            l->y0 = l->y1;
        }
        else st2Rp(d, l, n, b, a);
    }
    else{
        unsigned char tmp1;
        if(n >= -32 && n <= -1){
            tmp1 = (l->pr << 6) | b[a];
            l->x1 += ((int)tmp1 - 256);
            l->pr = 0;
        }
        else if(n >= 0 && n <= 31){
            tmp1 = (l->pr << 6) | b[a];
            l->x1 += (int)tmp1;
            l->pr = 0;
        }
        else if(n >= 968 && n <= 999){
            unsigned char tmp2 = b[a] << 2;
            tmp2 = tmp2 >> 2;
            tmp1 = (l->pr << 6) | tmp2;
            l->y1 += ((int)tmp1 - 256);
            line(d, l->x0, l->y0, l->x1, l->y1);
            l->x0 = l->x1;
            l->y0 = l->y1;
            l->pr = 0;
        }
        else if(n >= 1000 && n <= 1031){
            unsigned char tmp2 = b[a] << 2;
            tmp2 = tmp2 >> 2;
            tmp1 = (l->pr << 6) | tmp2;
            l->y1 += (int)tmp1;
            line(d, l->x0, l->y0, l->x1, l->y1);
            l->x0 = l->x1;
            l->y0 = l->y1;
            l->pr = 0;
        }
        else st2Rp(d, l, n, b, a);
    }
}

void st2Draw(display *d, lineS *l, int n, unsigned char *b, int a){
    if(l->pen % 2 == 0){
        if(n >= -32 && n <= 31) l->x0 += n;
        else if(n >= 968 && n <= 1031) l->y0 += (n - 1000);
        else st2Rp(d, l, n, b, a);
        l->x1 = l->x0;
        l->y1 = l->y0;
    }
    else{
        st2PenOn(d, l, n, b, a);
    }
}

void st2Main(display *d, unsigned char *b, int len){
    char tmp[3];
    lineS *l = malloc(sizeof(lineS));
    *l = (lineS) { 0, 0, 0, 0, 0, 0, 0 };
    for(int a = 0; a < len; a++){
        sprintf(tmp, "%x", b[a]);
        if(strlen(tmp) == 1){
            tmp[1] = tmp[0];
            tmp[0] = '0';
        }
        int n = toDeci(tmp);
        st2Draw(d, l, n, b, a);
    }
    end(d);
    free(l);
}

void findDraw(char *file, display *d, unsigned char *b, int len){
    if(strcmp(file, "lines") == 0 || strcmp(file, "lines.sketch") == 0) st1Main(d, b, len);
    else if(strcmp(file, "square") == 0 || strcmp(file, "square.sketch") == 0) st1Main(d, b, len);
    else if(strcmp(file, "oxo") == 0 || strcmp(file, "oxo.sketch") == 0) st1Main(d, b, len);
    else if(strcmp(file, "diag") == 0 || strcmp(file, "diag.sketch") == 0) st1Main(d, b, len);
    else if(strcmp(file, "cross") == 0 || strcmp(file, "cross.sketch") == 0) st1Main(d, b, len);
    else if(strcmp(file, "field") == 0 || strcmp(file, "field.sketch") == 0) st2Main(d, b, len);
    else if(strcmp(file, "box") == 0 || strcmp(file, "box.sketch") == 0) st2Main(d, b, len);
    else if(strcmp(file, "clear") == 0 || strcmp(file, "clear.sketch") == 0) st2Main(d, b, len);
    else if(strcmp(file, "key") == 0 || strcmp(file, "key.sketch") == 0) st2Main(d, b, len);
    else if(strcmp(file, "lawn") == 0 || strcmp(file, "lawn.sketch") == 0) st2Main(d, b, len);
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
