/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: ohtbl.c    */

#include "ohtbl.h"

static char vacated;

/*  */
OHTBL * ohtbl_initialize ( int positions, int ( * h1 ) ( const void * key ), int ( * h2 ) ( const void * key ), int ( * match ) ( const void * key_1 , const void * key_2 ), void ( * destroy ) ( void * data ) )
{
    OHTBL *new = NULL;

    if ( positions > 0 )
    {
        new = ( OHTBL * ) malloc ( sizeof ( OHTBL ) );

        if ( new != NULL )
        {
            new->positions = positions;
            new->vacated = &vacated;

            new->h1 = h1;
            new->h2 = h2;
            new->match = match;
            new->destroy = destroy;

            new->size = 0;
            new->table = ( void ** ) malloc ( sizeof ( void * ) * positions );
        }
    }

    return new;
}

/*  */
void ohtble_destroy ( OHTBL * ohtbl )
{
    unsigned int i = 0;

    if ( ( ohtbl != NULL ) && ( ohtbl->destroy != NULL ) )
    {
        for ( ; i < ohtbl->positions; i++ )
        {
            if ( ( ohtbl->table[ i ] != NULL ) && ( ohtbl->table[ i ] != ohtbl->vacated ) )
                ohtbl->destroy ( ohtbl->table[ i ] );
        }

        free ( ohtbl->table );
        free ( ohtbl );
    }
}

/*  */
int ohtbl_insert ( OHTBL * ohtbl, void * data )
{
    unsigned int pos = 0, i = 0;

    if ( ( ohtbl == NULL ) || ( data == NULL ) )
        return ERROR;

    else if ( ohtbl_size( ohtbl ) != ohtbl->positions )
    {
        if ( ohtbl_lookup ( ohtbl, data ) == NULL )
        {
            for ( ; i < ohtbl->positions; i++ )
            {
                pos = ( ohtbl->h1 ( data ) + ( i * ohtbl->h2 ( data ) ) ) % ohtbl->positions;

                if ( ( ohtbl->table[ pos ] == NULL ) || ( ohtbl->table[ pos ] == ohtbl->vacated ) )
                    break;
            }

            ohtbl->table[ pos ] = data;
            ohtbl->size++;

            return SUCESS;
        }

        else
            return EXIST;
    }

    else
        return ERROR;
}

/*  */
void * ohtbl_remove ( OHTBL * ohtbl, void * data )
{
    unsigned int pos = 0, i = 0;
    void *rtnval = NULL;

    if ( ( ohtbl == NULL ) || ( data == NULL ) )
        return NULL;

    else
    {
        if ( ohtbl_lookup ( ohtbl, data ) != NULL )
        {
            for ( ; i < ohtbl->positions; i++ )
            {
                pos = ( ohtbl->h1 ( data ) + ( i * ohtbl->h2 ( data ) ) ) % ohtbl->positions;

                if ( ohtbl->table[ pos ] == NULL )
                    break;

                else if ( ohtbl->table[ pos ] == ohtbl->vacated )
                    continue;

                else if ( !ohtbl->match ( ohtbl->table[ pos ], data ) )
                {
                    rtnval = ohtbl->table[ pos ];
                    ohtbl->table[ pos ] = ohtbl->vacated;
                    ohtbl->size--;

                    break;
                }
            }
        }

        return rtnval;
    }
}

/*  */
void * ohtbl_lookup ( const OHTBL * ohtbl, const void * data )
{
    unsigned int pos = 0, i = 0;
    void *rtnval = NULL;

    if ( ( ohtbl == NULL ) || ( data == NULL ) )
        return NULL;

    else
    {
        for ( ; i < ohtbl->positions; i++ )
        {
            pos = ( ohtbl->h1 ( data ) + ( i * ohtbl->h2 ( data ) ) ) % ohtbl->positions;

            if ( ohtbl->table[ pos ] == NULL )
                break;

            else if ( !ohtbl->match ( ohtbl->table[ pos ], data ) )
            {
                rtnval = ohtbl->table[ pos ];

                break;
            }
        }

        return rtnval;
    }
}
