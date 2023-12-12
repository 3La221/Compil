%{
    #include <stdio.h>
    int yywrap(void);
    int yylex(void);
    int yyerror ( char*  msg )  ;
    void initialisation(); 
    void afficher();
    extern int col ; 
    extern int nb_ligne ;
    char* file_name = NULL;
FILE* yyin;
%}



%token mc_prog mc_end mc_routine mc_endr mc_read mc_write mc_if mc_then mc_else mc_endif mc_dowhile mc_enddo mc_equivalence type OPR mul mc_call idf cst aff pvg vig po pf  mc_err mc_reel cst_chaine mc_dimension mc_true 
mc_false  tabl moin plus divsep   pt 

%%
S : ROUTINES  {
    printf("\n --------------------------- \n");
    printf("\n Compilation reussie ! Le programme est bien forme.\n");
    printf("\n --------------------------- \n");
    YYACCEPT;
}


ROUTINES : type mc_routine idf po idf ARGS pf  DECROUTINE mc_endr ROUTINES  
| PROG



ARGS : vig idf  ARGS 
| 





    

    
DECROUTINE: type idf ARGS pvg DECROUTINE 
              | type idf mul cst  pvg DECROUTINE 
              | type idf mc_dimension po cst pf pvg DECROUTINE 
              | type idf mc_dimension po cst vig cst pf pvg DECROUTINE 
              | INSTROUTINE

INSTROUTINE : INSTES INSTROUTINE
| INSTDOWHILE INSTROUTINE
| INSTIF INSTROUTINE
| INSTEQ INSTROUTINE
| INSTCALL INSTROUTINE
| INSTAFF INSTROUTINE
| idf aff cst
| idf aff mc_true
| idf aff mc_false
| idf aff mc_reel
| idf aff cst_chaine
| idf aff tabl
| idf aff idf 


PROG : mc_prog idf DEC mc_end

DEC:  type idf ARGS pvg DEC  
            | type idf mul cst  pvg DEC 
            | type idf mc_dimension po cst pf pvg DEC  
            | type idf mc_dimension po cst vig cst pf pvg DEC 
            | INST

             
INST: INSTES INST
| INSTDOWHILE INST
| INSTIF INST
| INSTEQ INST
| INSTAFF INST
| INSTCALL INST
|


INSTAFF : idf aff EXP pvg 
| idf aff mc_false pvg 
| idf aff mc_true pvg 
| idf aff cst_chaine pvg 





INSTES : mc_read po idf pf pvg 
| mc_write po SMT pf pvg 

SMT : idf vig SMT
| cst_chaine vig SMT
| idf
| cst_chaine

INSTDOWHILE: mc_dowhile po LOGIC_EXP pf INST mc_enddo pvg 

INSTIF : mc_if po LOGIC_EXP pf mc_then INST mc_else INST mc_endif pvg 
| mc_if po LOGIC_EXP pf mc_then INST mc_endif pvg 


INSTEQ : mc_equivalence po idf EQARGS pf vig po idf EQARGS pf pvg

EQARGS: vig idf EQARGS
| vig tabl EQARGS
| vig idf
| vig tabl


INSTCALL : idf aff mc_call idf po CALLARGS pf pvg

CALLARGS : idf vig   CALLARGS
| DATA vig   CALLARGS
| idf 
| DATA

LOGIC_EXP :  CODT 
| LOGIC_EXP COPR CODT
| mc_false
| mc_true

CODT : po EXP COPR EXP pf
| po EXP COPR  mc_false pf
| po EXP COPR  mc_true pf
| po mc_false COPR  EXP pf
| po mc_true COPR  EXP pf
| idf COPR idf 

COPR :pt OPR  pt
           

DATA : cst 
    | mc_true
    | mc_false
    | mc_reel 
    | cst_chaine 
    | tabl 


EXP :   EXP plus  T 
|  EXP moin  T 
|  T 

T : T mul F 
| T divsep F 
| F

F: po EXP pf
| EXP_item

EXP_item : idf
| cst
| tabl
| mc_reel




         

%%
int yyerror(char *msg)
{   printf("File "", line %d, character %d: syntax error",nb_ligne,col);
return 1; }

int main(int argc ,char* argv[]) {

file_name = argv[1];


    initialisation();
    yyparse();
    afficher();
    

}
int yywrap()
{}