/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: main.c */

#include <stdio.h>
#include "list.h"

#define SIZE 4

void destroy ( void * data );
static void ** alloc_ptr ( void );
static void print_list ( const LIST * list );
static LISTELEMENT * search_element ( const LIST * list, const void * data );

/*  programa  apenas  para  debbugar  as  estrturas feitas de listas encadeadas.
    Neste caso, SIZE tem que ter, no mínimo, o valor 4
*/
int main ( int argc, char ** argv )
{
    LIST *list = NULL;
    void **ptr = NULL;
    int i = 0, test1 = 0, test2 = ( SIZE / 2 ) - 1;

    /*  carrega a lista a ser utilizada */
    list = list_initialize ( destroy );
    /*  prepara os ponteiros que receberão os dados a serem utilizados  */
    ptr = alloc_ptr ( );

    if ( ( list == NULL ) || ( ptr == NULL ) )
        printf ( "The list and/or pointer couldn't be created\n" );

    else
    {
        /*  inserções na cabeça da lista    */
        for ( i = 0; i < SIZE - 2; i++ )
        {
            /*  passa,  endereço por endereço, o ponteiro void que aponta para o
                inteiro  armazenado na memória heap que possui o valor de "i" em
                determinada iteração do "for"
            */
            list_insertion_next ( list, NULL, ptr[ i ] );
        }

        printf ( "   Sequential add\n" );
        print_list ( list );

        /*  inserções na cauda da lista */
        list_insertion_next ( list, search_element ( list, ( void * ) &test1 ), ptr[ i ] );

        printf ( "   Tail add\n" );
        print_list ( list );

        /*  inserções no meio da lista  */
        list_insertion_next ( list, search_element ( list, ( void * ) &test2 ), ptr[ ++i ] );

        printf ( "   Middle add\n" );
        print_list ( list );

        /*  irá  liberar todos os valores que "i" teve dentro do "for" que estão
            armazenados na heap
        */
        list_destroy ( list );
        /*  como   os   inteiros  armazenados  na  memória  já  foram  liberados
            através do "list_destroy",  resta  apenas  liberar  os ponteiros que
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
static void print_list ( const LIST * list )
{
    LISTELEMENT *element = NULL;

    printf ( "Head: %d\n", * ( ( int * ) list_head( list )->data ) );

    for ( element = list_head( list ); element != NULL; element = list_next( element ) )
        printf ( "Element data: %d\n", * ( ( int * ) list_data( element ) ) );

    printf ( "Tail: %d\n\n", * ( ( int * ) list_tail( list )->data ) );
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
static LISTELEMENT * search_element ( const LIST * list, const void * data )
{
    LISTELEMENT *element = NULL;

    if ( ( list != NULL ) && ( data != NULL ) )
    {
        for ( element = list_head( list ); element != NULL; element = list_next( element ) )
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
