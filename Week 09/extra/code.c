// Testing for the lists module. Strings are used to describe lists. The strings
// "|37", "3|7", "37|" represent a list of two items, with the current position
// at the start, middle or end.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node{
    struct node *back;
    struct node *next;
    char a;
};
typedef struct node node;

struct list{
    node *start;
    node *current;
    node *end;
};
typedef struct list list;

struct encrypt { char origin[101], code[101], after[101]; };
typedef struct encrypt encrypt;

struct decrypt { char origin[101], after[101]; };
typedef struct decrypt decrypt;

list *newList(){
    list *l = (list*)malloc(sizeof(list));
    l->start = (node*)malloc(sizeof(node));
    l->end = (node*)malloc(sizeof(node));
    l->start->back = NULL;
    l->start->next = l->end;
    l->end->back = l->start;
    l->end->next = NULL;
    l->start->a = '\0';
    l->end->a = '\0';
    l->current = l->start;
    return l;
}

void freeList(list *l){
    node *n1 = l->start;
    node *n2 = n1;
    while (n1 != l->end) {
        n1 = n2;
        n2 = n1->next;
        free(n1);
    }
    free(l);
}

void intro(encrypt *e){
    printf("This is encrypting program.\n");
    printf("Write a sentence(maximum 100 characters): ");
    fgets(e->origin, sizeof(e->origin), stdin);
    e->origin[strlen(e->origin)- 1] = '\0';
}

char ask(){
    char ok;
    printf("Do you want to see the decryption? [y/n]: ");
    scanf("%c", &ok);
    return ok;
}

int findString(encrypt *e, char s) {
    int a = strlen(e->origin);
    for(int n = 0; n < a; n++) {
        if(e->code[n] == s) {
            return n;
        }
    }
    return -1;
}

void insertL(char x, list *l){
    node *n1 = l->start;
    node *n2 = l->current;
    if(n2 == n1){
        if(n1->a == '\0') {
            n1->a = x;
            l->current = l->end;
        }
        else{
            node *new = (node*)malloc(sizeof(node));
            new->a = x;
            new->back = NULL;
            l->start->back = new;
            new->next = l->start;
            l->start = new;
        }
    }
    else{
        node *new = (node*)malloc(sizeof(node));
        new->a = x;
        new->back = n2->back;
        new->next = l->current;
        l->current->back->next = new;
        l->current->back = new;
    }
}

void insertR(char x, list *l){
    if(l->start->a == '\0'){
        l->start->a = x;
        l->current = l->start;
    }
    else if(l->current == l->end){
        node *new = (node*)malloc(sizeof(node));
        new->a = x;
        new->back = l->current->back;
        new->next = l->current;
        l->current->back->next = new;
        l->current->back = new;
        l->current = new;
    }
    else if(l->current == l->start){
        node *new = (node*)malloc(sizeof(node));
        new->a = x;
        new->back = NULL;
        new->next = l->start;
        l->start->back = new;
        l->start = new;
        l->current = new;
    }
    else{
        node *new = (node*)malloc(sizeof(node));
        new->a = x;
        new->back = l->current->back;
        new->next = l->current;
        l->current->back->next = new;
        l->current->back = new;
        l->current = new;
    }
}

void findList(char x, list *l){
    l->current = l->start;
    while(1){
        if(l->current->a == x) break;
        else l->current = l->current->next;
    }
}

void select(encrypt *e){
    int j = 0;
    for(int i = 0; i < strlen(e->origin); i++){
        if(e->origin[i] >= 'a' && e->origin[i] <= 'z'){
            if(findString(e, e->origin[i]) == -1){
                e->code[j] = e->origin[i];
                j++;
            }
        }
    }
    e->code[j] = '\0';
}

void makeList(encrypt *e, list *l){
    for(int i = 0; i < strlen(e->code); i++){
        if((i+1) % 3 == 0) insertL(e->code[i], l);
        else insertR(e->code[i], l);
    }
}

void encCon(encrypt *e, list *l){
    for(int i = 0; i < strlen(e->origin); i++){
        if(e->origin[i] >= 'a' && e->origin[i] <= 'z'){
            findList(e->origin[i], l);
            if(l->current->next == l->end) e->after[i] = l->start->a;
            else e->after[i] = l->current->next->a;
        }
        else e->after[i] = e->origin[i];
    }
    e->after[strlen(e->origin)] = '\0';
}

void decCon(decrypt *d, list *l){
    for(int i = 0; i < strlen(d->origin); i++){
        if(d->origin[i] >= 'a' && d->origin[i] <= 'z'){
            findList(d->origin[i], l);
            if(l->current == l->start){
                l->current = l->end->back;
                d->after[i] = l->current->a;
            }
            else{
                l->current = l->current->back;
                d->after[i] = l->current->a;
            }
        }
        else d->after[i] = d->origin[i];
    }
    d->after[strlen(d->origin)] = '\0';
}

void enc(encrypt *e, list *l){
    select(e);
    makeList(e, l);
    encCon(e, l);
}

void dec(encrypt *e, decrypt *d, list *l){
    strcpy(d->origin, e->after);
    decCon(d, l);
}

//---------------------------------------------------------------------------------------------------

