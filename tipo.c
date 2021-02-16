#include "tipo.h"

typedef struct _Tipo Tipo;

struct _Tipo{
  int id;
  char* tipo;
  int tam;
  int elem;
  int tipoBase;
};

Tipo tipo = malloc(sizeof(Tipo));

// REVISAR
simbolo *crea_entrada_tipo(int id, char *tipo, int tam, int elem, int tipoBase) {
  //implementa
  tipo->id = id;
  tipo->tipo = tipo;
  tipo->tam = tam;
  tipo->elem = elem;
  tipo->tipoBase = tipoBase;
}
