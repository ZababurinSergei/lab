#include <stdio.h>
#include <math.h>
#include <locale.h>

int main(void)
{
    setlocale(LC_ALL, "Russian");

    double x, a, b;
    double chisl, znam, rez;

    printf("Введите x, a, b через пробел: ");
    scanf("%lf%lf%lf", &x, &a, &b);

    if (a == 0)
    {
        printf("Ошибка: a = 0\n");
        return 1;
    }

    chisl = tan(atan(x / a) + 1) - pow(cos(b * x), 2);
    znam = (x - a) * (b * b + a);

    if (znam == 0)
    {
        printf("Ошибка: знаменатель = 0\n");
        return 1;
    }

    rez = chisl / znam;
    printf("Результат = %.6lf\n", rez);

    return 0;
}