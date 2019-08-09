#include <iostream>
#include <string>
#include <vector>
#include "queue.h"

using namespace std;

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> ans;
    if (nums.size() < k) return ans;
    datawhale::Queue<int> que;
    for (int i = 0; i < nums.size(); i ++) {
        if (!que.empty() && que.front() == i - k) { // 越界, 删除队首元素
            que.pop_front();
        }
        // 队列中始终保存最大值下标，通过第一个if判断是否越界，判断是否使用
        while (!que.empty() && nums[que.back()] < nums[i]) que.pop_back();
        que.push(i);
        if (i >= k - 1) {
            ans.push_back(nums[que.front()]);
        }
    }
    return ans;   
}

int main()
{
    datawhale::Queue<int, 5> que;
    que.push(1);
    que.push(2);
    que.push(3);
    que.push(4);
    que.push(5);
    que.push(6);
    que.push(7);
    que.push(8);
    
    // cout << que.front() << endl;
    cout << que.size() << endl;

    // que.pop();
    // cout << que.front() << endl;
    
    // que.pop_back();
    // cout << que.back() << endl;
    
    
    return 0;
}