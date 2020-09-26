/*
	FileName: quicksort.h 
	Description: Contains the function declarations required to perform quicksort operation on the given numbers.
	Author: Nitik Gupta
	References Used: for quick sort algorithm :
					http://www.cplusplus.com/forum/beginner/185537/ 
					https://www.geeksforgeeks.org/quick-sort/ 
*/
#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include <iostream>

using namespace std;
/*
	Function Name: quicksort
	Description: Initial recursive function to split the vector for sorting
*/
void quicksort(vector<int> &nums,int left,int right);
/*
	Function Name: seperate
	Description: Gets the pivot for next split.
*/
int seperate(vector<int> &nums,int left,int right);
void* quicksort_thread(void* args);
void final_quick_sorted(vector<int> &nums,int num_thread,int agg);

#endif