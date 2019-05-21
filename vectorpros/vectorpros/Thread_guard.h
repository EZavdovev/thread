#pragma once
#include <thread>
#include <vector>

class Thread_guard{
private:
	std::vector<std::thread> threads;
	int max_amount_of_threads;

public:
	Thread_guard();
	int hardware_concurrency();
	void add_thread(std::thread obj);
	void join();
	~Thread_guard();
};

