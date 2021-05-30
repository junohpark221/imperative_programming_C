#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node{
    struct node *next;
    name x;
    number p;
}

struct hash{ node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m, *n, *o, *p, *q, *r, *s, *t, *u, *v, *w, *x, *y, *z, *current; }

hash *newHash() {
    hash *h = (hash*)malloc(sizeof(hash));
    h->a = (node*)malloc(sizeof(node);
    h->a->next = NULL;
    h->b = (node*)malloc(sizeof(node);
    h->b->next = NULL;
    h->c = (node*)malloc(sizeof(node);
    h->c->next = NULL;
    h->d = (node*)malloc(sizeof(node);
    h->d->next = NULL;
    h->e = (node*)malloc(sizeof(node);
    h->e->next = NULL;
    h->f = (node*)malloc(sizeof(node);
    h->f->next = NULL;
    h->g = (node*)malloc(sizeof(node);
    h->g->next = NULL;
    h->h = (node*)malloc(sizeof(node);
    h->h->next = NULL;
    h->i = (node*)malloc(sizeof(node);
    h->i->next = NULL;
    h->j = (node*)malloc(sizeof(node);
    h->j->next = NULL;
    h->k = (node*)malloc(sizeof(node);
    h->k->next = NULL;
    h->l = (node*)malloc(sizeof(node);
    h->l->next = NULL;
    h->m = (node*)malloc(sizeof(node);
    h->m->next = NULL;
    h->n = (node*)malloc(sizeof(node);
    h->n->next = NULL;
    h->o = (node*)malloc(sizeof(node);
    h->o->next = NULL;
    h->p = (node*)malloc(sizeof(node);
    h->p->next = NULL;
    h->q = (node*)malloc(sizeof(node);
    h->q->next = NULL;
    h->r = (node*)malloc(sizeof(node);
    h->r->next = NULL;
    h->s = (node*)malloc(sizeof(node);
    h->s->next = NULL;
    h->t = (node*)malloc(sizeof(node);
    h->t->next = NULL;
    h->u = (node*)malloc(sizeof(node);
    h->u->next = NULL;
    h->v = (node*)malloc(sizeof(node);
    h->v->next = NULL;
    h->w = (node*)malloc(sizeof(node);
    h->w->next = NULL;
    h->x = (node*)malloc(sizeof(node);
    h->x->next = NULL;
    h->y = (node*)malloc(sizeof(node);
    h->y->next = NULL;
    h->z = (node*)malloc(sizeof(node);
    h->z->next = NULL;
    h->current = h->a;
    return h;
}

void freeHash(hash *h){
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
    h->current = h->a;
    while(h->current->next != NULL){
        h->current = h->a->next;
        free(h->a);
        h->a = h->current;
    }
}

void searchHash(hash *h, char *s){
    if(s[0] == 'a') h->current = h->a;
    else if(s[0] == 'b') h->current = h->b;
    else if(s[0] == 'c') h->current = h->c;
    else if(s[0] == 'd') h->current = h->d;
    else if(s[0] == 'e') h->current = h->e;
    else if(s[0] == 'f') h->current = h->f;
    else if(s[0] == 'g') h->current = h->g;
    else if(s[0] == 'h') h->current = h->h;
    else if(s[0] == 'i') h->current = h->i;
    else if(s[0] == 'j') h->current = h->j;
    else if(s[0] == 'k') h->current = h->k;
    else if(s[0] == 'l') h->current = h->l;
    else if(s[0] == 'm') h->current = h->m;
    else if(s[0] == 'n') h->current = h->n;
    else if(s[0] == 'o') h->current = h->o;
    else if(s[0] == 'p') h->current = h->p;
    else if(s[0] == 'q') h->current = h->q;
    else if(s[0] == 'r') h->current = h->r;
    else if(s[0] == 's') h->current = h->s;
    else if(s[0] == 't') h->current = h->t;
    else if(s[0] == 'u') h->current = h->u;
    else if(s[0] == 'v') h->current = h->v;
    else if(s[0] == 'w') h->current = h->w;
    else if(s[0] == 'x') h->current = h->x;
    else if(s[0] == 'y') h->current = h->y;
    else if(s[0] == 'z') h->current = h->z;
    else printf("The name is incorrect.\n");
}

void searchNode(hash *h, char *s, char *t){
    if(h->current->next == NULL){
        node *new = (node*)malloc(sizeof(node));
        h->current->next = new;
        new->x = s;
        new->p = t;
        new->next = NULL;
    }
    else{
        h->current = h->current->next;
        while(1){
            if(h->current->x[1]
        }
    }
}

void insert(hash *h){
    char s[100], t[100];
    printf("Write the name: ");
    fgets(s, sizeof(s), stdin);
    printf("Write the phone number: ");
    fgets(t, sizeof(t), stdin);
    s[strlen(s) - 1] = '\0';
    t[strlen(t) - 1] = '\0';
    h->current = h->a;
    searchHash(h, s);
    searchNode(h, s, t);
}

void main(){
    int c;
    hash *h = newHash();
    while(1){
        printf("This is telephone directory. What do you want to do?\n");
        printf("1. Insert\n2. Search(By name)\n3. Delete\n4. Quit\n: ");
        scanf("%d", &c);
        if(c == 1) insert(h);
        else if(c == 2) search(h);
        else if(c == 3) delete(h);
        else if(c == 4) break;
        else printf("Please chosse 1 or 2 or 3 or 4.\n");
    }
}
