#ifndef ATTESA
#define ATTESA
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct coda {
    char cliente[30];
    char nomeVeicolo[30];
    int priority;
    struct coda *next;
}coda;

typedef struct  coda *Attesa;

Attesa creaAttesa(char*,char*);
Attesa enqueue(Attesa,char*,char*);
Attesa dequeue(Attesa,char*);
char *maxPriority(Attesa,char*);
void stampaAttesa(Attesa);
bool attesaIsEmpty(Attesa);
bool checkAttesaPrestito(Attesa,char*);
bool checkAttesaAlreadyExist(Attesa,char*,char*);

#endif
