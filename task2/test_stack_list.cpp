#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "stack_list.h"

// using namespace datawhale;
using namespace std;

bool isValid(string s) {
    datawhale::StackList<char> sta;
    for(int i = 0; i < s.size(); i ++) {
        if (s[i] == '[' || s[i] == '{' || s[i] == '(') {
            sta.push(s[i]);
            // cout << sta.top() << endl;
        }
        else if (s[i] == ']' && !sta.empty() && sta.top() == '[') {
            sta.pop();
        }
        else if (s[i] == '}' && !sta.empty() && sta.top() == '{') {
            sta.pop();
        }
        else if (s[i] == ')' && !sta.empty() && sta.top() == '(') {
            sta.pop();
        }
        else {
            return false;
        }
    }
    return sta.empty();
}

int longestValidParentheses(string s) {
    datawhale::StackList<int> sta;
    int start = 0;
    int ans = 0;
    int maxLen = 0;
    for (int i = 0; i < s.size(); i ++) {
        if (s[i] == '(') sta.push(i);
        else { // s[i] = ')'
            if (sta.empty()) { // 当前结束，跳过所有的)新的从下标i+1开始, 保证"("个数大于")"的个数
                start = i + 1;
            }
            else { // "(()()"
                // 计算当前
                ans = max(ans, i - sta.top() + 1);
                sta.pop();
                // 当前满足，计算扩展
                if (sta.empty()) { // 合并计算多个满足的区间"()(())""
                    ans = max(ans, i - start + 1);
                }
                else { // 最前）到当前位置都满足
                    ans = max(ans, i - sta.top());
                }
            }
        }
    }
    return ans;
}

bool is_op(string s) {
    if (s == "+" || s == "-" || s == "*" || s == "/") {
        return true;
    }
    return false;
}

int evalRPN(vector<string>& tokens) {
    if (tokens.size() == 1) return stoi(tokens[0]);
    datawhale::StackList<int> data;
    for (int i = 0; i < tokens.size(); i ++) {
        if (tokens[i] == "+") {
            int a = data.top();
            data.pop();
            int b = data.top();
            data.pop();
            data.push(b + a);
        }
        else if (tokens[i] == "-") {
            int a = data.top();
            data.pop();
            int b = data.top();
            data.pop();
            data.push(b - a);
        }  
        else if (tokens[i] == "*") {
            int a = data.top();
            data.pop();
            int b = data.top();
            data.pop();
            data.push(b * a);

        }  
        else if (tokens[i] == "/") {
            int a = data.top();
            data.pop();
            int b = data.top();
            data.pop();
            data.push(b / a);
        }  
        else {
            data.push(stoi(tokens[i]));
        }
    }
    return data.top();
}


int main()
{
    string s = "([)]";
    cout << longestValidParentheses(")()()") << endl;
    // cout << isValid("(]") << endl;
    datawhale::StackList<int> a;
    a.push(6);
    datawhale::StackList<int> b(a);
    cout << b.top() << endl;
    return 0;
}