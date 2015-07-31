/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: chtbl.h    */

#ifndef CHTBL_H_
#define CHTBL_H_

#include "list.h"

/* --------------------------------- MACROS --------------------------------- */

#define chtbl_size( chtbl ) ( ( chtbl )->size )

/* ------------------------------- ESTRUTURAS ------------------------------- */

typedef struct chtbl
{
    unsigned int buckets;

    int ( * h ) ( const void * key );
    int ( * match ) ( const void * key_1, const void * key_2 );
    void ( * destroy ) ( void * data );

    unsigned int size;
    LIST ** table;

} CHTBL;

/* -------------------------------- FUNÇÕES --------------------------------- */

/*  */
CHTBL * chtbl_initialize ( int buckets, int ( * h ) ( const void * key ), int ( * match ) ( const void * key_1, const void * key_2 ), void ( * destroy ) ( void * data ) );

/*  */
void chtbl_destroy ( CHTBL * chtbl );

/*  */
int chtbl_insert ( CHTBL * chtbl, void * data );

/*  */
void * chtbl_remove ( CHTBL * chtbl, void * data );

/*  */
void * chtbl_lookup ( const CHTBL * chtbl, void * data );

#endif
