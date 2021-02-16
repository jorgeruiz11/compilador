#ifndef TOKENS_H
#define TOKENS_H

#define COMA 1001
#define PCOMA 1002
#define CIZQ 1003
#define CDER 1004
#define INT 1005
#define FLOAT 1006
#define NUM 1007
#define ID 1008
#define PARIZQ 1009
#define PARDER 1010
#define FUNC 1011
#define IF 1012
#define ELSE 1013
#define SWITCH 1014
#define CASE 1015
#define DEFAULT 1016
#define WHILE 1017
#define DO 1018
#define BREAK 1019
#define DPUNTOS 1020
#define DAMPER 1021
#define DIGUAL 1022
#define DIST 1023
#define SPORCENTAJE 1024
#define SADMIRACION 1025
#define TRUE 1026
#define FALSE 1027
#define CADENA 1028
#define CHAR 1029
#define DOUBLE 1030
#define VOID 1031
#define IGUAL 1032
#define MENOR 1033
#define MAYOR 1034
#define MENORIG 1035
#define MAYORIG 1036
#define SUMA 1037
#define RESTA 1038
#define MULT 1039
#define DIV 1040
#define FIN 9001
#define LIZQ 8090
#define LDER 8091
#define RETURN 8092
#define PRINT 8093
#define SCAN 8094
#define OR 8095
/* 
 * podemos definir más o cambiar las definiciones 
 * siempre y cuando actualicemos el lexer 
 */
#endif

#include <string.h>
#include <stdlib.h>


/**
 * Estructura para modelar tokens (componentes léxicos)
 */
typedef struct token {
  int clase; //léxica
  char *valor; //lexema
  int tipo; //para diferenciar entre diferentes lexemas de una misma clase léxica
} token;

/**
 * Inicialización de tokens sin tipo
 */
token *crea_token(int clase, char *valor);

/**
 * Inicialización de tokens con tipo
 */
token *crea_token_tipo(int clase, char *valor, int tipo);

/**
 * Verificación de token perteneciente a una clase léxica
 */
int equals(token *t1, int clase);

/**
 * Liberación de memoria de un token
 */
void libera(token *t);



