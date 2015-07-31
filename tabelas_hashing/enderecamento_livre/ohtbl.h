/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: ohtbl.h    */

#ifndef OHTBL_H_
#define OHTBL_H_

#include <stdlib.h>

/* --------------------------------- MACROS --------------------------------- */

#define ERROR  0
#define SUCESS 1
#define EXIST -1

#define ohtbl_size( ohtbl ) ( ( ohtbl )->size )

/* ------------------------------- ESTRUTURAS ------------------------------- */

typedef struct ohtbl
{
    unsigned int positions;
    void * vacated;

    int ( * h1 ) ( const void * key );
    int ( * h2 ) ( const void * key );
    int ( * match ) ( const void * key_1, const void * key_2 );
    void ( * destroy ) ( void * data );

    unsigned int size;
    void ** table;
} OHTBL;

/* -------------------------------- FUNÇÕES --------------------------------- */

/*  */
OHTBL * ohtbl_initialize ( int positions, int ( * h1 ) ( const void * key ), int ( * h2 ) ( const void * key ), int ( * match ) ( const void * key_1 , const void * key_2 ), void ( * destroy ) ( void * data ) );

/*  */
void ohtble_destroy ( OHTBL * ohtbl );

/*  */
int ohtbl_insert ( OHTBL * ohtbl, void * data );

/*  */
void * ohtbl_remove ( OHTBL * ohtbl, void * data );

/*  */
void * ohtbl_lookup ( const OHTBL * ohtbl, const void * data );

#endif
