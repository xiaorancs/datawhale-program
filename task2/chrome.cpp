/**
 * File: chrome.cpp
 * Author: xiaoran
 * Email: xiaoranone@126.com
 * Time: 2019-08-09 PM.
 */

#include <iostream>
#include <string>

#include "chrome.h"
using namespace std;

int main()
{
    datawhale::Chrome chrome;
    chrome.go("1.html");
    chrome.go("2.html");
    chrome.go("3.html");
    
    cout << "back: " << chrome.back() << endl;
    cout << "back: " << chrome.back() << endl;

    cout << "front: " << chrome.front() << endl;
    cout << "front: " << chrome.front() << endl;
    return 0;
}