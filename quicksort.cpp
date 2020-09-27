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
extern int thread_num;
extern int offset;
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
void* quicksort_thread(void* args)
{
	size_t thread_part = *((size_t*)args);
	int size = UnsortedArray.size();
	int left =thread_part * (size/thread_num);
	// cout<<"\n\r"<<left<<"\n\r";
	int right=((thread_part+1) * (size/thread_num)) -1;
	// cout<<"\n\r"<<right<<"\n\r";
	if (thread_part == thread_num - 1) 
	{
        right += offset;
    }
	if(left<right)
	{
		// Takes the RIGHT number as pivot and uses it for sorting
		int sep = seperate(UnsortedArray,left,right);
		quicksort(UnsortedArray,left,sep-1);
		quicksort(UnsortedArray,sep+1,right);
	}
}
void final_quick_sorted(vector<int> &nums,int num_thread,int agg)
{
	int size = UnsortedArray.size();
	for(int i=0;i<num_thread;i+=2)
	{
		int left = i*(size/thread_num)*agg;
		int right = ((i+2)*(size/thread_num)*agg)- 1;
		if(right >= size)
		{
			right = size - 1;
		}
		quicksort(nums,left,right);
	}
	if(num_thread/2 >= 1)
	{
		final_quick_sorted(nums,num_thread/2,agg*2);
	}
}