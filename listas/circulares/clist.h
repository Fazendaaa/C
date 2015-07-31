/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: clist.h    */

#ifndef CLIST_H_
#define CLIST_H_

#include <stdlib.h>

/* --------------------------------- MACROS --------------------------------- */

#define ERROR  0
#define SUCESS 1

#define clist_size( clist ) ( ( clist )->size )
#define clist_head( clist ) ( ( clist )->head )
#define clist_is_head( clist, element ) ( ( ( element ) == ( clist )->head ) ? SUCESS : ERROR )
#define clist_data( element ) ( ( element )->data )
#define clist_next( element ) ( ( element )->next )

/* ------------------------------- ESTRUTURAS ------------------------------- */

typedef struct clistelement
{
    void * data;
    struct clistelement * next;
} CLISTELEMENT;

typedef struct clist
{
    unsigned int size;
    int ( * match ) ( const void * key1, const void * key2 );
    void ( * destroy ) ( void * data );
    CLISTELEMENT * head;
} CLIST;

/* -------------------------------- FUNÇÕES --------------------------------- */

/*  retornará uma lista circular    */
CLIST * clist_initialize ( void ( * destroy ) ( void * data ) );

/*  liberara da memória a lista e de seus elementos */
void clist_destroy ( CLIST * list );

/*  inserirá, logo após o "element", o dado ( "data" )  */
int clist_insertion_next ( CLIST * list, CLISTELEMENT * element, void * data );

/*  removerá o elemento e irá retornar seu dado em "data"   */
int clist_remove_next ( CLIST * list, CLISTELEMENT * element, void ** data );

/*  tanto    em   "clist_insertion_next"   como   em   "clist_remove_next",   se
    element == NULL, será considerado como a cabeça da lista    */

#endif
