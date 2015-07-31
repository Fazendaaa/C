/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: dlist.h    */

#ifndef DLIST_H_
#define DLIST_H_

#include <stdlib.h>

/* --------------------------------- MACROS --------------------------------- */

#define ERROR  0
#define SUCESS 1

#define dlist_size( dlist ) ( ( dlist )->size )
#define dlist_head( dlist ) ( ( dlist )->head )
#define dlist_tail( dlist ) ( ( dlist )->tail )
#define dlist_is_head( dlist, element ) ( ( element ) == ( dlist )->head ? SUCESS : ERROR )
#define dlist_is_tail( dlist, element ) ( ( element ) == ( dlist )->tail ? SUCESS : ERROR )
#define dlist_data( element ) ( ( element )->data )
#define dlist_next( element ) ( ( element )->next )
#define dlist_prev( element ) ( ( element )->prev )

/* ------------------------------- ESTRUTURAS ------------------------------- */

typedef struct dlistelement
{
    void *data;
    struct dlistelement *next, *prev;
} DLISTELEMENT;

typedef struct dlist
{
    unsigned int size;
    int ( * match ) ( const void * key1, const void * key2 );
    void ( * destroy ) ( void * data );
    DLISTELEMENT *head, *tail;
} DLIST;

/* -------------------------------- FUNÇÕES --------------------------------- */

/*  retornará uma lista duplamente encadeada  */
DLIST * dlist_initialize ( void ( * destroy ) ( void * data ) );

/*  liberara da memória a lista e de seus elementos */
void dlist_destroy ( DLIST * list );

/*  inserirá, logo após o "element", o dado ( "data" )  */
int dlist_insertion_next ( DLIST * list, DLISTELEMENT * element, void * data );

/*  inserirá, logo antes o "element", o dado ( "data" ) */
int dlist_insertion_prev ( DLIST * list, DLISTELEMENT * element, void * data );

/*  removerá o elemento e irá retornar seu dado em "data"   */
int dlist_remove ( DLIST * list, DLISTELEMENT * element, void ** data );

/*  tanto em "dlist_insertion_next", "dlist_insertion_prev" e em "dlist_remove",
    se element == NULL, será considerado como a cabeça da lista */

#endif
