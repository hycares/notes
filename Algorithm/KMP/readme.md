KMP算法

重点

1. 利用已经匹配的串转移到可用最长前缀位置。
2. 转移表的计算

```cpp
class KMP {
private:
    string pattern;
    // next 数组的值是除当 字符外（注意不包括当前字符）的
    // 公共前后缀最长长度
    vector<int> next;
    void buildNext() {
        int j = 0, k = -1;
        next[j] = -1;
        while (j < pattern.size()) {
            if (k == -1 || pattern[j] == pattern[k]) {
                j++;
                k++;
                next[j] = k;
            } else {
                k = next[k];
            }
        }
    }
public:
    KMP() = delete;
    explicit KMP(const string& p) : pattern(p), next(p.size(), 0) {
        buildNext();
    }
    
    explicit KMP(const char* p) : KMP(string(p)) {
        
    }
    
    int match(const char* str) {
        auto ss = strlen(str);
        int size = pattern.size();
        int i=0, j=0;
        if (size == 0) return 0;
        if (size > ss) return -1;
        while (str[i] != '\0' && j < size) {
            if (j == -1 || str[i] == pattern[j]) {
                i++;
                j++;
            } else {
                // 相对于主串进行偏移
                j = next[j];
            }
        }
        if (j == size) return i - j;
        else return -1;
    }
};
```



参考

[1 KMP详解](https://blog.csdn.net/yyzsir/article/details/89462339)