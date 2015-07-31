/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: main.c */

#include <stdio.h>
#include "clist.h"

#define SIZE 3

void destroy ( void * data );
static void ** alloc_ptr ( void );
static void print_list ( const CLIST * list );
static CLISTELEMENT * search_element ( const CLIST * list, const void * data );

/*  programa  apenas  para  debbugar  as  estrturas feitas de listas circulares.
    Neste caso, SIZE tem que ter, no mínimo, o valor 3
*/
int main ( int argc, char ** argv )
{
    CLIST *list = NULL;
    void **ptr = NULL;
    unsigned int i = 0, test = ( ( SIZE / 2 ) - 2 );

    /*  carrega a lista a ser utilizada */
    list = clist_initialize ( destroy );
    /*  prepara os ponteiros que receberão os dados a serem utilizados  */
    ptr = alloc_ptr ( );

    if ( ( list == NULL ) || ( ptr == NULL ) )
        printf( "The list and/or the array couldn't be created\n" );

    else
    {
        for ( i = 0; i < ( ( SIZE / 2 ) + 1 ); i++ )
            clist_insertion_next ( list, NULL, ptr[ i ] );

        /*  inserções na cabeça da lista    */
        printf ( "Sequential add ( HEAD )\n" );
        print_list ( list );

        for ( ; i < SIZE; i++ )
            clist_insertion_next ( list, search_element ( list, &test ), ptr[ i ] );

        /*  inserções no meio da lista  */
        printf ( "Sequential add ( Middle )\n" );
        print_list ( list );

        /*  irá  liberar todos os valores que "i" teve dentro do "for" que estão
            armazenados na heap
        */
        clist_destroy ( list );
        /*  como   os   inteiros  armazenados  na  memória  já  foram  liberados
            através do "clist_destroy", resta  apenas  liberar  os ponteiros que
            apontaram para eles
        */
        free ( ptr );
    }

    return 0;
}

/*  irá liberar todos os dados armazenados na memória dentro da lista

    Complexidade == O(1)
*/
void destroy ( void * data )
{
    free ( data );
}

/*    Complexidade == O(n); sendo n := número de elementos na pilha */
static void ** alloc_ptr ( void )
{
    void **new = NULL;
    unsigned int i = 0;

    /*  pode-se substituir os voids por int, mas não haverá diferença   */
    new = malloc ( sizeof ( void * ) * SIZE );

    if ( new != NULL )
    {
        for ( ; i < SIZE; i++ )
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

/*  imprime os dados da lista

    Complexidade == O(n); sendo n := número de elementos na lista
*/
static void print_list ( const CLIST * list )
{
    CLISTELEMENT *element = NULL;

    element = clist_head( list );

    printf ( "Head: %d\n", * ( ( int * ) element->data ) );

    do
    {
        printf ( "Element data: %d\n", * ( ( int * ) clist_data( element ) ) );
        element = clist_next( element );
    } while ( element != clist_head( list ) );

    printf ( "\n" );
}

/*  retorna o valor da diferença de dois números passados

    Complexidade == O(1)
*/
static int element_compare ( const void * data_1, const void * data_2 )
{
    return ( * ( ( int * ) data_1 ) - * ( ( int * ) data_2 ) );
}

/*  Pior caso := o elemento procurado não existe ou está na ponta da lista
    Complexidade == O(n); sendo n := número de elementos na lista

    Caso médio := o elemento procurado está na metade da lista
    Complexidade == O(n/2);

    Melhor caso := o elemento procurado é a cabeça da lista
    Complexidade == O(1);
*/
static CLISTELEMENT * search_element ( const CLIST * list, const void * data )
{
    CLISTELEMENT *element = NULL;

    element = clist_head( list );

    do
    {
        if ( !element_compare ( element->data, data ) )
            break;

        element = clist_next( element );
    } while ( element != clist_head( list ) );

    /*  caso  o  elemento  não  exista na lista, "element" receberá a cabeça; ou
        seja, o novo elemento será adicionado na cabeça da lista
    */
    return element;
}
