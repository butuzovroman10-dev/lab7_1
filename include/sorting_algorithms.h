#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <vector>
#include <functional>

class SortingAlgorithms {
public:
    // Сортировка выбором
    static void selectionSort(std::vector<int>& arr);
    
    // Пузырьковая сортировка
    static void bubbleSort(std::vector<int>& arr);
    
    // Сортировка слиянием
    static void mergeSort(std::vector<int>& arr);
    
    // Вспомогательная функция для измерения времени выполнения
    static double measureTime(std::function<void(std::vector<int>&)> sortFunction, 
                             std::vector<int>& arr);
    
    // Генерация тестовых данных
    static std::vector<int> generateBestCase(int n);
    static std::vector<int> generateAverageCase(int n);
    static std::vector<int> generateWorstCase(int n);

private:
    // Вспомогательные функции для сортировки слиянием
    static void mergeSortHelper(std::vector<int>& arr, int left, int right);
    static void merge(std::vector<int>& arr, int left, int mid, int right);
};

#endif