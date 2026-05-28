# vector 删除多个下标元素

## 问题

删除 vector 中多个指定下标元素

---

## 错误写法

```cpp
for (auto idx : indices)
{
    vec.erase(vec.begin() + idx);
}
```

## 原因

erase 后元素前移。

---

## 正确做法

倒序删除。

---

## 时间复杂度

erase:
O(n)

整体：
O(n²)

---

## 面试考点

- iterator失效
- vector内存连续
- erase复杂度