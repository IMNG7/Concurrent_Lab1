/*
	FileName: mergesort.h
	Description:Contains the function declarations required to perform mergesort operation on the given numbers.
	Author: Nitik Gupta

*/
#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>

using namespace std;


/*
	Function Name: mergesort
	Description: Initial recursive function to split the vector for sorting
*/
void mergesort(vector<int> &nums,int left,int right);
/*
	Function Name: merge
	Description: Combines the sorted vectors from their indices
*/
void merge(vector<int> &nums,int left,int middle,int right);

void mergesort(void *args);

#endif