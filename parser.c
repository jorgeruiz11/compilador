#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "pila.h" // ?


extern token *yylex();
extern int yylineno;
extern FILE *yyin;

// int dir = 0;
// Stack* pilaTS = new_stack();
// Stack* pilaTT = new_stack();

void eat(int clase) {
  if(equals(tokenActual, clase)) {
    tokenActual = yylex();
  } else {
    error("Error de sintaxis");
  }
}

void parse() {
  //inicializar TS y TT
  programa();
  //imprimir TS y TT
}

void programa() {
  declaraciones();
  funciones();
  // Posiblemente hay que hacer una copia de esas o literalmente crear una nueva tabla
  // Definirlas fuera del método para que sean accesibles en los demás.
  Stack* pilaTS = new_stack();
  Stack* pilaTT = new_stack();
  push(pilaTS, tablaSimbolos);
  push(pilaTT, tablaTipos);
  dir = 0;
  if(equals(tokenActual, FIN)) {
    puts("Fin de análisis sintáctico.");
    return;
  }
}

void declaraciones() {
  if(equals(tokenActual, INT) || equals(tokenActual, FLOAT) || equals(tokenActual, CHAR) || equals(tokenActual, DOUBLE) || equals(tokenActual, VOID)){
    int tipo = tipo();
    lista_var(tipo);
    eat(PCOMA);
    declaraciones();
  }
}

// No se cual es. No estoy seguro que sea int
int tipo(){
  int tipo = basico(); // verificar que si sea int
  tipo = compuesto(tipo);
  return tipo;
}

int basico(){
  if(equals(tokenActual, INT)){
    eat(INT);
    return 1005;
  }else if(equals(tokenActual, FLOAT)){
    eat(FLOAT);
    return 1006;
  }else if(equals(tokenActual, CHAR)){
    eat(CHAR);
    return 1029;
  }else if(equals(tokenActual, DOUBLE)){
    eat(DOUBLE);
    return 1030;
  }else if(equals(tokenActual, VOID)){
    eat(VOID);
    return 1031;
  }
}

int compuesto(int base){
  String valor;
  int tipo;
  if (equals(tokenActual, CIZQ)) {
    char* valor;
    eat(CIZQ);
    valor = tokenActual->valor;
    eat(NUM);
    eat(CDER);
    tipo = compuesto(base);
    id = tablaTipos->longitud;
    Stack* copiapilaTT = stack_copia(pilaTT);
    lista_agrega_inicio(pop(copiapilaTT), crea_entrada_tipo(id, "array", 1000, atoi(valor), tipo));
    return tipo;
  } else {
    return base;
  }
}

void lista_var(int tipo){
  lista_var(tipo);
  if(equals(tokenActual, ID)){
    Stack* copiapilaTS = stack_copia(pilaTS);
    // Si no funciona, modificar top o hacerlo como arriba. Además, revisar que es first.
    if(!lista_busca(top(pilaTS), tokenActual->valor)){
      int var = 0; // revisar que onda con var
      lista_agrega_final(top(pilaTS), crea_simbolo(tokenActual->valor, dir, tipo, var, NULL));
      dir = dir + getTam(tipo);
    }else{
      error("El id no está declarado");
    }
    eat(ID); // Checar si va aqui o antes
    lista_varp(tipo);
  }else{
    error("Error de sintáxis");
  }
}

void lista_varp(int tipo){
  if(equals(tokenActual, COMA)){
    eat(COMA);
    Stack* copiapilaTS = stack_copia(pilaTS);
    // Si no funciona, modificar top o hacerlo como arriba. Además, revisar que es first.
    if(!lista_busca(top(pilaTS), tokenActual->valor)){
      int var = 0; // revisar que onda con var
      lista_agrega_final(top(pilaTS), crea_simbolo(tokenActual->valor, dir, tipo, var, NULL));
      dir = dir + getTam(tipo);
    }else{
      error("El id no está declarado");
    }
    eat(ID);
    lista_varp();
  }else{
    error("Error de sintaxis");
  }
}

