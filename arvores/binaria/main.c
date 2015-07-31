/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: main.c */

#include <stdio.h>
#include "bitree.h"

#define SIZE      5
#define DIFERENCE 2

void destroy ( void * data );
int compare_element ( const void * key_1, const void * key_2 );
static void ** alloc_ptr ( const int size );
static BITREENODE * search_left ( BITREENODE * node );
static BITREENODE * search_right ( BITREENODE * node );
static BITREENODE * search_element ( const BITREE * bitree, const void * data );
static void print_tree ( const BITREE * bitree );

/*  programa  apenas  para debbugar as estrturas feitas de árvore binária. Neste
    caso, SIZE  tem  que  ter, no mínimo, o valor 5 e DIFERENCE tem que possuir,
    no  mínimo,  ( SIZE + 1 ) -- tais valores podem alterar caso mude-se o valor
    de  test_1  e/ou  test_2, não recomendado fazer isso a não ser que entenda o 
    código
*/
int main ( int argc, char ** argv )
{
    BITREE *tree_1 = NULL, *tree_2 = NULL, *tree_3 = NULL, *tree_merge = NULL;
    BITREENODE *element = NULL;
    void **ptr_1 = NULL, **ptr_2 = NULL, **ptr_3 = NULL;
    unsigned int i = 0, test_1 = 3, test_2 = 5;

    /*  carregam as árvores a serem utilizadas  */
    tree_1 = bitree_initialize ( destroy, compare_element );
    tree_2 = bitree_initialize ( destroy, compare_element );
    tree_3 = bitree_initialize ( destroy, compare_element );

    /*  prepara os ponteiros que receberão os dados a serem utilizados  */
    ptr_1 = alloc_ptr ( SIZE );
    ptr_2 = alloc_ptr ( SIZE + DIFERENCE );
    ptr_3 = alloc_ptr ( SIZE );

    if ( ( tree_1 == NULL ) || ( tree_2 == NULL ) || ( tree_3 == NULL ) || ( ptr_1 == NULL ) || ( ptr_2 == NULL ) || ( ptr_3 == NULL ) )
        printf ( "The tree and/or the array couldn't be created\n" );

    else
    {
        /*  inserssões nas árovres  */

        /*  na primeria ávore, partindo da raiz, haverá apenas filhos a esquerda
        */
        for ( ; i < SIZE; i++ )
            bitree_insertion_left ( tree_1, search_left ( tree_1->root ), ptr_1 [ i ] );

        /*  na  segunda  ávore, partindo da raiz, haverá apenas filhos a direita
        */
        for ( i = 0; i < SIZE + DIFERENCE; i++ )
            bitree_insertion_right ( tree_2, search_right ( tree_2->root ), ptr_2 [ i ] );

        /*  imprime as árvores  */
        printf ( "First tree\n" );
        print_tree ( tree_1 );

        printf ( "Second tree\n" );
        print_tree ( tree_2 );

        /*  junção dos elmentos da primeira com a segunda árvore    */
        tree_merge =  bitree_merge ( tree_1, tree_2, sizeof ( int ) );
        printf ( "Merge tree\n" );
        print_tree ( tree_merge );

        /*  removem-se todas as subárvores do dado test_1 na primeira árvore*/
        element = search_element ( tree_1, &test_1 );
        if ( element != NULL )
            printf ( "First tree -- remove elements after element = %d\n", * ( ( int * ) element->data ) );
        bitree_remove_left ( tree_1, element );
        print_tree ( tree_1 );

        /*  removem-se todas as subárvores do dado test_2 na segunda árvore */
        element = search_element ( tree_2, &test_2 );
        if ( element != NULL )
            printf ( "Second tree -- remove elements after element = %d\n", * ( ( int * ) element->data ) );
        bitree_remove_right ( tree_2, element );
        print_tree ( tree_2 );

        /*  mesmo  com  um  elementos  removidos  da primeira e segunda árvores,
            tree_merge  --  que  nada mais é que a junção dos elementos das duas
            árvores  --  não  terá esses elementos  removidos  de  sua estrutura
            porque o valor de cada elemento foi copiado e não referenciado
        */
        printf ( "Merge tree\n" );
        print_tree ( tree_merge );

        /*  ávore que haverá, somente na raiz, filhos a esquerda e a direita*/
        bitree_insertion_left ( tree_3, search_left ( tree_3->root ), ptr_3 [ SIZE / 2 ] );

        for ( i = 0; i < SIZE; i++ )
        {
            if ( * ( ( int * ) ptr_3 [ i ] ) < * ( ( int * ) ptr_3 [ SIZE / 2 ] ) )
                bitree_insertion_left ( tree_3, search_left ( tree_3->root ), ptr_3 [ i ] );

            else if ( * ( ( int * ) ptr_3 [ i ] ) == * ( ( int * ) ptr_3 [ SIZE / 2 ] ) )
                continue;

            else
                bitree_insertion_right ( tree_3, search_right ( tree_3->root ), ptr_3 [ i ] );
        }

        printf ( "Third tree\n" );
        print_tree ( tree_3 );


        /*  destrói  os  dados  que  cada  árvore  possui  e, logo em seguida, a
            árvore em si
        */
        bitree_destroy ( tree_1 );
        bitree_destroy ( tree_2 );
        bitree_destroy ( tree_merge );
        bitree_destroy ( tree_3 );
        /*  como   os   inteiros  armazenados  na  memória  já  foram  liberados
            através  de  "bitree_destroy", resta apenas liberar os ponteiros que
            os referenciavam
        */
        free ( ptr_1 );
        free ( ptr_2 );
        free ( ptr_3 );
    }

    return 0;
}

