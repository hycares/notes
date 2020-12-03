#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size();
        vector<vector<int>> dp(size, vector<int>(size, numeric_limits<int>::max()));

        int ret = 0;

        // init dp
        for (int i=0; i<size; ++i) {
            dp[i][i] = heights[i];
            ret = max(ret, heights[i]);
        }

        // dp[i][j] means the minimun value of range(i, j);
        // dp[i][j] = min(dp[i][j-1], dp[i+1][j]);
        // while calculate dp, the maximun area is (j - i + 1) * dp[i][j];
        // error TLE
        for (int i=0; i<size; ++i) {
            int c = 0;
            for (int j=i+1; j<size; ++j, ++c) {
                dp[c][j] = min(dp[c][j-1], dp[c+1][j]);
                ret = max(ret, (j - c + 1) * dp[c][j]);
            }
        }

        return ret;
    }
};

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0); // 放到最后弹出所有栈
        int size = heights.size();
        vector<int> pstack;
        int ret = 0;
        for (int i=0; i<size; ++i) {
            // 单调栈
            while (!pstack.empty() && heights[pstack.back()] >= heights[i]) {
                int h = heights[pstack.back()];
                pstack.pop_back();
                int previdx = pstack.empty() ? -1 : pstack.back();
                // tricky use prev index
                ret = max(ret, h * (i - previdx - 1));
            }
            pstack.push_back(i);
        }
        return ret;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    vector<int> tmp{2,1,5,6,2,3};
    return s.largestRectangleArea(tmp);
}
