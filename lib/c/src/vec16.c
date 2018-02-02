#include <euler/vec16.h>
#include <stdlib.h>

#define default_cmp uint16_cmp
#define vec_get vec16_get
#define vec_set vec16_set
#define vec_len vec16_len
#define vec_clear vec16_clear
#define vec_new vec16_new
#define vec_alloc vec16_alloc
#define vec_reserve vec16_reserve
#define vec_push vec16_push
#define vec_free vec16_free
#define vec_index vec16_index
#define vec_lsearch vec16_lsearch
#define vec_bsearch vec16_bsearch
#define vec_sort vec16_sort
#define vec_sum vec16_sum

typedef uint16_t element_type;
typedef vec16_t vector_type;
typedef vec16_cmp element_cmp;

#include "vec_impl.h"
