#include "closest_pair.h"
#include <chrono>
#include <random>
#include <algorithm>
#include <cmath>

// Метод грубой силы
std::pair<double, std::pair<Point, Point>> ClosestPair::bruteForce(const std::vector<Point>& points) {
    double minDist = std::numeric_limits<double>::max();
    Point p1, p2;
    int n = points.size();
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = points[i].distanceTo(points[j]);
            if (dist < minDist) {
                minDist = dist;
                p1 = points[i];
                p2 = points[j];
            }
        }
    }
    
    return {minDist, {p1, p2}};
}

// Вспомогательная функция для поиска ближайших точек в полосе
std::pair<double, std::pair<Point, Point>> ClosestPair::stripClosest(const std::vector<Point>& strip, double d) {
    double minDist = d;
    Point p1, p2;
    int size = strip.size();
    
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; j++) {
            double dist = strip[i].distanceTo(strip[j]);
            if (dist < minDist) {
                minDist = dist;
                p1 = strip[i];
                p2 = strip[j];
            }
        }
    }
    
    return {minDist, {p1, p2}};
}

// Вспомогательная рекурсивная функция для метода декомпозиции
std::pair<double, std::pair<Point, Point>> ClosestPair::closestUtil(const std::vector<Point>& pointsX, 
                                                                   const std::vector<Point>& pointsY) {
    int n = pointsX.size();
    
    // Базовый случай: используем метод грубой силы для малого количества точек
    if (n <= 3) {
        return bruteForce(pointsX);
    }
    
    // Разделяем точки на две половины
    int mid = n / 2;
    Point midPoint = pointsX[mid];
    
    std::vector<Point> leftX(pointsX.begin(), pointsX.begin() + mid);
    std::vector<Point> rightX(pointsX.begin() + mid, pointsX.end());
    
    std::vector<Point> leftY, rightY;
    for (const auto& point : pointsY) {
        if (point.x <= midPoint.x)
            leftY.push_back(point);
        else
            rightY.push_back(point);
    }
    
    // Рекурсивно находим минимальные расстояния в левой и правой половинах
    auto leftResult = closestUtil(leftX, leftY);
    auto rightResult = closestUtil(rightX, rightY);
    
    double d = std::min(leftResult.first, rightResult.first);
    auto minPair = (leftResult.first < rightResult.first) ? leftResult.second : rightResult.second;
    
    // Создаем полосу точек вокруг средней линии
    std::vector<Point> strip;
    for (const auto& point : pointsY) {
        if (std::abs(point.x - midPoint.x) < d) {
            strip.push_back(point);
        }
    }
    
    // Проверяем точки в полосе
    auto stripResult = stripClosest(strip, d);
    if (stripResult.first < d) {
        return stripResult;
    }
    
    return {d, minPair};
}

// Метод декомпозиции (разделяй и властвуй)
std::pair<double, std::pair<Point, Point>> ClosestPair::divideAndConquer(const std::vector<Point>& points) {
    if (points.size() < 2) {
        return {std::numeric_limits<double>::max(), {Point(), Point()}};
    }
    
    std::vector<Point> pointsX = points;
    std::vector<Point> pointsY = points;
    
    // Сортируем по x и y
    std::sort(pointsX.begin(), pointsX.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });
    
    std::sort(pointsY.begin(), pointsY.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });
    
    return closestUtil(pointsX, pointsY);
}

// Измерение времени выполнения
double ClosestPair::measureTime(std::function<std::pair<double, std::pair<Point, Point>>(const std::vector<Point>&)> algorithm, 
                               const std::vector<Point>& points) {
    auto start = std::chrono::high_resolution_clock::now();
    algorithm(points);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

// Генерация случайных точек
std::vector<Point> ClosestPair::generateRandomPoints(int n) {
    std::vector<Point> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1000.0);
    
    for (int i = 0; i < n; i++) {
        points.emplace_back(dis(gen), dis(gen));
    }
    return points;
}

// Генерация худшего случая (все точки на одной линии)
std::vector<Point> ClosestPair::generateWorstCasePoints(int n) {
    std::vector<Point> points;
    for (int i = 0; i < n; i++) {
        points.emplace_back(i, 0); // Все точки на оси X
    }
    return points;
}