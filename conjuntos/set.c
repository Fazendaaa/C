/*
    Autor: Lucas de Almeida Carotta
*/

/*  nome do arquivo: set.c  */

#include "set.h"

/*  Complexidade == O(1)  */
SET * set_initialize ( int ( * match ) ( const void * key_1, const void * key_2 ), void ( * destroy ) ( void * data ) )
{
    SET *new = NULL;

    new = list_initialize ( destroy );

    if ( new != NULL )
        new->match = match;

    return new;
}

/*  Complexidade == O(n); sendo n := número de elementos na conjunto    */
int set_insert ( SET * set, void * data )
{
    if ( ( set == NULL ) || ( data == NULL ) )
        return ERROR;

    /*  só adiciona o dado no conjunto caso ele já não esteja adicionado    */
    else if ( !set_is_member ( set, data ) )
        /*  sempre adicona o dado no final do conjunto -- como em uma fila  */
        return list_insertion_next ( set, set_last( set ), data );

    else
        return EXIST;
}

/*  Complexidade == O(n); sendo n := número de elementos na conjunto    */
void * set_remove ( SET * set, void * data )
{
    SETELEMENT *element = NULL, *prev = NULL;
    void *rem = NULL;

    if ( ( set == NULL ) || ( data == NULL ) )
        return ERROR;

    else
    {
        for ( element = set_first( set ); element != NULL; element = set_next( element ) )
        {
            /*  quando  encontrar o elemento desejado, irá sair do for. A última
                atribuição de rem foi elemento anterior ao desejado.
            */
            if ( !set->match( set_data( element ), data ) )
                break;

            prev = element;
        }

        /*  se  element  for  nulo,  isso  significa  que  o  conjunto  todo foi
            percorrido  e  o elemento desejado não foi encontrado; lembrando que
            prev é o elemento anterior ao desejado, por isso é invocada a função
            que remove o próximo elemento ao passado
        */
        if ( element != NULL )
            list_remove_next ( set, prev, &rem );
    }

    /*  retorna o dado do elemento removido do conjunto */
    return rem;
}

/*  Complexidade == O(mn); sendo:
        * m := número de elementos no primeiro conjunto
        * n := número de elementos no segundo conjunto
*/
SET * set_union ( SET * set_1, SET * set_2, size_t size )
{
    SET *new = NULL;
    SETELEMENT *element = NULL;
    void *data = NULL;

    if ( ( set_1 != NULL ) && ( set_2 != NULL ) )
    {
        new = set_initialize ( set_1->match, set_1->destroy );

        if ( new != NULL )
        {
            /*  adiciona  os elementos do primeiro conjunto em new -- como set_1
                já  é  um conjunto, não é necessário verificar se seus elementos
                são repetidos
            */
            for ( element = set_first( set_1 ); element != NULL; element = set_next( element ) )
            {
                /*  copia o dado do elemento antes de inseri-lo no novo conjunto
                    para  que, dessa maneira, não passe apenas sua referência --
                    o  que  evita  que o dado seja perdido em ambos os conjuntos
                    caso  seja  removido  em  um  deles
                */
                data = malloc ( size );
                memcpy ( data, set_data( element ), size );
                list_insertion_next ( new, set_last( new ), data );
            }

            /*  adiciona  os elementos do segundo conjunto em new -- como new já
                possui  os  elementos  de set_1, agora é necessário verificar se
                set_2   não  possui  nenhum  elemento  que  já  fora  adicionado
                evitando, dessa maneira, a repetição de elementos
            */
            for ( element = set_first( set_2 ); element != NULL; element = set_next( element ) )
            {
                /*  aqui  não é utilizado o "set_insert" porque a verificação de
                    se  o   elemento do segundo conjunto existe no primeiro deve
                    ser  feita antes de se fazer a cópia de tal elemento -- isso
                    porque,  do  contrário,  se  alocariam todos os elementos do
                    segundo  conjunto mas só seriam adicionados os que não estão
                    presentes  no  primeiro;  ou  seja,  haveria um vazamento na
                    memória dos elementos que já se encontram no primeiro --; há
                    como utilizar o "set_insert", mas teria que se verificar seu
                    valor  de  retorno  e  liberar-se  a  memória do elemento já
                    alocado  caso  ele  já  existisse  no  novo  conjunto; dessa
                    maneira   haveria  alocação  desnecessária  e,  além  disso,
                    haveria  que  ter  de liberar da memória essa alocação feita
                    desnecessariamente
                */
                if ( !set_is_member ( new, set_data( element ) ) )
                {
                    data = malloc ( size );
                    memcpy ( data, set_data( element ), size );
                    list_insertion_next ( new, set_last( new ), data );
                }
            }
        }
    }

    return new;
}

