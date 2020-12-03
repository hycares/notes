单调栈结构

首先作为栈结构，满足先进后出，相比于普通栈，单调性是需要考虑的，需要在插入元素后保证单调，却要弹出最少的元素。

```c
insert x
while !sta.empty() && sta.top() < x
    sta.pop()
sta.push(x)
```



