#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex g_mutex;
std::condition_variable g_cv;

char g_ch = 'A';

void printA()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(g_mutex);
		
		g_cv.wait(lock, []()
		{
			return g_ch == 'A';
		});

		std::cout << g_ch;
		g_ch = 'B';
		g_cv.notify_all();
	}
}

void printB()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(g_mutex);

		g_cv.wait(lock, []()
		{
			return g_ch == 'B';
		});

		std::cout << g_ch;
		g_ch = 'C';
		g_cv.notify_all();
	}
}

void printC()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(g_mutex);

		g_cv.wait(lock, []()
		{
			return g_ch == 'C';
		});

		std::cout << g_ch;
		g_ch = 'A';
		g_cv.notify_all();
	}
}

int main()
{
	std::thread threadA(printA);
	std::thread threadB(printB);
	std::thread threadC(printC);

	threadA.join();
	threadB.join();
	threadC.join();
	
	return 0;
}