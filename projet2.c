#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//question 5) 

leaf* product_needs(int coeff,leaf *scope,leaf *Branch,article *head,article **list,int *check_realisable)
{
	leaf *p;
	int c;
	c= 0;
	p=NULL;

	if (scope->rightChild && scope->leftChild)
	{	
		c = article_calculation(coeff,scope->key,scope->quantite,head,list,check_realisable,1);//1 to notice that the article is a semi-final product

		if(c)
		{

			p=(product_needs(c,scope->leftChild,scope,head,list,check_realisable));
			if (p)
				product_needs(coeff,p->rightChild,Branch,head,list,check_realisable);	
		}
	

	}
	else if (scope->leftChild)
	{		
		c = article_calculation(coeff,scope->key,scope->quantite,head,list,check_realisable,1);
		if (c)
			product_needs(c,scope->leftChild,Branch,head,list,check_realisable);
		else
			return Branch;

	}
	else if (scope->rightChild)
	{	

		article_calculation(coeff,scope->key,scope->quantite,head,list,check_realisable,0);
		product_needs(coeff,scope->rightChild,Branch,head,list,check_realisable);
	}
	else 
	{
		article_calculation(coeff,scope->key,scope->quantite,head,list,check_realisable,0);
		return Branch;
	}	
}
leaf* getPlanDeProduction(void)
{
	char option[2],P[6],Q[6];
	leaf *production_plan,*pr;
	production_plan = NULL;
	pr = NULL;
	option[0]='x';
	while(strcasecmp(option,"f") && strcasecmp(option,"k"))
	{

		printf("\n---How would you set a production plan ?\n File or keyboard [F/K]\n");
		scanf("%1s",option);
		
	}
	if (!strcasecmp(option,"k"))
	{
		printf("\nKeybord method set\ntype your production plan: \nP1 Q1\n.. ..\nPn Qn\nType 'exit' to end the production plan\n");
		printf("\n>");
		scanf("%5s %5s",P,Q);
		while(strcasecmp(P,"exit"))
		{
			pr = make_leaf(P,Q);
			pr->rightChild = production_plan;
			production_plan = pr;
			printf("\n>");
			scanf("%5s %5s",P,Q);
		}
	}
	else if (!strcasecmp(option,"f"))
	{
		FILE *programme = fopen("programme.txt","r");
		fscanf(programme,"%5s %5s",P,Q);
		while(strcasecmp(P,"exit"))
		{
			pr = make_leaf(P,Q);
			pr->rightChild = production_plan;
			production_plan = pr;
			fscanf(programme,"%5s %5s",P,Q);
		}	
		fclose(programme);
	}
 return production_plan;
}
void production_plan(leaf *root,article *head)
{
	article *art ,*p;
	leaf *l,*pr,*plan;
	int check_realisable,quantite_en_stock,coeff;
	check_realisable = 1; //le plan de production est realisable
	quantite_en_stock = 0;
	coeff=1;
	art = NULL;l=NULL;pr=NULL;plan=NULL;p=NULL;
	l = getPlanDeProduction();
	plan = l; 
	while(plan)
	{
		pr = NULL;
		find_leaf(root,root,plan->key,&pr);
		if(pr)
		{
			sscanf(plan->quantite,"%i",&coeff);
			coeff = article_calculation(coeff,pr->key,"1",head,&art,&check_realisable,1);//verifier s'il existe du produit finit en stock
			product_needs(coeff,pr->leftChild,pr->leftChild,head,&art,&check_realisable);
		}

		plan=plan->rightChild;
	}
	if (check_realisable)
	{
		printf("\n------------------------------------------------\n");
		printf("\n  Votre programme de Production est realisable\n");
		printf("\n------------------------------------------------\n");
	}
	else
	{
		printf("\n_____________________________________________________________________________________\n");
		printf("\n  Votre programme de production est irrealisable avec les données de stock valable   \n");
		printf("  A fin de le realiser, veuiller completer les materiaux manquants lister si dessous \n");
		p = art;
		while(p)
		{
			sscanf(p->quantite_en_stock,"%i",&quantite_en_stock);
				if(quantite_en_stock < 0)	
					printf("\n\t%s\t%s\t%s\t%i",p->code,p->designation,p->prix_achat,-quantite_en_stock);
			p = p->next;
		}
		printf("\n\n");
		printf("\n_____________________________________________________________________________________\n");
	}
