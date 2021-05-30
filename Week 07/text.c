#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// Store text using a dynamically allocated character array with a given
// capacity. Use strlen to find the length of the string contained in the array.
struct text {
    int capacity;
    char *content;
};

// Create a new text structure, containing a copy of the given string.
text *newText(char *s) {
    int i = 24;
    while(1) {
        if(strlen(s) > i-1) {
            i = i * 2;
        }
        else break;
    }
    printf("%lu\n", sizeof(text));
    text *t = malloc(i);
    t->capacity = i;
    t->content = s;
    return t;
}

// Free up both the space for the struct and the space for the content.
// Be careful not to access anything after it has been freed.
void freeText(text *t) {
    //free(t->content);
    free(t);
}

int length(text *t) {
    int i = strlen(t->content);
    return i;
}

char get(text *t, int i) {
    char s = t->content[i];
    return s;
}

void set(text *t, int i, char c) {
    int a = length(t);
    char tmp[a+1];
    for(int b = 0; b < a+1; b++) {
        tmp[b] = t->content[b];
    }
    tmp[i] = c;
    t->content = calloc(1, t->capacity);
    t->content = tmp;
}

text *copy(text *t) {
    int a = length(t);
    char tmp[a+1];
    for(int b = 0; b < a+1; b++) {
        tmp[b] = t->content[b];
    }
    text *t2 = newText(tmp);
    return t2;
}

int compare(text *t1, text *t2) {
    int a = strcmp(t1->content, t2->content);
    return a;
}

void append(text *t1, text *t2) {
    int i = t1->capacity;
    int a = length(t1), b = length(t2);
    while(1) {
        if(a + b > i - 1) {
            i = i * 2;
        }
        else break;
    }
    t1->capacity = i;
    char tmp[(a + b + 1)];
    for(int i = 0; i < a+b+1; i++) {
        if(i < a) tmp[i] = get(t1, i);
        else tmp[i] = get(t2, i - a);
    }
    t1->content = calloc(1, i);
    t1->content = tmp;
}

text *slice(text *t, int i, int j) {
    int c = length(t);
    int a = j - i + 1;
    char tmp[a];
    for(int b = i; b < i+a-1; b++) {
        tmp[b-i] = t->content[b];
    }
    tmp[a-1] = t->content[c];
    text *t2 = newText(tmp);
    return t2;
}

int find(text *t, text *p) {
    int a = length(t), b = length(p), val = 0;
    for(int n = 0; n < a; n++) {
        if(t->content[n] == p->content[0]) {
            for(int m = 0; m < b; m++) {
                if(t->content[n+m] == p->content[m]) val++;
            }
            if(val == b) return n;
            else val = 0;
        }
    }
    return -1;
}

//-----------------------------------------------------------------------------
// Testing. Use -Dtest_text when compiling for testing.
#ifdef test_text

// Check whether a text is like a given string, as far as can be checked
// without knowing how much memory has been allocated.
bool like(text *t, char *s) {
    if (t == NULL) return false;
    if (t->capacity < strlen(s) + 1) return false;
    if (strcmp(t->content, s) != 0) return false;
    return true;
}

// Test that new allocates 24 bytes if the string fits, or doubles the capacity
// until it does fit, taking the final null character into account.
void testNew() {
    text *t = newText("");
    assert(like(t, ""));
    assert(t->capacity == 24);
    freeText(t);
    t = newText("cat");
    assert(like(t, "cat"));
    assert(t->capacity == 24);
    freeText(t);
    char *s = "supercalifragilisticexpialidocious";
    t = newText(s);
    assert(like(t, s));
    assert(t->capacity == 48);
    freeText(t);
    s = "12345678901234567890123";
    t = newText(s);
    assert(like(t, s));
    assert(t->capacity == 24);
    freeText(t);
    s = "123456789012345678901234";
    t = newText(s);
    assert(like(t, s));
    assert(t->capacity == 48);
    freeText(t);
    s = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
    t = newText(s);
    assert(like(t, s));
    assert(t->capacity == 96);
    freeText(t);
}

void testLength() {
    text *t = newText("cat");
    assert(length(t) == 3);
    freeText(t);
}

void testGet() {
    text *t = newText("cat");
    assert(get(t,0) == 'c');
    assert(get(t,1) == 'a');
    assert(get(t,2) == 't');
    assert(get(t,3) == '\0');
    freeText(t);
}

void testSet() {
    text *t = newText("cat");
    set(t, 0, 'b');
    set(t, 2, 'r');
    assert(like(t, "bar"));
    freeText(t);
}

void testCopy() {
    text *t = newText("cat");
    text *t2 = copy(t);
    assert(t2 != t);
    assert(t2->content != t->content);
    assert(like(t2, "cat"));
    freeText(t);
    freeText(t2);
}

void testCompare() {
    text *t = newText("cat");
    text *t2 = newText("cat");
    assert(compare(t, t2) == 0);
    text *t3 = newText("car");
    assert(compare(t, t3) > 0);
    text *t4 = newText("caw");
    assert(compare(t, t4) < 0);
    text *t5 = newText("catch");
    assert(compare(t, t5) < 0);
    freeText(t);
    freeText(t2);
    freeText(t3);
    freeText(t4);
    freeText(t5);
}

void testAppend() {
    text *t = newText("car");
    text *t2 = newText("pet");
    append(t, t2);
    assert(like(t, "carpet"));
    assert(t->capacity == 24);
    text *t3 = newText("789012345678901234");
    append(t, t3);
    assert(like(t, "carpet789012345678901234"));
    assert(t->capacity == 48);
    freeText(t);
    freeText(t2);
    freeText(t3);
}

void testSlice() {
    text *t = newText("carpet");
    text *t2 = slice(t, 0, 3);
    assert(like(t2, "car"));
    text *t3 = slice(t, 3, 6);
    assert(like(t3, "pet"));
    freeText(t);
    freeText(t2);
    freeText(t3);
}

void testFind() {
    text *t = newText("carpet");
    text *t2 = newText("car");
    assert(find(t, t2) == 0);
    text *t3 = newText("pet");
    assert(find(t, t3) == 3);
    text *t4 = newText("cat");
    assert(find(t, t4) == -1);
    freeText(t);
    freeText(t2);
    freeText(t3);
    freeText(t4);
}

// Test the library.
int main() {
    testNew();
    testLength();
    testGet();
    testSet();
    testCopy();
    testCompare();
    testAppend();
    testSlice();
    testFind();
    printf("Tests all pass.\n");
    return 0;
}

#endif