/*  irá liberar todos os dados armazenados na memória dentro da árvore

    Complexidade == O(1)
*/
void destroy ( void * data )
{
    free ( data );
}

/*  retorna a diferença dos valores passados

    Complexidade == O(1)
*/
int compare_element ( const void * key_1, const void * key_2 )
{
    return ( * ( ( int * ) key_1 ) - * ( ( int * ) key_2 ) );
}

/*    Complexidade == O(n); sendo n := número de elementos da árvore    */
static void ** alloc_ptr ( const int size )
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

/*  procura o último filho a esquerda de uma determinada subarvore

    Pior caso := o elemento procurado não existe ou está em uma folha
    Complexidade == O(n); sendo n := número de elementos a direita

    Caso médio := o elemento procurado está na metade do caminho
    Complexidade == O(n/2);

    Melhor caso := o elemento procurado é a raiz da subarvore
    Complexidade == O(1);
*/
static BITREENODE * search_left ( BITREENODE * node )
{
    BITREENODE *search = NULL, *prev = NULL;

    if ( node != NULL )
    {
        for ( search = node; search != NULL; search = search->left )
            prev = search;

        return prev;
    }

    else
        return NULL;
}

/*  procura o último filho a direita de uma determinada subarvore

    Pior caso := o elemento procurado não existe ou está em uma folha
    Complexidade == O(n); sendo n := número de elementos a direita

    Caso médio := o elemento procurado está na metade do caminho
    Complexidade == O(n/2);

    Melhor caso := o elemento procurado é a raiz da subarvore
    Complexidade == O(1);
*/
static BITREENODE * search_right ( BITREENODE * node )
{
    BITREENODE *search = NULL, *prev = NULL;

    if ( node != NULL )
    {
        for ( search = node; search != NULL; search = search->right )
            prev = search;

        return prev;
    }

    else
        return NULL;
}

/*  realiza  uma  pesquisa recursivamente pos ordenada nas subarvores de node em
    busca do elemento que possua data

    Complexidade == O(1)
*/
static BITREENODE * recursive_search ( BITREENODE * node, const void * data )
{
    BITREENODE *element = NULL;

    if ( node != NULL )
    {
        element = recursive_search ( node->left, data );

        /*  caso  não encontre nada nos filhos da esquerda, realiza a pesquisa a
            direita
        */
        if ( element == NULL )
            element = recursive_search ( node->right, data );

        /*  verifica se o elemento do node é o procurado    */
        if ( !compare_element ( node->data, data ) )
            element = node;
    }

    /*  caso node seja igual a nulo ou se o elemento desejado não for encontrado
    */
    return element;
}

/*  procura a presença de um determinado dado na árvore

    Pior caso := o elemento procurado não existe ou está em uma folha
    Complexidade == O(n); sendo n := número de elementos na árvore

    Caso médio := o elemento procurado está na metade da árvore
    Complexidade == O(n/2);

    Melhor caso := o elemento procurado é a raiz da árvore
    Complexidade == O(1);
*/
static BITREENODE * search_element ( const BITREE * bitree, const void * data )
{
    BITREENODE *element = NULL;

    if ( ( bitree != NULL ) && ( data != NULL ) )
        element = recursive_search ( bitree->root, data );

    return element;
}

/*  dado  um node, irá imprimir seu conteúdo antes de mandar imprimir o conteúdo
    de seus filhos

    Complexidade == O(1)
*/
static void recursive_node_print_pre_ord ( const BITREENODE * node )
{
    if ( node != NULL )
    {
        if ( node->data != NULL )
            printf ( "Element data = %d\n", * ( ( int * ) node->data ) );

        recursive_node_print_pre_ord ( node->left );
        recursive_node_print_pre_ord ( node->right );
    }
}

/*  dado  um node, irá percorrer todos os possíveis filhos a esquerda para então
    imprimir  o  conteúdo  e somente então invocar a função para que os filhos a
    direita sejam impressos

    Complexidade == O(1)
*/
static void recursive_node_print_in_ord ( const BITREENODE * node )
{
    if ( node != NULL )
    {
        recursive_node_print_in_ord ( node->left );

        if ( node->data != NULL )
            printf ( "Element data = %d\n", * ( ( int * ) node->data ) );

        recursive_node_print_in_ord ( node->right );
    }
}

/*  dado  um  node,  irá visitar todos os possíveis filhos, seja a esquerda ou a
    direita antes de imprimir seu conteúdo

    Complexidade == O(1)
*/
static void recursive_node_print_pos_ord ( const BITREENODE * node )
{
    if ( node != NULL )
    {
        recursive_node_print_pos_ord ( node->left );
        recursive_node_print_pos_ord ( node->right );

        if ( node->data != NULL )
            printf ( "Element data = %d\n", * ( ( int * ) node->data ) );
    }
}

/*  imprime  a raiz da árvore e faz a chamada para a impressão recursiva de cada
    item dela [ da árvore ] -- neste caso foi utilizada a impressão pos ordenada
    mas tanto a pre ordenada ou a ordenada poderiam ser utilizadas

    Complexidade == O(n); sendo n := número de elementos da árvore
*/
static void print_tree ( const BITREE * bitree )
{
    if ( bitree != NULL )
    {
        if ( bitree->root->data != NULL )
            printf ( "[ Root ] Data = %d\n", * ( ( int * ) bitree->root->data ) );

        recursive_node_print_pos_ord ( bitree->root );
        printf ( "\n" );
    }
}
