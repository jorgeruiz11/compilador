#include "tokens.h"
#include "lista.h"

/* Token actual en la lectura */
token *tokenActual;
/* Dirección disponible en la TT */
int dir;
/* Tabla de símbolos */
Lista *tablaSimbolos;
/* Tabla de tipos */
Lista *tablaTipos;

void programa();

void declaraciones();

void tipo();

void basico();

void compuesto();

void lista_var();

void lista_varp();

void funciones();

void argumentos();

void lista_args();

void lista_argsp();

void bloque();

void instrucciones();

void instruccionesp();

void sentencias();

void sentenciasp();

void sentenciaspp();

void casos();

void caso();

void predeterminado();

void parte_izquierda();

void boolg();

void boolp();

void comb();

void combp();

void igualdad();

void igualdadp();

void rel();

void relp();

void expg();

void expp();

void term();

void termp();

void unario();

void factor();

void parametros();

void lista_params();

void lista_paramsp();

void localizacion();

void localizacionp();
/**
 * Función para consumo de componente léxico actual al hacer empate
 */
void eat(int clase);

/**
 * Función principal de análisis sintáctico. 
 * Debe llamar a función de símbolo inicial de la gramática.
 * También inicializar las tablas de símbolos y tipos.
 */
void parse();

/**
 * Función para reporte de errores sintácticos y semánticos.
 */
void error(char *msg);

/**
 * (opcional) Función para buscar símbolos en la tabla de símbolos
 */
int buscar(char *simbolo);

/**
 * Obtener tamaño de elemento de la tabla de tipos
 */
int getTam(int id);

/**
 * Función para imprimir Tabla de tipos
 */
void printTT(Lista *TT);

/**
 * Función para imprimir Tabla de símbolos
 */
void printTS(Lista *TS);


