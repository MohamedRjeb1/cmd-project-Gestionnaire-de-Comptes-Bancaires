#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tr {
    char t[20];
    double m;
    struct Tr* s;
} Tr;

typedef struct Cpt {
    int n;
    char nm[50];
    double sld;
    Tr* ts;
    struct Cpt* nxt;
} Cpt;

typedef struct Clt {
    char nm[50];
    Cpt* cpt;
    struct Clt* nxt;
} Clt;

Clt* lstClt = NULL;

Cpt* crtCpt(int n, const char* nm, double sld, const char* nmClt);
void ajtTr(Cpt* cpt, const char* t, double m, const char* nmClt);
void effctOp(Cpt* cpt, const char* t, double m, const char* nmClt);
void mAJCpt(Cpt* cpt, const char* nn, double ns);
void spCpt(Cpt* cpt);
void afTr(Cpt* cpt);
void afDtlsCpt(Cpt* cpt);
void afLstClt();
void svCpt(Cpt* cpt);
Cpt* chrgCpts();


Cpt* crtCpt(int n, const char* nm, double sld, const char* nmClt) {
    Cpt* nc = (Cpt*)malloc(sizeof(Cpt));
    nc->n = n;
    strcpy(nc->nm, nm);
    nc->sld = sld;
    nc->ts = NULL;
    nc->nxt = NULL;

    Clt* nClt = (Clt*)malloc(sizeof(Clt));
    strcpy(nClt->nm, nmClt);
    nClt->cpt = nc;
    nClt->nxt = NULL;

    if (lstClt == NULL) {
        lstClt = nClt;
    } else {
        Clt* crnt = lstClt;
        while (crnt->nxt != NULL) {
            crnt = crnt->nxt;
        }
        crnt->nxt = nClt;
    }

    return nc;
}

void ajtTr(Cpt* cpt, const char* t, double m, const char* nmClt) {
    Tr* nTr = (Tr*)malloc(sizeof(Tr));
    strcpy(nTr->t, t);
    nTr->m = m;
    nTr->s = cpt->ts;
    cpt->ts = nTr;

    printf("Transaction de %.2f %s effectuée par %s.\n", m, t, nmClt);
}

void effctOp(Cpt* cpt, const char* t, double m, const char* nmClt) {
    if (strcmp(t, "D") == 0) {
        cpt->sld += m;
        ajtTr(cpt, t, m, nmClt);
        printf("Opération de dépôt effectuée avec succès par %s.\n", nmClt);
    } else if (strcmp(t, "R") == 0) {
        if (m <= cpt->sld) {
            cpt->sld -= m;
            ajtTr(cpt, t, m, nmClt);
            printf("Opération de retrait effectuée avec succès par %s.\n", nmClt);
        } else {
            printf("Solde insuffisant pour effectuer le retrait par %s.\n", nmClt);
        }
    } else {
        printf("Type d'opération non pris en charge.\n");
    }
}

void mAJCpt(Cpt* cpt, const char* nn, double ns) {
    strcpy(cpt->nm, nn);
    cpt->sld = ns;
    printf("Informations du compte %d mises à jour avec succès.\n", cpt->n);
}

void spCpt(Cpt* cpt) {
    Clt* crnt = lstClt;
    Clt* prcdnt = NULL;

    while (crnt != NULL && crnt->cpt != cpt) {
        prcdnt = crnt;
        crnt = crnt->nxt;
    }

    if (crnt != NULL) {
        if (prcdnt == NULL) {
            lstClt = crnt->nxt;
        } else {
            prcdnt->nxt = crnt->nxt;
        }

        free(cpt);
        free(crnt);

        printf("Le compte a été supprimé avec succès.\n");
    } else {
        printf("Le compte n'a pas été trouvé dans la liste des clients.\n");
    }
}

void afTr(Cpt* cpt) {
    printf("Transactions du compte %d:\n", cpt->n);
    Tr* tr = cpt->ts;
    while (tr != NULL) {
        printf("%s: %.2f\n", tr->t, tr->m);
        tr = tr->s;
    }
}

void afDtlsCpt(Cpt* cpt) {
    printf("Numéro de compte: %d\n", cpt->n);
    printf("Nom du titulaire: %s\n", cpt->nm);
    printf("Solde du compte: %.2f\n", cpt->sld);
    afTr(cpt);
}

void afLstClt() {
    Clt* crnt = lstClt;
    while (crnt != NULL) {
        afDtlsCpt(crnt->cpt);
        printf("\n---------------------------------\n");
        crnt = crnt->nxt;
    }
}

void svCpt(Cpt* cpt) {
    FILE* fichier = fopen("cpts.txt", "a");
    if (fichier != NULL) {
        fprintf(fichier, "%d %s %.2f\n", cpt->n, cpt->nm, cpt->sld);
        fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
    }
}

Cpt* chrgCpts() {
    FILE* fichier = fopen("cpts.txt", "r");
    if (fichier != NULL) {
        Cpt* lstCpts = NULL;
        int n;
        char nm[50];
        double sld;

        while (fscanf(fichier, "%d %s %lf", &n, nm, &sld) == 3) {
            Cpt* nCpt = crtCpt(n, nm, sld, "Client Inconnu");
            if (nCpt != NULL) {
                nCpt->nxt = lstCpts;
                lstCpts = nCpt;
            }
        }

        fclose(fichier);
        return lstCpts;
    } else {
        printf("Erreur lors de l'ouverture du fichier de chargement.\n");
        return NULL;
    }
}

