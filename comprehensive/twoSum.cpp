/*在一个增序的整数数组里找到两个数,使它们的和为给定值
* 需要输出两个数的位置,从1开始计数
*/

#include <stdio.h>
#include <iostream>
#include <vector>

using std::vector;

struct two_num_st {
    int position1;
    int position2;
};

two_num_st twoSum(int *numbers, int target) {
    int len = sizeof(numbers) / sizeof(int);
    int left = 0;
    int right = len - 1;
    while (left < right) {
        int sum = numbers[left] + numbers[right];
        if (sum == target) break;
        if (sum < target) {
            right --;
        } else {
            left ++;
        }
    }
    two_num_st result;
    result.position1 = numbers[left];
    result.position2 = numbers[right];
    return result;
}

// vector<int> twoSum(vector<int>& numbers, int target) {
//     int left = 0, right = numbers.size() -1, sum = 0;
//     while (left < right) {
//         sum = numbers[left] + numbers[right];
//         if (sum == target) break;
//         if (sum < target) {
//             left ++;
//         } else {
//             right --;
//         }
//     }
//     return vector<int>{left + 1, right + 1};
// }

int main() {
    int numbers[4] = {2, 7, 11, 15};
    two_num_st result = twoSum(numbers, 9);
    // vector<int> numbers{2, 7, 11, 15};
    // vector<int> res = twoSum(numbers, 9); 
    printf("first num position is:%d, second num position is:%d\n", result.position1, result.position2);
    //printf("first num position is:%d, second num position is:%d\n", res[0], res[1]);
}
