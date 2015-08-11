/*
    Autor: Lucas de Almeida Carotta
*/

/*
    nome do arquivo: heap.h
*/

#ifndef HEAP_H_
#define HEAP_H_

#include <stdlib.h>

/* --------------------------------- MACROS --------------------------------- */

#define ERROR  0
#define SUCESS 1

#define heap_size( heap ) ( ( heap )->size )

/* ------------------------------- ESTRUTURAS ------------------------------- */

typedef struct heap
{
    unsigned int size;

    int ( * compare ) ( const void * key_1, const void * key_2 );
    void ( * destroy ) ( void * data );

    void ** tree;
} HEAP;

/* -------------------------------- FUNÇÕES --------------------------------- */

/*  */
HEAP * heap_initialize ( int ( * compare ) ( const void * key_1, const void * key_2 ), void ( * destroy ) ( void * data ) );

/*  */
void heap_destroy ( HEAP * heap );

/*  */
int heap_insert ( HEAP * heap, const void * data );

/*  */
void * heap_extract ( HEAP * heap, void * data );

#endif
