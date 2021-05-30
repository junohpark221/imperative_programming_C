#include "draw.h"
#include "record.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

struct storage { int x0; int y0; int x1; int y1; int len; char col[6]; int op; char test[50]; int save[500]; };

void midDraw(storage *s, int prevLen){
    display *d = newDisplay(s->test, 500, 500);
    int i = 0;
    while(i < prevLen){
        if(s->save[i] == 2001) i = recordMove(s, i);
        else if(s->save[i] == 2002) i = recordLine(s, d, i);
        else if(s->save[i] == 2003) i = recordClear(d, i);
        else if(s->save[i] == 2004) i = recordColour(s, d, i);
        else if(s->save[i] == 2005) i = recordPause(s, d, i);
    }
    int j = prevLen;
    pause(d, 2000);
    line(d, s->save[j + 1], s->save[j + 2], s->save[j + 3], s->save[j + 4]);
    end(d);
    free(d);
}

void getValue(storage *s){
    int x, y;
    printf("\n\nCurrent possition:   X: %d,  Y: %d\n", s->x0, s->y0);
    while(1){
        printf("Put the location you want to go:     X: ");
        scanf("%d", &x);
        fflush(stdin);
        if(x >= -499 && x <= 500){
            while(1){
                s->x1 = x;
                printf("Put the location you want to go:     Y: ");
                scanf("%d", &y);
                fflush(stdin);
                if(y >= -499 && y <= 500){
                    s->y1 = y;
                    break;
                }
                printf("\nInvalid value\n\n");
            }
            break;
        }
        printf("\nInvalid value\n\n");
    }
}

void moveMain(storage *s){
    getValue(s);
    s->x0 = s->x1;
    s->y0 = s->y1;
    s->save[s->len] = 2001;
    s->save[s->len + 1] = s->x1;
    s->save[s->len + 2] = s->y1;
    s->len += 3;
    printf("\nSuccess to move.\n\n\n");
}

void lineMain(storage *s){
    getValue(s);
    int prevLen = s->len;
    s->save[s->len] = 2002;
    s->save[s->len + 1] = s->x0;
    s->save[s->len + 2] = s->y0;
    s->save[s->len + 3] = s->x1;
    s->save[s->len + 4] = s->y1;
    s->len += 5;
    s->x0 = s->x1;
    s->y0 = s->y1;
    midDraw(s, prevLen);
    printf("\n\n\n");
}

void clearMain(storage *s){
    char c;
    printf("\n\n");
    while(1){
        printf("Do you want to add clearing??\n");
        printf("[y/n]: ");
        scanf(" %c", &c);
        fflush(stdin);
        printf(" %c\n", c);
        if(c == 'y'){
            s->save[s->len] = 2003;
            s->len += 1;
            printf("\nSuccess to add clearing\n\n\n");
            break;
        }
        else if(c == 'n') break;
        printf("\nInvalid value\n\n");
    }
}

void restartMain(storage *s){
    char c;
    printf("\n\n");
    while(1){
        printf("Do you want to clear all??\n");
        printf("[y / n]: ");
        scanf(" %c", &c);
        fflush(stdin);
        if(c == 'y'){
            for(int i = 0; i < s->len; i++) s->save[i] = '\0';
            s->x0 = 0;
            s->x1 = 0;
            s->y0 = 0;
            s->y1 = 0;
            s->len = 0;
            for(int j = 0; j < 6; j++) s->col[j] = '\0';
            strcpy(s->col, "black");
            printf("\nSuccess to clear all\n\n\n");
            break;
        }
        else if(c == 'n') break;
        printf("\nInvalid value\n\n");
    }
}

void selRGB(storage *s){
    char c;
    printf("\n\n");
    while(1){
        printf("Current Colour: %s\n", s->col);
        printf("Choose the colour that you want to change\n");
        printf("1. black\n2. white\n3. red\n4. green\n5. blue\n> ");
        scanf(" %c", &c);
        fflush(stdin);
        if((c - '1') >= 0 && (c - '1') <= 4){
            s->save[s->len] = 2004;
            if(c == '1'){
                for(int i = 0; i < 6; i++) s->col[i] = '\0';
                strcpy(s->col, "black");
                s->save[s->len + 1] = 1;
            }
            else if(c == '2'){
                for(int i = 0; i < 6; i++) s->col[i] = '\0';
                strcpy(s->col, "white");
                s->save[s->len + 1] = 2;
            }
            else if(c == '3'){
                for(int i = 0; i < 6; i++) s->col[i] = '\0';
                strcpy(s->col, "red");
                s->save[s->len + 1] = 3;
            }
            else if(c == '4'){
                for(int i = 0; i < 6; i++) s->col[i] = '\0';
                strcpy(s->col, "green");
                s->save[s->len + 1] = 4;
            }
            else if(c == '5'){
                for(int i = 0; i < 6; i++) s->col[i] = '\0';
                strcpy(s->col, "blue");
                s->save[s->len + 1] = 5;
            }
            s->len += 2;
            printf("\nSuccess to change colour\n\n");
            break;
        }
        printf("\nInvalid Value\n\n");
    }
}

