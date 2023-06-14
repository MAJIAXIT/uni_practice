#include "Triangle.h"

Triangle::Triangle() : a(0), b(0), abAngle(0)
{
    std::cout << "Конструктор без параметров\n";
}

Triangle::Triangle(double a, double b, double abAngle) : a(a), b(b), abAngle(abAngle)
{
    std::cout << "Конструктор с параметрами\n"; 
}

Triangle::Triangle(Triangle &tr) : a(tr.a), b(tr.b), abAngle(tr.abAngle)
{ 
    std::cout << "Конструктор копирования\n"; 
}

Triangle::~Triangle() { std::cout << "Вызов деструктора\n"; }

void Triangle::setA(double val) { a = val; }
void Triangle::setB(double val) { b = val; }
void Triangle::setABAngle(double val) { abAngle = val; }

double Triangle::getA() { return a; }
double Triangle::getB() { return b; }
double Triangle::getABAngle() { return abAngle; }

bool Triangle::isDataValid(void) { return a > 0 && b > 0 && abAngle > 0 && abAngle < M_PI; }

// Вычисления третьей стороны
double Triangle::calcC(void)
{
    if (isDataValid()) // Если данные треугольника корректны
        // Вернуть вычисленную по теореме косинусов сторону
        return sqrt(a * a + b * b - 2 * a * b * cos(abAngle));
    else
        // Иначе вернуть 0
        return 0;
}

// Вычисление угла BC
double Triangle::calcBCAngle(void)
{
    if (isDataValid()) // Если данные треугольника корректны
    {
        double c = calcC(); // Вычислить сторону c
        // Вернуть вычисленный по теореме косинусов угол
        return acos((b * b + c * c - a * a) / (2 * c * b));
    }
    else
        return 0;
}

// Вычисление угла AC
double Triangle::calcACAngle(void)
{
    if (isDataValid()) // Если данные треугольника корректны
    {
        double c = calcC(); // Вычислить сторону С
        // Вернуть вычисленный по теореме косинусов угол
        return acos((a * a + c * c - b * b) / (2 * a * c));
    }
    else
        return 0;
}

// Вычисление биссектрис всех углов
void Triangle::bisector()
{
    if (isDataValid()) // Если данные треугольника корректны
    {
        double abBis, bcBis, acBis, c;
        c = calcC(); // Вычислить сторону С
        // Вычислить биссектрисы
        abBis = sqrt(a * b * (a + b - c) * (a + c + b)) / (a + b);
        bcBis = sqrt(b * c * (b + c - a) * (a + c + b)) / (b + c);
        acBis = sqrt(a * c * (a + c - b) * (a + c + b)) / (a + c);
        // Вывести вычисленные биссектрисы
        std::cout << "Биссектриса угла ab: " << abBis
                  << "\nБиссектриса угла bc: " << bcBis
                  << "\nБиссектриса угла ac: " << acBis << std::endl;
    }
    else
        std::cout << "Данные треугольника не корректны" << std::endl;
}

// Вычисление медианы, проведенной к большей стороне
double Triangle::median()
{
    if (isDataValid()) // Если данные верны
    {
        /* Создаем массив сторон, далее проверяем все комбинации
         * перестановок сторон в формуле вычисление медиан,
         * используя остатки от деления индекса на 3,
         * чтобы найти наименьшую медиану, т.к. к наибольшей
         * стороне проведена наименьшая по длине медиана
         */
        double min = 1000000, med, sides[] = {a, b, calcC()};
        for (int i = 0; i < 3; i++)
        {
            med = sqrt(2 * sides[i % 3] * sides[i % 3] +
                       2 * sides[(i + 2) % 3] * sides[(i + 2) % 3] -
                       sides[(i + 1) % 3] * sides[(i + 1) % 3]) /
                  2;
            min = min < med ? min : med;
        }
        return min;
    }
    else
        return 0;
}

// Радиус вписаной окружности
double Triangle::inRadius()
{
    if (isDataValid()) // Если данные треугольника корректны
    {
        // Вычисление площади для нахождения радиуса
        double s = (a * b * sin(abAngle)) / 2;
        // Возврат вычисленного по формуле радиуса
        return 2 * s / (a + b + calcC());
    }
    else
        return 0;
}

// Вычисление высоты, проведенной из заданного угла
double Triangle::height(char *angle)
{
    if (isDataValid()) // Если данные треугольника корректны
    {
        // Вычисление стороны С
        double c = calcC(), p = (a + b + c) / 2;
        // Подстановка указанного угла в формулу и фозврат значения
        if (strcmp(angle, "ab") == 0 ||
            strcmp(angle, "ba") == 0 ||
            strcmp(angle, "AB") == 0 ||
            strcmp(angle, "BA") == 0)
            return 2 * sqrt(p * (p - a) * (p - b) * (p - c)) / c;
        else if (strcmp(angle, "bc") == 0 ||
                 strcmp(angle, "cb") == 0 ||
                 strcmp(angle, "BC") == 0 ||
                 strcmp(angle, "CB") == 0)
            return 2 * sqrt(p * (p - a) * (p - b) * (p - c)) / a;
        else if (strcmp(angle, "ac") == 0 ||
                 strcmp(angle, "ca") == 0 ||
                 strcmp(angle, "AC") == 0 ||
                 strcmp(angle, "CA") == 0)
            return 2 * sqrt(p * (p - a) * (p - b) * (p - c)) / b;
        else
            return -1;
    }
    else
        return 0;
}

// Оператор масштабирования треугольника
Triangle Triangle::operator*=(int &scale)
{
    a *= scale;
    b *= scale;
    return *this;
}

Triangle Triangle::operator=(Triangle &tr)
{
    tr.a = a;
    tr.b = b;
    tr.abAngle = abAngle;
    return *this;
}

std::ostream &operator<<(std::ostream &out, Triangle &tr)
{
    out << "A: " << tr.a
        << "\nB: " << tr.b
        << "\nC: " << tr.calcC()
        << "\nab angle: " << tr.abAngle * 180 / M_PI
        << "\nbc angle: " << tr.calcBCAngle() * 180 / M_PI
        << "\nac angle: " << tr.calcACAngle() * 180 / M_PI << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, Triangle &tr)
{
    in >> tr.a >> tr.b >> tr.abAngle;
    tr.abAngle *= M_PI / 180;
    return in;
}