// ON DEFINIT LE TYPE BOOLEAN "VRAI" et "FAUX"
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define NULL 0
typedef struct _iobuf FILE;
enum boolean {true,false};
typedef enum boolean boolean;
// STRUCTURE DES NUMEROS FAVORIS
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
/** machine abstraite **/
struct nfav *allouer()
{
    return ((struct nfav *)malloc(sizeof(struct nfav)));
};

struct nfav *suivant(struct nfav *p)
{
  return p->suivant;
};

void affadr(struct nfav *p,struct nfav *q)
{
    p->suivant=q;
}

void affnumero(struct nfav *p, char n[20])
{
    strcpy(p->nom,n);
}

void affnom(struct nfav *p,char n [20]) //affecte un nom au client
{
strcpy(p->nom,n);
}
char *nom(struct nfav *p)
{
    return(p->nom);
}

char *numero(struct nfav *p)
{
   return(p->num);
}
/** pour verifier le credit (balance) du client est suffisant ou pas  **/
boolean balance(struct abonne abo)
{
    boolean suffisant;
    suffisant=false;
    if(abo.credit>=50)suffisant=true;
    return suffisant;
}

boolean numero_client(char per[1000],char s[1000])
{
   boolean id=false;
   if(strcmp(per,s)==0)id=true;
   return id;
}

/** calcule le nombre des favoris restants **/
int frestant(struct abonne abo)
{
    int r;
    r=0;
    if ((strcmp(abo.profile,"M'heni")==0)||(strcmp(abo.profile,"Gosto")==0)||(strcmp(abo.profile,"Line 1200")==0)||(strcmp(abo.profile,"Family")==0)) r=4-abo.nfavo;
    else if((strcmp(abo.profile,"Prix 3g")==0)||(strcmp(abo.profile,"Plus")==0)) r=2-abo.nfavo;
    return r;
}
/** la verificationt du max des numéros favoris **/
boolean maxfav(struct abonne abo)
{
    boolean max;
    max=false;
    if(frestant(abo)==0)max=true;
    return max;
}

void effacer(char *f)
{
    int l;
    l=1;
    int s;
    while(f[0]==' ')
    {
        s=1;
        while(s<=strlen(f))
        {
            f[s-1]=f[s];
            s++;
        }
    }
    while(l<=strlen(f))
    {
        if((f[l-1]==' ')&&(f[l]==' ')) f[l-1]='\0';else l++;
    }
}

boolean existe(struct nfav *tete,char numo[1000])
{
    boolean ex=false;
    struct nfav *exo;
    exo=tete;
    while ((exo!=NULL)&&(ex==false))
    {
        if(strcmp((exo->num),numo)==0)ex=true;
        exo=suivant(exo);
    };
    return ex;
}
/** vérification des droits de service favoris **/
int droitfav(struct abonne abo)
{
    char d[1000];
    int droit;
    droit=0;
    strcpy(d,abo.profile);
    effacer(d);
    if((strcmp(abo.profile,"M'heni")==0)||(strcmp(abo.profile,"Gosto")==0)||(strcmp(abo.profile,"Line 1200")==0)||(strcmp(abo.profile,"Family")==0)||(strcmp(abo.profile,"Prix 3g")==0)||(strcmp(abo.profile,"Plus")==0)) droit=1;
    return droit;
}
/** procédure génératrice des numéro aléatoire selon chaque service réseaux **/
void genere_numero(int reseau,char numero[100])
{
    int r,f,d;
    int z;


    d=rand()%60+1;
    z=rand()%90+1;
    f=rand()%90+1;
    r=rand()%90+1;
    if (d<10) d=d*10;
    if (f<10) f=f*10;
    if (z<10) z=z*10;
    if (r<10) r=r*10;

   if      (reseau==0){sprintf(numero,"06 %d %d %d %d",z,f,d,r);}
   else if (reseau==1){sprintf(numero,"07 %d %d %d %d",z,f,d,r);}
   else if (reseau==2){sprintf(numero,"05 %d %d %d %d",z,f,d,r);};
}

