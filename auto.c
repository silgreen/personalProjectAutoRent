#include "auto.h"

bool checkTreeIsEmpty(Auto aut) { return aut == NULL; }

Auto creaNodo(char *name,int quant) {

    Auto temp = (Auto)malloc(sizeof(struct autoTree));
    strcpy(temp->nome,name);
    temp->quant = quant;
    temp->dx = NULL;
    temp->sx = NULL;

    return temp;
}

Auto inserisciAuto(Auto aut, char *name, int quant) {
    if(checkTreeIsEmpty(aut)) 
        return creaNodo(name,quant);
    
    if(strcmp(name,aut->nome) < 0) 
        aut->sx = inserisciAuto(aut->sx,name,quant);
    else
        aut->dx = inserisciAuto(aut->dx,name,quant);

return aut;
}

Auto initAuto(Auto tree, FILE *fp) {
    char str[30];
    int n;

    fp = fopen("auto.txt","r");
    if(!fp) {
        perror("ERRORE CARICAMENTO FILE!");
        return NULL;
    }
    while (!feof(fp)) {
        fscanf(fp,"%s %d",str,&n);
        tree = inserisciAuto(tree,str,n);
    }
    fclose(fp);

return tree;    
}

void stampaAuto(Auto aut) {
    if(!checkTreeIsEmpty(aut)) {
        stampaAuto(aut->sx);
        printf("%s : %d\n",aut->nome,aut->quant);
        stampaAuto(aut->dx);   
    }
}

bool checkDisp(Auto aut, char *name) {
    bool disp = false;

    if (!checkTreeIsEmpty(aut)) {
        if(strcmp(aut->nome,name) == 0 && aut->quant > 0) {
            disp = true;
        } 
        else if (strcmp(name,aut->nome) < 0)
            disp = checkDisp(aut->sx,name);
        else if (strcmp(name,aut->nome) > 0)
            disp = checkDisp(aut->dx,name);
    }
return disp;
}

bool checkAuto(Auto aut, char *name) {
    bool found = false;

    if (!checkTreeIsEmpty(aut)) {
        if(strcmp(aut->nome,name) == 0) {
            found = true;
        } 
        else if (strcmp(name,aut->nome) < 0)
            found = checkAuto(aut->sx,name);
        else if (strcmp(name,aut->nome) > 0)
            found = checkAuto(aut->dx,name);
    }
return found;
}

void updateQuantity(Auto aut, char *nomeVeicolo, int operazione) {
    if (!checkTreeIsEmpty(aut)) {
        if(strcmp(aut->nome,nomeVeicolo) == 0) {
            if(operazione == CHIEDI)
                aut->quant -= 1;
            else if(operazione == RESO)
                aut->quant += 1;
        } 
        else if (strcmp(nomeVeicolo,aut->nome) < 0)
            updateQuantity(aut->sx,nomeVeicolo,operazione);
        else if (strcmp(nomeVeicolo,aut->nome) > 0)
            updateQuantity(aut->dx,nomeVeicolo,operazione);
    }
}
