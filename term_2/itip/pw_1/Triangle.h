#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <cmath>

class Triangle
{
    double a;       // Первая сторона
    double b;       // Вторая сторона
    double abAngle; // Угол между a и b

public:
    Triangle();                       // Конструктор без параметров
    Triangle(double, double, double); // Конструктор с параметрами
    Triangle(Triangle &);             // Конструктор копирования
    void setA(double);                // Сеттер первой стороны
    void setB(double);                // Сеттер второй стороны
    void setABAngle(double);          // Сеттер угла между сторонами
    double getA(void);                // Геттер первой стороны
    double getB(void);                // Геттер второй стороны
    double getABAngle(void);          // Геттер угла между сторонами
    double calcC(void);               // Подсчет 3 стороны
    double calcBCAngle(void);         // Подсчет угла между b и c
    double calcACAngle(void);         // Подсчет угла между c и a
    void bisector(void);              // Длины биссектрис всех углов
    double median(void);              // Медиана, проведенная к большей стороне
    double inRadius(void);            // Радиус вписанной окружности
    double height(char *);            // Высота из заданного угла
    bool isDataValid(void);           // Проверка на корректность данных
    ~Triangle();                      // Деструктор
    // Перегрузка операторов
    Triangle operator=(Triangle &);
    Triangle operator*=(int &);
    friend std::ostream &operator<<(std::ostream &, Triangle &);
    friend std::istream &operator>>(std::istream &, Triangle &);
};
#endif