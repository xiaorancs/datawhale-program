/**
 * File: fact.cpp
 * Author: xiaoran
 * Email: xiaoranone@126.com
 * Time: 2019-08-09 PM.
 */

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

int ans[10005]; // 每一位表示10000
const int UNIT = 10000;

string fact(int n) {
    memset(ans, 0, sizeof(ans));
    ans[0] = 1;
    int flag = 0;
    for (int i = 1; i <= n; i ++) {
        for (int j = 0; j <= 10000; j ++) {
            // if (ans[j] == 0) break;
            ans[j] *= i;
            ans[j] += flag;
            flag = ans[j] / UNIT;
            ans[j] %= UNIT;
        }
    }
    int i;
    for (i = 10000; ans[i] == 0; i --);
    string res = "";
    char tmp[10];
    for (int j = i; j >= 0; j--) {
        // cout << ans[j] << endl;
        if (j != i) {
            sprintf(tmp, "%04d", ans[j]);
        }
        else {
            sprintf(tmp, "%d", ans[j]);
        }
        string t(tmp);
        res += t;
    }
    return res;
}
int main()
{
    cout << fact(5) << endl;
    cout << fact(6) << endl;
    cout << fact(7) << endl;
    cout << fact(8) << endl;
    cout << fact(9) << endl;
    cout << fact(10) << endl;
    cout << fact(10000) << endl;
}