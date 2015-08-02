/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: main.c */

#include <stdio.h>
#include "bistree.h"

#define FROM_1 6
#define TO_1   10

#define FROM_2 0
#define TO_2   3

#define FROM_3 0
#define TO_3   5

void destoy ( void * data );
int compare ( const void * key_1, const void * key_2 );
static void ** alloc_ptr ( const int from, const int to );
static void print_tree ( const BISTREE * bistree );

int main ( int argc, char ** argv )
{
    BISTREE *tree = NULL;
    void **ptr_1 = NULL, **ptr_2 = NULL, **ptr_3 = NULL;
    unsigned int i = 0;

    tree = bistree_initialize ( destoy, compare );
    ptr_1 = alloc_ptr ( FROM_1, TO_1 );
    ptr_2 = alloc_ptr ( FROM_2, TO_2 );
    ptr_3 = alloc_ptr ( FROM_3, TO_3 );

    if ( ( tree == NULL ) || ( ptr_1 == NULL ) || ( ptr_2 == NULL ) || ( ptr_3 == NULL ) )
        printf ( "The tree and/or the array couldn't be created\n" );

    else
    {
        /*for ( i = ( TO_1 - FROM_1 ); i >= 0; i-- )
            bistree_insert ( tree, ptr_1[ i ] );*/

        for ( ; i < ( TO_1 - FROM_1 + 1 ); i++ )
            bistree_insert ( tree, ptr_1[ i ] );

        printf ( "\n" );
        print_tree ( tree );

        for ( i = 0; i < ( TO_2 - FROM_2 + 1 ); i++ )
            bistree_insert ( tree, ptr_2[ i ] );

        /*for ( i = TO_3 + 1; i > 0; i-- )
            bistree_insert ( tree, ptr_3[ i ] );*/

        printf ( "\n" );
        print_tree ( tree );

        bistree_destroy ( tree );
        free ( ptr_3 );
        free ( ptr_2 );
        free ( ptr_1 );
    }

    return 0;
}

void destoy ( void * data )
{
    free ( data );
}

int compare ( const void * key_1, const void * key_2 )
{
    return ( * ( ( int * ) key_1 ) - * ( ( int * ) key_2 ) );
}

static void ** alloc_ptr ( const int from, const int to )
{
    void **new = NULL;
    unsigned int i = 0, begin = 0;

    /*  pode-se substituir os voids por int, mas não haverá diferença   */
    new = malloc ( sizeof ( void * ) * ( to - from + 1 )  );
    begin = from;

    if ( new != NULL )
    {
        for ( ; i < ( to - from + 1 ); i++ )
        {
            /*  o ponteiro void irá receber como conteúdo os valores de "i" que,
                por sua vez, serão armazenados na heap -- a notação seguinte é o
                método de acesso do ponteiro, com o cast de int, utilizado
            */
            new[ i ] = malloc ( sizeof ( int ) );

            if ( new[ i ] != NULL )
                * ( ( int * ) new[ i ] ) = begin++;
        }
    }

    return new;
}

static void recursive_print ( const BITREENODE * node  )
{
    if ( node != NULL )
    {
        recursive_print ( node->left );
        recursive_print ( node->right );
        printf ( "Element data = %d\n", * ( ( int * ) bistree_avl_data( node ) ) );
    }
}

static void print_tree ( const BISTREE * bistree )
{
    if ( bistree != NULL )
        recursive_print  ( bistree->root );

    printf ( "\n" );
}
