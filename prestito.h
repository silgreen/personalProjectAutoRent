#ifndef PRESTITO
#define PRESTITO
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "auto.h"

typedef struct prestitoList {
    char nome[30];
    struct prestitoList *next;
}prestitoList;

typedef struct prestitoList *Prestiti;

Prestiti creaPrestito(char*);
Prestiti inserisciPrestito(Prestiti,char*);
Prestiti eliminaPrestito(Prestiti,char*);
Prestiti eliminaListaPrestiti(Prestiti,Auto);
bool checkPrestito(Prestiti,char*);
bool checkPrestitoIsEmpty(Prestiti);
int prestitiLen(Prestiti);
void stampaPrestiti(Prestiti);

#endif