void recherche(struct nfav *tete,char t[5000],struct nfav **po,struct nfav **prec)
{
    *prec=NULL;
    *po=tete;
    while ((*po!=NULL)&&(strcmp(numero(*po),t)!=0))
    {
        *prec=*po;
        *po=suivant(*po);
    }
}
// LE FCHIER CONTIENT LES DONNEES DES ABONNES
/** utilisation du fichier pour le sauvegarde des clients **/
void sauvgarde(struct abonne abo)
{
    FILE* fichier=NULL;
    struct nfav *favor=abo.favo;
    int cp=0;
    fichier=fopen("abonne.txt","r+");
    if (fichier!=NULL)
    {
        fseek(fichier,0,SEEK_END);
        fprintf(fichier,"%-20s|%-20s|%-20s|%-20s|%-20s|%-20d|%20d|",abo.numero,abo.nomm,abo.prenom,abo.operateur,abo.profile,abo.credit,abo.nfavo);
        for(cp=0;cp<4;cp++)
        {
            if(favor!=NULL)
            {
                fprintf(fichier,"%-20s|%-20s|",nom(favor),numero(favor));
                favor=suivant(favor);
            } else { fprintf(fichier,"%-20s|%-20s|","vide","vide");}

        }
        fprintf(fichier,"\n"," ");
        fclose(fichier);
    }
    else
    {
        printf("il y a un problem dans le fichier 'abonne.txt'.");
    }

}

/** module pour recuperer  les abonnés **/
int recup(struct abonne *abo,char *numero)
{
    FILE *fichier=NULL;
    char tab[1000];
    int k,m=0,comp;
    struct nfav *p,*q;

    int trouv;
    (*abo).favo=NULL;
    fichier=fopen("abonne.txt","r+");
    if (fichier!=NULL)
    {
        rewind(fichier);
        while ((comp)&&(trouv==0))
        {
            fseek(fichier,m,SEEK_SET);
            comp=fgets(tab,20,fichier);
            if (strcmp(numero,tab)==0)
            {
                trouv=1;
            } else if (comp==0)
            {
            printf("le numero que vous etes entraine de chercher est erronee ");
            }
        }
        fseek(fichier,m,SEEK_SET);
        if (trouv)
             {
                fgets((*abo).numero,20,fichier);
                fseek(fichier,2,SEEK_CUR);
                fgets((*abo).nomm,20,fichier);
                fseek(fichier,2,SEEK_CUR);
                fgets((*abo).prenom,20,fichier);
                fseek(fichier,2,SEEK_CUR);
                fgets((*abo).profile,20,fichier);
                fseek(fichier,2,SEEK_CUR);
                fgets((*abo).operateur,20,fichier);
                fgets(tab,20,fichier);
                (*abo).credit=strtol(tab,NULL,20);
                fseek(fichier,2,SEEK_CUR);
                (*abo).nfavo=strtol(tab,NULL,20);
                // pour récupérer les données des abonnés du fichier "abonnee.txt"
                if (((*abo).nfavo)!=0)
                       {
                           q=allouer();
                           (*abo).favo=q;
                              for (k=0;k<((*abo).nfavo);k++)
                                    {
                                       p=q;
                                       fseek(fichier,2,SEEK_CUR);
                                       fgets(p->nom,20,fichier);
                                       fseek(fichier,2,SEEK_CUR);
                                       fgets(p->num,20,fichier);
                                       q=allouer();
                                       affadr(p,q);
                                    }
                                       affadr(p,NULL);
                       }
             }
             fclose(fichier);
    } else printf("il y a un problem dans le fichier 'abonne.txt' \n " );
 return trouv;
}
/** Module de modification des utilisateurs déja inscrit **/
void modifier(struct abonne abo)
{
    FILE *fichier=NULL;
    int t;
    char tab[1000];
    int echo,sau;
    t=0;
    struct nfav *p=abo.favo;
    sau=0;

    fichier=fopen("abonne.txt","r+");
    if (fichier!=NULL)
           {
             rewind(fichier);
             while((echo)&&(sau==0))
                   {
                      fseek(fichier,t,SEEK_SET);
                      echo=fgets(tab,20,fichier);
                      if (strcmp(abo.numero,tab)==0)
                         {
                           sau=1;
                         } else if(echo==0) {printf("ERREUR CE NUMERO EST ERRONE \n ");};
                   }
                   fseek(fichier,t,SEEK_SET);
                   fprintf(fichier,"%-20s|%-20s|%-20s|%-20s|%-20s|%-20d|%20d|",abo.numero,abo.nomm,abo.prenom,abo.operateur,abo.profile,abo.credit,abo.nfavo);
                    for(t=0;t<4;t++)
                    {
                        if(p!=NULL)
                        {
                            fprintf(fichier,"%-20s|%-20s|",nom(p),numero(p));
                            p=suivant(p);
                        } else fprintf(fichier,"%-20s|%-20|","VIDE","VIDE");

                    } fclose(fichier);
           } else printf("ERREUR IL Y A UN PROBLEME DANS LE FICHIER 'abonne.txt' ");

}

