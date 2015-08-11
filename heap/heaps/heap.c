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

    }

    return heap;
}

/*  */
void heap_destroy ( HEAP * heap )
{
    if ( heap != NULL )
    {

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
