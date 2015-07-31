/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: clist.h    */

#include "clist.h"

/*  Complexidade == O(1)  */
CLIST * clist_initialize ( void ( * destroy ) ( void * data ) )
{
    CLIST *new = NULL;

    new = ( CLIST * ) malloc ( sizeof ( CLIST ) );

    if ( new != NULL )
    {
        new->size = 0;

        new->match = NULL;
        new->destroy = destroy;

        new->head = NULL;
    }

    return new;
}

/*  Complexidade == O(n); sendo n := número de elementos na lista   */
void clist_destroy ( CLIST * list )
{
    void *data = NULL;

    /*  caso  a  função  "destroy"  não tenha sido expecificada, será impossível
        fazer a remoção dos elementos da lista
    */
    if ( ( list != NULL ) && ( list->destroy != NULL ) )
    {
        while ( clist_size( list ) != 0 )
        {
            /*  sempre irá remover a cabeça da lista    */
            clist_remove_next ( list, NULL, &data );
            list->destroy ( data );
        }

        /*  remover a lista da memória  */
        free ( list );
    }
}

/*  Complexidade == O(1)  */
static CLISTELEMENT * alloc_clist ( void * data )
{
    CLISTELEMENT *new = NULL;

    if ( data != NULL )
    {
        new = ( CLISTELEMENT * ) malloc ( sizeof ( CLISTELEMENT ) );

        if ( new != NULL )
        {
            new->data = data;
            new->next = NULL;
        }
    }

    return new;
}

/*  Pior caso := o elemento a ser adicionado será na cabeça
    Complexidade == O(n); sendo n := número de elementos na lista

    Melhor caso := o elemento será adicionado sem ser na cabeça
    Complexidade == O(1);
*/
int clist_insertion_next ( CLIST * list, CLISTELEMENT * element, void * data )
{
    CLISTELEMENT *new = NULL, *next = NULL;

    new = alloc_clist ( data );

    /*  expressão  impede que se insira um elemento na lista vazia e em uma nova
        estrutura que não pode ser criada
    */
    if ( ( list == NULL ) || ( new == NULL ) )
        return ERROR;

    else
    {
        /*  inserssão na cabeça da lista    */
        if ( element == NULL )
        {
            /*  caso  seja  a  primeira  inserssão,  tem  que  fazer  com  que o
                próximo  elemento  da  cabeça  aponte  para  ele mesmo mantendo,
                dessa maneira, a propriedade circular da lista
            */
            if ( clist_size( list ) == 0 )
                new->next = new;

            else
            {
                new->next = list->head;

                /*  percorre  a lista para conectar o último elemento com a nova
                    cabeça
                */
                for ( next = clist_head( list ); clist_next( next ) != clist_head( list ); next = clist_next( next )  );

                next->next = new;
            }

            list->head = new;
        }

        else
        {
            new->next = element->next;
            element->next = new;
        }

        list->size++;

        return SUCESS;
    }
}

/*  Complexidade == O(1)  */
static void remove_element ( CLISTELEMENT * element )
{
    free ( element );
}

/*  Pior caso := o elemento a ser removido será a cabeça
    Complexidade == O(n); sendo n := número de elementos na lista

    Melhor caso := o elemento será removido não é a cabeça
    Complexidade == O(1);
*/
int clist_remove_next ( CLIST * list, CLISTELEMENT * element, void ** data )
{
    CLISTELEMENT *rem = NULL, *next = NULL;

    /*  "dlist_size ( list ) == 0" impede  a remoção de um elemento de uma lista
        vazia  e  que  seja  removido  um  elemento  de  uma  lista  que  não há
        referências para a sua cabeça ou sua cauda
    */
    if ( ( list == NULL ) || ( clist_size( list ) == 0 ) || ( list->head == NULL ) || ( data == NULL ) )
        return ERROR;

    else
    {
        /*  remoção na cabeça da lista  */
        if ( ( element == NULL ) || ( clist_is_head( list, element ) ) )
        {
            rem = list->head;

            if ( clist_size( list ) > 1 )
            {
                /*  percorre  a  lista  para  conectar  o  último elemento com o
                    elemento seguinte a cabeça já que ela será removida
                */
                for ( next = clist_head( list ); clist_next( next ) != clist_head( list ); next = clist_next( next ) );

                next->next = ( list->head )->next;
                list->head = ( list->head )->next;
            }

            /*  quando  haver apenas a cabeça para ser removida, garante que sua
                referência será apagada
            */
            else
                list->head = NULL;
        }

        else
        {
            rem = element->next;
            /*  recebe  o  elemento  seguinte  ao  elemento  a  ser  removido no
                elemento  anterior,  mantendo,  dessa  maneira,  a  estutura  da
                lista
            */
            element->next = rem->next;
        }

        /*  transfere para "data" o conteúdo do elemento a ser removido */
        *data = rem->data;

        remove_element ( rem );

        list->size--;

        return SUCESS;
    }
}
