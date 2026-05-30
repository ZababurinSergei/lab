#include <cstdio>
#include <cmath>
#include <clocale>

int main()
{
    setlocale(LC_ALL, "Russian");

    double x, a, b;

    printf("Введите x, a, b через пробел: ");
    scanf("%lf%lf%lf", &x, &a, &b);

    if (a == 0)
    {
        printf("Ошибка: a = 0\n");
        return 1;
    }

    const double chisl = tan(atan(x / a) + 1) - pow(cos(b * x), 2);
    double znam = (x - a) * (b * b + a);

    if (znam == 0)
    {
        printf("Ошибка: знаменатель = 0\n");
        return 1;
    }

    const double rez = chisl / znam;
    printf("Результат = %.6lf\n", rez);

    return 0;
}