void funciones(){
  if(equals(tokenActual, FUNC)){
    eat(FUNC);
    Lista* listaRetorno = NULL;
    Stack* pilaTS = new_stack();
    Stack* pilaTT = new_stack();
    Stack* pilaDir = new_stack();
    Lista* nuevaTablaSimbolos = lista_nueva();
    Lista* nuevaTablaTipos = lista_nueva();
    push(pilaTS, nuevaTablaSimbolos);
    push(pilaTT, nuevaTablaTipos);
    push(pilaDir, dir);
    tipo();

    if(!lista_busca(top(pilaTS), tokenActual->valor)){

    }
    eat(ID);
    eat(CIZQ);
    argumentos();
    eat(CDER);
    bloque();
    funciones();
  }
}

void argumentos(){
  if(equals(tokenActual, INT) || equals(tokenActual, FLOAT) || equals(tokenActual, CHAR) || equals(tokenActual, DOUBLE) || equals(tokenActual, VOID)){
    lista_args();
  }
}

void lista_args(){
  tipo();
  eat(ID);
  lista_argsp();
}

void lista_argsp(){
  if(equals(tokenActual, COMA)){
    eat(COMA);
    tipo();
    eat(ID);
    lista_argsp();
  }
}

void bloque(){
  eat(LIZQ);
  bloque();
  eat(LDER);
}

void instrucciones(){
  sentencias();
  instruccionesp();
}

void instruccionesp(){
  if(equals(tokenActual, ID) || equals(tokenActual, IF) || equals(tokenActual, WHILE) || equals(tokenActual, DO) || equals(tokenActual, BREAK) || equals(tokenActual, LIZQ) || equals(tokenActual, RETURN) || equals(tokenActual, SWITCH) || equals(tokenActual, PRINT) || equals(tokenActual, SCAN)){
    sentencias();
    instruccionesp();
  }
}

void sentencias(){
  if(equals(tokenActual, ID)){
    parte_izquierda();
    eat(IGUAL);
    boolg();
    eat(PCOMA);
  }else if(equals(tokenActual, IF)){
    eat(IF);
    eat(PARIZQ);
    boolg();
    eat(PARDER);
    sentencias();
    sentenciasp();
  }else if(equals(tokenActual, WHILE)){
    eat(WHILE);
    eat(PARIZQ);
    boolg();
    eat(PARDER);
    sentencias();
  }else if(equals(tokenActual, DO)){
    eat(DO);
    sentencias();
    eat(WHILE);
    eat(PARIZQ);
    boolg();
    eat(PARDER);
  }else if(equals(tokenActual, BREAK)){
    eat(BREAK);
    eat(PCOMA);
  }else if(equals(tokenActual, LIZQ)){
    bloque();
  }else if(equals(tokenActual, RETURN)){
    eat(RETURN);
    sentenciaspp();
  }else if(equals(tokenActual, SWITCH)){
    eat(SWITCH);
    eat(PARIZQ);
    boolg();
    eat(PARDER);
    eat(LIZQ);
    casos();
    eat(LDER);
  }else if(equals(tokenActual, PRINT)){
    eat(PRINT);
    expg();
    eat(PCOMA);
  }else if(equals(tokenActual, SCAN)){
    eat(SCAN);
    parte_izquierda();
  }
}

void sentenciasp(){
  if(equals(tokenActual, ELSE)){
    eat(ELSE);
    sentencias();
  }
}

void sentenciaspp(){
  if(equals(tokenActual, PCOMA)){
    eat(PCOMA);
  }else{
    expg();
    eat(PCOMA);
  }
}

void casos(){
  if(equals(tokenActual, CASE)){
    caso();
    casos();
  }else if(equals(tokenActual, DEFAULT)){
    predeterminado();
  }
}

void caso(){
  eat(CASE);
  eat(NUM);
  eat(DPUNTOS);
  instrucciones();
}

void predeterminado(){
  eat(DEFAULT);
  eat(DPUNTOS);
  instrucciones();
}

void parte_izquierda(){
  eat(ID);
  if(equals(tokenActual, CIZQ)){
    localizacion();
  }
}

