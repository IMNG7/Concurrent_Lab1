/*
	FileName: quicksort.h 
	Description: Contains the function declarations required to perform quicksort operation on the given numbers.
	Author: Nitik Gupta
	References Used: for quick sort algorithm :
					http://www.cplusplus.com/forum/beginner/185537/ 
					https://www.geeksforgeeks.org/quick-sort/ 
*/
#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include <vector>
//#include <algorithm>

using namespace std;

void* bucketsort_thread(void* args);
void bucketsort(int range,pthread_t *threads);

#endif