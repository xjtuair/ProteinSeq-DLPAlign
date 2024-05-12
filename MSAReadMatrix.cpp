
/***********************************************
 * # Copyright 2009-2010. Liu Yongchao
 * # Contact: Liu Yongchao, School of Computer Engineering,
 * #			 Nanyang Technological University.
 * # Emails:	 liuy0039@ntu.edu.sg; nkcslyc@hotmail.com
 * #
 * # GPL version 3.0 applies.
 * #
 * ************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MSAReadMatrix.h"

#define TRACE 0

////////////////////////////////////////////////////////////
// extern variables for scoring matrix data
////////////////////////////////////////////////////////////
extern float g_gap_open1, g_gap_open2, g_gap_ext1, g_gap_ext2;
extern char *aminos, *bases, matrixtype[20];
extern int subst_index[26];

extern double sub_matrix[26][26];

extern float TEMPERATURE;
extern int MATRIXTYPE;

extern float GAPOPEN;
extern float GAPEXT;

typedef struct
{
    char input[30];
    int matrix;
    int N;
    float T;
    float beta;
    char opt;			//can be 'P' or 'M'
    float gapopen;
    float gapext;
} argument_decl;

//argument support
extern argument_decl argument;

/////////////////////////////////////////////////////////
//sets substitution matrix type
////////////////////////////////////////////////////////
void setmatrixtype(int le)
{
    switch (le)
    {
    case 160:
        strcpy(matrixtype, "gonnet_160");
        break;
    case 200:
        strcpy(matrixtype, "vtml_200");
        break;
    case 4:
        strcpy(matrixtype, "nuc_simple");
        break;
    default:
        strcpy(matrixtype, "CUSTOM");
        break;
    };

}

///////////////////////////////////////////////////////////////////
//sets matrix flag
///////////////////////////////////////////////////////////////////
inline int matrixtype_to_int()
{

    if (!strcmp(matrixtype, "nuc_simple"))
        return 4;
    else if (!strcmp(matrixtype, "gonnet_160"))
        return 160;
    else if (!strcmp(matrixtype, "vtml_200"))
        return 200;
    else
        return 1000;

}

/////////////////////////////////////////////////////////////////
//
// Can read any scoring matrix as long as it is defined in Matrix.h
// AND it is a lower triangular
// AND the order of amino acids/bases is mentioned
/////////////////////////////////////////////////////////////////

inline void read_matrix(score_matrix matrx)
{
    int i, j, basecount, position = 0;

    bases = (char *) matrx.monomers;

    basecount = strlen(bases);

    for (i = 0; i < basecount; i++)
        subst_index[i] = -1;

    for (i = 0; i < basecount; i++)
        subst_index[bases[i] - 'A'] = i;

    if (TRACE == 1)
        printf("\nbases read: %d\n", basecount);