/** recherche du numéro favoris **/
void favoris(struct abonne abo,int a,char *res)
{
    int l;
    struct nfav *p=abo.favo;
    l=0;
    do
    {
        p=suivant(p);
        l++;
    }while((l<a)&&(p!=NULL)) ;
    if (p==NULL)
    {
        printf("Ce numéro n'est pas dans la liste des favoris");
    }else strcpy(res,numero(p));
}
/** les grands modules **/
//CREATION DU COMPTE
void sign_up()
{
    struct abonne abo;
    int opr;
    char nom[1000]; char prenom[1000];
    printf("Entrez votre nom\n");
    scanf("%s",&nom);
    printf("Entrez votre prenom\n");
    scanf("%s",&prenom);
    strcpy(abo.nomm,nom);
    strcpy(abo.prenom,prenom);
    genere_numero(0,(abo.numero));
    abo.credit=450;
    abo.nfavo=0;
    abo.favo=NULL;
    sauvgarde(abo);
    printf("Votre numero est %s : \n",(abo.numero));
    printf("Votre balance est de :%d DA \n",(abo.credit));
    printf("Creation du compte termine \n");
    printf("Utiliser votre numero pour se connecter au compte \n");

}
/** les modules de manipulation des listes des numéros favoris  **/
// le parcour des numéros favoris
void lister(struct nfav *tete)
{
    struct nfav *p;
    p=tete;

    if(p==NULL) printf("il y a aucun numero dans votre liste \n");
    while(p!=NULL)
    {
        printf("%s",nom(p));
        printf("%s",numero(p));
        p=suivant(p);

    }
}

void ajouter(struct abonne *abo,int r)
{
    char nom[1000];
    char numero[1000];
    char t[1000];
    struct nfav *p,*q,*pointeur;
    struct nfav **tete=&((*abo).favo);
    if((maxfav(*abo)==false)&&(balance(*abo)==true))
    {
        printf("Entrez le numero pour l'ajouter a votre favoris");
        scanf("%s",&numero);
    }
    if ((existe(*tete,numero)==false)&&(maxfav(*abo)==false)&&(numero_client((*abo).numero,numero)==false)&&(balance(*abo)==true))
    {
        printf("Entrez le nom du nouveau favori : \n");
        scanf("%s",&nom);
        printf("Cette operation coute 50 DA");
        (*abo).credit-=50;
        pointeur=*tete;
        q=NULL;
        while(pointeur!=NULL)
        {
            q=pointeur;
            pointeur=suivant(pointeur);
        }
     if((pointeur==NULL)&&(q==NULL))
     {
        p=allouer();
        affnumero(p,numero);
        affnom(p,nom);
        *tete=p;
        affadr(p,q);
        ((*abo).favo)=*tete;
     }
     else
     {
         p=allouer();
         affnumero(p,numero);
         affnom(p,nom);
         affadr(q,p);
         affadr(p,NULL);
     }
     (*abo).nfavo++;
      printf("vous avez ajouter un numero avec sucess \n");
      modifier(*abo);
    } else if (existe(*tete,numero)==true)
      {
          printf("le numero existe deja \n");
      }
      else if (maxfav(*abo)==true)
      {
          printf("le nombre max des numero favoris est atteint \n");
      }
      else if (numero_client((*abo).numero,numero)==true)
      {
          printf("c'est votre numero vous ne pouvez pas l'ajouter aux favoris \n");

      }
      else if (balance((*abo)==false))
               {
                   printf("votre balance est inferieure pour l'ajout \n");

               }

}

