#include "Triangle.h"

using namespace std;

int main()
{
    Triangle tr;
    double tmp;
    int ans;
    do
    {
        system("clear");
        cin.clear();
        cout << "1: Ввести данные треугольника"                   << endl
             << "2: Вывести данные треугольника"                  << endl
             << "3: Длины биссектрис всех углов"                  << endl
             << "4: Длина медианы, проведенной к большей стороне" << endl
             << "5: Радиус вписаной окружности"                   << endl
             << "6: Высота из заданного угла"                     << endl
             << "7: Выйти"                                        << endl;
        cin >> ans;

        switch (ans)
        {
        case 1:
            cout << "Введите данные: две стороны и угол между ними" << endl;
            while (!(cin >> tr) || !tr.isDataValid())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректные данные, попробуйте снова" << endl;
            }
            break;
        case 2:
            cout << tr;
            getchar();
            getchar();
            break;
        case 3:
            tr.bisector();
            getchar();
            getchar();
            break;
        case 4:
            tmp = tr.median();
            if (tmp == 0)
                cout << "Данные треугольника не корректны" << endl;
            else
                cout << "Медиана, проведенная к большей стороне: "
                     << tmp << endl;
            getchar();
            getchar();
            break;
        case 5:
            tmp = tr.inRadius();
            if (tmp == 0)
                cout << "Данные треугольника не корректны" << endl;
            else
                cout << "Радиус вписаной окружности: "
                     << tr.inRadius() << endl;
            getchar();
            getchar();
            break;
        case 6:
            if (tr.isDataValid())
            {
                char angle[3];
                cout << "Введите стороны меджу которыми находится угол из которого проведена высота" << endl;
                while (!(cin >> angle) || (tmp = tr.height(angle)) == -1)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Введен некорректный угол, введите ab, bc или ac" << endl;
                }
                cout << "Высота, проведенная из угла " << angle << " равна: " << tmp << endl;
            }
            else
                cout << "Данные треугольника некорректны" << endl;
            getchar();
            getchar();
            break;
        }
    } while (ans < 7);
    return 0;
}