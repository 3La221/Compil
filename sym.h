#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Ajout de cet en-tête pour utiliser la fonction strcpy
#include <stdbool.h> // Ajout de cet en-tête pour utiliser le type de donnees bool

// la Table de identificateurs
  
typedef struct element1 {
    int state;
    char name[20];
    char code[20];
    char type[20];
    struct element1* svt;
    char value[20];  
} identificateur;
typedef identificateur* idf;

//la table des motcles

typedef struct element2 {
    int state;
    char name[20];
    char code[20];
    struct element2* svt;  
} motCle;
typedef motCle* motc; 

// la table des separateurs

typedef struct element3 {
    int state;
    char name[20];
    char code[20];
    struct element3* svt;  
} separateur;
typedef separateur* separ; 

// la table des operateursLogique

typedef struct element4 {
    int state;
    char name[20];
    char code[20];
    struct element4* svt;  
} operateur;
typedef operateur* oper; 

// la table des operateursArithmetique
typedef struct element5 {
    int state;
    char name[20];
    char code[20];  
    struct element5* svt;  
} operAr;
typedef operAr* operar; 

// table des constants
typedef struct element6 {
    int state;
    char name[20];
    char code[20];
    char type[20];
    struct element6* svt;  
} Constant;
typedef Constant* cst;

typedef struct element7{
 char valeur[20];  
 char type[20]; 
 struct element7* svt; 
}Declaration;
typedef Declaration* dec;

idf listIDF;
motc listMotCLe;
separ listSepar;
oper listOperLog;
operar listOperAr;
cst listCst;
dec listDec;
extern char sav[20];



void AjouterDec(char identificateur[],char type[]) {
    dec nouveaudec = (dec)malloc(sizeof(Declaration));
    if (nouveaudec == NULL) {
        fprintf(stderr, "Erreur d'allocation de memoire pour l'element declarer a echouer.\n");
        exit(EXIT_FAILURE);
    }
    nouveaudec->svt = NULL; 
        strcpy(nouveaudec->valeur, identificateur);
        strcpy(nouveaudec->type,type);
        nouveaudec->svt = listDec;
        listDec = nouveaudec;
}





 void insererType(char Nentite[], char type[]) {
    idf courantIdf = listIDF;
    motc courantMots = listMotCLe;
   while(strcmp(courantIdf->name,Nentite)!=0){
    courantIdf=courantIdf->svt;
   }
   while(strcmp(courantMots->name,type)!=0){
    courantMots=courantMots->svt;
   }
   if(courantIdf !=NULL && courantMots != NULL){
    AjouterDec(Nentite,type);
    strcpy(courantIdf->type,courantMots->name);
   }
    // Recherche de l'entité dans la table des identificateurs (IDF) 
}
 void insererTypeChain(char Nentite[],char mul[]) {
    idf courantIdf = listIDF;
   while(strcmp(courantIdf->name,Nentite)!=0){
    courantIdf=courantIdf->svt;
   }
   if (courantIdf!=NULL && mul == "*") {
     AjouterDec(Nentite,"Chaine");
    strcpy(courantIdf->type,"Chaine");
   }
   }
   
    // Recherche de l'entité dans la table des identificateurs (IDF)
   




void verifierDoubleDeclaration(char Nentite[]) {
  idf courantIdf =listIDF;
  dec courantDec =listDec;
  int cpt = 0;
  while (courantIdf!=NULL && strcmp(courantIdf->name,Nentite)!=0) {
    courantIdf=courantIdf->svt;
}
while(courantDec!=NULL && strcmp(courantDec->valeur,Nentite)==0){
courantDec=courantDec->svt;
cpt=cpt+1;
}
if( cpt>1){
    printf("ERREUR SYMENTIQUE DOUBLE DECLARATION!!!!!!!!!!!!!!\n");
}else{
printf("TOUT EST BIEN!!!!!!!!!!!\n");
}
}

int verifierDeclaration(char entite[]){
dec pointeur = listDec;
int cpt = 0;
while(pointeur != NULL){
if(strcmp(pointeur->valeur,entite)==0){
    cpt++;
}
pointeur=pointeur->svt;
}
if(cpt>0){
    printf("ERREUR SYMENTIQUE IDF NON DECLARER!!!!!");
    return 0;
} else {
    return 1;
}
}

void verifierCompaBool(char entite[], int Bool){
    idf pointeur = listIDF;
    int check =verifierDeclaration(entite);
    if(check == 1){
        while(strcmp(pointeur->name,entite)!=0){
            pointeur=pointeur->svt;
        }
        if(pointeur!=NULL){
      if(strcmp(pointeur->type,"LOGICAL")==0){
        printf("COMPATIBLE SANS PROBLEME§§§§§§§\n");
      }else {
        printf("ERREUR SYMENTIQUE INCOMPATIBLE!!!!! \n");
      }
    } else {
        printf("ELEMENT NON TROUVER!!!!\n");
    }
    }else{
        printf("!!!!!!!!!!!ELEMENT NON DECLARER!!!!!!!!!!!\n");
    }
}

void InserValChaine(char Nentit[] , char Val[]){
    idf courantIdf =listIDF;
    cst courantCst =listCst;
    int check =verifierDeclaration(Nentit);
    while(courantIdf!=NULL && strcmp(courantIdf->name,Nentit)!=0){
        courantIdf=courantIdf->svt;
    }
    while(courantCst!=NULL && strcmp(courantCst->name,Val)!=0){
        courantCst=courantCst->svt;
    }
    if(courantCst!=NULL && courantIdf!=NULL){
        if(check ==1){
strcpy(courantIdf->value,courantCst->name);
        } else{
            printf("ENTITE NON DECLARER");
        }
        
    }
}

void InserValBool(char Nentit[] , int Val){
    idf courantIdf =listIDF;
    cst courantCst =listCst;
    int check =verifierDeclaration(Nentit);

    if (check == 1) {
    if(Val == 1 ){
       while(courantIdf!=NULL && strcmp(courantIdf->name,Nentit)!=0){
        courantIdf=courantIdf->svt;
    }
    if (courantIdf!=NULL){
        strcpy(courantIdf->value, "TRUE");
    }
    } 
    
    else {
       while(courantIdf!=NULL && strcmp(courantIdf->name,Nentit)!=0){
        courantIdf=courantIdf->svt;
    }
    if (courantIdf!=NULL){
        strcpy(courantIdf->value, "FALSE");
    }
    }
    }else {
        printf("element non declarée\n");
    }
}

void inser(char entite[], char code[], char type[], char val[], int i) {
           cst nouveaucst = (cst)malloc(sizeof(Constant));
                if (nouveaucst == NULL) {
                    fprintf(stderr, "Erreur d'allocation de memoire pour operateur.\n");
                    exit(EXIT_FAILURE);
                }
                nouveaucst->state = 1;
                strcpy(nouveaucst->name, entite);
                strcpy(nouveaucst->code, code);
                strcpy(nouveaucst->type, type);

                // Ajouter nouveauOper a la listeOper
                nouveaucst->svt = listCst;
                listCst = nouveaucst;
}


void chercher(char entite[], char code[], char type[], char val[]) {
       cst courant = listCst;
                while (courant != NULL && strcmp(entite, courant->name) != 0) {
                    courant = courant->svt;
                }

                if (courant == NULL) {
                    // L'entite n'existe pas, on l'ajoute a la liste
                    inser(entite, code, type, val, 0);
                } else {
                    printf("L'entite existe deja.\n");
                }
}



// un liste qui comport les noms des focntion chaque nom de focntion comport sec declarations
