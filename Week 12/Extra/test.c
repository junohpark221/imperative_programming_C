#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct display{ char **calls; char name[50]; int n; char comp[100]; };
typedef struct display display;

static void error(display *d){
    char *answer = d->calls[d->n];
    if(answer == NULL) printf("There is an error on test storage!!\n");
    else{
        printf("Error is occured!!!!\n");
        printf("The location of error is: %s   %s\n", d->name, d->comp);
    }
    free(d);
    exit(1);
}

void check(display *d){
    char *answer = d->calls[d->n];
    if(strcmp(answer, d->comp) != 0) error(d);
    else if(answer == NULL) error(d);
    d->n += 1;
    for(int i = 0; i < 100; i++) d->comp[i] = '\0';
}

void line(display *d, int x0, int y0, int x1, int y1){
    sprintf(d->comp, "line(d, %d, %d, %d, %d)", x0, y0, x1, y1);
    check(d);
}

void colour(display *d, int r, int g, int b, int a){
    sprintf(d->comp, "colour(d, %d, %d, %d, %d)", r, g, b, a);
    check(d);
}

void clear(display *d){
    sprintf(d->comp, "clear(d)");
    check(d);
}

void pause(display *d, int time){
    sprintf(d->comp, "pause(d, %d)", time);
    check(d);
}

void end(display *d){
    sprintf(d->comp, "end(d)");
    check(d);
    free(d);
}

static char *t1Store[] = {
    "line(d, 20, 20, 40, 40)", "end(d)"
};

static char *t2Store[] = {
    "line(d, 20, 20, 40, 40)", "line(d, 0, 40, 50, -100)", "line(d, 10, 60, -450, 200)", "end(d)"
};

static char *t3Store[] = {
    "pause(d, 1000)", "clear(d)", "pause(d, 1000)", "end(d)"
};

static char *t4Store[] = {
    "colour(d, 255, 255, 255, 255)", "end(d)"
};

static char *t5Store[] = {
    "colour(d, 255, 0, 0, 64)", "end(d)"
};

static char *t6Store[] = {
    "pause(d, 3000)", "end(d)"
};

static char *t7Store[] = {
    "line(d, 0, 0, 20, 20)", "pause(d, 1000)", "clear(d)", "pause(d, 1000)",
    "line(d, 20, 20, 100, 100)", "colour(d, 0, 0, 255, 128)", "pause(d, 2000)",
    "line(d, 100, 100, 300, 50)", "end(d)" 
};

static char **findCalls(char *test){
    if(strcmp(test, "linetest.t1") == 0) return t1Store;
    else if(strcmp(test, "linetest.t2") == 0) return t2Store;
    else if(strcmp(test, "cleartest.t3") == 0) return t3Store;
    else if(strcmp(test, "colourtest.t4") == 0) return t4Store;
    else if(strcmp(test, "colourtest.t5") == 0) return t5Store;
    else if(strcmp(test, "pausetest.t6") == 0) return t6Store;
    else if(strcmp(test, "mixedtest.t7") == 0) return t7Store;
    else{
        printf("\nInvalid Name\n\n");
        return NULL;
    }
}

display *newDisplay(char *test, int width, int height){
    display *d = malloc(sizeof(display));
    *d = (display) { findCalls(test) };
    strcpy(d->name, test);
    d->n = 0;
    return d;
}

