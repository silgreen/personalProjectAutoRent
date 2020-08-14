#include "cliente.h"

bool checkClienteIsEmpty(Clienti treeClienti) {
    return treeClienti == NULL;
}

Clienti creaCliente(char *username) {
    Clienti temp = (Clienti)malloc(sizeof(struct clienteTree));
    strcpy(temp->username,username);
    temp->listaPrestiti = NULL;
    temp->dx = NULL;
    temp->sx = NULL;
    return temp;
}

Clienti inserisciCliente(Clienti treeClienti, char *username) {
    if(checkClienteIsEmpty(treeClienti))
        return creaCliente(username);

    if(strcmp(username,treeClienti->username) < 0)
        treeClienti->sx = inserisciCliente(treeClienti->sx,username);
    else if(strcmp(username,treeClienti->username) >= 0)
        treeClienti->dx = inserisciCliente(treeClienti->dx,username);

return treeClienti;
}

bool checkCliente(Clienti treeClienti, char *username) {
    bool found = false;
    if(!checkClienteIsEmpty(treeClienti)) {
        if(strcmp(treeClienti->username,username) == 0)
            found = true;

        else if(strcmp(username,treeClienti->username) < 0)
            found = checkCliente(treeClienti->sx,username);

        else if(strcmp(username,treeClienti->username) > 0)
            found = checkCliente(treeClienti->dx,username);
    }
return found;
}

Clienti aggiungiPrestitoCliente(Clienti treeClienti, char *username, char *nomeVeicolo) {
    if(!checkClienteIsEmpty(treeClienti)) {
        if(strcmp(treeClienti->username,username) == 0)
            treeClienti->listaPrestiti = inserisciPrestito(treeClienti->listaPrestiti,nomeVeicolo);

        else if(strcmp(username,treeClienti->username) < 0)
            treeClienti->sx = aggiungiPrestitoCliente(treeClienti->sx,username,nomeVeicolo);

        else if(strcmp(username,treeClienti->username) > 0)
            treeClienti->dx = aggiungiPrestitoCliente(treeClienti->dx,username,nomeVeicolo);
    }
return treeClienti;
}

Clienti eliminaPrestitoCliente(Clienti treeClienti, char *username, char *nomeVeicolo) {
    if(!checkClienteIsEmpty(treeClienti)) {
        if(strcmp(treeClienti->username,username) == 0)
            treeClienti->listaPrestiti = eliminaPrestito(treeClienti->listaPrestiti,nomeVeicolo);

        else if(strcmp(username,treeClienti->username) < 0)
            treeClienti->sx = eliminaPrestitoCliente(treeClienti->sx,username,nomeVeicolo);

        else if(strcmp(username,treeClienti->username) > 0)
            treeClienti->dx = eliminaPrestitoCliente(treeClienti->dx,username,nomeVeicolo);
    }
return treeClienti;
}

bool prestitiException(Clienti treeClienti, char *username) {
    bool check = false;
    if(!checkClienteIsEmpty(treeClienti)) {
        if(strcmp(treeClienti->username,username) == 0 && prestitiLen(treeClienti->listaPrestiti) == 3)
            check = true;
        
        else if(strcmp(username,treeClienti->username) < 0)
            check = prestitiException(treeClienti->sx,username);

        else if(strcmp(username,treeClienti->username) > 0)
            check = prestitiException(treeClienti->dx,username);
    }
return check;
}

bool checkPrestitoClienteIsEmpty(Clienti treeClienti, char *username) {
    bool check = false;
    if(!checkClienteIsEmpty(treeClienti)) {
        if(strcmp(treeClienti->username,username) == 0 && checkPrestitoIsEmpty(treeClienti->listaPrestiti))
            check = true;
        
        else if(strcmp(username,treeClienti->username) < 0)
            check = checkPrestitoClienteIsEmpty(treeClienti->sx,username);

        else if(strcmp(username,treeClienti->username) > 0)
            check = checkPrestitoClienteIsEmpty(treeClienti->dx,username);
    }
return check;
}

bool checkPrestitoCliente(Clienti treeClienti, char *username, char *nomeVeicolo) {
    bool check = false;
    if(!checkClienteIsEmpty(treeClienti)) {
        if(strcmp(treeClienti->username,username) == 0 && checkPrestito(treeClienti->listaPrestiti, nomeVeicolo))
            check = true;
        
        else if(strcmp(username,treeClienti->username) < 0)
            check = checkPrestitoCliente(treeClienti->sx,username,nomeVeicolo);

        else if(strcmp(username,treeClienti->username) > 0)
            check = checkPrestitoCliente(treeClienti->dx,username,nomeVeicolo);
    }
return check;
}

Clienti sequestraVeicoli(Clienti treeClienti,Auto aut) {
    if(!checkClienteIsEmpty(treeClienti)) {
        treeClienti->sx = sequestraVeicoli(treeClienti->sx,aut);
        treeClienti->listaPrestiti = eliminaListaPrestiti(treeClienti->listaPrestiti,aut);
        treeClienti->dx = sequestraVeicoli(treeClienti->dx,aut);
    }
return treeClienti;
}

void stampaClienti(Clienti treeClienti) {
    if(!checkClienteIsEmpty(treeClienti)) {
        stampaClienti(treeClienti->sx);
        printf("|%s|\n",treeClienti->username);
        stampaClienti(treeClienti->dx);
    }
}

void stampaPrestitoCliente(Clienti treeClienti, char *username) {
    if(!checkClienteIsEmpty(treeClienti)) {
        if(strcmp(treeClienti->username, username) == 0) {
            if(checkPrestitoIsEmpty(treeClienti->listaPrestiti)) {
                printf("Il cliente non ha effettuato prestiti\n");
            } else
                stampaPrestiti(treeClienti->listaPrestiti);      
        }
        else if (strcmp(username, treeClienti->username) < 0)
            stampaPrestitoCliente(treeClienti->sx, username);
            
        else if (strcmp(username, treeClienti->username) > 0)
            stampaPrestitoCliente(treeClienti->dx, username);
    }
}