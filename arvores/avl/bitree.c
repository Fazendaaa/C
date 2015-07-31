/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: bitree.c   */

#include "bitree.h"

/*  */
static void free_node ( BITREE * bitree, BITREENODE * node )
{
    if ( ( bitree != NULL ) && ( bitree->destroy != NULL ) && ( node != NULL ) )
    {
        bitree->destroy ( node->data );
        free ( node );
    }
}

/*  */
BITREE * bitree_initialize ( void ( * destroy ) ( void * data ), int ( * compare ) ( const void * key_1, const void * key_2 ) )
{
    BITREE *new = NULL;

    new = ( BITREE * ) malloc ( sizeof ( BITREE ) );

    if ( new != NULL )
    {
        new->size = 0;
        new->root = NULL;

        new->compare = compare;
        new->destroy = destroy;
    }

    return new;
}

/*  */
void bitree_destroy ( BITREE * bitree )
{
    if ( ( bitree != NULL ) && ( bitree->destroy != NULL ) )
    {
        bitree_remove_left ( bitree, bitree->root );
        free ( bitree );
    }
}

static BITREENODE * alloc_bitreenode ( void * data )
{
    BITREENODE *new = NULL;

    if ( data != NULL )
    {
        new = ( BITREENODE * ) malloc ( sizeof ( BITREENODE ) );

        if ( new != NULL )
        {
            new->data = data;

            new->dad = NULL;
            new->left = NULL;
            new->right = NULL;
        }
    }

    return new;
}

/*  */
int bitree_insertion_left ( BITREE * bitree, BITREENODE * node, void * data )
{
    BITREENODE *new = NULL;

    new = alloc_bitreenode ( data );

    if ( ( bitree == NULL ) || ( new == NULL ) )
        return ERROR;

    else
    {
        /*  inserssão  na  raiz;  permite a inserssão apenas se a árvore estiver
            vazia
        */
        if ( ( node == NULL ) && ( bitree_size( bitree ) == 0 ) )
            bitree->root = new;

        /*  o  novo  dado só poderá ser inserido em determinada posição caso
            não haja outro dado já lá posicionado
        */
        else if ( bitree_left( node ) == NULL )
        {
            node->left = new;
            new->dad = node;
        }

        /*  se  nenhuma  das  condições  acima forem garantidas, a inserssão não
            será possivel
        */
        else
        {
            free_node ( bitree, new );

            return ERROR;
        }

        bitree->size++;

        return SUCESS;
    }
}

/*  */
int bitree_insertion_right ( BITREE * bitree, BITREENODE * node, void * data )
{
    BITREENODE *new = NULL;

    new = alloc_bitreenode ( data );

    if ( ( bitree == NULL ) || ( new == NULL ) )
        return ERROR;

    else
    {
        if ( ( node == NULL ) && ( bitree_size( bitree ) == 0 ) )
            bitree->root = new;

        else if ( bitree_right( node ) == NULL )
        {
            node->right = new;
            new->dad = node;
        }

        else
        {
            free_node ( bitree, new );

            return ERROR;
        }

        bitree->size++;

        return SUCESS;
    }
}

/*  */
static BITREENODE * recursive_remove ( BITREE * bitree, BITREENODE * node )
{
    if ( node != NULL )
    {
        node->left = recursive_remove ( bitree, node->left );
        node->right = recursive_remove ( bitree, node->right );

        free_node ( bitree, node );
        bitree->size--;
    }

    return NULL;
}

/*  */
void bitree_remove_left ( BITREE * bitree, BITREENODE * node )
{
    /*  permite remoção apenas se a árvore não estiver vazia    */
    if ( ( bitree != NULL ) && ( bitree_size( bitree ) != 0 ) )
    {
        /*  remoção a partir da raiz    */
        if ( ( node == NULL ) || ( bitree->root == node ) )
            bitree->root = recursive_remove ( bitree, bitree->root );

        else
            node->left = recursive_remove ( bitree, node->left );
    }
}

/*  */
void bitree_remove_right ( BITREE * bitree, BITREENODE * node )
{
    if ( ( bitree != NULL ) && ( bitree_size( bitree ) != 0 ) )
    {
        if ( ( node == NULL ) || ( bitree->root == node ) )
            bitree->root = recursive_remove ( bitree, bitree->root );

        else
            node->right = recursive_remove ( bitree, node->right );
    }
}

/*  */
static BITREENODE * cpy_bitreenode ( BITREENODE * node, size_t size )
{
    void *data = NULL;

    data = malloc ( size );
    memcpy ( data, node->data, size );

    return alloc_bitreenode ( data );
}

/*  */
static BITREENODE * recursive_cpy ( BITREE * bitree, BITREENODE * node, size_t size )
{
    BITREENODE *new = NULL;

    if ( ( node != NULL ) && ( bitree->compare( ( bitree->root )->data, node->data ) ) )
    {
        new = cpy_bitreenode ( node, size );

        if ( new != NULL )
        {
            new->dad = node;
            new->left = recursive_cpy ( bitree, node->left, size );
            new->right = recursive_cpy ( bitree, node->right, size );

            bitree->size++;
        }
    }

    return new;
}

/*  */
static BITREENODE * recursive_root_search ( BITREENODE * node, int side )
{
    BITREENODE *element = NULL, *next = NULL, *other = NULL;

    if ( node != NULL )
    {
        next = ( side == LEFT ) ? node->left : node->right;
        element = recursive_root_search ( next, side );

        if ( element == NULL )
        {
            other = ( side == RIGHT ) ? node->left : node->right;
            element = recursive_root_search ( other, side );

            if ( element == NULL )
                element = node;
        }
    }

    return element;
}

/*  */
static BITREENODE * search_new_root ( BITREE * bitree, int side )
{
    if ( ( side == LEFT ) || ( side == RIGHT ) )
        return recursive_root_search ( bitree->root, side );

    else
        return NULL;
}

/*  */
BITREE * bitree_merge ( BITREE * left, BITREE * right, size_t size )
{
    BITREE *new = NULL;

    if ( ( left != NULL ) && ( right != NULL ) && ( size > 0 ) )
    {
        new = bitree_initialize ( left->destroy, left->compare );

        if ( new != NULL )
        {
            new->root = cpy_bitreenode ( search_new_root ( right, LEFT ), size );

            new->root->left = recursive_cpy ( new, left->root, size );
            new->root->right = recursive_cpy ( new, right->root, size );
        }
    }

    return new;
}