int main() {
    int a;
    printf("1. Créer un compte\n");
    printf("2. Ajouter une transaction\n");
    printf("3. Effectuer une opération\n");
    printf("4. Mettre à jour un compte\n");
    printf("5. Suppression du compte\n");
    printf("6. Afficher les transactions\n");
    printf("7. Afficher les détails du compte\n");
    printf("8. Afficher la liste des clients\n");
    printf("Choisir le service que vous voudrez: ");
    scanf("%d", &a);

    Cpt* lstCpts = chrgCpts();

    switch (a) {
        case 1: {
            int n;
            char nm[50];
            double sld;
            printf("Entrez le numéro de compte: ");
            scanf("%d", &n);
            printf("Entrez le nom du titulaire: ");
            scanf("%s", nm);
            printf("Entrez le solde initial: ");
            scanf("%lf", &sld);

            Cpt* nCpt = crtCpt(n, nm, sld, "Client Inconnu");
            if (nCpt != NULL) {
                svCpt(nCpt);
            }
            break;
        }
        case 2: {
            int n;
            char t[20];
            double m;
            printf("Entrez le numéro de compte: ");
            scanf("%d", &n);
            printf("Entrez le type de transaction (D/R): ");
            scanf("%s", t);
            printf("Entrez le montant de la transaction: ");
            scanf("%lf", &m);

            Cpt* cpt = NULL;
            Clt* crnt = lstClt;
            while (crnt != NULL) {
                if (crnt->cpt->n == n) {
                    cpt = crnt->cpt;
                    break;
                }
                crnt = crnt->nxt;
            }

            if (cpt != NULL) {
                ajtTr(cpt, t, m, "Client Inconnu");
                svCpt(cpt);
            } else {
                printf("Le compte avec le numéro %d n'a pas été trouvé.\n", n);
            }
            break;
        }
        case 3: {
            int n;
            char t[20];
            double m;
            printf("Entrez le numéro de compte: ");
            scanf("%d", &n);
            printf("Entrez le type d'opération (D/R): ");
            scanf("%s", t);
            printf("Entrez le montant de l'opération: ");
            scanf("%lf", &m);

            Cpt* cpt = NULL;
            Clt* crnt = lstClt;
            while (crnt != NULL) {
                if (crnt->cpt->n == n) {
                    cpt = crnt->cpt;
                    break;
                }
                crnt = crnt->nxt;
            }

            if (cpt != NULL) {
                effctOp(cpt, t, m, "Client Inconnu");
                svCpt(cpt);
            } else {
                printf("Le compte avec le numéro %d n'a pas été trouvé.\n", n);
            }
            break;
        }
        case 4: {
            int n;
            char nn[50];
            double ns;
            printf("Entrez le numéro de compte à mettre à jour : ");
            scanf("%d", &n);

            Cpt* cpt = NULL;
            Clt* crnt = lstClt;
            while (crnt != NULL) {
                if (crnt->cpt->n == n) {
                    cpt = crnt->cpt;
                    break;
                }
                crnt = crnt->nxt;
            }

            if (cpt != NULL) {
                printf("Entrez le nouveau nom du titulaire : ");
                scanf("%s", nn);
                printf("Entrez le nouveau solde du compte : ");
                scanf("%lf", &ns);

                mAJCpt(cpt, nn, ns);
                svCpt(cpt);
            } else {
                printf("Le compte avec le numéro %d n'a pas été trouvé.\n", n);
            }
            break;
        }
        case 5: {
            int n;
            printf("Entrez le numéro de compte à supprimer : ");
            scanf("%d", &n);

            Cpt* cpt = NULL;
            Clt* crnt = lstClt;
            while (crnt != NULL) {
                if (crnt->cpt->n == n) {
                    cpt = crnt->cpt;
                    break;
                }
                crnt = crnt->nxt;
            }

            if (cpt != NULL) {
                spCpt(cpt);
            } else {
                printf("Le compte avec le numéro %d n'a pas été trouvé.\n", n);
            }
            break;
        }
        case 6: {
            int n;
            printf("Entrez le numéro de compte dont vous voulez afficher les transactions : ");
            scanf("%d", &n);

            Cpt* cpt = NULL;
            Clt* crnt = lstClt;
            while (crnt != NULL) {
                if (crnt->cpt->n == n) {
                    cpt = crnt->cpt;
                    break;
                }
                crnt = crnt->nxt;
            }

            if (cpt != NULL) {
                afTr(cpt);
            } else {
                printf("Le compte avec le numéro %d n'a pas été trouvé.\n", n);
            }
            break;
        }
        case 7: {
            int n;
            printf("Entrez le numéro de compte dont vous voulez afficher les détails : ");
            scanf("%d", &n);

            Cpt* cpt = NULL;
            Clt* crnt = lstClt;
            while (crnt != NULL) {
                if (crnt->cpt->n == n) {
                    cpt = crnt->cpt;
                    break;
                }
                crnt = crnt->nxt;
            }

            if (cpt != NULL) {
                afDtlsCpt(cpt);
            } else {
                printf("Le compte avec le numéro %d n'a pas été trouvé.\n", n);
            }
            break;
        }
        case 8:
            afLstClt();
            break;
        default:
            printf("Choix non valide.\n");
            break;
    }


    return 0;
}
