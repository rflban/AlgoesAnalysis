#ifndef AALAB03_SORT_H_
#define AALAB03_SORT_H_

template <typename Type>
void quicksort(Type *arr, int len, bool (*comp)(Type, Type));

template <typename Type>
void insertionsort(Type *arr, int len, bool (*comp)(Type, Type));

template <typename Type>
void shakersort(Type *arr, int len, bool (*comp)(Type, Type));

#include "quicksort.hh"
#include "insertionsort.hh"
#include "shakersort.hh"

#endif // AALAB03_SORT_H_

