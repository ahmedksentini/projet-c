#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct data4
{
    char code[5];
    char quantite[5];
};
typedef struct data4 DATA4;


struct arbre_pro
 {
    DATA4 d;
    struct arbre_pro *frere ;
    struct arbre_pro *fils ;
 };
typedef struct arbre_pro ARBRE_PRO ;

ARBRE_PRO *seek_noeud(ARBRE_PRO *racine,char code[5])
{
    ARBRE_PRO *p;
    if(!racine)
        return(NULL);
    if (strcmp(((racine->d).code),code)==0)
        return(racine);
    if (p=seek_noeud(racine->frere,code))
        return(p);
    return(seek_noeud(racine->fils,code));
}
int est_fils(ARBRE_PRO *racine,ARBRE_PRO *p)
{
    if (racine)
    {
        if (racine==p)
            return(1);
        return (est_fils(racine->frere,p));
    }
    return (0);
}
ARBRE_PRO *seek_pere(ARBRE_PRO *racine,ARBRE_PRO *p)
{
    ARBRE_PRO *pere;
    if (!racine) return(NULL);
    if (est_fils(racine->fils,p))
        return(racine);
    if (pere=seek_pere(racine->frere,p)) return(pere);
    return(seek_pere(racine->fils,p));
}
//les fonctions  d'insertion
void insert_article(ARTICLE **first,FILE * fp)
{
    char ligne [20];
    while(fgets(ligne,45,fp))
    {

           ARTICLE *p;
           p = (ARTICLE *) malloc(sizeof(ARTICLE));

          sscanf(ligne,"%5s %15s %5s %10s %5s %5s",((p->d).code),((p->d).designation),((p->d).code_famille),((p->d).prix_achat),((p->d).code_fournisseur),((p->d).quantite_en_stock));
           (p->next) = *first;
           *first = p;
    }
}

void insert_famile(FAMILLE **first,FILE * fp)
{
    char ligne [20];
    while(fgets(ligne,21,fp))
    {

           FAMILLE *p;
           p = (FAMILLE *) malloc(sizeof(FAMILLE));

          sscanf(ligne,"%5s %15s",((p->d).code),((p->d).designation));
           p->next = *first;
           *first = p;
    }
}

void insert_fournisseur(FOURNISSEUR **first,FILE * fp)
{
    char ligne[20];
    while(fgets(ligne,21,fp))
    {

           FOURNISSEUR *p;
           p = (FOURNISSEUR *) malloc(sizeof(FOURNISSEUR));

          sscanf(ligne,"%5s %15s",((p->d).code),((p->d).raison_sociale));
           (p->next) = *first;
           *first = p;
    }
}

void insert_procede (ARBRE_PRO **racine,FILE *fp)
{
    char ligne[20];
    char code[5];
    ARBRE_PRO *pere;
    while (fgets(ligne,20,fp))
    {
        ARBRE_PRO *p;
        p = (ARBRE_PRO *) malloc(sizeof(ARBRE_PRO));
        sscanf(ligne,"%5s %5s %5s",code,((p->d).code),((p->d).quantite));
        p->fils=NULL;
        p->frere=NULL;
        if ((pere=seek_noeud(*racine,code)))
        {
            (p->frere)=(pere->fils);
            (pere->fils)=p;
        }
        else
        {
            pere = (ARBRE_PRO *) malloc(sizeof(ARBRE_PRO));
            strcpy(((pere->d).code),code);
            strcpy(((pere->d).quantite),"1");
            (pere->fils)=p;
            (pere->frere)=*racine;
            *racine=pere;
        }

    }
}

void view_arbre(ARBRE_PRO *racine)
{
    if(racine)
    {
        puts ("*********");
        view_arbre(racine->frere) ;

        view_arbre(racine->fils);

          puts(racine->d.code);
          puts(racine->d.quantite);
    }
}
/*/
//fonctions pour afficher  un produit donner 1)
int affiche_produit(ARBRE_PRO *racine)
{
    if (!racine)
        return(0);
    if (racine->fils)
    {
        affiche(racine);
        affiche_produit(racine->fils);
        affiche_produit(racine->frere);
    }
}

int affiche(ARBRE_PRO *racine)
{
    char code[5];
    strcpy(code,((racine->d).code));
    return(print_ligne(code,(racine->fils)));

}
int print_ligne(char code[5],ARBRE_PRO *fils)
{
    if (fils)
    {
        printf("%s %s %s\n",code,((fils->d).code),((fils->d).quantite));
        print_ligne(code,fils->frere);
        return(1);
    }
    return(0);
}

//2)

/*/
// fonction open file
int open_files(FILE **fp_art,FILE **fp_fam,FILE **fp_fou,FILE **fp_pro)
{



/*/
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
if (!( fp_fou = fopen("fourni.txt","r")))
   {
    printf("le fichier fournisseur.txt n'existe pas") ;
    return (0) ;
   }/*/
if (!((*fp_pro)=fopen("procede.txt","r")))
   {
    printf("le fichier procede.txt n'existe pas") ;
    return (0) ;
   }
   return(1) ;
   }

//fonction copy

void copy_arbre(ARBRE_PRO* in ,ARBRE_PRO** out)
{
   if(in)
{     (*out) =(ARBRE_PRO*)malloc(sizeof(ARBRE_PRO));


       strcpy ((*out)->d.code,in->d.code);
        strcpy ((*out)->d.quantite,in->d.quantite);
       copy_arbre(in->frere,&((*out)->frere)) ;
       copy_arbre(in->fils,&((*out)->fils)) ;

   }
}
int main ()
{
    ARBRE_PRO *racine=NULL;
    FILE *fp_art, *fp_fam, *fp_fou, *fp_pro ;

if (!open_files(&fp_art,&fp_fam,&fp_fou,&fp_pro))
    return (0);
insert_procede (&racine,fp_pro);
 view_arbre(racine);



}



