/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: set.h  */

#ifndef SET_H_
#define SET_H_H

#include <string.h>
#include "list.h"

/* --------------------------------- MACROS --------------------------------- */

/*  #define list_size( list ) ( ( list )->size )    */
#define set_size list_size
/*  #define list_next( element ) ( ( element )->next )  */
#define set_next list_next
/*  #define list_data( element ) ( ( element )->data )  */
#define set_data list_data
/*  #define list_head( list ) ( ( list )->head )    */
#define set_first list_head
/*  #define list_tail( list ) ( ( list )->tail )    */
#define set_last list_tail

#define EXIST -1

/* ------------------------------- ESTRUTURAS ------------------------------- */

typedef LIST SET;
typedef LISTELEMENT SETELEMENT;

/* -------------------------------- FUNÇÕES --------------------------------- */

/*  retorna um conjunto */
SET * set_initialize ( int ( * match ) ( const void * key_1, const void * key_2 ), void ( * destroy ) ( void * data ) );

/*  liberará da memória do conjunto e de seus elementos

    void set_destroy ( SET * set );
*/
#define set_destroy list_destroy

/*  inserirá um elemento no conjunto    */
int set_insert ( SET * set, void * data );

/*  remove um elemento do conjunto  */
void * set_remove ( SET * set, void * data );

/*  retorna a união de dois conjuntos   */
SET * set_union ( SET * set_1, SET * set_2, size_t size );

/*  retorna a instersecção de dois conjuntos    */
SET * set_intersection ( SET * set_1, SET * set_2, size_t size );

/*  retorna a diferença de dois conjuntos   */
SET * set_difference ( SET * set_1, SET * set_2, size_t size );

/*  verifica se determinado dado faz parte do cojnunto ou não   */
int set_is_member ( const SET * set, const void * data );

/*  verifica se set_2 é um subconjunto de set_1 */
int set_is_subset ( const SET *set_1, const SET * set_2 );

/*  verifica se set_2 é igual a set_1   */
int set_is_equal ( const SET *set_1, const SET * set_2 );

#endif