void boolg(){
  comb();
  boolp();
}

void boolp(){
  if(equals(tokenActual, OR)){
    comb();
    boolp();
  }
}

void comb(){
  igualdad();
  combp();
}

void combp(){
  if(equals(tokenActual, DAMPER)){
    igualdad();
    combp();
  }
}

void igualdad(){
  rel();
  igualdadp();
}

void igualdadp(){
  if(equals(tokenActual, DIGUAL)){
    eat(DIGUAL);
    rel();
    igualdadp();
  }else if(equals(tokenActual, DIST)){
    eat(DIST);
    rel();
    igualdadp();
  }
}

void rel(){
  expg();
  relp();
}

void relp(){
  if(equals(tokenActual, MENOR)){
    eat(MENOR);
    expg();
  }else if(equals(tokenActual, MENORIG)){
    eat(MENORIG);
    expg();
  }else if(equals(tokenActual, MAYORIG)){
    eat(MAYORIG);
    expg();
  }else if(equals(tokenActual, MAYOR)){
    eat(MAYOR);
    expg();
  }
}

void expg(){
  term();
  expp();
}

void expp(){
  if(equals(tokenActual, SUMA)){
    eat(SUMA);
    term();
    expp();
  }else if(equals(tokenActual, RESTA)){
    eat(RESTA);
    term();
    expp();
  }
}

void term(){
  unario();
  termp();
}

void termp(){
  if(equals(tokenActual, MULT)){
    eat(MULT);
    unario();
    termp();
  }else if(equals(tokenActual, DIV)){
    eat(DIV);
    unario();
    termp();
  }else if(equals(tokenActual, SPORCENTAJE)){
    eat(SPORCENTAJE);
    unario();
    termp();
  }
}

void unario(){
  if(equals(tokenActual, SADMIRACION)){
    eat(SADMIRACION);
    unario();
  }else if(equals(tokenActual, RESTA)){
    eat(RESTA);
    unario();
  }else{
    factor();
  }
}

void factor(){
  if(equals(tokenActual, PARIZQ)){
    eat(PARIZQ);
    boolg();
    eat(PARDER);
  }else if(equals(tokenActual, ID)){
    eat(ID);
    if(equals(tokenActual, PARIZQ)){
      eat(PARIZQ);
      parametros();
      eat(PARDER);
    }else if(equals(tokenActual, CIZQ)){
      localizacion();
    }
  }else if(equals(tokenActual, NUM)){
    eat(NUM);
  }else if(equals(tokenActual, TRUE)){
    eat(TRUE);
  }else if(equals(tokenActual, FALSE)){
    eat(FALSE);
  }
}

void parametros(){
  if(equals(tokenActual, MULT) || equals(tokenActual, DIV) || equals(tokenActual, SPORCENTAJE)){
    lista_params();
  }
}

void lista_params(){
  boolg();
  lista_paramsp();
}

void lista_paramsp(){
  if(equals(tokenActual, COMA)){
    eat(COMA);
    boolg();
    lista_paramsp();
  }
}

void localizacion(){
  eat(CIZQ);
  boolg();
  eat(CDER);
  localizacionp();
}

void localizacionp(){
  if(equals(tokenActual, CIZQ)){
    eat(CIZQ);
    boolg();
    eat(CDER);
    localizacionp();
  }
}

void error(char *msg) {
  printf(msg);
  printf(": línea %i\n", yylineno);
  exit(1);
}


int getTam(int id){
  NodoLista* temp = tablaTipos->cabeza;
  while(temp != NULL){
    if(temp->element->id == id){
      return temp->element->tam;
    } else{
      return -1;
    }
    temp = temp->siguiente;
  }
}




int main(int argc, char **argv) {
  if(argc < 2) {
    puts("Falta archivo de entrada.");
    exit(1);
  }
  printf("Archivo de entrada: ");
  puts(argv[1]);
  FILE *fin = fopen(argv[1], "r");
  yyin = fin;

  puts("Comenzando análisis...");
  tokenActual = yylex();
  //puts(tokenActual->valor); //verificación de lectura
  parse();
}