void selA(storage *s){
    int c;
    while(1){
        printf("Current Opacity: %s\n", s->col);
        printf("(0: fully transparent   ~   255: fully opague)\n");
        printf("Choose the opcaity that you want to change: ");
        scanf("%d", &c);
        fflush(stdin);
        if(c >= 0 && c <= 255){
            s->save[s->len] = c;
            s->len += 1;
            printf("\nSuccess to change opacity\n\n\n");
            break;
        }
        printf("\nInvalid Value\n\n");
    }
}

void colourMain(storage *s){
    selRGB(s);
    selA(s);
}

void pauseMain(storage *s){
    int n;
    char c;
    printf("\n\n");
    while(1){
        printf("Do you want to add pause??\n");
        printf("[y/n]: ");
        scanf(" %c", &c);
        if(c == 'y'){
            printf("\n");
            while(1){
                printf("Put the time that you want to pause(milliseconds): ");
                scanf("%d", &n);
                if(n > 0){
                    s->save[s->len] = 2005;
                    s->save[s->len + 1] = n;
                    s->len += 2;
                    printf("Success to add pause\n\n\n");
                    break;
                }
                printf("\nInvalid Value!!\n");
                printf("Put the number which is bigger than 0\n\n");
            }
            break;
        }
        else if(c == 'n') break;
        printf("\nInvalid Value\n\n");
    }
}

int recordMove(storage *s, int i){
    return (i + 3);
}

int recordLine(storage *s, display *d, int i){
    line(d, s->save[i + 1], s->save[i + 2], s->save[i + 3], s->save[i + 4]);
    return (i + 5);
}

int recordClear(display *d, int i){
    pause(d, 1000);
    clear(d);
    pause(d, 1000);
    return (i + 1);
}

int recordColour(storage *s, display *d, int i){
    int r, g, b, a;
    if(s->save[i + 1] == 1){
        r = 255;
        g = 255;
        b = 255;
    }
    else if(s->save[i + 1] == 2){
        r = 0;
        g = 0;
        b = 0;
    }
    else if(s->save[i + 1] == 3){
        r = 255;
        g = 0;
        b = 0;
    }
    else if(s->save[i + 1] == 4){
        r = 0;
        g = 255;
        b = 0;
    }
    else{
        r = 0;
        g = 0;
        b = 255;
    }
    a = s->save[i+2];
    colour(d, r, g, b, a);
    return (i + 3);
}

int recordPause(storage *s, display *d, int i){
    pause(d, s->save[i + 1]);
    return (i + 2);
}

void recordMain(storage *s){
    if(s->len == 0) printf("\nNothing is recorded\n\n");
    else{
        display *d = newDisplay(s->test, 500, 500);
        int i = 0;
        while(i < s->len){
            if(s->save[i] == 2001) i = recordMove(s, i);
            else if(s->save[i] == 2002) i = recordLine(s, d, i);
            else if(s->save[i] == 2003) i = recordClear(d, i);
            else if(s->save[i] == 2004) i = recordColour(s, d, i);
            else if(s->save[i] == 2005) i = recordPause(s, d, i);
        }
        end(d);
    }
}

void mainMenu(storage *s){
    while(1){
        char n;
        printf("---------------------------------------------------------------------------------\n");
        printf("This program records your drawing.\n");
        printf("It can save maximum 100 times drawing.\n");
        printf("The range that you can move at once is from -499 to 500.\n");
        printf("Select one of the options.\n");
        printf("1. Move\n2. Draw the line\n3. Add clearing\n4. Clear all\n");
        printf("5. Change Colour\n6. Add pause\n7. Show recorded file\n8. Quit\n> ");
        scanf(" %c", &n);
        fflush(stdin);
        if(n == '1') moveMain(s);
        else if(n == '2') lineMain(s);
        else if(n == '3') clearMain(s);
        else if(n == '4') restartMain(s);
        else if(n == '5') colourMain(s);
        else if(n == '6') pauseMain(s);
        else if(n == '7') recordMain(s);
        else if(n == '8') exit(1);
        else printf("Invalid Number\n");
    }
}

