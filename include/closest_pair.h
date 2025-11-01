#ifndef CLOSEST_PAIR_H
#define CLOSEST_PAIR_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <functional>

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    double distanceTo(const Point& other) const {
        return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }
    
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

class ClosestPair {
public:
    // Метод грубой силы
    static std::pair<double, std::pair<Point, Point>> bruteForce(const std::vector<Point>& points);
    
    // Метод декомпозиции (разделяй и властвуй)
    static std::pair<double, std::pair<Point, Point>> divideAndConquer(const std::vector<Point>& points);
    
    // Вспомогательная функция для измерения времени выполнения
    static double measureTime(std::function<std::pair<double, std::pair<Point, Point>>(const std::vector<Point>&)> algorithm, 
                             const std::vector<Point>& points);
    
    // Генерация тестовых данных
    static std::vector<Point> generateRandomPoints(int n);
    static std::vector<Point> generateWorstCasePoints(int n);

private:
    // Вспомогательные функции для метода декомпозиции
    static std::pair<double, std::pair<Point, Point>> closestUtil(const std::vector<Point>& pointsX, 
                                                                  const std::vector<Point>& pointsY);
    static std::pair<double, std::pair<Point, Point>> stripClosest(const std::vector<Point>& strip, 
                                                                   double d);
};

#endif