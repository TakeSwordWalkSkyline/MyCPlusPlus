/*
 * 给定一个长度为N的string,这个string中每一个字符均为'D'或者'I'
 * 请输出一个由string下标{0,1,...,N}中元素组成的数组a[],该数组满足以下条件:
 * 当s[i]=='I'时, a[i] < a[i + 1]
 * 当s[i]=='D'时, a[i] > a[i + 1]
 *
 * 例如: s='IDID', 则输出的数组为 {0, 4, 1, 3, 2}
 *       s='DDI', 则输出数组为{3, 2, 0, 1}
 */




#include <iostream>
#include <vector>


using std::string;
using std::vector;

vector<int> distringMatch(string s) {
    int n = s.size();
    int max = s.size();
    int min = 0;
    vector<int> result(max + 1);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'I') {
            result[i] = min;
            min ++;
        }
        if (s[i] == 'D') {
            result[i] = max;
            max --;
        }
    }
    result[n] = max;
    return result;
}

void printVector(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    string s1 = "IDID";
    string s2 = "DIDI";
    string s3 = "DDI";
    string s4 = "IID";
    std::cout <<s1 << std::endl;
    printVector(distringMatch(s1));
    std::cout <<s2 << std::endl;
    printVector(distringMatch(s2));
    std::cout <<s3 << std::endl;
    printVector(distringMatch(s3));
    std::cout <<s4 << std::endl;
    printVector(distringMatch(s4));

    return 0;
}
