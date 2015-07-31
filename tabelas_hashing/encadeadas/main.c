/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: main.c */

#include <stdio.h>
#include "chtbl.h"

#define BUCKETS 1699
#define SIZE    50

void destroy ( void * data );
int hashing ( const void * data );
int matching ( const void * key_1, const void * key_2 );
static void ** alloc_ptr ( int size );
static void print_chtbl ( const CHTBL * chtbl, void ** ptr );

int main ( int argc, char ** argv )
{
    CHTBL *chtbl = NULL;
    void **ptr = NULL;
    unsigned int i = 0;

    chtbl = chtbl_initialize ( BUCKETS, hashing, matching, destroy );
    ptr = alloc_ptr ( SIZE );

    if ( ( chtbl == NULL ) || ( ptr == NULL ) )
        printf ( "The hashing table and/or the array couldn't be created\n" );

    else
    {
        for ( ; i < SIZE; i++ )
            chtbl_insert ( chtbl, ptr[ i ] );

        print_chtbl ( chtbl, ptr );

        chtbl_destroy ( chtbl );
        free ( ptr );
    }

    return 0;
}

/*  */
void destroy ( void * data )
{
    free ( data );
}

/*  a = n/m; sendo:
        * a := fator de carregamento;
        * n := número de elementos;
        * m := número de posições;

    h(k) = x; x := código de hashing de k ( sendo k pertencente aos inteiros )

    h(k) = k mod m; "método da divisão"  -- evitar números que sejam potência de
    dois  para  m, de preferência que ele seja um número primo não muito próximo
    a uma potência de dois.

    h(k) = [em(kA mod 1)]; "método da multiplicação"
*/
int hashing ( const void * data )
{
    return ( * ( ( int * ) data ) );
}

/*  */
int matching ( const void * key_1, const void * key_2 )
{
    return ( * ( ( int * ) key_1 ) - * ( ( int * ) key_2 ) );
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

/*  */
static void print_chtbl ( const CHTBL * chtbl, void ** ptr )
{
    unsigned int i = 0;

    for ( ; i < chtbl->size; i++ )
        printf ( "Element data = %d\n" , * ( ( int * ) chtbl_lookup ( chtbl, ptr[ i ] ) ) );

    printf ( "\n" );
}
