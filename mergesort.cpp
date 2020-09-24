/*
	FileName: mergesort.cpp
	Description:Contains the function definitions required to perform mergesort operation on the given numbers.
	Author: Nitik Gupta
	References Used: For Merge Sort Algorithm:
					 https://www.geeksforgeeks.org/merge-sort/ 
*/
#include "mergesort.h"

extern vector<int> UnsortedArray;
extern int part;
/*
	Function Name: mergesort
	Description: Initial recursive function to split the vector for sorting
	Inputs: nums- vector to be printed.
			left - Left index of vector to be split
			Right - Right index of the smal vector to be split.
	Returns: Nothing.
*/
void mergesort(vector<int> &nums,int left,int right)
{
	if(left<right)
	{
		// Calculates the middle value of the array given
		int middle = left+((right-left)/2);
		//Splits the array into two parts and further given to split
		//until there is only one element left in each.
		mergesort(nums,left,middle);
		mergesort(nums,middle+1,right);
		// After splitting each, the are given to merge back after 
		// sorting
		merge(nums,left,middle,right);
	}
}
/*
	Function Name: mergesort
	Description: Initial recursive function to split the vector for sorting
	Inputs: nums- vector to be printed.
			left - Left index of vector to be split
			Right - Right index of the smal vector to be split.
	Returns: Nothing.
*/
void mergesort(void *args)
{
		int thread_part = part++;
		int size = UnsortedArray.size();
		// Calculates the middle value of the array given
		int left =size,right=size;

		int middle = left+((right-left)/2);
		//Splits the array into two parts and further given to split
		//until there is only one element left in each.
		mergesort(UnsortedArray,left,middle);
		mergesort(UnsortedArray,middle+1,right);
		// After splitting each, the are given to merge back after 
		// sorting
		merge(UnsortedArray,left,middle,right);
	
}
/*
	Function Name: merge
	Description: Combines the sorted vectors from their indices
	Inputs: nums- vector to be printed.
			left - Left index of the splitted vector
			middle - the middle portion of the splited vector.
			Right - Right index of the splitted vector.
	Returns: Nothing.
*/
void merge(vector<int> &nums,int left,int middle,int right)
{	
	//Size of the left side array
	int leftsize = middle - left + 1;
	//Size of the Right side array
	int rightsize = right - middle;
	//Temp arrays to save the numbers
	int lefttemp[leftsize],righttemp[rightsize];
	int i,j,k;
	// Save the arrays from the left and right to temp.
	for(i=0;i<leftsize;i++)
	{
		lefttemp[i] = nums[i+left];
	}
	for(i=0;i<rightsize;i++)
	{
		righttemp[i] = nums[middle+i+1];
	}
	i=0;j=0;k=left;
	while(i<leftsize && j<rightsize)
	{
	// compare the values in two arrays and kept on adding to the final
	// array until one of them exhausts.
		if(lefttemp[i]<=righttemp[j])
		{
			nums[k]=lefttemp[i];
			i++;
		}
		else
		{
			nums[k]=righttemp[j];
			j++;
		}
		k++;
	}
	// Store the remaining value inside the array.
	while(i<leftsize)
	{
		nums[k]=lefttemp[i];
		i++;
		k++;
	}
	while(j<rightsize)
	{
		nums[k]=righttemp[j];
		j++;
		k++;
	}
}
