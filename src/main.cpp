#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/sorting_algorithms.h"
#include "../include/searching_algorithms.h"
#include "../include/closest_pair.h"

// Структуры для хранения результатов
struct SortingResult {
    std::string algorithm;
    std::string caseType;
    int size;
    double time;
};

struct SearchResult {
    std::string algorithm;
    int size;
    double time;
};

struct ClosestPairResult {
    std::string algorithm;
    int pointsCount;
    double time;
};

// Глобальные векторы для хранения результатов
std::vector<SortingResult> sortingResults;
std::vector<SearchResult> searchResults;
std::vector<ClosestPairResult> closestPairResults;

// Функция для сохранения в CSV
void saveToCSV() {
    // Сохранение результатов сортировки
    std::ofstream sortingFile("sorting_results.csv");
    sortingFile << "Algorithm,Case,Size,Time(sec)\n";
    for (const auto& result : sortingResults) {
        sortingFile << result.algorithm << "," 
                   << result.caseType << "," 
                   << result.size << "," 
                   << std::fixed << std::setprecision(6) << result.time << "\n";
    }
    sortingFile.close();

    // Сохранение результатов поиска
    std::ofstream searchFile("search_results.csv");
    searchFile << "Algorithm,Size,Time(sec)\n";
    for (const auto& result : searchResults) {
        searchFile << result.algorithm << "," 
                  << result.size << "," 
                  << std::fixed << std::setprecision(6) << result.time << "\n";
    }
    searchFile.close();

    // Сохранение результатов поиска ближайших точек
    std::ofstream closestFile("closest_pair_results.csv");
    closestFile << "Algorithm,PointsCount,Time(sec)\n";
    for (const auto& result : closestPairResults) {
        closestFile << result.algorithm << "," 
                   << result.pointsCount << "," 
                   << std::fixed << std::setprecision(6) << result.time << "\n";
    }
    closestFile.close();
}

