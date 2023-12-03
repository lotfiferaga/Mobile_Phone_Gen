## Présentation de la structure de donnée utilisée 
STRUCTURE DES NUMEROS FAVORIS
```C
struct nfav
{
char num [1000];
char nom [1000];
struct nfav *suivant;
};
// STRUCTURE DES ABONNES
struct abonne
{
char nomm [1000];
char prenom [1000];
char numero [1000];
char operateur [1000];
char profile[1000];
int credit;
int nfavo;
struct nfav *favo;
};
```

## I. La première structure est ‘nfav’ : 
utilisée pour la sauvegarde des numéros favoris et les
contacts favoris introduisez par l’utilisateur selon l’opérateur réseau choisi. Cette structure
représente le maillon de liste des favoris. Chaque maillon contient le nom et le numéro qui
sont introduit en chaine de caractère. ‘suivant’ est un pointeur vers le maillon suivant pour
le chainage des maillons des favoris.

## II. La deuxième structure est ‘abonne’ : utilisée pour les données de l’abonné selon
l’opérateur choisi dont est inclus les champs suivants :
 ‘nomm’ chaine de caractère pour le nom de l’abonné.
 ‘prenom’ pour le prénom de l’abonné.
 ‘numero’ pour le numéro de l’abonné ce qui est nécessaire pour la connexion au
compte et pour effectuer les opérations sur la liste des favoris ‘lister, supprimer,
ajouter, modifier…etc’
 Les deux champs ‘operateur’ et ‘profile’ est pour le choix d’opérateur réseau et le
profil dont l’utilisateur est abonné au.
 Le champ ‘credit ‘ et pour le balance de l’abonné exprimé en DA.
 ‘nfavo’ est déclaré pour contenir le nombre de favoris que chaque abonné possède.
 ‘favo’ est un pointeur vers la première structure des numéros favoris pour la liaison
entre l’abonné et ses contacts favoris.

# Présentation de la machine abstraite après la
modélisation
/** machine abstraite **/
```C
struct nfav *allouer() //allocation mémoire d’un maillon
{
return ((struct nfav *)malloc(sizeof(struct nfav)));
}
struct nfav *suivant(struct nfav *p)
{
return p-&gt;suivant;
}
void affadr(struct nfav *p,struct nfav *q)
{
p-&gt;suivant=q;
}
void affnumero(struct nfav *p, char n[20]) // affecte un numero au abonné(e)
{
strcpy(p-&gt;nom,n);
}
void affnom(struct nfav *p,char n [20]) //affecte un nom au abonné(e)
{
strcpy(p-&gt;nom,n);
}

char *nom(struct nfav *p) // pour la lecture du nom de favori
{
return(p-&gt;nom);
}
char *numero(struct nfav *p) // pour la lecture du numéro favori
{

return(p-&gt;num);
}
```
