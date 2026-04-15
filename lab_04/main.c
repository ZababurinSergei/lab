#include <stdio.h>
#include <math.h>

int main(void) {
    double x, y, z, d;

    printf("Лабораторная работа №4\n");
    printf("Вариант 9\n");
    printf("Программа вычисления z = f(x, y)\n");
    printf("----------------------------------------\n\n");

    // Ввод исходных данных
    printf("Введите значения x и y: ");
    scanf("%lf %lf", &x, &y);

    printf("\n--- Вычисление ---\n");
    printf("x = %.6f, y = %.6f\n", x, y);

    // Вычисление разности квадратов
    d = x * x - y * y;
    printf("d = x^2 - y^2 = %.6f\n", d);

    // Разветвление по условиям
    if (d != 0) {
        printf("Условие: x^2 - y^2 != 0 (%.6f != 0)\n", d);
        printf("Ветвь 1: z = (2x + y)/(x + 2y) + x^2\n");

        // Проверка знаменателя
        double denominator = x + 2 * y;
        if (denominator == 0) {
            printf("ОШИБКА: знаменатель (x + 2y) = 0!\n");
            return 1;
        }

        z = (2 * x + y) / denominator + x * x;
        printf("(2*%.6f + %.6f) = %.6f\n", x, y, 2 * x + y);
        printf("(x + 2y) = %.6f\n", denominator);
        printf("z = %.6f / %.6f + %.6f = %.6f\n", 2 * x + y, denominator, x * x, z);
    }
    else if (y >= 0) {
        printf("Условие: x^2 - y^2 = 0 (%.6f = 0) и y >= 0 (%.6f >= 0)\n", d, y);
        printf("Ветвь 2: z = sqrt(2x + y)\n");

        // Проверка подкоренного выражения
        double radicand = 2 * x + y;
        printf("Подкоренное выражение: 2x + y = %.6f\n", radicand);

        if (radicand < 0) {
            printf("ОШИБКА: подкоренное выражение отрицательно!\n");
            return 1;
        }

        z = sqrt(radicand);
        printf("z = sqrt(%.6f) = %.6f\n", radicand, z);
    }
    else if (fabs(d - 1.0) < 1e-9 && y < 0) {
        printf("Условие: x^2 - y^2 = 1 (%.6f = 1) и y < 0 (%.6f < 0)\n", d, y);
        printf("Ветвь 3: z = 2y / sqrt(3 - x)\n");

        // Проверка знаменателя
        double radicand = 3 - x;
        printf("Знаменатель: sqrt(3 - x) = sqrt(%.6f)\n", radicand);

        if (radicand <= 0) {
            printf("ОШИБКА: подкоренное выражение в знаменателе <= 0!\n");
            return 1;
        }

        z = 2 * y / sqrt(radicand);
        printf("2y = %.6f\n", 2 * y);
        printf("sqrt(3 - x) = sqrt(%.6f) = %.6f\n", radicand, sqrt(radicand));
        printf("z = %.6f / %.6f = %.6f\n", 2 * y, sqrt(radicand), z);
    }
    else {
        printf("ОШИБКА: условия не выполнены!\n");
        printf("Проверьте:\n");
        printf("  - x^2 - y^2 = %.6f\n", d);
        printf("  - y = %.6f\n", y);
        return 1;
    }

    printf("\n--- Результат ---\n");
    printf("z = %.6f\n", z);

    return 0;
}