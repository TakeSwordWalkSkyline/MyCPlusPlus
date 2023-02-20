/*
 * Assign Cookies
 * leet code 455
 * 有一群孩子和一堆饼干，每个孩子有一定饥饿度，每个饼干有一定大小
 * 每个孩子只能吃最多一块饼干，且只有饼干的大小大于孩子的饥饿度时，这个孩子才能吃饱。
 * 求解最多有多少孩子可以吃饱
 *
 * 输入输出样例:
 * 输入两个数组，分别代表孩子的饥饿度和饼干的大小。输出最多有多少孩子可以吃饱的数量。
 * Input: [1,2] [1,2,3]
 * Output: 2
 */


#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

bool compare(int first, int second) {
    return (first < second);
}

static int findContentChildren(vector<int>& children, vector<int>& cookies) {
    sort(children.begin(), children.end()); //C语言 stdlib.h 中有一个内置快排 qsort, 如果用C语言实现可以用这个函数排序
    sort(cookies.begin(), cookies.end());
    int child_index = 0;
    int cookie_index = 0;
    while ((child_index < children.size()) &&
           (cookie_index < cookies.size())) {
        if (children[child_index] <= cookies[cookie_index]) {
            child_index++;
        }
        cookie_index ++;
    }
    return child_index;
}

int main(int argc, char* argv[]) {
    vector<int> children = {1, 3, 2, 4, 4, 5};
    vector<int> cookies = {1 ,2 ,3 ,3, 4};
    string str_child = "";
    string str_cookies = "";
    vector<int>::iterator it;
    for (it = children.begin(); it != children.end(); ++it) {
        if (it != children.begin()) {
            str_child += ", ";
        }
        char a[8] = {0};
        snprintf(a, sizeof(a), "%d", *it);
        str_child += a;
    }
    for (it = cookies.begin(); it != cookies.end(); ++it) {
        if (it != cookies.begin()) {
            str_cookies += ", ";
        }
        char a[8] = {0};
        snprintf(a, sizeof(a), "%d", *it);
        str_cookies += a;
    }
    std::cout << "孩子饥饿度:" << "[" << str_child << "]" << std::endl;
    std::cout << "饼干大小:" << "[" << str_cookies << "]" << std::endl;
    int a = findContentChildren(children, cookies);
    std::cout << "最多有" << a << "个孩子能吃饱" << std::endl;
}
