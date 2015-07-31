/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: bistree.c  */

#include "bistree.h"

/*  */
void bistree_destroy ( BISTREE * bistree )
{

}

/*  */
static AVLNODE * alloc_avlnode ( void * data )
{
    AVLNODE *new = NULL;

    new = ( AVLNODE * ) malloc ( sizeof ( AVLNODE ) );

    if ( new != NULL )
    {
        new->data = data;

        new->hidden = SHOW;
        new->height = LEAF;
    }

    return new;
}

/*  */
static BITREENODE * create_bistreenode ( void * data )
{
    BITREENODE *new = NULL;

    new = ( BITREENODE * ) malloc ( sizeof ( BITREENODE ) );

    if ( new != NULL )
    {
        new->data = alloc_avlnode ( data );

        new->dad = NULL;
        new->left = NULL;
        new->right = NULL;
    }

    return new;
}

/*  */
static int get_height ( BITREENODE * node )
{
    if ( has_both_son( node ) )
    {
        if ( ( bistree_avl_height_right_son( node ) == 1 ) && ( bistree_avl_height_left_son( node ) != LEAF ) )
            return AVL_RL_ROTATE;

        else if ( ( bistree_avl_height_left_son( node ) == -1 ) && ( bistree_avl_height_right_son( node ) != LEAF ) )
            return AVL_LR_ROTATE;

        else
            return ( bistree_avl_height_left_son( node ) - bistree_avl_height_right_son( node ) );
    }

    else if ( has_left_son( node ) )
    {
        if ( bistree_avl_height_left_son( node ) == -1 )
            return AVL_LR_ROTATE;

        return ( ( bistree_avl_height_left_son( node ) == LEAF ) ? AVL_LEFT_HEAVY : ( bistree_avl_height_left_son( node ) + 1 ) );
    }

    else if ( has_right_son( node ) )
    {
        if ( bistree_avl_height_right_son( node ) == 1 )
            return AVL_RL_ROTATE;

        return ( ( bistree_avl_height_right_son( node ) == LEAF ) ? AVL_RIGHT_HEAVY : ( bistree_avl_height_right_son( node ) - 1 ) );
    }

    else
        return LEAF;
}

/*  */
static BITREENODE * rotate_right ( BITREENODE * node )
{
    BITREENODE *rtnval = NULL, *tmp = NULL;

    rtnval = node->left;
    tmp = rtnval->right;
    rtnval->right = node;
    node->left = tmp;

    bistree_avl_height( rtnval->right ) = get_height ( rtnval->right );
    bistree_avl_height( rtnval ) = get_height ( rtnval );

    return rtnval;
}

/*  */
static BITREENODE * rotate_left ( BITREENODE * node )
{
    BITREENODE *rtnval = NULL, *tmp = NULL;

    rtnval = node->right;
    tmp = rtnval->left;
    rtnval->left = node;
    node->right = tmp;

    bistree_avl_height( rtnval->left ) = get_height ( rtnval->left );
    bistree_avl_height( rtnval ) = get_height ( rtnval );

    return rtnval;
}

/*  */
static BITREENODE * rotate_right_left ( BITREENODE * node )
{
    node->right = rotate_right ( node->right );

    return rotate_left ( node );
}

/*  */
static BITREENODE * rotate_left_right ( BITREENODE * node )
{
    node->left = rotate_left ( node->left );

    return rotate_right ( node );
}

/*  */
static BITREENODE * verifiy_balance ( BITREENODE * node )
{
    int balance = LEAF;

    /*  atualiza a altura do node   */
    balance = get_height ( node );
    bistree_avl_height( node ) = balance;

    printf ( "DATA = %d | BALANCE = %d\n", * ( ( int * ) bistree_avl_data( node ) ), balance );

    if ( balance == AVL_RR_ROTATE )
    {
        printf ( "Rotate right right\n" );
        return rotate_right ( node );
    }

    else if ( balance == AVL_LL_ROTATE )
    {
        printf ( "Rotate left left\n" );
        return rotate_left ( node );
    }

    else if ( balance == AVL_LR_ROTATE )
    {
        printf ( "Rotate left right\n" );
        return rotate_left_right ( node );
    }

    else if ( balance == AVL_RL_ROTATE )
    {
        printf ( "Rotate right left\n" );
        return rotate_right_left ( node );
    }

    /*  caso  não  precise  rotacionar  para  nenhum  lado,  o  valor  do node é
        alterado e ele é simplesmente retornado
    */
    else
        return node;
}

/*  */
static BITREENODE * recursive_add_avl ( BISTREE * bistree, BITREENODE * node, BITREENODE * add )
{
    int compare = 0;

    if ( node != NULL )
    {
        /*  não  há  um  caso  de  balanço  igual  a  zero porque não é possível
            adicionar  chaves repetidas -- poderia ser colocado apenas um "else"
            mas,  dessa  forma,  poderia haver dúvidas quanto ao caso do balanço
            ser  igual  a  zero;  o  que  não  ocorre  por  causa  da chamada de
            "bistree_lookup" antes do processo de adicionar o novo node
        */
        compare = bistree->compare ( bistree_avl_data( node ), bistree_avl_data( add ) );

        if ( compare < 0 )
            node->right = recursive_add_avl ( bistree, node->right, add );

        else if ( compare > 0 )
            node->left = recursive_add_avl ( bistree, node->left, add );

        /*  fazer aqui a verificação para saber se há, ou não, que rebalançear a
            árvore
        */
        return verifiy_balance ( node );
    }

    /*  há  três  casos onde a subárvore apontada por node pode ser nula, quando
        for  um  dos filhos de uma folha, quando for um nó antes de uma folha ou
        quando for a primeira inserssão na árvore
    */
    else
        return add;
}

/*  */
int bistree_insert ( BISTREE * bistree, void * data )
{
    BITREENODE *new = NULL;

    /*  só será adicionado o elmento caso ele não exista previamente na árvore*/
    if ( ( bistree != NULL ) && ( data != NULL ) && ( bistree_lookup ( bistree, data ) == NULL ) )
    {
        new = create_bistreenode ( data );

        if ( new != NULL )
        {
            bistree->root = recursive_add_avl ( bistree, bistree->root, new );
            bistree_size( bistree )++;

            return SUCESS;
        }
    }

    return ERROR;
}

/*  */
int bistree_remove ( BISTREE * bistree, void * data )
{
    return ERROR;
}

/*  */
static void * recursive_lookup ( BISTREE * bistree, BITREENODE * node, void * data )
{
    int balance = 0;

    if ( node != NULL )
    {
        balance = bistree->compare ( node->data, data );

        if ( balance < 0 )
            return recursive_lookup ( bistree, node->right, data );

        else if ( balance > 0 )
            return recursive_lookup ( bistree, node->left, data );

        /*  o  elmento  já  se  encontra  presente na árovre -- se o elemento se
            encontra  presente  mas  fora  removido  logicamente,  não  irá  ser
            retornado e, neste caso, se retorna nulo
        */
        else
            return ( bistree_avl_hidden( node ) == SHOW ) ? bistree_avl_data( node ) : NULL;
    }

    /*  se  node  for  nulo  --  ou  seja,  onde  possivelmente se encontraria o
        não está presente na árvore
    */
    return NULL;
}

/*  */
void * bistree_lookup ( BISTREE * bistree, void * data )
{
    return ( ( bistree != NULL ) && ( data != NULL ) ) ? recursive_lookup ( bistree, bistree->root, data ) : NULL;
}
