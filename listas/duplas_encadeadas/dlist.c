/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: dlist.c    */

#include "dlist.h"

/*  Complexidade == O(1)  */
DLIST * dlist_initialize ( void ( * destroy ) ( void * data ) )
{
    DLIST *new = NULL;

    new = ( DLIST * ) malloc ( sizeof ( DLIST ) );

    if ( new != NULL )
    {
        new->size = 0;

        new->match = NULL;
        new->destroy = destroy;

        new->head = NULL;
        new->tail = NULL;
    }

    return new;
}

/*  Complexidade == O(n); sendo n := número de elementos na lista   */
void dlist_destroy ( DLIST * list )
{
    void *data = NULL;

    /*  caso  a  função  "destroy"  não tenha sido expecificada, será impossível
        fazer a remoção dos elementos da lista
    */
    if ( ( list != NULL ) && ( list->destroy != NULL ) )
    {
        while ( dlist_size( list ) )
        {
            /*  sempre irá remover a cabeça da lista    */
            dlist_remove ( list, NULL, &data );
            list->destroy ( data );
        }

        /*  remover a lista da memória  */
        free ( list );
    }
}

/*  Complexidade == O(1)  */
static DLISTELEMENT * alloc_dlist ( void * data )
{
    DLISTELEMENT *new = NULL;

    if ( data != NULL )
    {
        new = ( DLISTELEMENT * ) malloc ( sizeof ( DLISTELEMENT ) );

        if ( new != NULL )
        {
            new->data = data;
            new->prev = NULL;
            new->next = NULL;
        }
    }

    return new;
}

/*  Complexidade == O(1)  */
int dlist_insertion_next ( DLIST * list, DLISTELEMENT * element, void * data )
{
    DLISTELEMENT *prev = NULL, *next = NULL, *new = NULL;

    new = alloc_dlist( data );

    /*  expressão  impede que se insira um elemento na lista vazia e em uma nova
        estrutura que não pode ser criada
    */
    if ( ( list == NULL ) || ( new == NULL ) )
        return ERROR;

    else
    {
        /*  caso a inserssão seja realizada na cabeça da lista */
        if ( element == NULL )
        {
            /*  se  a  lista  estiver vazia,  o primeiro elemento a ser inserido
                será tanto a cabeça quanto a cauda dela
            */
            if ( dlist_size( list ) == 0 )
                list->tail = new;

            next = list->head;
            list->head = new;
        }

        else
        {
            if ( list->tail == element )
                list->tail = new;

            prev = element;
            next = element->next;
        }

        new->next = next;
        new->prev = prev;

        /*  caso seja a cabeça, o prev == NULL  */
        if ( prev != NULL )
            prev->next = new;

        /*  caso seja a cauda, o next == NULL   */
        if ( next != NULL )
            next->prev = new;

        list->size++;
    }

    return SUCESS;
}

/*  O interessante neste tipo de inserssão é que a cauda nunca será alterada

    Complexidade == O(1)
*/
int dlist_insertion_prev ( DLIST * list, DLISTELEMENT * element, void * data )
{
    DLISTELEMENT *prev = NULL, *next = NULL, *new = NULL;

    new = alloc_dlist( data );

    if ( ( list == NULL ) || ( new == NULL ) )
        return ERROR;

    else
    {
        if ( dlist_size( list ) == 0 )
        {
            list->head = new;
            list->tail = new;
        }

        else if ( element == NULL )
        {
            next = list->head;
            list->head = new;
        }

        else
        {
            next = element;
            prev = element->prev;
        }

        new->next = next;
        new->prev = prev;

        if ( next != NULL )
            next->prev = new;

        if ( prev != NULL )
            prev->next = new;

        list->size++;
    }

    return SUCESS;
}

/*  Complexidade == O(1)  */
static void remove_element ( DLISTELEMENT * element )
{
    free ( element );
}

/*  Complexidade == O(1)  */
int dlist_remove ( DLIST * list, DLISTELEMENT * element, void ** data )
{
    DLISTELEMENT *rem = NULL;

    /*  "dlist_size ( list ) == 0" impede  a remoção de um elemento de uma lista
        vazia  e  que  seja  removido  um  elemento  de  uma  lista  que  não há
        referências para a sua cabeça ou sua cauda
    */
    if ( ( list == NULL ) || ( dlist_size( list ) == 0 ) || ( data == NULL ) || ( list->head == NULL ) || ( list->tail == NULL ) )
        return ERROR;

    else
    {
        /*  remoção da cabeça da lista  */
        if ( ( element == NULL ) || dlist_is_head( list, element ) )
        {
            /*  caso  o  usuário  passe  NULL  não  haverá  como dereferenciar o
                elemento  para conseguir o seu dado, então, neste caso, se usa o
                ponteiro "rem" para apontar para list->head
            */
            rem = list->head;
            list->head = ( list->head )->next;

            /*  quando o último elemento for removido a cauda apontará para nulo
                assim  como  a  cabeça
            */
            if ( list->head == NULL )
                list->tail = NULL;

            else
                ( list->head )->prev = NULL;
        }

        else
        {
            /*  não  seria  necessário  neste  caso, mas para seguir o padrão do
                código, optou-se por deixar dessa maneira a atribuição
            */
            rem = element;
            if ( element == list->tail )
                list->tail = element->prev;

            ( element->prev )->next = element->next;
        }

        *data = rem->data;

        remove_element ( rem );

        list->size--;
    }

    return SUCESS;
}
