#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

class KMP {
private:
    string pattern;
    // next 数组的值是除当前字符外（注意不包括当前字符）的
    // 公共前后缀最长长度
    vector<int> next;
    void buildNext() {
        if (pattern.size() == 0) return;
        next.assign(pattern.size() + 1, 0);
        int j = 0, k = -1;
        // 起始值为 -1
        next[j] = -1;
        while (j < pattern.size()) {
            if (k == -1 || pattern[j] == pattern[k]) {
                j++;
                k++;
                // 找到最前方也没有值相等则为0, 当p[j]==p[k]时, next[j] = next[j-1]+1
                next[j] = k;
            } else {
                // 不相等时, 收缩位置往前找到相同的, 如果一直找不到则会到达-1
                k = next[k];
            }
        }
    }


    // 递归计算 K 值
    int getNext(int i) {
        if (i == 0) {
            return -1;
        }
        if (i > 0) {
            int k = getNext(i-1);
            while (k >= 0) {
                if (pattern[k] == pattern[j-1]) return k+1;
                else k = getNext(k);
            }
            return 0;
        }
        return 0;
    }
public:
    KMP() = delete;
    explicit KMP(const string& p) : pattern(p) {
        buildNext();
    }
    
    explicit KMP(const char* p) : KMP(string(p)) {
        
    }
    
    void printNext() const {
        for (auto i : next) {
          cout << i << " ";
        }
        cout << endl;
    }

    int match(const string& str) {
        return match(str.c_str());
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

class Solution {
public:
    int strStr(string haystack, string needle) {
        KMP k(needle);
        return k.match(haystack);
    }
};

int main() {
  Solution s;
  int i = s.strStr("hello", "ll");
  cout << i << endl;
  KMP k("abcdabce");
  k.printNext();
  return 0;
}