#ifndef SEARCHING_ALGORITHMS_H
#define SEARCHING_ALGORITHMS_H

#include <vector>
#include <functional>

class SearchingAlgorithms {
public:
    // Последовательный поиск
    static int sequentialSearch(const std::vector<int>& arr, int target);
    
    // Бинарный поиск (требует отсортированный массив)
    static int binarySearch(const std::vector<int>& arr, int target);
    
    // Вспомогательная функция для измерения времени выполнения
    static double measureTime(std::function<int(const std::vector<int>&, int)> searchFunction, 
                             const std::vector<int>& arr, int target);
    
    // Генерация тестовых данных
    static std::vector<int> generateSortedArray(int n);
};

#endif