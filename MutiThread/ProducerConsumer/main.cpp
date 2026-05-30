#include <iostream>
#include <thread>
#include <chrono>

#include "Producer.hpp"
#include "Consumer.hpp"

int main()
{
	BlockQueue<int> queue(5);

	Producer<int> producer(queue);

	Consumer<int> consumer1(queue);
	Consumer<int> consumer2(queue);

	std::thread producerThread([&]()
		{
			for (int i = 1; i <= 20; ++i)
			{
				producer.produce(i);

				std::cout << "[Producer] produce: "
					<< i
					<< std::endl;

				std::this_thread::sleep_for(
					std::chrono::milliseconds(100));
			}

			queue.close();
		});

	std::thread consumerThread1([&]()
		{
			int value = 0;

			while (consumer1.consume(value))
			{
				std::cout << "[Consumer1] consume: "
					<< value
					<< std::endl;

				std::this_thread::sleep_for(
					std::chrono::milliseconds(150));
			}

			std::cout << "[Consumer1] exit" << std::endl;
		});

	std::thread consumerThread2([&]()
		{
			int value = 0;

			while (consumer2.consume(value))
			{
				std::cout << "[Consumer2] consume: "
					<< value
					<< std::endl;

				std::this_thread::sleep_for(
					std::chrono::milliseconds(150));
			}

			std::cout << "[Consumer2] exit" << std::endl;
		});

	producerThread.join();
	consumerThread1.join();
	consumerThread2.join();

	std::cout << "All threads finished." << std::endl;

	return 0;
}