Gestionnaire de Comptes Bancaires
Ce programme en C est un gestionnaire simple de comptes bancaires qui permet de créer des comptes, d'effectuer des transactions, de mettre à jour les informations des comptes, de supprimer des comptes, et d'afficher les détails des comptes et les transactions associées.

Structures de Données
1. Structure Tr (Transaction)
char t[20]: Type de transaction (par exemple, "D" pour dépôt, "R" pour retrait).
double m: Montant de la transaction.
struct Tr* s: Pointeur vers la transaction suivante.
2. Structure Cpt (Compte)
int n: Numéro du compte.
char nm[50]: Nom du titulaire du compte.
double sld: Solde du compte.
struct Tr* ts: Pointeur vers la liste des transactions associées au compte.
struct Cpt* nxt: Pointeur vers le compte suivant dans la liste.
3. Structure Clt (Client)
char nm[50]: Nom du client.
struct Cpt* cpt: Pointeur vers le premier compte du client.
struct Clt* nxt: Pointeur vers le client suivant dans la liste.
Fonctions
1. Cpt* crtCpt(int n, const char* nm, double sld, const char* nmClt)
Crée un nouveau compte avec les informations fournies.
Ajoute le compte à la liste des clients (lstClt).
2. void ajtTr(Cpt* cpt, const char* t, double m, const char* nmClt)
Ajoute une transaction au compte spécifié.
Affiche un message de confirmation.
3. void effctOp(Cpt* cpt, const char* t, double m, const char* nmClt)
Effectue une opération (dépôt ou retrait) sur le compte spécifié.
Affiche un message de confirmation ou d'erreur en cas de solde insuffisant.
4. void mAJCpt(Cpt* cpt, const char* nn, double ns)
Met à jour les informations du compte spécifié avec un nouveau nom et solde.
Affiche un message de confirmation.
5. void spCpt(Cpt* cpt)
Supprime le compte spécifié de la liste des clients.
Affiche un message de confirmation.
6. void afTr(Cpt* cpt)
Affiche la liste des transactions associées au compte spécifié.
7. void afDtlsCpt(Cpt* cpt)
Affiche les détails complets du compte spécifié, y compris les transactions.
8. void afLstClt()
Affiche la liste complète des clients avec les détails de leurs comptes.
9. void svCpt(Cpt* cpt)
Sauvegarde les informations du compte dans un fichier texte (cpts.txt).
10. Cpt* chrgCpts()
Charge les comptes à partir du fichier texte (cpts.txt).
Fonctionnalités Principales
Créer un Compte

Demande le numéro du compte, le nom du titulaire, et le solde initial.
Crée un nouveau compte et l'ajoute à la liste des clients.
Sauvegarde le compte dans le fichier cpts.txt.
Ajouter une Transaction

Demande le numéro du compte, le type de transaction (dépôt ou retrait), et le montant.
Ajoute la transaction au compte spécifié.
Affiche un message de confirmation.
Sauvegarde le compte mis à jour dans le fichier cpts.txt.
Effectuer une Opération

Demande le numéro du compte, le type d'opération (dépôt ou retrait), et le montant.
Effectue l'opération sur le compte spécifié.
Affiche un message de confirmation ou d'erreur en cas de solde insuffisant.
Sauvegarde le compte mis à jour dans le fichier cpts.txt.
Mettre à Jour un Compte

Demande le numéro du compte à mettre à jour.
Demande le nouveau nom du titulaire et le nouveau solde.
Met à jour les informations du compte spécifié.
Affiche un message de confirmation.
Sauvegarde le compte mis à jour dans le fichier cpts.txt.
Suppression du Compte

Demande le numéro du compte à supprimer.
Supprime le compte de la liste des clients.
Affiche un message de confirmation.
Afficher les Transactions

Demande le numéro du compte.
Affiche la liste des transactions associées au compte.
Afficher les Détails du Compte

Demande le numéro du compte.
Affiche les détails complets du compte, y compris les transactions.
Afficher la Liste des Clients

Affiche la liste complète des clients avec les détails de leurs comptes.
Utilisation du Programme
Exécutez le programme et choisissez l'option correspondant au service souhaité.
Suivez les instructions pour effectuer l'opération souhaitée.
Les données des comptes sont sauvegardées dans le fichier cpts.txt et peuvent être chargées au démarrage du programme.
Remarques
Les données sont stockées localement dans le fichier cpts.txt.
Les clients sont identifiés par leur nom, et les comptes sont identifiés par un numéro unique.
