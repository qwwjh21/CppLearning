#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <assert.h>

template<typename T>
class BlockQueue
{
public:
	explicit BlockQueue(size_t maxSize)
		: m_maxSize(maxSize)
		, m_bClose(false)
	{
		assert(m_maxSize > 0);
	}

	~BlockQueue()
	{
		close();
	}

	bool push(const T& value);
	bool push(T&& value);
	bool pop(T& value);

	void close();

	BlockQueue(const BlockQueue&) = delete;
	BlockQueue& operator=(const BlockQueue&) = delete;

	BlockQueue(BlockQueue&&) = delete;
	BlockQueue& operator=(BlockQueue&&) = delete;

	size_t size() const;
	bool empty() const;
	bool closed() const;

private:
	bool isFull() const
	{
		return m_queue.size() >= m_maxSize;
	}

	bool isEmpty() const
	{
		return m_queue.empty();
	}

private:
	size_t						m_maxSize;
	mutable std::mutex			m_mutex;
	std::queue<T>				m_queue;
	std::condition_variable		m_notFullCv;
	std::condition_variable		m_notEmptyCv;
	bool						m_bClose;
};

template<typename T>
bool BlockQueue<T>::push(const T& value)
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_notFullCv.wait(lock, [this]()
	{
		return m_bClose || !isFull();
	});

	if (m_bClose)
		return false;

	m_queue.push(value);
	lock.unlock();
	m_notEmptyCv.notify_one();
	return true;
}

template<typename T>
bool BlockQueue<T>::push(T&& value)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_notFullCv.wait(lock, [this]() { return m_bClose || !isFull(); });
	
	if (m_bClose)
		return false;

	m_queue.push(std::move(value));
	lock.unlock();

	m_notEmptyCv.notify_one();
	return true;
}

template<typename T>
bool BlockQueue<T>::pop(T& value)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	
	m_notEmptyCv.wait(lock, [this]()
	{
		return m_bClose || !isEmpty();
	});

	if (m_bClose && isEmpty())
	{
		return false;
	}

	value = std::move(m_queue.front());
	m_queue.pop();
	lock.unlock();
	m_notFullCv.notify_one();
	return true;
}

template<typename T>
void BlockQueue<T>::close()
{
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		if (m_bClose)
			return;

		m_bClose = true;
	}

	m_notEmptyCv.notify_all();
	m_notFullCv.notify_all();
}

template<typename T>
size_t BlockQueue<T>::size() const
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_queue.size();
}

template<typename T>
bool BlockQueue<T>::empty() const
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_queue.empty();
}

template<typename T>
bool BlockQueue<T>::closed() const
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_bClose;
}