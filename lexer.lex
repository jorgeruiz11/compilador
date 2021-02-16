%{
  #include <stdio.h>
  #include "tokens.h"
  #define YY_DECL token *yylex(void)
%}

%option noyywrap
%option yylineno

num_ent [0-9]+
num_float [0-9]*"."[0-9]+
id [a-zA-Z][a-zA-Z0-9]*
num_double {num_ent}*\.?{num_ent}*([eE][-+]?{num_ent}+)?
cadena (\"[ a-zA-Z0-9\\"'_+!,*-[\]]*\")|(\'[ a-zA-Z0-9\\"'_+!,*-[\]\n]*\')
whitespace [ \t\n]

%%

"," { ECHO; return crea_token(COMA, ""); }
";" { ECHO; return crea_token(PCOMA, ""); }
"[" { ECHO; return crea_token(CIZQ, ""); }
"]" { ECHO; return crea_token(CDER, ""); } 
"int" { ECHO; return crea_token(INT, ""); }
"float" { ECHO; return crea_token(FLOAT, "");}
"char" { ECHO; return crea_token(CHAR, ""); }
"double" { ECHO; return crea_token(DOUBLE, "");}
"(" { ECHO; return crea_token(PARIZQ, "");}
")" { ECHO; return crea_token(PARDER, "");}
"func" { ECHO; return crea_token(FUNC, "");}
"if" { ECHO; return crea_token(IF, "");}
"else" { ECHO; return crea_token(ELSE, "");}
"switch" { ECHO; return crea_token(SWITCH, "");}
"case" { ECHO; return crea_token(CASE, "");}
"default" { ECHO; return crea_token(DEFAULT, "");}
"while" { ECHO; return crea_token(WHILE, "");}
"do" { ECHO; return crea_token(DO, "");}
"break" { ECHO; return crea_token(BREAK, "");}
"return" { ECHO; return crea_token(RETURN, "");}
"print" { ECHO; return crea_token(PRINT, "");}
"scan" { ECHO; return crea_token(SCAN, "");}
":" { ECHO; return crea_token(DPUNTOS, "");}
"&&" { ECHO; return crea_token(DAMPER, "");}
"==" { ECHO; return crea_token(DIGUAL, "");}
"!=" { ECHO; return crea_token(DIST, "");}
"%" { ECHO; return crea_token(SPORCENTAJE, "");}
"!" { ECHO; return crea_token(SADMIRACION, "");}
"true" { ECHO; return crea_token(TRUE, "");}
"false" { ECHO; return crea_token(FALSE, "");}
"void" { ECHO; return crea_token(VOID, "");}
"=" { ECHO; return crea_token(IGUAL, "");}
"<" { ECHO; return crea_token(MENOR, "");}
">" { ECHO; return crea_token(MAYOR, "");}
"<=" { ECHO; return crea_token(MENORIG, "");}
">=" { ECHO; return crea_token(MAYORIG, "");}
"+" { ECHO; return crea_token(SUMA, "");}
"-" { ECHO; return crea_token(RESTA, "");}
"*" { ECHO; return crea_token(MULT, "");}
"/" { ECHO; return crea_token(DIV, "");}
"{" { ECHO; return crea_token(LIZQ, "");}
"}" { ECHO; return crea_token(LDER, "");}
"||" { ECHO; return crea_token(OR, "");}
{num_ent} { ECHO; return crea_token_tipo(NUM, yytext, 0); }
{num_float} { ECHO; return crea_token_tipo(NUM, yytext, 1); }
{num_double} { ECHO; return crea_token_tipo(NUM, yytext, 2); }
{id} { ECHO; return crea_token(ID, yytext); }
{cadena} { ECHO; return crea_token(CADENA, yytext); }
{whitespace} { ECHO; }
<<EOF>> { puts("Fin de análisis léxico."); return crea_token(FIN, ""); }
. { printf("Error léxico en la linea: %i\n", yylineno); exit(1); }

%%