// Функция для генерации HTML отчета с графиками
// Функция для генерации HTML отчета с графиками
void generateHTMLReport() {
    std::ofstream htmlFile("report.html");
    
    htmlFile << R"(<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Анализ алгоритмов - Вычислительный эксперимент</title>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            background-color: #f5f5f5;
        }
        .container {
            max-width: 1200px;
            margin: 0 auto;
            background: white;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
        }
        h1, h2 {
            color: #333;
            text-align: center;
        }
        .chart-container {
            margin: 30px 0;
            padding: 20px;
            background: #fafafa;
            border-radius: 8px;
            height: 400px;
        }
        canvas {
            max-height: 400px;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
        }
        th, td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: center;
        }
        th {
            background-color: #4CAF50;
            color: white;
        }
        tr:nth-child(even) {
            background-color: #f2f2f2;
        }
        .data-section {
            margin: 20px 0;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Анализ алгоритмов - Вычислительный эксперимент</h1>
        
        <h2>1. Алгоритмы сортировки</h2>
        <div class="chart-container">
            <canvas id="sortingChart"></canvas>
        </div>

        <h2>2. Алгоритмы поиска</h2>
        <div class="chart-container">
            <canvas id="searchChart"></canvas>
        </div>

        <h2>3. Поиск ближайших точек</h2>
        <div class="chart-container">
            <canvas id="closestPairChart"></canvas>
        </div>

        <div class="data-section">
            <h2>Таблицы результатов</h2>
            
            <h3>Сортировка (размер 1000)</h3>
            <table id="sortingTable">
                <thead>
                    <tr>
                        <th>Алгоритм</th>
                        <th>Случай</th>
                        <th>Время (сек)</th>
                    </tr>
                </thead>
                <tbody>)";

    // Заполняем таблицу сортировки
    for (const auto& result : sortingResults) {
        if (result.size == 1000) {
            htmlFile << "<tr><td>" << result.algorithm 
                     << "</td><td>" << result.caseType 
                     << "</td><td>" << std::fixed << std::setprecision(6) << result.time 
                     << "</td></tr>";
        }
    }

    htmlFile << R"(</tbody>
            </table>

            <h3>Поиск</h3>
            <table id="searchTable">
                <thead>
                    <tr>
                        <th>Алгоритм</th>
                        <th>Размер</th>
                        <th>Время (сек)</th>
                    </tr>
                </thead>
                <tbody>)";

    // Заполняем таблицу поиска
    for (const auto& result : searchResults) {
        htmlFile << "<tr><td>" << result.algorithm 
                 << "</td><td>" << result.size 
                 << "</td><td>" << std::fixed << std::setprecision(6) << result.time 
                 << "</td></tr>";
    }

    htmlFile << R"(</tbody>
            </table>

            <h3>Ближайшие точки</h3>
            <table id="closestPairTable">
                <thead>
                    <tr>
                        <th>Алгоритм</th>
                        <th>Кол-во точек</th>
                        <th>Время (сек)</th>
                    </tr>
                </thead>
                <tbody>)";

    // Заполняем таблицу ближайших точек
    for (const auto& result : closestPairResults) {
        htmlFile << "<tr><td>" << result.algorithm 
                 << "</td><td>" << result.pointsCount 
                 << "</td><td>" << std::fixed << std::setprecision(6) << result.time 
                 << "</td></tr>";
    }

    htmlFile << R"(</tbody>
            </table>
        </div>
    </div>

    <script>
        // Данные для графиков
        const sortingData = {
            labels: [100, 500, 1000, 2000],
            datasets: [)";

    // Готовим данные для сортировки выбором (лучший случай)
    htmlFile << R"({
                    label: 'Выбором (лучший)',
                    data: [)";
    std::vector<int> sortingSizes = {100, 500, 1000, 2000};
    for (int size : sortingSizes) {
        bool found = false;
        for (const auto& result : sortingResults) {
            if (result.algorithm == "SelectionSort" && result.caseType == "Лучший" && result.size == size) {
                htmlFile << result.time;
                found = true;
                break;
            }
        }
        if (!found) htmlFile << "0";
        if (size != 2000) htmlFile << ", ";
    }
    htmlFile << R"(],
                    borderColor: 'rgb(255, 99, 132)',
                    backgroundColor: 'rgba(255, 99, 132, 0.2)'
                },)";

    // Данные для сортировки слиянием (средний случай)
    htmlFile << R"({
                    label: 'Слиянием (средний)',
                    data: [)";
    for (int size : sortingSizes) {
        bool found = false;
        for (const auto& result : sortingResults) {
            if (result.algorithm == "MergeSort" && result.caseType == "Средний" && result.size == size) {
                htmlFile << result.time;
                found = true;
                break;
            }
        }
        if (!found) htmlFile << "0";
        if (size != 2000) htmlFile << ", ";
    }
    htmlFile << R"(],
                    borderColor: 'rgb(54, 162, 235)',
                    backgroundColor: 'rgba(54, 162, 235, 0.2)'
                }])";

    htmlFile << R"(};

        const searchData = {
            labels: [1000, 10000, 100000, 1000000],
            datasets: [)";

    // Данные для последовательного поиска
    htmlFile << R"({
                    label: 'Последовательный поиск',
                    data: [)";
    std::vector<int> searchSizes = {1000, 10000, 100000, 1000000};
    for (int size : searchSizes) {
        bool found = false;
        for (const auto& result : searchResults) {
            if (result.algorithm == "SequentialSearch" && result.size == size) {
                htmlFile << result.time;
                found = true;
                break;
            }
        }
        if (!found) htmlFile << "0";
        if (size != 1000000) htmlFile << ", ";
    }
    htmlFile << R"(],
                    borderColor: 'rgb(255, 159, 64)',
                    backgroundColor: 'rgba(255, 159, 64, 0.2)'
                },)";

    // Данные для бинарного поиска
    htmlFile << R"({
                    label: 'Бинарный поиск',
                    data: [)";
    for (int size : searchSizes) {
        bool found = false;
        for (const auto& result : searchResults) {
            if (result.algorithm == "BinarySearch" && result.size == size) {
                htmlFile << result.time;
                found = true;
                break;
            }
        }
        if (!found) htmlFile << "0";
        if (size != 1000000) htmlFile << ", ";
    }
    htmlFile << R"(],
                    borderColor: 'rgb(75, 192, 192)',
                    backgroundColor: 'rgba(75, 192, 192, 0.2)'
                }])";

    htmlFile << R"(};

        const closestPairData = {
            labels: [10, 50, 100, 500, 1000],
            datasets: [)";

    // Данные для метода грубой силы
    htmlFile << R"({
                    label: 'Грубая сила',
                    data: [)";
    std::vector<int> closestSizes = {10, 50, 100, 500, 1000};
    for (int size : closestSizes) {
        bool found = false;
        for (const auto& result : closestPairResults) {
            if (result.algorithm == "BruteForce" && result.pointsCount == size) {
                htmlFile << result.time;
                found = true;
                break;
            }
        }
        if (!found) htmlFile << "0";
        if (size != 1000) htmlFile << ", ";
    }
    htmlFile << R"(],
                    borderColor: 'rgb(153, 102, 255)',
                    backgroundColor: 'rgba(153, 102, 255, 0.2)'
                },)";

    // Данные для метода декомпозиции
    htmlFile << R"({
                    label: 'Декомпозиция',
                    data: [)";
    for (int size : closestSizes) {
        bool found = false;
        for (const auto& result : closestPairResults) {
            if (result.algorithm == "DivideAndConquer" && result.pointsCount == size) {
                htmlFile << result.time;
                found = true;
                break;
            }
        }
        if (!found) htmlFile << "0";
        if (size != 1000) htmlFile << ", ";
    }
    htmlFile << R"(],
                    borderColor: 'rgb(255, 205, 86)',
                    backgroundColor: 'rgba(255, 205, 86, 0.2)'
                }])";

    htmlFile << R"(};

        // Создание графиков
        window.onload = function() {
            // График сортировки
            const sortingCtx = document.getElementById('sortingChart').getContext('2d');
            new Chart(sortingCtx, {
                type: 'line',
                data: sortingData,
                options: {
                    responsive: true,
                    maintainAspectRatio: false,
                    plugins: {
                        title: {
                            display: true,
                            text: 'Время выполнения алгоритмов сортировки'
                        }
                    },
                    scales: {
                        y: {
                            type: 'logarithmic',
                            title: {
                                display: true,
                                text: 'Время (сек, логарифмическая шкала)'
                            }
                        },
                        x: {
                            title: {
                                display: true,
                                text: 'Размер массива'
                            }
                        }
                    }
                }
            });

            // График поиска
            const searchCtx = document.getElementById('searchChart').getContext('2d');
            new Chart(searchCtx, {
                type: 'line',
                data: searchData,
                options: {
                    responsive: true,
                    maintainAspectRatio: false,
                    plugins: {
                        title: {
                            display: true,
                            text: 'Время выполнения алгоритмов поиска'
                        }
                    },
                    scales: {
                        y: {
                            type: 'logarithmic',
                            title: {
                                display: true,
                                text: 'Время (сек, логарифмическая шкала)'
                            }
                        },
                        x: {
                            title: {
                                display: true,
                                text: 'Размер массива'
                            }
                        }
                    }
                }
            });

            // График ближайших точек
            const closestCtx = document.getElementById('closestPairChart').getContext('2d');
            new Chart(closestCtx, {
                type: 'line',
                data: closestPairData,
                options: {
                    responsive: true,
                    maintainAspectRatio: false,
                    plugins: {
                        title: {
                            display: true,
                            text: 'Время поиска ближайших точек'
                        }
                    },
                    scales: {
                        y: {
                            type: 'logarithmic',
                            title: {
                                display: true,
                                text: 'Время (сек, логарифмическая шкала)'
                            }
                        },
                        x: {
                            title: {
                                display: true,
                                text: 'Количество точек'
                            }
                        }
                    }
                }
            });
        };
    </script>
