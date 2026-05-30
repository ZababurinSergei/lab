#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>

void printMatrix(double **matrix, const int rows, const int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printColumnOrder(const double *max_abs, const int cols, char *title) {
    printf("%s: ", title);
    for (int j = 0; j < cols; j++) {
        printf("[%d:%.2f] ", j + 1, max_abs[j]);
    }
    printf("\n");
}

double findMaxAbsInColumn(double **matrix, const int rows, const int col) {
    double max_abs = fabs(matrix[0][col]);
    for (int i = 1; i < rows; i++) {
        double current_abs = fabs(matrix[i][col]);
        if (current_abs > max_abs) {
            max_abs = current_abs;
        }
    }
    return max_abs;
}

void swapColumns(double **matrix, const int rows, const int col1, const int col2) {
    if (col1 == col2) return;

    for (int i = 0; i < rows; i++) {
        const double temp = matrix[i][col1];
        matrix[i][col1] = matrix[i][col2];
        matrix[i][col2] = temp;
    }
}

int isSorted(const double *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);

    int rows, cols;

    srand(time(NULL));

    printf("========================================\n");
    printf("Лабораторная работа №11 (Вариант 9)\n");
    printf("Сортировка столбцов по возрастанию\n");
    printf("максимального по модулю элемента\n");
    printf("========================================\n\n");

    printf("Введите количество строк: ");
    scanf("%d", &rows);
    printf("Введите количество столбцов: ");
    scanf("%d", &cols);

    if (rows <= 0 || cols <= 0) {
        printf("Ошибка: Размеры массива должны быть положительными!\n");
        return 1;
    }

    auto** matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
    }
    auto* max_abs_values = (double*)malloc(cols * sizeof(double));
    auto* original_max_abs = (double*)malloc(cols * sizeof(double));

    printf("\nИсходный массив:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (double)(rand() % 1000 - 500) / 10.0;
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n--- Характеристики столбцов (до сортировки) ---\n");
    for (int j = 0; j < cols; j++) {
        max_abs_values[j] = findMaxAbsInColumn(matrix, rows, j);
        original_max_abs[j] = max_abs_values[j]; // Сохраняем исходные значения
        printf("Столбец %d: max|элемент| = %.2f\n", j + 1, max_abs_values[j]);
    }
    printColumnOrder(max_abs_values, cols, "Порядок столбцов (до сортировки)");

    printf("\n--- Сортировка столбцов (методом выбора) ---\n");

    for (int i = 0; i < cols - 1; i++) {
        printf("\nШаг %d:\n", i + 1);
        printf("  Ищем столбец с минимальным max|элемент| среди столбцов %d-%d\n", i + 1, cols);

        int min_index = i;
        for (int j = i + 1; j < cols; j++) {
            if (max_abs_values[j] < max_abs_values[min_index]) {
                min_index = j;
            }
        }

        printf("  Минимальный max|элемент| = %.2f находится в столбце %d\n",
               max_abs_values[min_index], min_index + 1);

        if (min_index != i) {
            printf("  Столбец %d имеет max|элемент| = %.2f, что больше\n",
                   i + 1, max_abs_values[i]);
            printf("  Меняем местами столбцы %d и %d\n", i + 1, min_index + 1);

            const double temp_abs = max_abs_values[i];
            max_abs_values[i] = max_abs_values[min_index];
            max_abs_values[min_index] = temp_abs;

            swapColumns(matrix, rows, i, min_index);

            printf("  Текущий порядок max|элемент|: ");
            for (int k = 0; k < cols; k++) {
                printf("%.2f ", max_abs_values[k]);
            }
            printf("\n");

            printf("  Текущее состояние массива:\n");
            printMatrix(matrix, rows, cols);
        } else {
            printf("  Столбец %d уже на своем месте\n", i + 1);
            printf("  Текущий порядок max|элемент|: ");
            for (int k = 0; k < cols; k++) {
                printf("%.2f ", max_abs_values[k]);
            }
            printf("\n");
        }
    }

    printf("\n========================================\n");
    printf("Результат сортировки:\n");
    printMatrix(matrix, rows, cols);

    printf("\n--- Отсортированные характеристики ---\n");
    for (int j = 0; j < cols; j++) {
        printf("Столбец %d: max|элемент| = %.2f\n", j + 1, max_abs_values[j]);
    }
    printColumnOrder(max_abs_values, cols, "Порядок столбцов (после сортировки)");

    printf("\n--- Проверка ---\n");
    if (isSorted(max_abs_values, cols)) {
        printf("✓ Сортировка выполнена корректно!\n");
        printf("  max|элемент| столбцов расположены по возрастанию.\n");
    } else {
        printf("✗ Ошибка: массив не отсортирован!\n");
    }

    printf("\n--- Контрольная проверка ---\n");
    printf("Пересчитаем максимальные по модулю элементы в каждом столбце:\n");
    for (int j = 0; j < cols; j++) {
        double check_max = findMaxAbsInColumn(matrix, rows, j);
        printf("  Столбец %d: max|элемент| = %.2f ", j + 1, check_max);
        if (fabs(check_max - max_abs_values[j]) < 0.001) {
            printf("✓\n");
        } else {
            printf("✗ (должно быть %.2f)\n", max_abs_values[j]);
        }
    }

    printf("\n========================================\n");
    printf("СРАВНИТЕЛЬНАЯ ТАБЛИЦА\n");
    printf("========================================\n");
    printf("+----------+-------------------+-------------------+------------+\n");
    printf("| Столбец  | Было max|элемент| | Стало max|элемент| | Изменение |\n");
    printf("+----------+-------------------+-------------------+------------+\n");

    for (int new_col = 0; new_col < cols; new_col++) {
        const double current_max = max_abs_values[new_col];

        for (int old_col = 0; old_col < cols; old_col++) {
            if (fabs(original_max_abs[old_col] - current_max) < 0.001) {
                break;
            }
        }

        const double difference = max_abs_values[new_col] - original_max_abs[new_col];

        printf("|    %d     |       %.2f        |       %.2f        |   %+7.2f   |\n",
               new_col + 1,
               original_max_abs[new_col],
               max_abs_values[new_col],
               difference);
    }
    printf("+----------+-------------------+-------------------+------------+\n");

    printf("\n--- Информация о перестановках ---\n");
    printf("Было (порядок столбцов по номерам): ");
    for (int j = 0; j < cols; j++) {
        printf("%d ", j + 1);
    }
    printf("\nСтало (порядок столбцов по номерам): ");

    for (int new_col = 0; new_col < cols; new_col++) {
        const double current_max = max_abs_values[new_col];
        for (int old_col = 0; old_col < cols; old_col++) {
            if (fabs(original_max_abs[old_col] - current_max) < 0.001) {
                printf("%d ", old_col + 1);
                break;
            }
        }
    }
    printf("\n");

    printf("\n--- Статистика ---\n");
    printf("Размер массива: %d x %d\n", rows, cols);
    printf("Диапазон значений: от -50.0 до 50.0\n");
    printf("Метод сортировки: выбором (selection sort)\n");
    printf("Критерий сортировки: max|элемент| столбца по возрастанию\n");

    printf("\n========================================\n");
    printf("Программа успешно завершена!\n");
    printf("========================================\n");

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(max_abs_values);
    free(original_max_abs);

    return 0;
}