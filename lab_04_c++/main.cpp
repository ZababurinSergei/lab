#include <cstdio>
#include <cmath>

int main() {
    double x, y, z, d;
    const double EPS = 1e-6;

    printf("Лабораторная работа №4\n");
    printf("Вариант 9\n");
    printf("Программа вычисления z = f(x, y)\n");
    printf("----------------------------------------\n\n");

    printf("Введите значения x и y: ");
    scanf("%lf %lf", &x, &y);

    printf("\n--- Вычисление ---\n");
    printf("x = %.6f, y = %.6f\n", x, y);

    d = x * x - y * y;
    printf("d = x^2 - y^2 = %.10f\n", d);

    double d_rounded = round(d * 1e6) / 1e6;
    printf("d (округлённое) = %.6f\n", d_rounded);

    if (fabs(d_rounded - 1.0) < EPS && y < 0) {
        printf("Условие: x^2 - y^2 = 1 (%.6f = 1) и y < 0 (%.6f < 0)\n", d, y);
        printf("Ветвь 3: z = 2y / sqrt(3 - x)\n");

        double radicand = 3 - x;
        printf("Знаменатель: sqrt(3 - x) = sqrt(%.10f)\n", radicand);

        if (radicand <= EPS) {
            printf("ОШИБКА: подкоренное выражение в знаменателе <= 0!\n");
            return 1;
        }

        double sqrt_val = sqrt(radicand);
        z = 2 * y / sqrt_val;
        printf("2y = %.6f\n", 2 * y);
        printf("sqrt(3 - x) = sqrt(%.10f) = %.10f\n", radicand, sqrt_val);
        printf("z = %.6f / %.10f = %.10f\n", 2 * y, sqrt_val, z);
    }
    else if (fabs(d_rounded) < EPS && y >= 0) {
        printf("Условие: x^2 - y^2 = 0 (%.6f = 0) и y >= 0 (%.6f >= 0)\n", d, y);
        printf("Ветвь 2: z = sqrt(2x + y)\n");

        double radicand = 2 * x + y;
        printf("Подкоренное выражение: 2x + y = %.10f\n", radicand);

        if (radicand < -EPS) {
            printf("ОШИБКА: подкоренное выражение отрицательно!\n");
            return 1;
        }

        if (radicand < 0) radicand = 0;
        z = sqrt(radicand);
        printf("z = sqrt(%.10f) = %.10f\n", radicand, z);
    }
    else if (fabs(d_rounded) > EPS) {
        printf("Условие: x^2 - y^2 != 0 (%.6f != 0)\n", d);
        printf("Ветвь 1: z = (2x + y)/(x + 2y) + x^2\n");

        double denominator = x + 2 * y;
        if (fabs(denominator) < EPS) {
            printf("ОШИБКА: знаменатель (x + 2y) = 0!\n");
            return 1;
        }

        z = (2 * x + y) / denominator + x * x;
        printf("(2*%.6f + %.6f) = %.10f\n", x, y, 2 * x + y);
        printf("(x + 2y) = %.10f\n", denominator);
        printf("z = %.10f / %.10f + %.10f = %.10f\n", 2 * x + y, denominator, x * x, z);
    }
    else {
        printf("ОШИБКА: условия не выполнены!\n");
        printf("Проверьте:\n");
        printf("  - x^2 - y^2 = %.6f\n", d);
        printf("  - y = %.6f\n", y);
        printf("  - (x^2 - y^2 != 0) -> НЕТ\n");
        printf("  - (x^2 - y^2 = 0 и y >= 0) -> НЕТ\n");
        printf("  - (x^2 - y^2 = 1 и y < 0) -> НЕТ\n");
        return 1;
    }

    printf("\n--- Результат ---\n");
    printf("z = %.10f\n", z);

    return 0;
}