#include "prestito.h"

Prestiti creaPrestito(char *nomeVeicolo) {
    Prestiti temp = (Prestiti)malloc(sizeof(struct prestitoList));
    strcpy(temp->nome,nomeVeicolo);
    temp->next = NULL;
    return temp;
}

bool checkPrestitoIsEmpty(Prestiti listaPrestiti) {
    return listaPrestiti == NULL;
}

Prestiti inserisciPrestito(Prestiti listaPrestiti, char *nomeVeicolo) {
    
    if(checkPrestitoIsEmpty(listaPrestiti)) 
        return creaPrestito(nomeVeicolo);
    else
        listaPrestiti->next = inserisciPrestito(listaPrestiti->next,nomeVeicolo);
    
return listaPrestiti;
}

bool checkPrestito(Prestiti listaPrestiti, char *nomeVeicolo) {
    bool found = false;
    if(!checkPrestitoIsEmpty(listaPrestiti)) {
        if(strcmp(listaPrestiti->nome,nomeVeicolo) == 0)
            found = true;
        else 
            found = checkPrestito(listaPrestiti->next,nomeVeicolo); 
    }
    return found;
}

Prestiti eliminaPrestito(Prestiti listaPrestiti, char *nomeVeicolo) {
    if(!checkPrestitoIsEmpty(listaPrestiti)) {
        if(strcmp(listaPrestiti->nome,nomeVeicolo) != 0)
            listaPrestiti->next = eliminaPrestito(listaPrestiti->next,nomeVeicolo);
        else {
            Prestiti temp = listaPrestiti->next;
            free(listaPrestiti);
            return temp;
        }
    }
    return listaPrestiti;
}

Prestiti eliminaListaPrestiti(Prestiti listaPrestiti,Auto  aut) {
    if(!checkPrestitoIsEmpty(listaPrestiti)) {
        updateQuantity(aut,listaPrestiti->nome,RESO);
        Prestiti temp = listaPrestiti->next;
        free(listaPrestiti);
        return eliminaListaPrestiti(temp,aut);
    } else return NULL;
}

int prestitiLen(Prestiti listaPrestiti) {
    if(!checkPrestitoIsEmpty(listaPrestiti))
        return prestitiLen(listaPrestiti->next) + 1;
    else return 0;
}

void stampaPrestiti(Prestiti listaPrestiti) {
    if(!checkPrestitoIsEmpty(listaPrestiti)) {
        printf("| %s |-",listaPrestiti->nome);
        stampaPrestiti(listaPrestiti->next);
        printf("\n");
    }
}