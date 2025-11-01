#include "../include/searching_algorithms.h"
#include <chrono>
#include <random>
#include <iostream>

// Последовательный поиск
int SearchingAlgorithms::sequentialSearch(const std::vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Бинарный поиск
int SearchingAlgorithms::binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// Измерение времени выполнения
double SearchingAlgorithms::measureTime(std::function<int(const std::vector<int>&, int)> searchFunction, 
                                       const std::vector<int>& arr, int target) {
    auto start = std::chrono::high_resolution_clock::now();
    searchFunction(arr, target);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

// Генерация отсортированного массива
std::vector<int> SearchingAlgorithms::generateSortedArray(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2; // Четные числа для разнообразия
    }
    return arr;
}