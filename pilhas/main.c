/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: main.c */

#include <stdio.h>
#include "stack.h"

#define SIZE 5

void destroy ( void * data );
static void ** alloc_ptr ( void );
static void print_stack ( STACK * stack );

/*  programa apenas para debbugar as estrturas feitas de pilha. Neste caso, SIZE
    tem que ter, no mínimo, o valor 1
*/
int main ( int argc, char ** argv )
{
    STACK *stack = NULL;
    void **ptr = NULL;
    unsigned int i = 0;

    /*  carrega a lista a ser utilizada */
    stack = stack_initialize ( destroy );
    /*  prepara os ponteiros que receberão os dados a serem utilizados  */
    ptr = alloc_ptr ( );

    if ( ( stack == NULL ) || ( ptr == NULL ) )
        printf ( "The stack and/or pointer couldn't be created\n" );

    else
    {
        /*  inserções na pilha  */
        for ( ; i < SIZE; i++ )
        {
            stack_push ( stack, ptr[ i ] );
            printf ( "[ %d ] Element push = %d\n", i, * ( ( int * ) ptr[ i ] ) );
        }
        printf ( "\n" );

        /*  imprime a pilha, a consumi-la   */
        print_stack ( stack );
        /*  como  os  dados  da  pilha  já  foram liberados, "stack_destroy" irá
            liberar apenas a pilha da memória
        */
        stack_destroy ( stack );
        /*  como   os   inteiros  armazenados  na  memória  já  foram  liberados
            através  do "print_stack",  resta  apenas  liberar  os ponteiros que
            apontaram para eles
        */
        free ( ptr );
    }

    return 0;
}

/*  irá liberar todos os dados armazenados na memória dentro da pilha

    Complexidade == O(1)
*/
void destroy ( void * data )
{
    free ( data );
}

/*    Complexidade == O(n); sendo n := número de elementos na pilha */
static void ** alloc_ptr ( void )
{
    void **new = NULL;
    unsigned int i = 0;

    /*  pode-se substituir os voids por int, mas não haverá diferença   */
    new = malloc ( sizeof ( void * ) * SIZE );

    if ( new != NULL )
    {
        for ( ; i < SIZE; i++ )
        {
            /*  o ponteiro void irá receber como conteúdo os valores de "i" que,
                por sua vez, serão armazenados na heap -- a notação seguinte é o
                método de acesso do ponteiro, com o cast de int, utilizado
            */
            new[ i ] = malloc ( sizeof ( int ) );

            if ( new[ i ] != NULL )
                * ( ( int * ) new[ i ] ) =  i;
        }
    }

    return new;
}

/*  imprime os dados da pilha

    Complexidade == O(n); sendo n := número de elementos na pilha
*/
static void print_stack ( STACK * stack )
{
    unsigned int i = 0, size = 0;
    void *data = NULL;

    if ( stack != NULL )
    {
        size = stack_size( stack );

        for ( ; i < size; i++ )
        {
            /*  recupera o elemento da pilha e reduz o tamanho dela */
            stack_pop ( stack, &data );
            printf ( "[ %d ] Element pop = %d\n", i, * ( ( int * ) data ) );
            /*  consome o dado da pilha, o libera da memória    */
            destroy ( data );
        }
    }
}
