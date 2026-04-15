#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX_SIZE 50

// Функция для генерации случайных чисел в диапазоне [min, max]
int rnd(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int n;
    int matrix[MAX_SIZE][MAX_SIZE];
    int mode;

    // Сначала выбор режима работы
    printf("Выберите режим ввода:\n");
    printf("1 — Заполнить случайными числами\n");
    printf("2 — Ввести вручную\n");
    printf("Ваш выбор: ");
    scanf("%d", &mode);

    if (mode != 1 && mode != 2) {
        printf("Неверный выбор режима.\n");
        return 1;
    }

    // Затем ввод размера матрицы
    printf("\nВведите размер квадратной матрицы (n <= %d): ", MAX_SIZE);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE) {
        printf("Некорректный размер матрицы.\n");
        return 1;
    }

    if (mode == 1) {
        // Случайные числа
        srand(time(NULL));
        printf("\nСгенерированная матрица:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = rnd(-10, 20);
                printf("%4d", matrix[i][j]);
            }
            printf("\n");
        }
    }
    else if (mode == 2) {
        // Ручной ввод
        printf("\nВведите элементы матрицы построчно (через пробел или Enter):\n");
        for (int i = 0; i < n; i++) {
            printf("Строка %d: ", i + 1);
            for (int j = 0; j < n; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }
        printf("\nВведённая матрица:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%4d", matrix[i][j]);
            }
            printf("\n");
        }
    }

    // 1. Суммы элементов по столбцам
    printf("\nСуммы элементов по столбцам:\n");
    for (int j = 0; j < n; j++) {
        int col_sum = 0;
        for (int i = 0; i < n; i++) {
            col_sum += matrix[i][j];
        }
        printf("Столбец %d: %d\n", j + 1, col_sum);
    }

    // 2. Сумма модулей элементов ниже главной диагонали
    int sum_below = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j) {
                sum_below += abs(matrix[i][j]);
            }
        }
    }
    printf("\nСумма модулей элементов ниже главной диагонали: %d\n", sum_below);

    return 0;
}