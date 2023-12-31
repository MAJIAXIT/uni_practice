#include <stdio.h>
#include <stdlib.h>

#define CUBE_SIDE 3 // Сторона куба

int main()
{
    int cube[CUBE_SIDE][CUBE_SIDE][CUBE_SIDE]; // Матрица 3x3x3
    int c1, c2, c3; // Первая, вторая, третья координаты
    printf("Enter 3d array 3x3x3:\n");
    // Ввод матрицы
    for (int i = 0; i < CUBE_SIDE; i++)
        for (int j = 0; j < CUBE_SIDE; j++)
            for (int k = 0; k < CUBE_SIDE; k++)
                scanf("%d", &cube[i][j][k]);
    // Проверка прозрачности по третьей координате
    for (c1 = 0; c1 < CUBE_SIDE; c1++)
    {
        for (c2 = 0; c2 < CUBE_SIDE; c2++)
        {
            for (c3 = 0; c3 < CUBE_SIDE; c3++)
            {
                if (cube[c1][c2][c3]) // Если элемент не прозрачный
                    break; // Выйти из цикла, линия не прозрачна
            }
            if (c3 == CUBE_SIDE) // Если третья координата имеет максимальное значение
                break; // Выйти из цикла, линия не прозрачна
        }
        if (c2 < CUBE_SIDE) // Если перебраны не все возможные вторые координаты
            break; // Выйти из цикла, линия прозрачна 
    }
    if (c1 < CUBE_SIDE) // Если перебраны не все возможные первые координаты, линия по последним координатам прозрачна
        printf("Куб прозрачен по третьей координате x = %d ; y = %d\n", c1, c2);
    else // Инече куб не прозрачен по третьей координате
        printf("Куб не прозрачен по третьей координате\n");

    // Проверка прозрачности по второй координате
    for (c3 = 0; c3 < CUBE_SIDE; c3++)
    {
        for (c1 = 0; c1 < CUBE_SIDE; c1++)
        {
            for (c2 = 0; c2 < CUBE_SIDE; c2++)
            {
                if (cube[c1][c2][c3]) // Если элемент не прозрачный
                    break; // Выйти из цикла, линия не прозрачна
            }
            if (c2 == CUBE_SIDE) // Если вторая координата имеет максимальное значение
                break; // Выйти из цикла, линия не прозрачна
        }
        if (c1 < CUBE_SIDE) // Если перебраны не все возможные первые координаты
            break; // Выйти из цикла, линия прозрачна
    }
    if (c3 < CUBE_SIDE) // Если перебраны не все возможные третьи координаты, линия по последним координатам прозрачна
        printf("Куб прозрачен по второй координате x = %d ; z = %d\n", c1, c3);
    else // Инече куб не прозрачен по второй координате
        printf("Куб не прозрачен по второй координате\n");

    // Проверка прозрачности по первой координате
    for (c3 = 0; c3 < CUBE_SIDE; c3++)
    {
        for (c2 = 0; c2 < CUBE_SIDE; c2++)
        {
            for (c1 = 0; c1 < CUBE_SIDE; c1++)
            {
                if (cube[c1][c2][c3]) // Если элемент не прозрачный
                    break; // Выйти из цикла, линия не прозрачна
            }
            if (c1 == CUBE_SIDE) // Если первая координата имеет максимальное значение
                break;// Выйти из цикла, линия не прозрачна
        }
        if (c2 < CUBE_SIDE) // Если перебраны не все возможные вторые координаты
            break; // Выйти из цикла, линия прозрачна
    }
    if (c3 < CUBE_SIDE) // Если перебраны не все возможные третьи координаты, линия по последним координатам прозрачна
        printf("Куб прозрачен по первой координате y = %d ; z = %d\n", c2, c3);
    else // Инече куб не прозрачен по первой координате
        printf("Куб не прозрачен по первой координате\n");

    return 0;
}

/*
1 1 1 
1 1 1 
1 1 1 

1 1 1 
1 1 1 
1 1 1 

1 1 1 
1 1 1 
1 1 1
*/