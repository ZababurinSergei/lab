#include <cstdio>
#include <cmath>
#include <clocale>

int main() {
    setlocale(LC_ALL, "Russian");

    double x, term, epsilon;
    int max_iter;

    printf("Введите значение x: ");
    scanf("%lf", &x);
    printf("Введите точность epsilon (например, 1e-6): ");
    scanf("%lf", &epsilon);
    printf("Введите максимальное число итераций: ");
    scanf("%d", &max_iter);

    double S = 0.0;
    int k = 1;

    printf("\nВычисление суммы ряда:\n");
    printf("k\t\tterm\t\t\tS\n");
    printf("------------------------------------------------\n");

    do {
        const double denominator = (2.0 * k - 1) * (2.0 * k - 1) * M_PI * M_PI;
        const double arg = 1.0 - (4.0 * x * x) / denominator;

        if (arg <= 0) {
            printf("Ошибка: аргумент логарифма <= 0 при k = %d\n", k);
            break;
        }

        term = log(arg);
        S += term;

        printf("%d\t\t%.10lf\t\t%.10lf\n", k, term, S);

        k++;

    } while (fabs(term) >= epsilon && k <= max_iter);

    printf("\nРезультат: S = %.10lf\n", S);
    printf("Число учтенных членов ряда: %d\n", k - 1);

    return 0;
}