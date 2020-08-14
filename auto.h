#ifndef AUTO
#define AUTO
#define RESO 0
#define CHIEDI 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct autoTree {
    char nome[30];
    int quant;
    struct autoTree *sx;
    struct autoTree *dx;
}autoTree;

typedef struct autoTree *Auto;

Auto creaNodo(char*,int);
Auto inserisciAuto(Auto,char*,int);
Auto initAuto(Auto,FILE*);
void updateQuantity(Auto,char*,int);
void stampaAuto(Auto);

bool checkTreeIsEmpty(Auto);
bool checkDisp(Auto,char*);
bool checkAuto(Auto,char*);


#endif