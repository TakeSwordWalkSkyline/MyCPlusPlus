#include <iostream>
#include <stdlib.h>

int partition(int *a, int low, int high) {
    int pivot = a[low]; //基准数
    int i = low;
    int j = high;
    // int pos = 0;
    while (i < j) {
        //下面这种实现方式移动i和j的指针,由于两个while都有进行判断,最终i和j一定会相等,不会出现i>j的情况
        while (i < j && a[j] >= pivot)
            j--; // 如果找到比pivot小的数则跳出循环,此时j的位置确定
        while (i < j && a[i] <= pivot)
            i++; //如果找到比pivot大的数则跳出循环,此时i的位置确定
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    // int temp = a[i];
    // a[i] = a[low];
    // a[low] = temp;
    a[low] = a[i];
    a[i] = pivot;
    for (int i = 0; i < high; i++) {
        printf("%d", a[i]);
    }
    printf("\n");
    return i;
}

void quickSort(int *a, int low, int high) {
    if (low > high) {
        return;
    }
    int p = partition(a, low, high);
    quickSort(a, low, p - 1);
    quickSort(a, p + 1, high);
    return;
}

int main() {
    int size;
    std::cout << "\nEnter the number of elements : ";

    std::cin >> size;

    int *arr = new int[size];

    std::cout << "\nEnter the unsorted elements : ";
    for (int i = 0; i < size; ++i) {
        std::cout << "\n";
        std::cin >> arr[i];
    }
    quickSort(arr, 0, size - 1);
    std::cout << "Sorted array\n";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}
