#include "../include/sorting_algorithms.h"
#include <chrono>
#include <random>
#include <algorithm>

// Сортировка выбором
void SortingAlgorithms::selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            std::swap(arr[i], arr[minIdx]);
        }
    }
}

// Пузырьковая сортировка
void SortingAlgorithms::bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Вспомогательная функция для слияния
void SortingAlgorithms::merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> leftArr(n1), rightArr(n2);
    
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Вспомогательная функция для сортировки слиянием
void SortingAlgorithms::mergeSortHelper(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Сортировка слиянием
void SortingAlgorithms::mergeSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    mergeSortHelper(arr, 0, arr.size() - 1);
}

// Измерение времени выполнения
double SortingAlgorithms::measureTime(std::function<void(std::vector<int>&)> sortFunction, 
                                     std::vector<int>& arr) {
    // Создаем копию массива для тестирования
    std::vector<int> testArr = arr;
    
    auto start = std::chrono::high_resolution_clock::now();
    sortFunction(testArr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

// Генерация лучшего случая (уже отсортированный массив)
std::vector<int> SortingAlgorithms::generateBestCase(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    return arr;
}

// Генерация среднего случая (случайный массив)
std::vector<int> SortingAlgorithms::generateAverageCase(int n) {
    std::vector<int> arr(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, n * 10);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Генерация худшего случая (обратно отсортированный массив)
std::vector<int> SortingAlgorithms::generateWorstCase(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    return arr;
}