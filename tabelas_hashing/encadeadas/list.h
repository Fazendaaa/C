/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: list.h */

#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>

/* --------------------------------- MACROS --------------------------------- */

#define ERROR  0
#define SUCESS 1

#define list_size( list ) ( ( list )->size )
#define list_head( list ) ( ( list )->head )
#define list_tail( list ) ( ( list )->tail )
#define list_is_head( list, element ) ( ( element ) == ( list )->head ? SUCESS : ERROR )
#define list_is_tail( list, element ) ( ( element ) == ( list )->tail ? SUCESS : ERROR )
#define list_data( element ) ( ( element )->data )
#define list_next( element ) ( ( element )->next )

/* ------------------------------- ESTRUTURAS ------------------------------- */

typedef struct listelement
{
    void *data;
    struct listelement *next;
} LISTELEMENT;

typedef struct list
{
    unsigned int size;
    int ( * match ) ( const void * key1, const void * key2 );
    void ( * destroy ) ( void * data );

    LISTELEMENT *head, *tail;
} LIST;

/* -------------------------------- FUNÇÕES --------------------------------- */

/*  retornará uma lista encadeada  */
LIST * list_initialize ( void ( * destroy ) ( void * data ) );

/*  liberara da memória a lista e de seus elementos */
void list_destroy ( LIST * list );

/*  inserirá, logo após o "element", o dado ( "data" )  */
int list_insertion_next ( LIST * list, LISTELEMENT * element, void * data );

/*  removerá, logo após o "element", o elemento seguinte e irá retornar seu dado
    em "data"
*/
int list_remove_next ( LIST * list, LISTELEMENT * element, void ** data );

/*  tanto    em    "list_insertion_next"    como   em   "list_remove_next",   se
    element == NULL, será considerado como a cabeça da lista
*/
#endif
