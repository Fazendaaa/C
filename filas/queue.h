/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: queue.h    */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "list.h"

/* --------------------------------- MACROS --------------------------------- */

#define queue_peek( queue ) ( ( ( queue )->head == NULL ) ? NULL : ( queue )->head->data )

/*  #define list_size( list ) ( ( list )->size )    */
#define queue_size list_size

/* ------------------------------- ESTRUTURAS ------------------------------- */

/*  define a estrutura de fila baseado em uma lista encadeada  */
typedef LIST QUEUE;

/* -------------------------------- FUNÇÕES --------------------------------- */

/*  retornará uma fila

    QUEUE * queue_initialize ( void ( * destroy ) ( void * data ) );
*/
#define queue_initialize list_initialize


/*  liberará da memória a fila e de seus elementos

    void queue_destory ( QUEUE * queue );
*/
#define queue_destroy    list_destroy

/*  insere um elemento apontado por data na fila   */
int queue_enqueue ( QUEUE * queue, void * data );

/*  retorna o elemento da fila em data consumindo-o    */
int queue_dequeue ( QUEUE * queue, void ** data );

#endif
