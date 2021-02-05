# 滑动窗口

针对字串，范围值问题可以使用滑动窗口解决

算法模板

```cpp
int l = 0, r = size;
while (r < size) {
    // expand r
    // do right operation
    r++;
    // shrink l
    // do left operation
    while (check() && l < r)
	    ++l;    
}
```

思路：

	1. 增大左边界，更新数据
 	2. 满足某种条件，缩小右边界
 	3. 缩小边界时更新数据
 	4. 返回结果 通常是到达右边界

