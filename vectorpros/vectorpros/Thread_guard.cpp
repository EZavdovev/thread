#include "pch.h"
#include "Thread_guard.h"

Thread_guard::Thread_guard(){
	std::thread t;
	int col = t.hardware_concurrency();
	max_amount_of_threads = col;
	if (max_amount_of_threads < 2)
		max_amount_of_threads = 2;
}

int Thread_guard::hardware_concurrency(){
	return max_amount_of_threads;
}

void Thread_guard::add_thread(std::thread obj){
	if (threads.size() < max_amount_of_threads)
		threads.push_back(std::move(obj));
}

void Thread_guard::join(){
	int col_threads = threads.size();
	for (int i = 0; i < col_threads; ++i)
		if (threads[i].joinable())
			threads[i].join();
	threads.clear();
}

Thread_guard::~Thread_guard(){
	int col_threads = threads.size();
	for (int i = 0; i < col_threads; ++i)
			threads[i].detach();
}