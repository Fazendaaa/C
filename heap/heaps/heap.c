/*
    Autor: Lucas de Almeida Carotta
*/

/*
    nome do arquivo: heap.c
*/

#include "heap.h"

/*  */
HEAP * heap_initialize ( int ( * compare ) ( const void * key_1, const void * key_2 ), void ( * destroy ) ( void * data ) )
{
    HEAP *heap = NULL;

    if ( ( heap = malloc ( sizeof ( HEAP ) ) ) != NULL )
    {
        heap->compare = compare;
        heap->destroy = destroy;

        heap_size( heap ) = 0;
    }

    return heap;
}

/*  */
void heap_destroy ( HEAP * heap )
{
    unsigned int i = 0;

    if ( heap != NULL )
    {
        for ( ; i < heap_size( heap ); i++ )
            heap->destroy ( heap->tree[ i ] );
    }
}

/*  */
int heap_insert ( HEAP * heap, const void * data )
{
    if ( ( heap != NULL ) && ( data != NULL ) )
    {

    }

    return ERROR;
}

/*  */
void * heap_extract ( HEAP * heap, void * data )
{
    if ( ( heap != NULL ) && ( data != NULL ) )
    {

    }

    return ERROR;
}
