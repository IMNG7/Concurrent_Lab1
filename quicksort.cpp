/*
	FileName: quicksort.cpp
	Description: Contains the function definitions required to perform quicksort operation on the given numbers.
	Author: Nitik Gupta
	References Used: for quick sort algorithm :
					http://www.cplusplus.com/forum/beginner/185537/ 
					https://www.geeksforgeeks.org/quick-sort/ 
*/
#include "quicksort.h"

extern vector<int> UnsortedArray;
extern int part;
/*
	Function Name: quicksort
	Description: Initial recursive function to split the vector for sorting
	Inputs: nums- vector to be printed.
			left - Left index of vector to be split
			Right - Right index of the smal vector to be split.
	Returns: Nothing.
*/
void quicksort(vector<int> &nums,int left,int right)
{
	if(left<right)
	{
		// Takes the RIGHT number as pivot and uses it for sorting
		int sep = seperate(nums,left,right);
		quicksort(nums,left,sep-1);
		quicksort(nums,sep+1,right);
	}
}
/*
	Function Name: seperate
	Description: Gets the pivot for next split.
	Inputs: nums- vector to be printed.
			left - Left index of the splitted vector.
			Right - Right index of the splitted vector.
	Returns: Index for the next Pivot.
*/
int seperate(vector<int> &nums,int left,int right)
{
	// The right number is taken as the piot
	int pivot = nums[right];
	int i=left-1,temp;
	for(int j=left;j<right;j++)
	{	// If number at j is less than pivot, then swap it 
		// with smaller number in line
		if(nums[j]<pivot)
		{
			i++;
			temp=nums[i];
			nums[i]=nums[j];
			nums[j]=temp;
		}
	}
	//swap the pivot to place it at correct position
	temp=nums[i+1];
	nums[i+1]= nums[right];
	nums[right] = temp;
	return (i+1);
}