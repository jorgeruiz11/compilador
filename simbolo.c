#include "simbolo.h"

typedef struct _Simbolo Simbolo;

struct _Simbolo{
  char *id;
  int dir;
  int type;
  int var;
  Lista* args;
};

Simbolo simbolo = malloc(sizeof(Simbolo));

simbolo *crea_simbolo(char *id, int dir, int type, int var, Lista *args) {
  //implementa
  simbolo->id = id;
  simbolo->dir = dir;
  simbolo->type = type;
  simbolo->var = var;
  simbolo->args = args;

  // return NULL;
  return NULL;
}
