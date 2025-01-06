#include <iostream> 

void quickBitSort(unsigned int array1[], unsigned int array2[], int cap) {
    int mask = 1 << 31;
    int start = 0;
    int end = cap-1;

    for (int i = 0; i < cap; i++) {
        if ((array1[i] & mask) == 0) {
            array2[start++] = array1[i];
        } else {
            array2[end--] = array1[i];

        }
    }
}


int main() {
    unsigned int array1[] = {(1u << 31) + 3, 1u << 31,  (1u << 31) + 5, (1u << 31) + 1, 4, 4, 2, 9, 1};
    int cap = sizeof(array1) / sizeof(array1[0]);
    unsigned int array2[cap];

    quickBitSort(array1, array2, cap);

 
    for (int i = 0; i < cap; i++) {
        std::cout << array2[i] << " ";
    }
    std::cout << "\n";

    return 0;
}