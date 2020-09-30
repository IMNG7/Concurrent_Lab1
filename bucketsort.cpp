#include <iostream>
#include <vector>
#include <mutex>
#include <pthread.h>
#include "bucketsort.h"
#include "quicksort.h"

using namespace std;
int range_given=0;
extern vector<int> UnsortedArray;
extern int thread_num;
extern int offset;
extern vector<int> *temp;
mutex mtx;

void* bucketsort_thread(void* args)
{
	
	size_t thread_part = *((size_t*)args);
	
	int divider = range_given/thread_num;
	
	int size = UnsortedArray.size();
	
	int left =thread_part * (size/thread_num);
	
	int right=((thread_part+1) * (size/thread_num)) -1;
	
	if (thread_part == thread_num - 1) 
	{
        right += offset;
    }
	for(int i=left;i<=right;i++)
	{	mtx.lock();
		int bucket_index = UnsortedArray[i]/divider;
		temp[bucket_index].push_back(UnsortedArray[i]);
		mtx.unlock();
	}
}
void bucketsort(int range,pthread_t *threads)
{
	range_given = range;
	ssize_t* argt = new ssize_t[thread_num+1];
	int ret;
	int size = UnsortedArray.size();
	temp = new vector<int>[thread_num+1];
	for(int i=0;i<thread_num;i++)
	{	
		argt[i]=i;
		ret = pthread_create(&threads[i],NULL,&bucketsort_thread,&argt[i]);
		if(ret)
		{
			cout<<"ERROR WHILE CREATION";
			exit(-1);
		}
		cout<<"\n\rThreads "<<i<<" Created";
	}
	for(int i=0;i<thread_num;i++)
	{
		ret = pthread_join(threads[i],NULL);
		if(ret)
		{
			printf("ERROR; pthread_join: %d\n", ret);
			exit(-1);
		}
		cout<<"\n\rThreads "<<i<<" Joined";
	}
	if(temp[thread_num].empty()!=true)
	{
		for(int i=0;i<temp[thread_num].size();i++)
		{
			temp[thread_num-1].push_back(temp[thread_num][i]);
		}
	}
	for(int i=0;i<thread_num;i++)
	{
		argt[i]=i;
		ret = pthread_create(&threads[i],NULL,&quicksort_thread_bucket,&argt[i]);
		if(ret)
		{
			cout<<"ERROR WHILE CREATION";
			exit(-1);
		}
		cout<<"\n\rThreads "<<i<<" Created";
	}
	for(int i=0;i<thread_num;i++)
	{
		ret = pthread_join(threads[i],NULL);
		if(ret)
		{
			printf("ERROR; pthread_join: %d\n", ret);
			exit(-1);
		}
		cout<<"\n\rThreads "<<i<<" Joined";
	}
	int index = 0;
	for(int i=0;i<thread_num;i++)
	{	cout<<"\n\rTempSize"<<i<<":"<<temp[i].size();
		for(int j=0;j<temp[i].size();j++)
		{	
			UnsortedArray[index++] = temp[i][j]; 
		}
	}
	delete argt;
}
void* quicksort_thread_bucket(void* args)
{
	size_t thread_part = *((size_t*)args);
	int left =0;
	// cout<<"\n\r"<<left<<"\n\r";
	int right=temp[thread_part].size()-1;
	// cout<<"\n\r"<<right<<"\n\r";
	if(left<right)
	{
		// Takes the RIGHT number as pivot and uses it for sorting
		int sep = seperate(temp[thread_part],left,right);
		quicksort(temp[thread_part],left,sep-1);
		quicksort(temp[thread_part],sep+1,right);
	}
}