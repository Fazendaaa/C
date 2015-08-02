/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: bistree.h  */

#ifndef BISTREE_H_
#define BISTREE_H_

#include <stdlib.h>
#include "bitree.h"

/* --------------------------------- MACROS --------------------------------- */

#define SHOW             1
#define HIDE             0

#define LEAF             0

#define AVL_RIGHT_HEAVY -1
#define AVL_LEFT_HEAVY   1

#define AVL_LL_ROTATE   -2
#define AVL_RR_ROTATE    2
#define AVL_LR_ROTATE   -3
#define AVL_RL_ROTATE    3

/*  #define bitree_size( bitree ) ( ( bitree )->size )  */
#define bistree_size bitree_size

#define has_both_son( node ) ( ( ( ( node )->left != NULL ) && ( ( node )->right != NULL )  ) ? SUCESS : ERROR )

#define has_no_son( node ) ( ( ( ( node )->left == NULL ) && ( ( node )->right == NULL )  ) ? SUCESS : ERROR )

#define has_left_son( node ) ( ( ( node )->left != NULL ) ? SUCESS : ERROR )

#define has_right_son( node ) ( ( ( node )->right != NULL ) ? SUCESS : ERROR )

#define bistree_left_son( node ) ( ( node )->left )

#define bistree_right_son( node ) ( ( node )->right )

#define bistree_avl( node ) ( ( ( AVLNODE * ) ( ( node )->data ) ) )

#define bistree_avl_data( node ) ( ( ( AVLNODE * ) ( ( node )->data ) )->data )

#define bistree_avl_height( node ) ( ( ( AVLNODE * ) ( ( node )->data ) )->height )

#define bistree_avl_height_left_son( node ) ( ( ( AVLNODE * ) ( ( node )->left )->data )->height )

#define bistree_avl_height_right_son( node ) ( ( ( AVLNODE * ) ( ( node )->right )->data )->height )

#define bistree_avl_data_left_son( node ) ( ( ( AVLNODE * ) ( ( node )->left )->data )->data )

#define bistree_avl_data_right_son( node ) ( ( ( AVLNODE * ) ( ( node )->right )->data )->data )

#define bistree_avl_is_hidden( node ) ( ( ( ( AVLNODE * ) ( ( node )->data ) )->hidden == HIDE ) ? SUCESS : ERROR )

#define bistree_avl_hidden( node ) ( ( ( AVLNODE * ) ( ( node )->data ) )->hidden )

#define avl_data( avl ) ( ( avl )->data )

#define avl_height( avl ) ( ( avl )->height )

#define avl_hidden( avl ) ( ( avl )->hidden )

/* ------------------------------- ESTRUTURAS ------------------------------- */

typedef struct avlnode
{
    void *data;
    int hidden, height;
} AVLNODE;

typedef BITREE BISTREE;

/* -------------------------------- FUNÇÕES --------------------------------- */

/*

    BISTREE * bistree_initialize ( void ( * destroy ) ( void * data ), int ( * compare ) ( const void * key_1, const void * key_2 ) );
*/
#define bistree_initialize bitree_initialize

/*  */
void bistree_destroy ( BISTREE * bistree );

/*  */
int bistree_insert ( BISTREE * bistree, void * data );

/*  */
int bistree_remove ( BISTREE * bistree, void * data );

/*  */
void * bistree_lookup ( BISTREE * bistree, void * data );

#endif
