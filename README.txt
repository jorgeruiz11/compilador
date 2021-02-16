Instrucciones para compilación y ejecución
1. Hacer `make` desde el directorio src/
2. Ejecutar: ./parser prueba.in

Actividades
1. Adecuar el analizador lexico lexer.lex de acuerdo a la gramatica del proyecto final.
2. Completar lista.c
3. Completar parser.c (con descenso recursivo) por el momento haciendo caso omiso de las reglas semanticas.

programa -> declaraciones funciones
declaraciones -> tipo lista_var;declaraciones | epsilon
tipo -> basico compuesto
basico- > int | float | char | double | void
compuesto -> [numero] compuesto | epsilon
lista_var -> id lista_var'
lista_var' -> ,id lista_var' | epsilon
funciones -> func tipo id(argumentos) bloque funciones | epsilon
argumentos -> lista_args | epsilon
lista_args -> tipo id lista_args'
lista_args' -> , tipo id lista_args' | epsilon
bloque -> { declaraciones instrucciones }
instrucciones -> sentencias instrucciones'
instrucciones' -> sentencias instrucciones' | epsilon
sentencias -> parte_izquierda = bool; | if(bool) sentencias sentencias' |while(bool) sentencias |do sentencias while(bool) | break;| bloque | return sentencias'' | switch(bool){casos}| print exp; | scan parte_izquierda
sentencias' -> else sentencias | epsilon
sentencias'' -> exp; | ;
casos -> caso casos | predeterminado | epsilon
caso -> case numero: instrucciones
predeterminado -> default: instrucciones
parte_izquierda -> id localizacion | id
bool -> comb bool'
bool' -> "||" comb bool' | epsilon
comb -> igualdad comb'
comb' -> && igualdad comb' | epsilon
igualdad -> rel igualdad'
igualdad' -> == rel igualdad' | != rel igualdad' | epsilon
rel -> exp rel'
rel' -> < exp | <= exp | >= exp | > exp | epsilon
exp -> term exp'
exp' -> + term exp' | - term exp' | epsilon
term -> unario term'
term' -> * unario term' | / unario term' | % unario term' | epsilon
unario -> !unario | -unario | factor
factor -> (bool) | id localizacion | numero | cadena |true | false | id(parametros) | id
parametros -> lista_params | epsilon
lista_params -> bool lista_params'
lista_params' -> ,bool lista_params' | epsilon
localizacion -> [bool]localizacion'
localizacion' -> [bool]localizacion' | epsilon