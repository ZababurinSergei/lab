#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <clocale>

#define MAX_SIZE 50

int rnd(const int min, const int max) {
    return rand() % (max - min + 1) + min;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int n;
    int matrix[MAX_SIZE][MAX_SIZE];
    int mode;

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

    printf("\nСуммы элементов по столбцам:\n");
    printf("\nстолбцов n:\n", n);

    for (int j = 0; j < n; j++) {
        int col_sum = 0;
        for (int i = 0; i < n; i++) {
            col_sum += matrix[i][j];
        }
        printf("Столбец %d: %d\n", j + 1, col_sum);
    }

    int sum_below = 0;
    printf("Количество столбцов n = %d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j) {
                printf("  matrix[%d][%d] = %d\n", i, j, matrix[i][j]);
                sum_below += abs(matrix[i][j]);
            }
        }
    }
    printf("\nСумма модулей элементов ниже главной диагонали: %d\n", sum_below);

    return 0;
}