</body>
</html>)";
    
    htmlFile.close();
}

void runSortingExperiments() {
    std::cout << "=== ЭКСПЕРИМЕНТЫ С АЛГОРИТМАМИ СОРТИРОВКИ ===\n\n";
    
    std::vector<int> sizes = {100, 500, 1000, 2000};
    std::vector<std::string> cases = {"Лучший", "Средний", "Худший"};
    std::vector<std::string> algorithms = {"SelectionSort", "BubbleSort", "MergeSort"};
    
    for (int size : sizes) {
        std::cout << "Размер массива: " << size << "\n";
        std::cout << std::string(80, '-') << "\n";
        std::cout << std::setw(15) << "Случай" 
                  << std::setw(20) << "Выбором (сек)" 
                  << std::setw(20) << "Пузырьком (сек)" 
                  << std::setw(20) << "Слиянием (сек)" << "\n";
        std::cout << std::string(80, '-') << "\n";
        
        for (const auto& caseName : cases) {
            std::vector<int> arr;
            
            if (caseName == "Лучший") {
                arr = SortingAlgorithms::generateBestCase(size);
            } else if (caseName == "Средний") {
                arr = SortingAlgorithms::generateAverageCase(size);
            } else {
                arr = SortingAlgorithms::generateWorstCase(size);
            }
            
            // Тестируем все алгоритмы
            std::vector<int> arrCopy = arr;
            double time1 = SortingAlgorithms::measureTime(SortingAlgorithms::selectionSort, arrCopy);
            sortingResults.push_back({"SelectionSort", caseName, size, time1});
            
            arrCopy = arr;
            double time2 = SortingAlgorithms::measureTime(SortingAlgorithms::bubbleSort, arrCopy);
            sortingResults.push_back({"BubbleSort", caseName, size, time2});
            
            arrCopy = arr;
            double time3 = SortingAlgorithms::measureTime(SortingAlgorithms::mergeSort, arrCopy);
            sortingResults.push_back({"MergeSort", caseName, size, time3});
            
            std::cout << std::setw(15) << caseName 
                      << std::setw(20) << std::fixed << std::setprecision(6) << time1
                      << std::setw(20) << time2
                      << std::setw(20) << time3 << "\n";
        }
        std::cout << "\n";
    }
}

