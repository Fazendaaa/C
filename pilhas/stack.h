/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: stack.h    */

#ifndef STACK_H_
#define STACK_H_

#include "list.h"

/* --------------------------------- MACROS --------------------------------- */

#define stack_peek ( stack ) ( ( ( stack )->head == NULL ) ? NULL : ( stack )->head->data )

/*  #define list_size( list ) ( ( list )->size )    */
#define stack_size list_size

/* ------------------------------- ESTRUTURAS ------------------------------- */

/*  define a estrutura de pilha baseado em uma lista encadeada  */
typedef LIST STACK;

/* -------------------------------- FUNÇÕES --------------------------------- */

/*  retornará uma pilha

    STACK * stack_initialize ( void ( * destroy ) ( void * data ) );
*/
#define stack_initialize list_initialize

/*  liberará da memória a pilha e de seus elementos

    void stack_destroy ( STACK * stack );
*/
#define stack_destroy    list_destroy

/*  insere um elemento apontado por data na pilha   */
int stack_push ( STACK * stack, void * data );

/*  retorna o elemento da pilha em data consumindo-o    */
int stack_pop ( STACK * stack, void ** data );

#endif