void toArray(encrypt *e, char *str){
    int a = strlen(str);
    int i = 0;
    for(i = 0; i < a; i++){
        e->origin[i] = str[i];
    }
    e->origin[i++] = '\0';
}

static void toList(list *l, char *pic) {
    int pos = strchr(pic, '|') - pic;
    for (int i = 0; i < strlen(pic); i++) {
        if (pic[i] == '|') continue;
        insertL(pic[i], l);
    }
    l->current = l->start;
    for (int i = 0; i < pos; i++) l->current = l->current->next;
}

static void toString(list *l, char s[]) {
    int pos = 0;
    while (l->current->back != NULL) {
        pos++;
        l->current = l->current->back;
    }
    int i = 0;
    while (l->current->next != NULL) {
        if (i == pos) s[i++] = '|';
        s[i++] = l->current->a;
        l->current = l->current->next;
    }
    if (i == pos) s[i++] = '|';
    s[i++] = '\0';
}

void preCheckSelect(encrypt *e, char *code, char *strb, char *strf){
    for(int i = 0; i < 101; i++){
        code[i] = '\0';
        e->code[i] = '\0';
    }
    toArray(e, strb);
    select(e);
    sprintf(code, "%s", strf);
}

int preCheckInsert(char *bef, char *aft, char x, int dir){
    list *l = newList();
    char a[101];
    int b = 0;
    toList(l, bef);
    if(dir == 0) insertL(x, l);
    else insertR(x, l);
    toString(l, a);
    b = strcmp(aft, a);
    freeList(l);
    return b;
}

int preCheckCon(char *bef, char *mid, char *aft){
    encrypt *e = malloc(sizeof(encrypt));
    decrypt *d = malloc(sizeof(decrypt));
    list *l = newList();
    char mid2[101];
    char aft2[101];
    int a = 0, b = 0;
    toArray(e, bef);
    enc(e, l);
    sprintf(mid2, "%s", mid);
    if(strcmp(e->after, mid2) == 0) a = 1;
    dec(e, d, l);
    sprintf(aft2, "%s", aft);
    if(strcmp(d->after, aft2) == 0) b = 1;
    free(e);
    free(d);
    freeList(l);
    if(a == 1 && b == 1) return 0;
    else return 1;
}

void checkNewList(){
    list *l = newList();
    assert(l->start->back == NULL);
    assert(l->end->next == NULL);
    assert(l->start->next == l->end);
    assert(l->end->back == l->start);
    assert(l->start->a == '\0');
    assert(l->end->a == '\0');
    assert(l->current == l->start);
    freeList(l);
}

void checkSelect(){
    encrypt *e = malloc(sizeof(encrypt));
    char code[101];
    preCheckSelect(e, code, "hi", "hi");
    assert(strcmp(e->code, code) == 0);
    preCheckSelect(e, code, "hello", "helo");
    assert(strcmp(e->code, code) == 0);
    preCheckSelect(e, code, "elephant", "elphant");
    assert(strcmp(e->code, code) == 0);
    preCheckSelect(e, code, "i am junoh", "iamjunoh");
    assert(strcmp(e->code, code) == 0);
    preCheckSelect(e, code, "apple pie", "aplei");
    assert(strcmp(e->code, code) == 0);
    preCheckSelect(e, code, "my name is lionel messi", "mynaeislo");
    assert(strcmp(e->code, code) == 0);
    free(e);
}

void checkInsert(){
    assert(preCheckInsert("|hi", "a|hi", 'a', 0) == 0);
    assert(preCheckInsert("h|i", "ha|i", 'a', 0) == 0);
    assert(preCheckInsert("hi|", "hia|", 'a', 0) == 0);
    assert(preCheckInsert("|hi", "|ahi", 'a', 1) == 0);
    assert(preCheckInsert("h|i", "h|ai", 'a', 1) == 0);
    assert(preCheckInsert("hi|", "hi|a", 'a', 1) == 0);
}

void checkCon(){
    assert(preCheckCon("hello", "lhooe", "hello") == 0);
    assert(preCheckCon("hi", "ih", "hi") == 0);
    assert(preCheckCon("i am junoh", "m in ajhuo", "i am junoh") == 0);
    assert(preCheckCon("my name is lionel messi", "nm iyna oe solias naeeo", "my name is lionel messi") == 0);
}

void test() {
    checkNewList();
    checkSelect();
    checkInsert();
    checkCon();
    printf("All Test Finished\n");
}

int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if(n == 1) test();
    else if(n == 2) {
        encrypt *e = malloc(sizeof(encrypt));
        decrypt *d = malloc(sizeof(decrypt));
        list *l = newList();
        intro(e);
        enc(e, l);
        printf("\n\nEncrypted Sentence: %s\n", e->after);
        char ok = ask();
        if(ok == 'y'){
            dec(e, d, l);
            printf("\n\nDecrypted Sentence: %s\n", d->after);
        }
        free(e);
        free(d);
        freeList(l);
    }
    else {
        fprintf(stderr, "Use lik this way: \n");
        fprintf(stderr, "./code      or       ./code start\n");
        fprintf(stderr, "Write the sentence you want to encrypt after the program start.\n");
    }
}
