#pragma once
#include "BlockQueue.hpp"

template<typename T>
class Producer
{
public:
	Producer(BlockQueue<T>& queue);

	bool produce(const T& value);

private:
	BlockQueue<T>& m_queue;
};

template<typename T>
Producer<T>::Producer(BlockQueue<T>& queue)
	: m_queue(queue)
{

}

template<typename T>
bool Producer<T>::produce(const T& value)
{
	return m_queue.push(value);
}