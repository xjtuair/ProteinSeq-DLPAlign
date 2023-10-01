/***********************************************
 * # Copyright 2019-2020. Kuang Mengmeng
 * # GPL version 3.0 applies.
 * ************************************************/

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <set>
#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <iomanip>
#include "ProbabilisticModel.h"
#include "MultiSequence.h"
#include "CalculateFeatures.h"


CalculateFeatures::CalculateFeatures(MultiSequence *sequences, const ProbabilisticModel &model)
{
    features = Calculation(sequences, model);
}
CalculateFeatures::~CalculateFeatures()
{
    features = "";
}


// string CalculateFeatures::Calculation(MultiSequence *sequences, const ProbabilisticModel &model)
// {
//     assert(sequences);
//     //feature
//     const int numSeqs = sequences->GetNumSequences();

//     const int numPairSeqs = (numSeqs - 1) * numSeqs / 2;
//     int sum_of_pairs = 0;
//     //feature
//     float pid = 0.0;
//     // do all pairwise alignments for family similarity
//     float* PIDs = new float[(numSeqs - 1) * numSeqs / 2 * sizeof(float)];
//     //feature
//     float avg_best_probs = 0.0;
//     float* BestProbs = new float[(numSeqs - 1) * numSeqs / 2 * sizeof(float)];
//     float avg_align_score = 0.0;
//     float* AlignScores = new float[(numSeqs - 1) * numSeqs / 2 * sizeof(float)];

//     float avg_emit_pairs = 0.0;
//     float* EmitPairs = new float[(numSeqs - 1) * numSeqs / 2 * sizeof(float)];
//     //feature
//     float avg_align_length = 0.0;
//     //feature
//     float avg_seq_length = 0.0;
//     for(int i = 0; i < numSeqs; i++)
//     {
//         avg_seq_length += sequences->GetSequenceLength(i);
//     }
//     avg_seq_length /= numSeqs;

//     int pairIdx = -1;
//     for (int a = 0; a < numSeqs - 1; a++)
//     {
//         for (int b = a + 1; b < numSeqs; b++)
//         {
//             pairIdx++;
//             Sequence *seq1 = sequences->GetSequence(a);
//             Sequence *seq2 = sequences->GetSequence(b);
//             pair<SafeVector<char> *, float> alignment = model.ComputeViterbiAlignment(seq1,seq2);
//             SafeVector<char>::iterator iter1 = seq1->GetDataPtr();
//             SafeVector<char>::iterator iter2 = seq2->GetDataPtr();
//             avg_best_probs += (1 + ((float)alignment.second / ( 10 * alignment.first->size())));
//             BestProbs[pairIdx] = 1 + ((float)alignment.second / ( 10 * alignment.first->size() ));
//             float N_correct_match = 0;
//             int i = 1;
//             int j = 1;
//             bool isFirst = true;
//             float tmp_alignment_score = 0.0;
//             float tmp_emit_pairs = 0.0;
//             for (SafeVector<char>::iterator iter = alignment.first->begin();
//                     iter != alignment.first->end(); ++iter)
//             {
//                 if (*iter == 'B')
//                 {
//                     unsigned char c1 = (unsigned char) iter1[i++];
//                     unsigned char c2 = (unsigned char) iter2[j++];
//                     float tmp_num = BLOSUM62[alphabet.find(c1)][alphabet.find(c2)];
//                     if (tmp_num >= -4 && tmp_num <= 11){
//                         tmp_alignment_score += tmp_num;
//                     }else{
//                         tmp_alignment_score += 0;
//                     }
//                     tmp_num =  emitPairs[alphabet.find(c1)][alphabet.find(c2)];
//                     if( tmp_num >= -10 && tmp_num <= 10){
//                         tmp_emit_pairs += tmp_num;
//                     }else{
//                         tmp_emit_pairs += 0;
//                     }
//                     isFirst = true;
//                     if(c1==c2)
//                     {
//                         N_correct_match += 1;
//                     }
//                 }
//                 else if(*iter == 'X')
//                 {
//                     i++;split
//                     {
//                         tmp_alignment_score -= 1;
//                     }
//                 }
//                 else if(*iter == 'Y')
//                 {
//                     j++;
//   