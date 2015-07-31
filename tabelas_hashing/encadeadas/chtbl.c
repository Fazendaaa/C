/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: chtbl.c    */

#include "chtbl.h"

/*  */
static LIST ** alloc_array_list ( int size, int ( * match ) ( const void * key_1, const void * key_2 ), void ( * destroy ) ( void * data )  )
{
    LIST **list = NULL;
    unsigned int i = 0;

    list = ( LIST ** ) malloc ( sizeof ( LIST * ) * size );

    if ( list != NULL )
    {
        for ( ; i < size; i++ )
        {
            list[ i ] = list_initialize ( destroy );

            if ( list[ i ] != NULL )
                list[ i ]->match = match;
        }
    }

    return list;
}

/*  */
CHTBL *  chtbl_initialize ( int buckets, int ( * h ) ( const void * key ), int ( * match ) ( const void * key_1, const void * key_2 ), void ( * destroy ) ( void * data ) )
{
    CHTBL *new = NULL;

    if ( buckets > 0 )
    {
        new = ( CHTBL * ) malloc ( sizeof ( CHTBL ) );

        if ( new != NULL )
        {
            new->buckets = buckets;

            new->h = h;
            new->match = match;
            new->destroy = destroy;

            new->size = 0;
            new->table = alloc_array_list ( buckets, match, destroy );
        }
    }

    return new;
}

/*  */
void chtbl_destroy ( CHTBL * chtbl )
{
    unsigned int i = 0;

    if ( ( chtbl != NULL ) && ( chtbl->destroy != NULL ) )
    {
        for ( ; i < chtbl->buckets; i++ )
            list_destroy ( chtbl->table[ i ] );

        free ( chtbl->table );
        free ( chtbl );
    }
}

/*  É  possível  fazer essa função ficar menor e com menos variáveis; o contra é
    que perderá sua legibilidade atual
*/
int chtbl_insert ( CHTBL * chtbl, void * data )
{
    unsigned int pos = 0, retval = ERROR;
    LIST *list = NULL;

    if ( ( chtbl != NULL ) && ( data != NULL ) )
    {
        /*  só é possível adicionar elementos que não são existem na tabela */
        if ( chtbl_lookup ( chtbl, data ) == NULL )
        {
            pos = chtbl->h ( data ) % chtbl->buckets;
            list = chtbl->table[ pos ];

            /*  assim  como  em  uma  fila, o elemento sempre será adicionado no
                final da lista encadeada
            */
            if ( ( retval = list_insertion_next ( list, list->tail, data ) ) )
                chtbl->size++;
        }
    }

    return retval;
}

/*  */
void * chtbl_remove ( CHTBL * chtbl, void * data )
{
    LISTELEMENT *element = NULL, *prev = NULL;
    LIST *list = NULL;
    unsigned int pos = 0;
    void *element_data = NULL;

    if ( ( chtbl == NULL ) || ( data == NULL ) )
        return NULL;

    else
    {
        pos = chtbl->h ( data ) % chtbl->buckets;
        list = chtbl->table[ pos ];

        /*  significa que há pelo menos um elemento naquela posição da tabela de
            hashing
        */
        if ( list_size( list ) != 0 )
        {
            /*  caso o elemento seja encontrado ele será retornado, do contŕaio,
                será  retornado nulo porque a lista toda será percorrida -- como
                a ideia de hashing é ser de acesso constante, em uma hashing bem
                feita  o  for  terá de rodar, no máximo, duas vezes; só que isso
                dependerá da função de hashing que o usuário passar
            */
            for ( element = list_head( list ); element != NULL; element = list_next( element ) )
            {
                if ( !list->match( list_data( element ), data ) )
                    break;

                prev = element;
            }

            /*  caso  element  seja  igual a nulo significa que o dado procurado
                não  se  encontra  na  tabela;  do  contrário,  o  elemento será
                removido  e,  em  caso  de  sucesso,  o  tamanho da hashing será
                reduzido
            */
            if ( ( element != NULL ) && ( list_remove_next ( list, prev, &element_data ) ) )
                chtbl->size--;
        }

        /*  retornará o dado do elemento removido -- caso ele exista    */
        return element_data;
    }
}

/*  */
void * chtbl_lookup ( const CHTBL * chtbl, void * data )
{
    LISTELEMENT *element = NULL;
    LIST *list = NULL;
    unsigned int pos = 0;
    void *element_data = NULL;

    if ( ( chtbl == NULL ) || ( data == NULL ) )
        return NULL;

    else
    {
        pos = chtbl->h ( data ) % chtbl->buckets;
        list = chtbl->table[ pos ];

        if ( list_size( list ) != 0 )
        {
            for ( element = list_head( list ); element != NULL; element = list_next( element ) )
            {
                if ( !list->match( list_data( element ), data ) )
                    break;
            }

            if ( element != NULL )
                element_data = list_data( element );
        }
    }

    return element_data;
}
