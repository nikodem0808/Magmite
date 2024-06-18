#pragma once

#include <thread>
#include <Windows.h>

using Task = void(size_t, void*);

struct thread_data
{
	size_t id;
	void* task_param;
	Task* task_ptr;
	bool task_running;
};


DWORD thread_supertask(LPVOID param)
{
	auto p = static_cast<thread_data*>(param);
	while (true)
	{
		while (!p->task_running) std::this_thread::yield();
		p->task_ptr(p->id, p->task_param);
		p->task_running = false;
	}
}

template<size_t n_threads>
struct TPool
{
	std::array<thread_data, n_threads> thread_data_list = { 0 };
	std::array<HANDLE, n_threads> threads = { 0 };

	TPool()
	{
		for (size_t i = 0; i < n_threads; ++i)
		{
			thread_data_list[i].id = i;
			thread_data_list[i].task_param = nullptr;
			thread_data_list[i].task_ptr = nullptr;
			thread_data_list[i].task_running = false;
			threads[i] = ::CreateThread(0, 8192, thread_supertask, static_cast<LPVOID>(&thread_data_list[i]), 0, 0);
		}
	}

	void Do(Task* task, void* task_param)
	{
		for (size_t i = 0; i < n_threads; ++i)
		{
			thread_data_list[i].task_ptr = task;
			thread_data_list[i].task_param = task_param;
			thread_data_list[i].task_running = true;
		}
	}

	void DoEach(Task** task, void** task_param)
	{
		for (size_t i = 0; i < n_threads; ++i)
		{
			thread_data_list[i].task_ptr = task[i];
			thread_data_list[i].task_param = task_param[i];
			thread_data_list[i].task_running = true;
		}
	}

	void Repeat()
	{
		for (size_t i = 0; i < n_threads; ++i)
		{
			thread_data_list[i].task_running = true;
		}
	}

	void Await()
	{
		for (size_t i = 0; i < n_threads; ++i)
		{
			while (thread_data_list[i].task_running) std::this_thread::yield();
		}
	}

	~TPool()
	{
		Await();
		for (auto hThread : threads)
		{
			TerminateThread(hThread, 0);
			CloseHandle(hThread);
		}
	}
};

