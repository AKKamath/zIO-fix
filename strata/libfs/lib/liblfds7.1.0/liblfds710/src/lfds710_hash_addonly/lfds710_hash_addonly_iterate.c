/***** includes *****/
#include "lfds710_hash_addonly_internal.h"





/****************************************************************************/
void lfds710_hash_a_iterate_init( struct lfds710_hash_a_state *has,
                                  struct lfds710_hash_a_iterate *hai )
{
  LFDS710_PAL_ASSERT( has != NULL );
  LFDS710_PAL_ASSERT( hai != NULL );

  hai->baus = has->baus_array;
  hai->baus_end = has->baus_array + has->array_size;
  hai->baue = NULL;

  return;
}





/****************************************************************************/
int lfds710_hash_a_iterate( struct lfds710_hash_a_iterate *hai,
                            struct lfds710_hash_a_element **hae )
{
  enum lfds710_misc_flag
    finished_flag = LFDS710_MISC_FLAG_LOWERED;

  int
    rv = 0;

  LFDS710_PAL_ASSERT( hai != NULL );
  LFDS710_PAL_ASSERT( hae != NULL );

  while( finished_flag == LFDS710_MISC_FLAG_LOWERED )
  {
    lfds710_btree_au_get_by_absolute_position_and_then_by_relative_position( hai->baus, &hai->baue, LFDS710_BTREE_AU_ABSOLUTE_POSITION_SMALLEST_IN_TREE, LFDS710_BTREE_AU_RELATIVE_POSITION_NEXT_LARGER_ELEMENT_IN_ENTIRE_TREE );

    if( hai->baue != NULL )
    {
      *hae = LFDS710_BTREE_AU_GET_VALUE_FROM_ELEMENT( *hai->baue );
      finished_flag = LFDS710_MISC_FLAG_RAISED;
      rv = 1;
    }

    if( hai->baue == NULL )
      if( ++hai->baus == hai->baus_end )
      {
        *hae = NULL;
        finished_flag = LFDS710_MISC_FLAG_RAISED;
      }
  }

  return rv;
}

