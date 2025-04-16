
/****************************************************************************************************
* File cc_algorithm.h Start!
****************************************************************************************************/
#ifndef _CC_ALGORITHM_H
#define _CC_ALGORITHM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_type.h"

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type Define
****************************************************************************************************/

typedef enum
{
    CC_ALGORITHM_LITTLE_ENDIAN = 0,
    CC_ALGORITHM_BIG_ENDIAN,
    CC_ALGORITHM_ENDIAN_END
}cc_algorithm_endianmode_enum;

/****************************************************************************************************
* Function Interface
****************************************************************************************************/

/* verify */
/* crc */

/* big endian & little endian */
cc_result cc_algorithm_checkendian(cc_algorithm_endianmode_enum *mode);

/* cryption */

/* sort */
/* cc_algorithm_sort.c */
/* cc_algorithm_sort.h */

/* Search */
/* cc_algorithm_search.c */
/* cc_algorithm_search.h */

/* DP */
/* Fibonacci Sequence */
/* 0/1 Knapsack Problem */
/* Longest Common Subsequence, LCS */
/* Shortest Path Problem */

/* Graph */
/* Depth First Search, DFS */
/* Breadth First Search, BFS */
/* Dijkstra */
/* Floyd-Warshall */

/* Math */
/* cc_algorithm_math.c */
/* cc_algorithm_math.h */

/* str */
/* Knuth-Morris-Pratt Algorithm */
/* Rabin-Karp Algorithm */
/* Boyer-Moore Algorithm */

/* other */
/* Merge Sort */
/* Activity Selection Problem */
/* Huffman Coding */
/* N-Queens Problem */
/* Sudoku Solver */




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CC_ALGORITHM_H */
/****************************************************************************************************
* File cc_algorithm.h End!
****************************************************************************************************/

