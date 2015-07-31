/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: list.c */

#include "list.h"

/*  Complexidade == O(1)  */
LIST * list_initialize ( void ( * destroy ) ( void * data ) )
{
    LIST *list = NULL;

    list = ( LIST * ) malloc ( sizeof ( LIST ) );

    if ( list != NULL )
    {
        list->size = 0;

        list->match = NULL;
        list->destroy = destroy;

        list->head = NULL;
        list->tail = NULL;
    }

    return list;
}

/*  Complexidade == O(n); sendo n := número de elementos na lista   */
void list_destroy ( LIST * list )
{
    void *data = NULL;

    /*  caso  a  função  "destroy"  não tenha sido expecificada, será impossível
        fazer a remoção dos elementos da lista
    */
    if ( ( list != NULL ) && ( list->destroy != NULL ) )
    {
        /*  se  a  lista  for destruida antes de receber qualquer elemento, essa
            verificação  impedirá  a  liberação  de  memória  que  não  fora nem
            alocada
        */
        while ( list_size( list ) != 0 )
        {
            /*  irá remover sempre a cabeça da lista    */
            list_remove_next ( list, NULL, &data );
            list->destroy ( data );
        }

        /*  remover a lista da memória  */
        free ( list );
    }
}

/*  Complexidade == O(1)  */
static LISTELEMENT * alloc_list ( void * data )
{
    LISTELEMENT *new = NULL;

    if ( data != NULL )
    {
        new = ( LISTELEMENT * ) malloc ( sizeof ( LISTELEMENT ) );

        if ( new != NULL )
        {
            new->data = data;
            new->next = NULL;
        }
    }

    return new;
}

/*  Complexidade == O(1)  */
int list_insertion_next ( LIST * list, LISTELEMENT * element, void * data )
{
    LISTELEMENT *next = NULL, *new = NULL;

    new = alloc_list ( data );

    /*  expressão  impede que se insira um elemento na lista vazia e em uma nova
        estrutura que não pode ser criada
    */
    if ( ( list == NULL ) || ( new == NULL ) )
        return ERROR;

    else
    {
        /*  o novo elemento deverá ser adicionado na cabeça.    */
        if ( element == NULL )
        {
            /*  neste  caso  significa  que  a  lista esta vazia e o ponteiro da
                cauda, assim como o da cabeça, irá apontar para o elemento a ser
                inserido
            */
            if ( list_size( list ) == 0 )
                list->tail = new;

            /*  se  o elemento a ser adicionado seja o primeiro da lista, o next
                manterá  seu  valor  nulo para garantir que só haja realmente um
                elemento
            */
            next = list->head;
            list->head = new;
        }

        else
        {
            /*  caso  o  elemento  a  ser  adicionado  seja o último da lista, a
                cauda da lista deverá apontar para esse novo elemento
            */
            if ( element == list->tail )
                list->tail = new;

            next = element->next;
            element->next = new;
        }

        new->next = next;
        list->size++;
    }

    return SUCESS;
}

/*  Complexidade == O(1)  */
static void remove_element ( LISTELEMENT * element )
{
    free ( element );
}

/*  Complexidade == O(1)  */
int list_remove_next ( LIST * list, LISTELEMENT * element, void ** data )
{
    LISTELEMENT *rem = NULL;

    /*  "list_size ( list ) == 0"  impede  a remoção de um elemento de uma lista
        vazia  e  que  seja  removido  um  elemento  de  uma  lista  que  não há
        referências para a sua cabeça ou sua cauda
    */
    if ( ( list == NULL ) || ( list_size( list ) == 0 ) || ( data == NULL ) || ( list->head == NULL ) || ( list->tail == NULL ) )
        return ERROR;

    else
    {
        /*  o element a ser removido é a cabeça.    */
        if ( ( element == NULL ) || list_is_head( list, element ) )
        {
            rem = list->head;
            /*  caso só aja element na lista ( list->head )->next == NULL   */
            list->head = ( list->head )->next;

            /*  quando o último elemento for removido a cauda apontará para nulo
                assim  como  a  cabeça
            */
            if ( list->head == NULL )
                list->tail = NULL;
        }

        else
        {
            /*  caso  o  elemento a ser removido seja o último da lista, a cauda
                da lista deverá apontar o penúltimo elemento
            */
            if ( list_next( element ) == list->tail )
                list->tail = element;

            rem = element->next;
        }

        *data = rem->data;

        remove_element ( rem );

        list->size--;
    }

    return SUCESS;
}