//-----------------------------------------------------------------------------------------------
//------------------------------------------Test-------------------------------------------------

void t1Test(){
    storage *s = malloc(sizeof(storage));
    *s = (storage) { 0, 0, 0, 0, 0, "black", 255, "linetest.t1" };
    s->save[0] = 2002;
    s->save[1] = 20;
    s->save[2] = 20;
    s->save[3] = 40;
    s->save[4] = 40;
    s->len = 5;
    recordMain(s);
    free(s);
}

void t2Test(){
    storage *s = malloc(sizeof(storage));
    *s = (storage) { 0, 0, 0, 0, 0, "black", 255, "linetest.t2" };
    s->save[0] = 2002;
    s->save[1] = 20;
    s->save[2] = 20;
    s->save[3] = 40;
    s->save[4] = 40;
    s->save[5] = 2002;
    s->save[6] = 0;
    s->save[7] = 40;
    s->save[8] = 50;
    s->save[9] = -100;
    s->save[10] = 2002;
    s->save[11] = 10;
    s->save[12] = 60;
    s->save[13] = -450;
    s->save[14] = 200;
    s->len = 15;
    recordMain(s);
    free(s);
}

void t3Test(){
    storage *s = malloc(sizeof(storage));
    *s = (storage) { 0, 0, 0, 0, 0, "black", 255, "cleartest.t3" };
    s->save[0] = 2003;
    s->len = 1;
    recordMain(s);
    free(s);
}


void t4Test(){
    storage *s = malloc(sizeof(storage));
    *s = (storage) { 0, 0, 0, 0, 0, "black", 255, "colourtest.t4" };
    s->save[0] = 2004;
    s->save[1] = 1;
    s->save[2] = 255;
    s->len = 3;
    recordMain(s);
    free(s);
}

void t5Test(){
    storage *s = malloc(sizeof(storage));
    *s = (storage) { 0, 0, 0, 0, 0, "black", 255, "colourtest.t5" };
    s->save[0] = 2004;
    s->save[1] = 3;
    s->save[2] = 64;
    s->len = 3;
    recordMain(s);
    free(s);
}

void t6Test(){
    storage *s = malloc(sizeof(storage));
    *s = (storage) { 0, 0, 0, 0, 0, "black", 255, "pausetest.t6" };
    s->save[0] = 2005;
    s->save[1] = 3000;
    s->len = 2;
    recordMain(s);
    free(s);
}

void t7Test(){
    storage *s = malloc(sizeof(storage));
    *s = (storage) { 0, 0, 0, 0, 0, "black", 255, "mixedtest.t7" };
    s->save[0] = 2002;
    s->save[1] = 0;
    s->save[2] = 0;
    s->save[3] = 20;
    s->save[4] = 20;
    s->save[5] = 2003;
    s->save[6] = 2002;
    s->save[7] = 20;
    s->save[8] = 20;
    s->save[9] = 100;
    s->save[10] = 100;
    s->save[11] = 2004;
    s->save[12] = 5;
    s->save[13] = 128;
    s->save[14] = 2005;
    s->save[15] = 2000;
    s->save[16] = 2002;
    s->save[17] = 100;
    s->save[18] = 100;
    s->save[19] = 300;
    s->save[20] = 50;
    s->len = 21;
    recordMain(s);
    free(s);
}

void lineTest(){
    t1Test();
    t2Test();
}

void clearTest(){
    t3Test();
}

void colourTest(){
    t4Test();
    t5Test();
}

void pauseTest(){
    t6Test();
}

void mixedTest(){
    t7Test();
}

void testMain(){
    lineTest();
    clearTest();
    colourTest();
    pauseTest();
    mixedTest();
}

//----------------------------------------------Test End--------------------------------------------
//--------------------------------------------------------------------------------------------------

int main(int n, char *args[n]){
    if(n == 1 && strcmp(args[0], "./record") == 0){
        storage *s = malloc(sizeof(storage));
        *s = (storage) { 0, 0, 0, 0, 0, "black", 255, "new" };
        mainMenu(s);
        free(s);
    }
    else if(n == 1 && strcmp(args[0], "./test") == 0){
        testMain();
        printf("All test finished\n");
    }
    else{
        fprintf(stdout, "Use    ./record     or     ./test\n");
        exit(1);
    }
}