void runSearchingExperiments() {
    std::cout << "=== ЭКСПЕРИМЕНТЫ С АЛГОРИТМАМИ ПОИСКА ===\n\n";
    
    std::vector<int> sizes = {1000, 10000, 100000, 1000000};
    
    std::cout << std::setw(15) << "Размер" 
              << std::setw(25) << "Последовательный (сек)" 
              << std::setw(20) << "Бинарный (сек)" << "\n";
    std::cout << std::string(60, '-') << "\n";
    
    for (int size : sizes) {
        auto arr = SearchingAlgorithms::generateSortedArray(size);
        
        // Ищем элемент, которого нет в массиве (худший случай)
        int target = -1;
        
        double time1 = SearchingAlgorithms::measureTime(SearchingAlgorithms::sequentialSearch, arr, target);
        searchResults.push_back({"SequentialSearch", size, time1});
        
        double time2 = SearchingAlgorithms::measureTime(SearchingAlgorithms::binarySearch, arr, target);
        searchResults.push_back({"BinarySearch", size, time2});
        
        std::cout << std::setw(15) << size 
                  << std::setw(25) << std::fixed << std::setprecision(6) << time1
                  << std::setw(20) << time2 << "\n";
    }
    std::cout << "\n";
}

void runClosestPairExperiments() {
    std::cout << "=== ЭКСПЕРИМЕНТЫ С ПОИСКОМ БЛИЖАЙШИХ ТОЧЕК ===\n\n";
    
    std::vector<int> sizes = {10, 50, 100, 500, 1000};
    
    std::cout << std::setw(15) << "Кол-во точек" 
              << std::setw(25) << "Грубая сила (сек)" 
              << std::setw(25) << "Декомпозиция (сек)" << "\n";
    std::cout << std::string(65, '-') << "\n";
    
    for (int size : sizes) {
        auto points = ClosestPair::generateRandomPoints(size);
        
        double time1 = ClosestPair::measureTime(ClosestPair::bruteForce, points);
        closestPairResults.push_back({"BruteForce", size, time1});
        
        double time2 = ClosestPair::measureTime(ClosestPair::divideAndConquer, points);
        closestPairResults.push_back({"DivideAndConquer", size, time2});
        
        std::cout << std::setw(15) << size 
                  << std::setw(25) << std::fixed << std::setprecision(6) << time1
                  << std::setw(25) << time2 << "\n";
    }
    std::cout << "\n";
}

int main() {
    std::cout << "ВЫЧИСЛИТЕЛЬНЫЙ ЭКСПЕРИМЕНТ: АНАЛИЗ АЛГОРИТМОВ\n";
    std::cout << std::string(50, '=') << "\n\n";
    
    try {
        // Задание 1: Алгоритмы сортировки
        runSortingExperiments();
        
        // Задание 2: Поиск ближайших точек
        runClosestPairExperiments();
        
        // Задание 3: Алгоритмы поиска
        runSearchingExperiments();
        
        // Сохранение результатов
        std::cout << "Сохранение результатов в CSV...\n";
        saveToCSV();
        
        std::cout << "Генерация HTML отчета...\n";
        generateHTMLReport();
        
        std::cout << "Готово! Созданы файлы:\n";
        std::cout << "- sorting_results.csv\n";
        std::cout << "- search_results.csv\n";
        std::cout << "- closest_pair_results.csv\n";
        std::cout << "- report.html (открыть в браузере)\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}