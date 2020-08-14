#ifndef CLIENTE
#define CLIENTE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "prestito.h"

typedef struct clienteTree {
    char username[30];
    Prestiti listaPrestiti;
    struct clienteTree *dx;
    struct clienteTree *sx;
}clienteTree;

typedef struct clienteTree *Clienti;

Clienti creaCliente(char*);
Clienti inserisciCliente(Clienti,char*);
Clienti aggiungiPrestitoCliente(Clienti,char*,char*);
Clienti eliminaPrestitoCliente(Clienti,char*,char*);
Clienti sequestraVeicoli(Clienti,Auto);
bool checkClienteIsEmpty(Clienti);
bool checkCliente(Clienti,char*);
bool prestitiException(Clienti,char*);
bool checkPrestitoClienteIsEmpty(Clienti,char*);
bool checkPrestitoCliente(Clienti,char*,char*);
void stampaClienti(Clienti);
void stampaPrestitoCliente(Clienti,char*);

#endif