/*  Complexidade == O(mn); sendo:
        * m := número de elementos no primeiro conjunto
        * n := número de elementos no segundo conjunto
*/
SET * set_intersection ( SET * set_1, SET * set_2, size_t size )
{
    SET *new = NULL;
    SETELEMENT *element = NULL;
    void *data = NULL;

    if ( ( set_1 != NULL ) && ( set_2 != NULL ) )
    {
        new = set_initialize ( set_1->match, set_1->destroy );

        if ( new != NULL )
        {
            /*  fixa  um  elemento  do  segundo  conjunto para ser comparado com
                todos os outros elementos do primeiro
            */
            for ( element = set_first( set_2 ); element != NULL; element = set_next( element ) )
            {
                /*  adiciona  somente  os elementos comuns aos conjuntos -- como
                    set_1  e  set_2  já  são  conjuntos, isso garante que não há
                    elementos  repetidos  dentro  deles e, por consequência, não
                    haverá elementos repetidos na sua intersecção
                */
                if ( set_is_member ( set_1, set_data( element ) ) )
                {
                    data = malloc ( size );
                    memcpy ( data, set_data( element ), size );
                    list_insertion_next ( new, set_last( new ), data );
                }
            }
        }
    }

    return new;
}

/*  Complexidade == O(mn); sendo:
        * m := número de elementos no primeiro conjunto
        * n := número de elementos no segundo conjunto
*/
SET * set_difference ( SET * set_1, SET * set_2, size_t size )
{
    SET *new = NULL;
    SETELEMENT *element = NULL;
    void *data = NULL;

    if ( ( set_1 != NULL ) && ( set_2 != NULL ) )
    {
        new = set_initialize ( set_1->match, set_1->destroy );

        if ( new != NULL )
        {
            for ( element = set_first( set_2 ); element != NULL; element = set_next( element ) )
            {
                if ( set_is_member ( set_1, set_data( element ) ) )
                    continue;

                /*  só  adiciona  um  elemento  caso  ele  não  seja  comum  aos
                    conjuntos
                */
                else
                {
                    data = malloc ( size );
                    memcpy ( data, set_data( element ), size );
                    list_insertion_next ( new, set_last( new ), data );
                }
            }
        }
    }

    return new;
}

/*  Complexidade == O(n); sendo n := número de elementos na conjunto    */
int set_is_member ( const SET * set, const void * data )
{
    SETELEMENT *element = NULL;

    if ( ( set != NULL ) && ( data != NULL ) )
    {
        for ( element = set_first( set ); element != NULL; element = set_next( element ) )
        {
            if ( !set->match( set_data( element ), data ) )
                return SUCESS;
        }
    }

    return ERROR;
}

/*  Complexidade == O(mn); sendo:
        * m := número de elementos no primeiro conjunto
        * n := número de elementos no segundo conjunto
*/
int set_is_subset ( const SET *set_1, const SET * set_2 )
{
    SETELEMENT *element = NULL;

    if ( ( set_1 == NULL ) && ( set_2 == NULL ) )
        return ERROR;

    /*  como  é  para  verificar  se  o  segundo  conjunto  é  um subconjunto do
        primeiro ele não pode ser maior do que o seu possível originador
    */
    else if ( set_1->size < set_2->size )
        return ERROR;

    else
    {
        for ( element = set_first( set_2 ); element != NULL; element = set_next( element ) )
        {
            /*  verifica  se  cada  membro  do  segundo conjunto está contido no
                primeiro,  caso  haja  um  que  não esteja presente o ciclo será
                interrompido
            */
            if ( !set_is_member ( set_1, set_data( element ) ) )
                break;
        }

        /*  se  element  for  diferente  de  nulo,  isso  significa que ele está
            presente no segundo conjunto mas não no primeiro
        */
        if ( element != NULL )
            return ERROR;
    }

    return SUCESS;
}

/*  Complexidade == O(mn); sendo:
        * m := número de elementos no primeiro conjunto
        * n := número de elementos no segundo conjunto
*/
int set_is_equal ( const SET *set_1, const SET * set_2 )
{
    if ( ( set_1 == NULL ) || ( set_2 == NULL ) )
        return ERROR;

    /*  os  conjuntos  não  podem serem considerados iguais se nem seus tamanhos
        forem iguais
    */
    else if ( set_1->size != set_2->size )
        return ERROR;

    else
        return set_is_subset ( set_1, set_2 );
}
