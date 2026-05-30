# 多线程中常见面试问题

## 什么是虚假唤醒

答：条件变量等待的线程可能没有收到notify的情况下从wait返回，这种现象称为虚假唤醒。
因此wait返回不能直接执行业务逻辑，必须重新检查等待条件。
C++推荐使用

```cpp
cv.wait(lock, predicate);
```
或者
```cpp
while (!condition)
{
    cv.wait(lock);
}
```
来避免虚假唤醒带来的问题。

---
无法预测虚假唤醒什么时候发生，因为它不是代码主动触发的，而是操作系统和条件变量允许发生的一种行为。

常见的“伪虚假唤醒”
两个消费者 Consumer1, Consumer2
```cpp
cv.wait(lock, []{
    return !queue.empty();
});
```
生产者
```cpp
queue.push(100);

cv.notify_all();
```
导致Consumer1 和 Consumer2都醒，最后只能有一个消费者抢到数据，另一个消费者线程继续睡