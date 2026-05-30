#pragma once
#include "BlockQueue.hpp"

template<typename T>
class Consumer
{
public:
	Consumer(BlockQueue<T>& queue);

	bool consume(T& value);

private:
	BlockQueue<T>& m_queue;
};

template<typename T>
Consumer<T>::Consumer(BlockQueue<T>& queue)
	:m_queue(queue)
{

}

template<typename T>
bool Consumer<T>::consume(T& value)
{
	return m_queue.pop(value);
}