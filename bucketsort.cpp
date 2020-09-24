#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include "bucketsort.h"

using namespace std;

void bucketsort(vector<int> &nums,int num_threads)
{ 
	int min=INT_MAX,max=INT_MIN;
	int size = nums.size()+1;
	for(int i=0;i<size;i++)
	{
		if(min>nums[i]) min = nums[i];
		else if(max<nums[i]) max = nums[i];
	}
	int range = max - min;
	vector<int> temp[num_threads+1];
	int divider = range/num_threads;
	for(int i=0;i<size;i++)
	{
		int bucket_index = nums[i]/divider;
		temp[bucket_index].push_back(nums[i]);
	}
	for(int i=0;i<num_threads;i++)
	{
		sort(temp[i].begin(),temp[i].end());
	}
	int index = 0;
	for(int i=0;i<num_threads;i++)
	{
		for(int j=0;j<temp[i].size();j++)
		{
			nums[index++] = temp[i][j]; 
		}
	}
}