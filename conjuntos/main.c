/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: main.c */

#include <stdio.h>
#include "set.h"

#define SIZE      3
#define DIFERENCE 2

void destroy ( void * data );
int compare_element ( const void * data_1, const void * data_2 );
static void ** alloc_ptr ( int size );
static void print_set ( SET * set );

/*  programa  apenas  para debbugar as estrturas feitas de conjunto. Neste caso,
    SIZE  tem  que  ter,  no  mínimo,  o valor 1 e DIFERENCE tem que possuir, no
    mínimo, ( SIZE + 1 )
*/
int main ( int argc, char ** argv )
{
    SET *set_1 = NULL, *set_2 = NULL, *union_set = NULL, *intersection_set = NULL, *difference_set = NULL;
    void **ptr_1 = NULL, **ptr_2 = NULL, *rem = NULL;
    unsigned int i = 0, test = 0;

    /*  carregam os conjuntos a serem utilizados    */
    set_1 = set_initialize ( compare_element, destroy );
    set_2 = set_initialize ( compare_element, destroy );

    /*  prepara os ponteiros que receberão os dados a serem utilizados  */
    ptr_1 = alloc_ptr ( SIZE );
    ptr_2 = alloc_ptr ( SIZE + DIFERENCE );

    if ( ( set_1 == NULL ) || ( set_2 == NULL ) || ( ptr_1 == NULL ) || ( ptr_2 == NULL ) )
        printf ( "The set and/or the array couldn't be created\n" );

    else
    {
        /*  inserções nos conjuntos */
        for ( ; i < SIZE; i++ )
            set_insert ( set_1, ptr_1[ i ] );

        for ( i = 0; i < SIZE + DIFERENCE; i++ )
            set_insert ( set_2, ptr_2[ i ] );

        /*  imprime os conjuntos    */
        printf ( "First set\n" );
        print_set ( set_1 );

        printf ( "Second set\n" );
        print_set ( set_2 );

        union_set = set_union ( set_1, set_2, sizeof ( int ) );
        printf ( "Union set ( First and Second sets )\n" );
        print_set ( union_set );

        /*  remove-se o primeiro elemento do primeiro conjunto  */
        rem = set_remove ( set_1, ( void * ) &test );
        printf ( "Removed element %d from first set\n", * ( ( int * ) rem ) );
        printf ( "First set -- after remove\n" );
        print_set ( set_1 );

        /*  mesmo  com  um  elemento removido do primeiro conjunto, union_set --
            que  nada  mais é que uma cópia do primeiro conjunto -- não tem esse
            elemento  removido  de  seu  conjunto porque o valor do elemento foi
            copiado e não referenciado
        */
        printf ( "Union set ( First and Second sets )\n" );
        print_set ( union_set );

        /*  recebe  os  elementos comuns ao primeiro e segundo conjunto -- assim
            como "set_union", os valores de cada conjunto são copiados; ou seja,
            pode-se  fazer remoções tanto no primeiro e segundo conjunto que não
            haverá diferença para o conjunto de intersecção
        */
        intersection_set = set_intersection ( set_1, set_2, sizeof ( int ) );
        printf ( "Intersection Set ( First and Second sets )\n" );
        print_set ( intersection_set );

        /*  recebe  os  elementos  não-comuns  ao primeiro e segundo conjunto --
            aqui também os conteúdos da memória são copiados e não referenciados
        */
        difference_set = set_difference ( set_1, set_2, sizeof ( int ) );
        printf ( "Difference Set ( First and Second sets )\n" );
        print_set ( difference_set );

        /*  verifica  se  os  elementos  do  primeiro conjunto estão contidos no
            segundo -- se houver algum que não há, não será válida a afirmação
        */
        if ( set_is_subset ( set_2, set_1 ) )
            printf ( "Second set is subset of the first\n" );

        else
            printf ( "Second set isn't subset of the first\n" );

        /*  destrói  os  dados  que  cada  conjunto possui e, logo em seguida, o
            conjunto em si
        */
        set_destroy ( set_1 );
        set_destroy ( set_2 );
        set_destroy ( union_set );
        set_destroy ( intersection_set );
        set_destroy ( difference_set );

        /*  como  a  função  "set_remove" retorna o dado removido do conjunto, é
            responsabilade de quem a invocou remover esse dado da memória
        */
        free ( rem );
        /*  como   os   inteiros  armazenados  na  memória  já  foram  liberados
            através  do "set_destroy",  resta  apenas  liberar  os ponteiros que
            apontaram para eles
        */
        free ( ptr_1 );
        free ( ptr_2 );
    }

    return 0;
}

/*  irá liberar todos os dados armazenados na memória dentro do conjunto

    Complexidade == O(1)
*/
void destroy ( void * data )
{
    free ( data );
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

/*  função de matching

    Complexidade == O(1)
*/
int compare_element ( const void * data_1, const void * data_2 )
{
    return ( * ( ( int * ) data_1 ) - * ( ( int * ) data_2 ) );
}

/*  Função para imprimir os elementos do conjunto

    Complexidade == O(n); sendo n := número de elementos no conjunto
*/
static void print_set ( SET * set )
{
    SETELEMENT *element = NULL;

    for ( element = set_first( set ); element != NULL; element = set_next( element ) )
        printf ( "Element data: %d\n", * ( ( int * ) set_data( element ) ) );

    printf ( "\n" );
}
