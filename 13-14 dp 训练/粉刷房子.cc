class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        //1.创建dp表
        vector<vector<int>> dp(n, vector<int>(3));
        //2.初始化
        dp[0][0] = costs[0][0]; dp[0][1] = costs[0][1]; dp[0][2] = costs[0][2];
        //3.填表
        for (int i = 1; i < n; i++)
        {
            dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + costs[i][0];
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + costs[i][1];
            dp[i][2] = min(dp[i - 1][1], dp[i - 1][0]) + costs[i][2];
        }
        //4.确认返回值
        return min(min(dp[n - 1][0], dp[n - 1][1]), dp[n - 1][2]);
    }
};