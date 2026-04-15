#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Функция для вывода двумерного массива
void printMatrix(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для вывода порядка столбцов
void printColumnOrder(double *max_abs, int cols, char *title) {
    printf("%s: ", title);
    for (int j = 0; j < cols; j++) {
        printf("[%d:%.2f] ", j + 1, max_abs[j]);
    }
    printf("\n");
}

// Функция для нахождения максимального по модулю элемента в столбце
double findMaxAbsInColumn(double **matrix, int rows, int col) {
    double max_abs = fabs(matrix[0][col]);
    for (int i = 1; i < rows; i++) {
        double current_abs = fabs(matrix[i][col]);
        if (current_abs > max_abs) {
            max_abs = current_abs;
        }
    }
    return max_abs;
}

// Функция для обмена двух столбцов
void swapColumns(double **matrix, int rows, int col1, int col2) {
    if (col1 == col2) return;

    for (int i = 0; i < rows; i++) {
        double temp = matrix[i][col1];
        matrix[i][col1] = matrix[i][col2];
        matrix[i][col2] = temp;
    }
}

// Функция для проверки правильности сортировки
int isSorted(double *arr, int n) {
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
    double **matrix;
    double *max_abs_values;
    double *original_max_abs; // Для сохранения исходных значений

    // Инициализация генератора случайных чисел
    srand(time(NULL));

    // Ввод размерности массива
    printf("========================================\n");
    printf("Лабораторная работа №11 (Вариант 9)\n");
    printf("Сортировка столбцов по возрастанию\n");
    printf("максимального по модулю элемента\n");
    printf("========================================\n\n");

    printf("Введите количество строк: ");
    scanf("%d", &rows);
    printf("Введите количество столбцов: ");
    scanf("%d", &cols);

    // Проверка корректности ввода
    if (rows <= 0 || cols <= 0) {
        printf("Ошибка: Размеры массива должны быть положительными!\n");
        return 1;
    }

    // Выделение памяти
    matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
    }
    max_abs_values = (double*)malloc(cols * sizeof(double));
    original_max_abs = (double*)malloc(cols * sizeof(double));

    // Заполнение массива случайными вещественными числами
    printf("\nИсходный массив:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Генерация случайных чисел от -50.0 до 50.0
            matrix[i][j] = (double)(rand() % 1000 - 500) / 10.0;
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }

    // Вычисление максимального по модулю элемента для каждого столбца
    printf("\n--- Характеристики столбцов (до сортировки) ---\n");
    for (int j = 0; j < cols; j++) {
        max_abs_values[j] = findMaxAbsInColumn(matrix, rows, j);
        original_max_abs[j] = max_abs_values[j]; // Сохраняем исходные значения
        printf("Столбец %d: max|элемент| = %.2f\n", j + 1, max_abs_values[j]);
    }
    printColumnOrder(max_abs_values, cols, "Порядок столбцов (до сортировки)");

    // Сортировка столбцов методом выбора с подробным выводом
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

            // Обмен значений max_abs
            double temp_abs = max_abs_values[i];
            max_abs_values[i] = max_abs_values[min_index];
            max_abs_values[min_index] = temp_abs;

            // Обмен столбцов в матрице
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

    // Вывод отсортированного массива
    printf("\n========================================\n");
    printf("Результат сортировки:\n");
    printMatrix(matrix, rows, cols);

    // Вывод отсортированных характеристик
    printf("\n--- Отсортированные характеристики ---\n");
    for (int j = 0; j < cols; j++) {
        printf("Столбец %d: max|элемент| = %.2f\n", j + 1, max_abs_values[j]);
    }
    printColumnOrder(max_abs_values, cols, "Порядок столбцов (после сортировки)");

    // Проверка правильности сортировки
    printf("\n--- Проверка ---\n");
    if (isSorted(max_abs_values, cols)) {
        printf("✓ Сортировка выполнена корректно!\n");
        printf("  max|элемент| столбцов расположены по возрастанию.\n");
    } else {
        printf("✗ Ошибка: массив не отсортирован!\n");
    }

    // Контрольная проверка: пересчёт максимальных элементов
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

    // ============================================
    // СРАВНИТЕЛЬНАЯ ТАБЛИЦА (добавленный блок)
    // ============================================
    printf("\n========================================\n");
    printf("СРАВНИТЕЛЬНАЯ ТАБЛИЦА\n");
    printf("========================================\n");
    printf("+----------+-------------------+-------------------+------------+\n");
    printf("| Столбец  | Было max|элемент| | Стало max|элемент| | Изменение |\n");
    printf("+----------+-------------------+-------------------+------------+\n");

    // Находим соответствие между исходными и новыми столбцами
    for (int new_col = 0; new_col < cols; new_col++) {
        // Для каждого нового столбца находим, какой это был исходный столбец
        int original_col = -1;
        double current_max = max_abs_values[new_col];

        // Ищем исходный столбец с таким же max значением
        for (int old_col = 0; old_col < cols; old_col++) {
            if (fabs(original_max_abs[old_col] - current_max) < 0.001) {
                original_col = old_col;
                break;
            }
        }

        double difference = max_abs_values[new_col] - original_max_abs[new_col];

        printf("|    %d     |       %.2f        |       %.2f        |   %+7.2f   |\n",
               new_col + 1,
               original_max_abs[new_col],
               max_abs_values[new_col],
               difference);
    }
    printf("+----------+-------------------+-------------------+------------+\n");

    // Дополнительная информация о перестановках
    printf("\n--- Информация о перестановках ---\n");
    printf("Было (порядок столбцов по номерам): ");
    for (int j = 0; j < cols; j++) {
        printf("%d ", j + 1);
    }
    printf("\nСтало (порядок столбцов по номерам): ");

    // Определяем новый порядок исходных столбцов
    for (int new_col = 0; new_col < cols; new_col++) {
        double current_max = max_abs_values[new_col];
        for (int old_col = 0; old_col < cols; old_col++) {
            if (fabs(original_max_abs[old_col] - current_max) < 0.001) {
                printf("%d ", old_col + 1);
                break;
            }
        }
    }
    printf("\n");

    // Статистика сортировки
    printf("\n--- Статистика ---\n");
    printf("Размер массива: %d x %d\n", rows, cols);
    printf("Диапазон значений: от -50.0 до 50.0\n");
    printf("Метод сортировки: выбором (selection sort)\n");
    printf("Критерий сортировки: max|элемент| столбца по возрастанию\n");

    printf("\n========================================\n");
    printf("Программа успешно завершена!\n");
    printf("========================================\n");

    // Освобождение памяти
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(max_abs_values);
    free(original_max_abs);

    return 0;
}