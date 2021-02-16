#include <stdlib.h>
#include <assert.h>
#include "stack.h"
// #include "lista.h"

// Una forma de hacer el top() es hacer pop a la pila, regresar ese elemento y volver a hacer push.

#define btoa(x) ((x)?"true":"false")

typedef struct _Node Node;

struct _Node{
	void* element;
	Node* previous;
};

struct _Stack{
	Node *first;
};

Stack *new_stack(){
	return malloc(sizeof(Stack));
}

void push(Stack* stack, void* element){
	assert(stack != NULL && element != NULL);
	Node* new_node = malloc(sizeof(Node));
	new_node->element = element;
	new_node->previous = stack->first;
	stack->first = new_node;
}

void* pop(Stack* stack){
	assert(stack != NULL);
	void* element = stack->first->element;
	Node* temp = stack->first;
	stack->first = temp->previous;
	free(temp);
	temp = NULL;
	return element;
}

bool is_empty(Stack* stack){
	assert(stack != NULL);
	return stack->first == NULL;
}

void free_stack(Stack* stack){
	assert(stack != NULL);
	free(stack->first->element);
	free(stack->first->previous);
	free(stack->first);
	free(stack);
	stack->first->element = NULL;
	stack->first->previous = NULL;
	stack->first = NULL;
}

Stack *stack_copia(Stack* stack){
  assert(satck != NULL);
  Stack* copia = new_stack();
  Stack* primero = stack->first;
  Lista* nueva = lista_nueva();
  while(!is_empty(stack)){
    lista_agrega_inicio(nueva, pop(stack))
  }

  NodoLista* temp = nueva->cabeza;
  while(temp != NULL){
    push(copia, temp->elemento);
    temp = temp->siguiente;
  }
  return copia;
}

// Node *top(Stack* stack){
//   Node* temp = pop(stack);
//   push(stack, temp);
//   // return temp;
//   return temp->element;
// }

Node *top(Stack* stack){
  return stack->first;
}


int main(){
	Stack *test_stack = new_stack();

	for (int i = 0; i < 11; ++i){
		int *element = malloc(sizeof(int));
		*element = i;
		push(test_stack, element);
	}

	int *top = pop(test_stack);
	int *new_top = pop(test_stack);
	printf("Ultimo agregado: %i\n", *top);
	printf("Penultimo agregado: %i\n", *new_top);
	free_stack(test_stack);
	printf("Es vacia: %s\n", btoa(is_empty(test_stack)));
	return 0;
}
