#include "frames.h"

int alloc_frame ( LIST * frames )
{
    int frame_number = 0;
    int *data = NULL;

    if ( list_size( frames ) == 0 )
        return ERROR;

    else
    {
        if ( list_remove_next ( frames, NULL, ( void ** ) &data ) != ERROR )
            return ERROR;

        else
        {
            frame_number = *data;
            free ( data );
        }
    }

    return frame_number;
}

int free_frame ( LIST * frames, int frame_number )
{
    int *data = NULL;

    data = ( int * ) malloc ( sizeof ( int ) );

    if ( data == NULL )
        return ERROR;

    else
    {
        *data = frame_number;

        if ( list_insertion_next ( frames, NULL, data ) != ERROR )
            return ERROR;
    }

    return SUCESS;
}
