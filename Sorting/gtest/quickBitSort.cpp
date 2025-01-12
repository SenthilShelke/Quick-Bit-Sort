#include "gtest/gtest.h"
#include <bitset>
#include <cassert>
#include <iostream>
#include <random>

int iterations{};

class Pairs {
public:
  int nPairs;
  int **pairs;
  Pairs(int nPairs_, int **pairs_) {
    nPairs = nPairs_;
    pairs = pairs_;
  }
};

Pairs *partition_array(unsigned int array1[], unsigned int array2[], Pairs *p,
                       unsigned int mask, int cap) {

  int **newRanges = new int *[cap];
  int newNPairs{};
  int nPairs = p->nPairs;
  int **pairs = p->pairs;

  for (int k{}; k < nPairs; k++) {

    if (pairs[k] == nullptr) {
      continue;
    }

    int start = pairs[k][0];
    int end = pairs[k][1];
    int upperPartitionIndex = start;
    int lowerPartitionIndex = end;

    for (int i{start}; i <= end; i++) {
      if ((array1[i] & mask) == 0) {
        array2[upperPartitionIndex++] = array1[i];
      } else {
        array2[lowerPartitionIndex--] = array1[i];
      }
      iterations++;
    }

    if (start <= lowerPartitionIndex) {
      newRanges[newNPairs++] = new int[2]{start, lowerPartitionIndex};
    }

    if (upperPartitionIndex <= end) {
      newRanges[newNPairs++] = new int[2]{upperPartitionIndex, end};
    }

    assert(upperPartitionIndex == (lowerPartitionIndex + 1));
  }

  return new Pairs(newNPairs, newRanges);
}

bool isSorted(unsigned int *array, int cap) {
  for (int i{}; i < cap - 1; i++) {
    if (array[i + 1] < array[i]) {
      return false;
    }
  }
  return true;
}


unsigned int randBetween() {
  const int minValue = 0;
  const int maxValue = 1 << 31;

  static std::mt19937 prng(std::random_device{}()); 
  static std::uniform_int_distribution<int> dist(minValue, maxValue);

  return dist(prng);
}


void quickBitSort(unsigned int array[], int size) {
//   int num{};

  unsigned int array2[size];
  int **ranges = new int *[1];
  ranges[0] = new int[2]{0, size - 1};
  unsigned int mask{1u << 31};
  int nPairs = 1;
  Pairs *p = new Pairs(nPairs, ranges);

//   auto start = std::chrono::high_resolution_clock::now();

  for (int i{}; i < 32; i++) {
    Pairs *newPairs = nullptr;
    if ((i % 2) == 0) {
      newPairs = partition_array(array, array2, p, mask >> i, size);
    } else {
      newPairs = partition_array(array2, array, p, mask >> i, size);
    }
    for (int a{}; a < p->nPairs; a++) {
      delete p->pairs[a];
    }
    delete p->pairs;
    delete p;
    p = newPairs;
  }
  //       auto end = std::chrono::high_resolution_clock::now();
  //       auto duration =
  //       std::chrono::duration_cast<std::chrono::milliseconds>(end -
  //       start).count(); 
            // num++;

        //     for(int j{0}; j < size; j++) {
        //     std::cout << std::bitset<32>(array[j]) << "  " << array[j] << std::endl; 
        // }


  //

  //   std::cout << "Round: " << num <<std::endl;
  //   std::cout << "Time: " << duration << " ms" << std::endl;
  //   std::cout << "Iterations: " << iterations << std::endl;
  //   std::cout << "Array size: " << size << std::endl;
}


TEST(SortingTests, IsSorted) {
  for (int size{}; size < 10000; size += 1000) {
    unsigned int array[size];
    for (int q{}; q < size; q++) {
      array[q] = randBetween();
    }

    quickBitSort(array, size);

    EXPECT_TRUE(isSorted(array, size));
  }
}


int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}