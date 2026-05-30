#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <clocale>

int rnd(const int min, const int max) {
    return rand() % (max - min + 1) + min;
}

void inputMatrix(int **matrix, const int n, const int mode) {
    if (mode == 1) {
        srand(time(NULL));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                matrix[i][j] = rnd(-10, 20);
    } else if (mode == 2) {
        printf("\nВведите элементы матрицы построчно (через пробел или Enter):\n");
        for (int i = 0; i < n; i++) {
            printf("Строка %d: ", i + 1);
            for (int j = 0; j < n; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }
    }
}

void printMatrix(int **matrix, int n) {
    printf("\nМатрица:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d", matrix[i][j]);
        printf("\n");
    }
}

void printColumnSums(int **matrix, const int n) {
    printf("\nСуммы элементов по столбцам:\n");
    for (int j = 0; j < n; j++) {
        int col_sum = 0;
        for (int i = 0; i < n; i++)
            col_sum += matrix[i][j];
        printf("Столбец %d: %d\n", j + 1, col_sum);
    }
}

// Сумма модулей ниже главной диагонали
int sumBelowDiagonalAbs(int **matrix, const int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i > j)
                sum += abs(matrix[i][j]);
    return sum;
}

void showMenu() {
    printf("\n=== МЕНЮ ===\n");
    printf("1. Заполнить случайными числами\n");
    printf("2. Ввести вручную\n");
    printf("3. Вывести матрицу\n");
    printf("4. Показать суммы по столбцам\n");
    printf("5. Показать сумму модулей ниже главной диагонали\n");
    printf("0. Выход\n");
}

int main() {
    setlocale(LC_ALL, "Rus");

    int n = 0;
    int **matrix = NULL;
    int mode;
    int choice;

    printf("Введите размер квадратной матрицы: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Некорректный размер матрицы.\n");
        return 1;
    }

    matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    do {
        showMenu();
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                mode = 1;
                inputMatrix(matrix, n, mode);
                printf("Матрица успешно заполнена случайными числами.\n");
                break;
            case 2:
                mode = 2;
                inputMatrix(matrix, n, mode);
                printf("Матрица успешно введена.\n");
                break;
            case 3:
                printMatrix(matrix, n);
                break;
            case 4:
                printColumnSums(matrix, n);
                break;
            case 5: {
                int res = sumBelowDiagonalAbs(matrix, n);
                printf("\nСумма модулей элементов ниже главной диагонали: %d\n", res);
                break;
            }
            case 0:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}