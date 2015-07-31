/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: main.c */

#include <stdio.h>
#include "ohtbl.h"

#define POSITIONS 1699
#define SIZE      50

void destroy ( void * data );
int matching ( const void * key_1, const void * key_2 );
int h1 ( const void * key );
int h2 ( const void * key );
static void ** alloc_ptr ( int size );
static void print_ohtbl ( OHTBL * ohtbl, void ** ptr );

/*  Faça também as verificações de retorno, não custa nada  */

/*  */
int main ( int argc, char ** argv )
{
    OHTBL *ohtbl = NULL;
    void **ptr = NULL;
    unsigned int i = 0;

    ohtbl = ohtbl_initialize ( POSITIONS, h1, h2, matching, destroy );
    ptr = alloc_ptr ( SIZE );

    if ( ( ohtbl == NULL ) || ( ptr == NULL ) )
        printf ( "The hashing table and/or the array couldn't be created\n" );

    else
    {
        for ( ; i < SIZE; i++ )
            ohtbl_insert ( ohtbl, ptr[ i ] );

        print_ohtbl ( ohtbl, ptr );

        ohtble_destroy ( ohtbl );
        free ( ptr );
    }

    return 0;
}

/*  */
void destroy ( void * data )
{
    free ( data );
}

/*  */
int matching ( const void * key_1, const void * key_2 )
{
    return ( * ( ( int * ) key_1 ) - * ( ( int * ) key_2 ) );
}

/*  */
int h1 ( const void * key )
{
    return ( * ( int * ) key );
}

/*  */
int h2 ( const void * key )
{
    return ( * ( int * ) key );
}

/*    Complexidade == O(n); sendo n := número de elementos no conjunto */
static void ** alloc_ptr ( int size )
{
    void **new = NULL;
    unsigned int i = 0;

    /*  pode-se substituir os voids por int, mas não haverá diferença   */
    new = malloc ( sizeof ( void * ) * size );

    if ( new != NULL )
    {
        for ( ; i < size; i++ )
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

static void print_ohtbl ( OHTBL * ohtbl, void ** ptr )
{
    unsigned int i = 0;

    printf ( "Size of hashing table = %d\n\n", ohtbl->size );

    for ( ; i < ohtbl->size; i++ )
        printf ( "Element data = %d\n", * ( ( int * ) ohtbl_lookup ( ohtbl, ptr[ i ] ) ) );
}
