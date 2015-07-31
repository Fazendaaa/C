/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: main.c */

#include <stdio.h>
#include "dlist.h"

#define SIZE 6

void destroy ( void * data );
static void ** alloc_ptr ( void );
static void print_list ( const DLIST * list );
static DLISTELEMENT * search_element ( const DLIST * list, const void * data );

/*  programa   apenas  para  debbugar  as  estrturas  feitas  de  listas  duplas
    encadeadas. Neste caso, SIZE tem que ter, no mínimo, o valor 6
*/
int main ( int argc, char ** argv )
{
    DLIST *list = NULL;
    int i = 0, test_1 = 0, test_2 = ( SIZE / 2 );
    void **ptr = NULL;

    /*  carrega a lista a ser utilizada */
    list = dlist_initialize ( destroy );
    /*  prepara os ponteiros que receberão os dados a serem utilizados  */
    ptr = alloc_ptr ( );

    if ( ( list == NULL ) || ( ptr == NULL ) )
        printf( "The list and/or the array couldn't be created\n" );

    else
    {
        i = 0;

        /*  inserções na cabeça da lista    */
        dlist_insertion_next ( list, NULL, ptr[ i++ ] );
        printf ( "Insertion next ( HEAD )\n" );
        print_list ( list );

        dlist_insertion_prev ( list, NULL, ptr[ i++ ] );
        printf ( "Insertion prev ( HEAD )\n" );
        print_list ( list );

        /*  inserções na cauda da lista */
        dlist_insertion_next ( list, list->tail, ptr[ i++ ] );
        printf ( "Insertion next ( TAIL )\n" );
        print_list ( list );

        dlist_insertion_prev ( list, list->tail, ptr[ i++ ] );
        printf ( "Insertion prev ( TAIL )\n" );
        print_list ( list );

        /*  inserções no meio da lista  */
        dlist_insertion_next ( list, search_element ( list, &test_1 ), ptr[ i++ ] );
        printf ( "Insertion next ( MIDDLE )\n" );
        print_list ( list );

        dlist_insertion_prev ( list, search_element ( list, &test_2 ), ptr[ i++ ] );
        printf ( "Insertion prev ( MIDDLE )\n" );
        print_list ( list );

        /*  irá  liberar todos os valores que "i" teve dentro do "for" que estão
            armazenados na heap
        */
        dlist_destroy ( list );
        /*  como   os   inteiros  armazenados  na  memória  já  foram  liberados
            através do "dlist_destroy", resta  apenas  liberar  os ponteiros que
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
static void print_list ( const DLIST * list )
{
    DLISTELEMENT *element = NULL;

    printf ( "Head: %d\n", * ( ( int * ) dlist_head( list )->data ) );

    for ( element = dlist_head( list ); element != NULL; element = dlist_next( element ) )
        printf ( "Element data: %d\n", * ( ( int * ) dlist_data( element ) ) );

    printf ( "Tail: %d\n\n", * ( ( int * ) dlist_tail( list )->data ) );
}

/*  retorna o valor da diferença de dois números passados

    Complexidade == O(1)
*/
static int element_compare ( const void * data_1, const void * data_2 )
{
    return ( * ( ( int * ) data_1 ) - * ( ( int * ) data_2 ) );
}

/*  Pior caso := o elemento procurado não existe ou está na cauda da lista
    Complexidade == O(n); sendo n := número de elementos na lista

    Caso médio := o elemento procurado está na metade da lista
    Complexidade == O(n/2);

    Melhor caso := o elemento procurado é a cabeça da lista
    Complexidade == O(1);
*/
static DLISTELEMENT * search_element ( const DLIST * list, const void * data )
{
    DLISTELEMENT *element = NULL;

    if ( ( list != NULL ) && ( data != NULL ) )
    {
        for ( element = dlist_head( list ); element != NULL; element = dlist_next( element ) )
        {
            if ( !element_compare ( element->data, data ) )
                break;
        }
    }

    /*  caso  o  elemento não exista na lista, "element" receberá nulo; ou seja,
        como  o  valor  será  nulo, o novo elemento será adicionado na cabeça da
        lista
    */
    return element;
}