void supprimer(struct abonne *abo)
{
    struct nfav **tete=&((*abo).favo);
    struct nfav *pointeur,*p;
    pointeur=*tete;
    int c;
    char numero[1000];
    p=NULL;
    if((*abo).nfavo>0)
    {
       lister((*abo).favo);
       printf("choisir le numero a supprimer \n");
       favoris(*abo,c,numero);
       (*abo).nfavo--;
       if (existe(*tete,numero)==true)
       {
           recherche(*tete,numero,&pointeur,&p);
           if(pointeur==*tete)
           {
               *tete=suivant(pointeur);

           }
           else
           {
               affadr(p,suivant(pointeur));
           }

       } else {printf("ce numero n'existe plus \n");}
       modifier(*abo);

    } else {printf("la liste des favoris est vide \n");}

}
// module modifier le numero favori
void mod(struct abonne *abo,int o)
{
    struct nfav *pointeur,*p;
    char mo[1000];
    char numero[1000];
    char nom[1000];
    char m[1000];
    int c;
    struct nfav *tete=(*abo).favo;
    strcpy(numero,(*abo).numero);
    while((*abo).credit>50)
    {
    if ((*abo).nfavo<1)
    {
        printf("la liste des favoris est vide , donc on peut pas faire des modification \n");
    } else if ((*abo).credit<50)
      {
        printf("votre balance est au niveau bas \n ");
      } else
      {
          lister((*abo).favo);
          printf("fait le choix du favoris pour le modifier \n");
          printf("nom \n");
          scanf("%s",&nom);
          printf("numero \n");
          scanf("%s",&numero);
          favoris(*abo,c,numero);
          if ((existe(tete,mo)==true)&&(strcmp(numero,mo)!=0))
          {
            printf("ce numero existe \n");
          } else if ((existe(tete,numero)==true)&&(numero_client(m,mo)==false))
          {
             recherche(tete,numero,&pointeur,&p);
             affnumero(pointeur,mo);
             affnom(pointeur,nom);
             (*abo).credit-=50;
             modifier(*abo);
          }
        else if (numero_client(m,mo)==true)
         {
          printf("c'est votre numero -_- \n ");
         }
      }
    }
}
// la gestion du compte
void compte(struct abonne *abo,int o)
{
    printf("Entrez le nombre  '100' pour modifier votre nom, '200' pour modifier le prenom , '300' pour un changement du profil \n");
    int mot;
    char nom[1000];
    char prenom[1000];
    char profil[1000];
    printf("SVP decidez-vous la modification a effectuer ! et entrez le nombre : \n");
    scanf("%s",&mot);
    switch(mot)
    {
    case 100:
        printf("Entrez le nouveau 'nom' : \n");
        scanf("%s",&nom);
        strcpy((*abo).nomm,nom);
        modifier(*abo);
        break;
    case 200:
        printf("Entrez le nouveau 'prenom' : \n");
        scanf("%s",&prenom);
        strcpy((*abo).prenom,prenom);
        modifier(*abo);
    case 300:
    if (balance(*abo)==false)
    {
        printf("votre balance est au niveau bas  \n");
    } else
        {
            if ((*abo).nfavo>0)
            {
                printf("cette operation coute 50DA \n ");
            }
            printf("Choix du nouveau profil \n ");
            (*abo).credit-=50;
            strcpy((*abo).profile,profil);
            (*abo).nfavo=0;
            (*abo).favo=NULL;
            modifier(*abo);
            recup(abo,(*abo).numero);
        }

    }

}

