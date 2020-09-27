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
vector<int> *temp;
mutex mtx;

void* bucketsort_thread(void* args)
{
	
	size_t thread_part = *((size_t*)args);
	
	int divider = range_given/thread_num;
	
	int size = UnsortedArray.size();
	
	int left =thread_part * (size/thread_num);
	
	cout<<"\n\r"<<left<<"\n\r";
	int right=((thread_part+1) * (size/thread_num)) -1;
	cout<<"\n\rleft:"<<left<<"\n\r";
	// cout<<"\n\r"<<right<<"\n\r";
	
	if (thread_part == thread_num - 1) 
	{
        right += offset;
    }
    cout<<"\n\rright:"<<right<<"\n\r";
	for(int i=left;i<right;i++)
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
	//temp.resize(thread_num+1);
	cout<<"Here\n\r";
	temp = new vector<int>[thread_num+1];
	cout<<"Here\n\r";
	for(int i=0;i<thread_num;i++)
	{	
		argt[i]=i;
		ret = pthread_create(&threads[i],NULL,&bucketsort_thread,&argt[i]);
		if(ret)
		{
			cout<<"ERROR WHILE CREATION";
			exit(-1);
		}
		else
		cout<<"\n\rThreads Created";
	}
	for(int i=0;i<thread_num;i++)
	{
		ret = pthread_join(threads[i],NULL);
		if(ret)
		{
			printf("ERROR; pthread_join: %d\n", ret);
			exit(-1);
		}
		else
		cout<<"\n\rThreads Joined";
	}
	for(int i=0;i<thread_num;i++)
	{
		//sort(temp[i].begin(),temp[i].end());
		quicksort(temp[i],0,temp[i].size()-1);
	}
	int index = 0;
	for(int i=0;i<thread_num;i++)
	{	cout<<"\n\rTempSize "<<i<<" "<<temp[i].size();
		for(int j=0;j<temp[i].size();j++)
		{
			//cout<<"\n\r"<<UnsortedArray[index]<<"\t"<<temp[i][j]<<"\t"<<index;
			UnsortedArray[index++] = temp[i][j]; 
		}
	}
	final_quick_sorted(UnsortedArray,thread_num,1);
}
