#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "prestito.h"
#include "cliente.h"
#include "attesa.h"
#include "lib.h"


int main(int argc, char const *argv[]) {
    Clienti clientela = NULL;
    Auto listino = NULL;
    Attesa waiting = NULL;
    FILE *fp;
    int termina = 0;
    listino = initAuto(listino,fp);

        do {
            system("cls");
            msgBenvenuto(listino);
            menuIniziale();
            int scelta;
            char username[30];
            printf("> ");
            scanf("%d",&scelta);
            switch (scelta) {
            case 1:
                termina = 0;
                system("cls");
                do {
                    printf("\nInserisci un username, se non sei gia' registrato ti inseriro' nel nostro database\n");
                    printf("> ");
                    scanf("%s",username);

                    if(strlen(username) < 4) printf("hai inserito un username non valido, riprova!\n");
                } while(strlen(username) < 4);
                
                if(!checkCliente(clientela,username)) {
                    printf("Non sei presente nel nostro Database, provvedo ad aggiungerti...\n\n");
                    clientela = inserisciCliente(clientela,username);
                } else { 
                    printf("Bentornato %s!\n", username);
                            
                    if(prestitiException(clientela,username)) {
                        printf("Possiedi troppe macchine, restituiscine qualcuna!\n");
                        system("pause && cls");
                        break;
                    }
                }
                char nomeVeicolo[30];
                int cont = 0;
                do {
                    if(prestitiException(clientela,username) || cont == 3) {
                        printf("Hai raggiunto il limite massimo di auto in tuo possesso o in attesa!\n");
                        system("pause && cls");
                        break;
                    }
                    printf("Puoi noleggiare massimo tre auto, Ecco il nostro listino:\n");
                    stampaAuto(listino);
                    printf("Inserisci il nome della macchina che vuoi noleggiare\n");
                    printf("> ");
                    scanf("%s",nomeVeicolo);

                    /* Eccezzioni */
                    if (!checkAuto(listino,nomeVeicolo)) {
                        printf("Il nome del veicolo che hai inserito non e' presente, riprova!\n");
                        system("pause && cls");
                        continue;
                    }
                    if(checkAttesaAlreadyExist(waiting,username,nomeVeicolo)) {
                        printf("Attendi gia' quest'auto, selezionane un'altra\n");
                        system("pause && cls");
                        continue;  
                    }                      

                    if(!checkDisp(listino,nomeVeicolo)) {
                        printf("La macchina selezionata al momento non e' disponibile, provvedo a metterti in attesa\n\n");
                        waiting = enqueue(waiting,username,nomeVeicolo);
                        printf("Appena l'auto tornera' disponibile, verrai servito!\n\n");
                        system("pause && cls");
                    } else {
                        aggiungiPrestitoCliente(clientela,username,nomeVeicolo);
                        updateQuantity(listino,nomeVeicolo,CHIEDI);
                        printf("Operazione effettuata con successo!\n");
                        }
                    printf("vuoi noleggiare un altro veicolo? Y/N\n");
                    printf("> ");
                    char conferma;
                    scanf(" %c", &conferma);
                    conferma = toupper(conferma);
                    if(conferma == 'N') break;
                    else  {
                        cont ++;
                        system("cls"); 
                        continue;
                        }
                } while (1);
                break;
            case 2:
                termina = 0;
                do {
                    char nomeVeicolo[30];
                    system("cls");
                    printf("Per restituire un Veicolo, inserisci il nome utente utilizzato quando hai noleggiato da noi\n");
                    printf("> ");
                    scanf("%s",username);
                    if(!checkCliente(clientela,username)) {
                    printf("L'username inserito non esiste\n");
                    printf("[1] Riprova con un nuovo username\n");
                    printf("[0] Torna al menu' principale\n");
                    printf("> ");
                    scanf("%d", &scelta);
                    if(scelta) continue;
                    else break;
                    } else {
                        if(checkPrestitoClienteIsEmpty(clientela,username)) {
                        printf("Non hai auto da restituire, prova a noleggiarne qualcuna\n");
                        system("pause");
                        break;
                    }

                do {
                    system("cls");
                    printf("Bentornato %s, questa e' la lista delle auto che hai in possesso:\n");
                    stampaPrestitoCliente(clientela,username);
                    printf("[1] Restituisci\n");
                    printf("[0] Indietro\n");
                    printf("> ");
                    scanf("%d",&scelta);

                    if(!scelta) break;

                    printf("Quale vuoi restituire?\n");
                    scanf("%s", nomeVeicolo);
                    if (!checkPrestitoCliente(clientela,username,nomeVeicolo)) {
                        printf("Non possiedi questo veicolo,riprova\n");
                        system("pause");
                        continue;
                        }
                    clientela = eliminaPrestitoCliente(clientela,username,nomeVeicolo);

                    if(attesaIsEmpty(waiting) || !checkAttesaPrestito(waiting,nomeVeicolo)) {
                        updateQuantity(listino,nomeVeicolo,RESO);
                        printf("Hai restituito il veicolo con successo!\n");
                        system("pause");
                        } else {
                            char clientePrioritario[30];
                            strcpy(clientePrioritario,maxPriority(waiting,nomeVeicolo));
                            printf("Sto provvedendo a servire il cliente %s dandogli il veicolo %s...\n\n",clientePrioritario,nomeVeicolo);
                            clientela = aggiungiPrestitoCliente(clientela,clientePrioritario,nomeVeicolo);
                            waiting = dequeue(waiting,clientePrioritario);
                            system("pause");
                        }
                    if(checkPrestitoClienteIsEmpty(clientela,username)) { 
                        printf("Hai restituito tutte le auto in tuo possesso\n");
                        break;
                        }
                    } while (1);
                    printf("Arrivederci!\n");
                    system("pause");
                    break;
                }
            } while (1);
                break;
            case 3:
                termina = 0;
                printf("\t\tListino Federica Autonoleggio &figli\n\n");
                stampaAuto(listino);
                system("pause && cls");
                break;
            case 0:
                if(checkClienteIsEmpty(clientela)) {
                    printf("Arrivederci <3\n");
                    return 0;
                }
                if(!attesaIsEmpty(waiting) && termina != 2) {
                    printf("Ci sono dei clienti in Attesa:\n");
                    stampaAttesa(waiting);
                    printf("Prova a restituire qualche veicolo\n");
                    termina++;
                    system("pause");
                    break;
                } else if(termina == 2) {
                    printf("Sono scaduti i termini per le restituzioni, Provvedo a sequestrare i veicoli\n\n");
                    clientela = sequestraVeicoli(clientela,listino);
                    printf("saranno serviti i clienti seguenti:\n");
                    stampaAttesa(waiting);
                    while(!attesaIsEmpty(waiting)) {

                        printf("Sto servendo %s\n",waiting->cliente);

                        if(!checkDisp(listino,waiting->nomeVeicolo)) {
                            printf("Il Veicolo non e' piu' disponibile, vuoi scegliere un auto sostitutiva? Y/N\n");
                            printf("> ");
                            char conferma;
                            scanf(" %c", &conferma);
                            conferma = toupper(conferma);
                            if(conferma == 'N') {
                                printf("Mi dispiace, prova a scegliere un altro veicolo la prossima volta\n");
                                waiting = dequeue(waiting,waiting->cliente);
                                continue;
                            } else if(conferma == 'Y') {
                                do {
                                system("cls");
                                printf("Scegli una tra queste auto, assicurati che sia disponibile: \n");
                                stampaAuto(listino);
                                printf("> ");
                                scanf("%s",nomeVeicolo);
                                if(!checkDisp(listino,nomeVeicolo)) {
                                    printf("Veicolo non disponibile, riprova!\n");
                                    system("pause && cls");
                                    continue;
                                }
                                if(!checkAuto(listino,nomeVeicolo)) {
                                    printf("Il nome dell'auto che hai inserito non esiste, riprova!\n");
                                    system("pause && cls");
                                    continue;
                                    }
                                break;
                                } while (1);
                                clientela = aggiungiPrestitoCliente(clientela,waiting->cliente,nomeVeicolo);
                                printf("L'auto sostitutiva %s e' stata consegnata a %s correttamente\n",nomeVeicolo,waiting->cliente);
                                waiting = dequeue(waiting,waiting->cliente);
                                system("pause && cls");
                                continue;
                            }
                        }
                        char clientePrioritario[30];
                        strcpy(clientePrioritario,maxPriority(waiting,waiting->nomeVeicolo));

                        clientela = aggiungiPrestitoCliente(clientela,clientePrioritario,waiting->nomeVeicolo);
                        updateQuantity(listino,waiting->nomeVeicolo,CHIEDI);
                        printf("%s Servito con successo!\n",waiting->cliente);
                        waiting = dequeue(waiting,clientePrioritario);
                        system("pause");
                    }
                    printf("Tutti i clienti in attesa sono stati serviti con successo, ora posso terminare\n\n");
                    system("pause");
                }
                printf("Arrivederci <3\n");
                return 0;
            default:
                printf("Scelta Non Corretta, riprova!\n");
                system("pause && cls");
                msgBenvenuto();
                menuIniziale();
                break;
            }
        } while (1);
    return 0;
}