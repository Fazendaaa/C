/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: main.c */

#include <stdio.h>
#include "queue.h"

#define SIZE 7

void destroy ( void * data );
static void ** alloc_ptr ( void );
static void print_queue ( QUEUE * queue );

/*  programa  apenas para debbugar as estrturas feitas de fila. Neste caso, SIZE
    tem que ter, no mínimo, o valor 1
*/
int main ( int argc, char ** argv )
{
    QUEUE *queue = NULL;
    void **ptr = NULL;
    unsigned int i = 0;

    /*  carrega a fila a ser utilizada  */
    queue = queue_initialize ( destroy );
    /*  prepara os ponteiros que receberão os dados a serem utilizados  */
    ptr = alloc_ptr ( );

    if ( ( queue == NULL ) || ( ptr == NULL ) )
        printf ( "The queue and/or pointer couldn't be created\n" );

    else
    {
        /*  inserções na fila   */
        for ( ; i < SIZE; i++ )
        {
            queue_enqueue ( queue, ptr[ i ] );
            printf ( "[ %d ] Element enqueue = %d\n", i, * ( ( int * ) ptr[ i ] ) );
        }
        printf ( "\n" );

        /*  imprime a fila, a consumi-la    */
        print_queue ( queue );
        /*  como  os  dados  da  fila  já  foram  liberados, "queue_destroy" irá
            liberar apenas a fila da memória
        */
        queue_destroy ( queue );
        /*  como   os   inteiros  armazenados  na  memória  já  foram  liberados
            através  do "print_queue",  resta  apenas  liberar  os ponteiros que
            apontaram para eles
        */
        free ( ptr );
    }

    return 0;
}

/*    Complexidade == O(n); sendo n := número de elementos na fila  */
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

/*  irá liberar todos os dados armazenados na memória dentro da fila

    Complexidade == O(1)
*/
void destroy ( void * data )
{
    free ( data );
}

/*  imprime os dados da fila

    Complexidade == O(n); sendo n := número de elementos na fila
*/
static void print_queue ( QUEUE * queue )
{
    unsigned int i = 0, size = 0;
    void *data = NULL;

    if ( queue != NULL )
    {
        size = queue->size;

        for ( ; i < size; i++ )
        {
            queue_dequeue ( queue, &data );
            printf ( "[ %d ] Element dequeue = %d\n", i, * ( ( int * ) data ) );
            destroy ( data );
        }
    }
}
