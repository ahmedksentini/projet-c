#include <stdio.h>
#include <stdlib.h>

struct data1
{
    char code[5];
    char designation[15];
    char code_famille[5];
    char prix_achat[10];
    char code_fournisseur[5];
    char quantite_en_stock[5];
};
typedef struct data1 DATA1;

struct article
{
    DATA1 d;
    struct article *next;
};
typedef struct article ARTICLE;

struct data2
{
    char code[5];
    char designation[15];
};
typedef struct data2 DATA2;

struct famille
{
    DATA2 d;
    struct famille *next;
};
typedef struct famille FAMILLE;

struct data3
{
    char code[5];
    char raison_sociale[15];
};
typedef struct data3 DATA3;

struct fournisseur
{
   DATA3 d;
   struct fournisseur *next;
};
typedef struct fournisseur FOURNISSEUR;

struct arbre_pro
 {
     char d[5] ;
     struct arbre *frere ;
     struct arbre *fils ;

 };
typedef struct arbe_pro ARBRE_PRO ;

//les fonctions  d'insertion
void insert_article(ARTICLE **first, char *ligne,FILE * fp)
{
    while(fgets(ligne,45,fp))
    {

           ARTICLE *p;
           p = (ARTICLE *) malloc(sizeof(ARTICLE));

          sscanf(ligne,"%5c %15c %5c %10c %5c %5c",&p->d.code,&p->d.designation,&p->d.code_famille,&p->d.prix_achat,&p->d.code_fournisseur,&p->d.quantite_en_stock);
           p->next = *first;
           *first = p;
    }
}

void insert_famile(FAMILLE **first, char *ligne,FILE * fp)
{
    while(fgets(ligne,21,fp))
    {

           FAMILLE *p;
           p = (FAMILLE *) malloc(sizeof(FAMILLE));

          sscanf(ligne,"%5c %15c",&p->d.code,&p->d.designation);
           p->next = *first;
           *first = p;
    }
}

void insert_fournisseur(FOURNISSEUR **first, char *ligne,FILE * fp)
{
    while(fgets(ligne,21,fp))
    {

           FOURNISSEUR *p;
           p = (FOURNISSEUR *) malloc(sizeof(FOURNISSEUR));

          sscanf(ligne,"%5c %15c",&p->d.code,&p->d.raison_sociale );
           p->next = *first;
           *first = p;
    }
}

void insert_procede (ARBRE_PRO **racine,char *ligne,FILE *fp )
{
    while (fgets(ligne,17,fp))
    {
        ARBRE_PRO *p ;
         p = (ARBRE_PRO *) malloc(sizeof(ARBRE_PRO));
        sscanf(ligne,"%5c %5c %5c",&p->d,&p->fils,&(p->fils)->fils);
        p->frere =*racine ;
        *racine = p ;

    }
}
//fonctions pour afficher  un produit donner 1)
void affiche_produit(ARBRE_PRO *racine,char *code )
{
    if (racine)
    {
        if (racine->d==code) affiche(racine) ;
        affiche_produit(racine->frere,code);
    }
}
void affiche(ARBRE_PRO *racine)
{
    if (racine)
    {
        printf ("%s",racine->d) ;
         printf ("%s",racine->fils) ;
          printf ("%s",(racine->fils)->fils) ;
    }
}


//2)


// fonction open file
int open_files(fp_art,fp_fam,fp_fou_fp_pro)
{


FILE *fp_art, *fp_fam, *fp_fou, *fp_pro ;

 if (!(fp_art=fopen("aricle.txt","r")))
   {
    printf("le fichier article.txt n'existe pas") ;
    return (0) ;
   }
if (!(fp_fam=fopen("famille.txt","r")))
   {
    printf("le fichier famille.txt n'existe pas") ;
    return (0) ;
   }
if (!( fp_fournisseurr = fopen("fourni.txt","r")))
   {
    printf("le fichier fournisseur.txt n'existe pas") ;
    return (0) ;
   }
if (!(fp_pro=fopen("procede.txt","r")))
   {
    printf("le fichier procede.txt n'existe pas") ;
    return (0) ;
   }
   return(1) ;
   }
int main ()
{
    FILE *fp_art, *fp_fam, *fp_fou, *fp_pro ;

if (!open_files(fp_art,fp_fam,fp_fou,fp_pro))
    return (0);




}
