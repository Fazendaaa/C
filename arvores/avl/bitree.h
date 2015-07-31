/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: bitree.h   */

#ifndef BITREE_H_
#define BITREE_H_

#include <stdlib.h>
#include <string.h>

/* --------------------------------- MACROS --------------------------------- */

#define ERROR  0
#define SUCESS 1

#define LEFT  0
#define RIGHT 1

#define bitree_size( bitree ) ( ( bitree )->size )

#define bitree_root( bitree ) ( ( bitree )->root )

#define bitree_is_leaf( node ) ( ( ( ( node )->left == NULL ) && ( ( node )->right == NULL ) ) ? SUCESS : ERROR )

#define bitree_data( node ) ( ( node )->data )

#define bitree_left( node ) ( ( node )->left )

#define bitree_right( node ) ( ( node )->right )

/* ------------------------------- ESTRUTURAS ------------------------------- */

typedef struct bitreenode
{
    void *data;
    struct bitreenode *dad, *left, *right;
} BITREENODE;

typedef struct bitree
{
    unsigned int size;

    int ( * compare ) ( const void * key_1, const void * key_2 );
    void ( * destroy ) ( void * data );

    BITREENODE *root;
} BITREE;

/* -------------------------------- FUNÇÕES --------------------------------- */

/*  */
BITREE * bitree_initialize ( void ( * destroy ) ( void * data ), int ( * compare ) ( const void * key_1, const void * key_2 ) );

/*  */
void bitree_destroy ( BITREE * bitree );

/*  */
int bitree_insertion_left ( BITREE * bitree, BITREENODE * node, void * data );

/*  */
int bitree_insertion_right ( BITREE * bitree, BITREENODE * node, void * data );

/*  */
void bitree_remove_left ( BITREE * bitree, BITREENODE * node );

/*  */
void bitree_remove_right ( BITREE * bitree, BITREENODE * node );

/*  */
BITREE * bitree_merge ( BITREE * left, BITREE * right, size_t size );

#endif
