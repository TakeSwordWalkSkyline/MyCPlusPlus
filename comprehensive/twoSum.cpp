/*在一个增序的整数数组里找到两个数,使它们的和为给定值*/

#include <stdio.h>
#include <iostream>
#include <vector>

struct two_num_st {
    int first;
    int second;
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
    result.first = numbers[left];
    result.second = numbers[right];
    return result;
}

int main() {
    int numbers[4] = {2, 7, 11, 15};
    two_num_st result = twoSum(numbers, 9);
    printf("first num:%d, second num:%d\n", result.first, result.second);
}
