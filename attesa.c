#include "attesa.h"

Attesa creaAttesa(char *nomeCliente,char *nomeVeicolo) {
    Attesa temp = (Attesa)malloc(sizeof(struct coda));
    strcpy(temp->cliente,nomeCliente);
    strcpy(temp->nomeVeicolo,nomeVeicolo);
    temp->priority = 0;
    temp->next = NULL;

return temp;
}

bool attesaIsEmpty(Attesa coda) {
    return coda == NULL;
}

Attesa enqueue(Attesa coda,char *nomeCliente,char *nomeVeicolo) {
    if(attesaIsEmpty(coda))
        return creaAttesa(nomeCliente,nomeVeicolo);
    else { 
        coda->next = enqueue(coda->next,nomeCliente,nomeVeicolo);
        coda->priority += 1;
    }
    
return coda;
}

Attesa dequeue(Attesa coda,char *nomeCliente) {
    if(!attesaIsEmpty(coda)) {
        if(strcmp(coda->cliente,nomeCliente) != 0)
            coda->next = dequeue(coda->next,nomeCliente);
        else {
            Attesa temp = coda->next;
            free(coda);
            return temp;
        }
    }
return coda;
}

char *maxPriority(Attesa coda,char *nomeVeicolo) {
    Attesa temp = coda;
    int max = 0;
    char *str = (char*)malloc(30 + sizeof(char));
    
    while (!attesaIsEmpty(temp)) {
        if(strcmp(temp->nomeVeicolo,nomeVeicolo) == 0 && temp->priority >= max) {
            strcpy(str,temp->cliente);
            max = temp->priority;
        }
        temp = temp->next;
    }
return str;
}

bool checkAttesaPrestito(Attesa coda, char *nomeVeicolo) {
    bool found = false;
    if(!attesaIsEmpty(coda)) {
        if(strcmp(coda->nomeVeicolo,nomeVeicolo) != 0)
            found = checkAttesaPrestito(coda->next,nomeVeicolo);
        else if(strcmp(coda->nomeVeicolo,nomeVeicolo) == 0) found = true;
    }
    return found;
}


bool checkAttesaAlreadyExist(Attesa coda, char*username, char *nomeVeicolo) {
    bool found = false;
    if(!attesaIsEmpty(coda)) {
        if(strcmp(coda->nomeVeicolo,nomeVeicolo) != 0 && strcmp(coda->cliente,username) != 0)
            found = checkAttesaAlreadyExist(coda->next,username,nomeVeicolo);
        else if(strcmp(coda->nomeVeicolo,nomeVeicolo) == 0 && strcmp(coda->cliente,username) == 0) found = true;
    }
    return found;
}

void stampaAttesa(Attesa coda) {
    if(!attesaIsEmpty(coda)) {
        printf("|%s %s| ",coda->cliente,coda->nomeVeicolo);
        stampaAttesa(coda->next);
        printf("\n");
    }
}
 