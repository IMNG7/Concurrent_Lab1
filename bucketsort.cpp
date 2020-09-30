#include <iostream>
#include <vector>
#include <mutex>
#include <pthread.h>
#include "bucketsort.h"
#include "quicksort.h"
#include <bits/stdc++.h>

using namespace std;
extern vector<int> UnsortedArray;
extern int thread_num;
extern int offset;
mutex mtx;
map<int,int> bucket;

void* bucketsort_thread(void* args)
{
	
	size_t thread_part = *((size_t*)args);
	
	int size = UnsortedArray.size();
	
	int left =thread_part * (size/thread_num);
	
	int right=((thread_part+1) * (size/thread_num)) -1;
	
	if (thread_part == thread_num - 1) 
	{
        right += offset;
    }
	for(int i=left;i<=right;i++)
	{	mtx.lock();
		bucket.insert(pair<int,int>(UnsortedArray[i],i));
		mtx.unlock();
	}
}
void bucketsort(pthread_t *threads)
{
	ssize_t* argt = new ssize_t[thread_num+1];
	int ret;
	int size = UnsortedArray.size();
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
	int index = 0;
	for(auto i=bucket.begin();i!=bucket.end();i++)
	{	
		UnsortedArray[index++] = i->first; 
	}
	delete argt;
}
