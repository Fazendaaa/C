/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: stack.c    */

#include "stack.h"

/*  Complexidade == O(1)  */
int stack_push ( STACK * stack, void * data )
{
    return list_insertion_next ( stack, NULL, data );
}

/*  Complexidade == O(1)  */
int stack_pop ( STACK * stack, void ** data )
{
    return list_remove_next ( stack, NULL, data );
}
