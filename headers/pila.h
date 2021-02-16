#include <stdbool.h>
#include <stdio.h>

typedef struct _Stack Stack;

Stack* new_stack(void);

void push(Stack* stack, void* element);

void* pop(Stack* stack);

bool is_empty(Stack* stack);

void free_stack(Stack* stack);
