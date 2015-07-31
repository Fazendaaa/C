/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: queue.c    */

#include "queue.h"

/*  Complexidade == O(1)  */
int queue_enqueue ( QUEUE * queue, void * data )
{
    return list_insertion_next ( queue, queue->tail, data );
}

/*  Complexidade == O(1)  */
int queue_dequeue ( QUEUE * queue, void ** data )
{
    return list_remove_next ( queue, NULL, data );
}
