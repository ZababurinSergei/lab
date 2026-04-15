#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* solve(const char* input_str) {
    char* input_copy = strdup(input_str);
    if (!input_copy) return NULL;

    char* A = strtok(input_copy, " \n");
    char* B = strtok(NULL, " \n");

    int lenA = strlen(A);
    int lenB = strlen(B);

    char* result = strdup(A);

    // Массив для отметки использованных ЦИФР (значений) из B
    int digit_used[10] = {0};

    // Собираем уникальные цифры из B
    char unique_digits[10];
    int unique_count = 0;

    for (int i = 0; i < lenB; i++) {
        int digit = B[i] - '0';
        if (!digit_used[digit]) {
            digit_used[digit] = 1;
            unique_digits[unique_count++] = B[i];
        }
    }

    // Сортируем уникальные цифры по убыванию
    for (int i = 0; i < unique_count - 1; i++) {
        for (int j = i + 1; j < unique_count; j++) {
            if (unique_digits[i] < unique_digits[j]) {
                char temp = unique_digits[i];
                unique_digits[i] = unique_digits[j];
                unique_digits[j] = temp;
            }
        }
    }

    // Сбрасываем массив использованных цифр
    for (int i = 0; i < 10; i++) {
        digit_used[i] = 0;
    }

    // Идём по цифрам A слева направо (от старшего разряда к младшему)
    for (int i = 0; i < lenA; i++) {
        // Ищем максимальную доступную цифру из B, которая больше текущей
        int best_digit = -1;

        for (int j = 0; j < unique_count; j++) {
            if (!digit_used[unique_digits[j] - '0'] &&
                unique_digits[j] > result[i]) {
                // Берём самую большую подходящую цифру (массив уже отсортирован по убыванию)
                best_digit = j;
                break;
            }
        }

        // Если нашли подходящую цифру, заменяем
        if (best_digit != -1) {
            result[i] = unique_digits[best_digit];
            digit_used[unique_digits[best_digit] - '0'] = 1; // Помечаем как использованную
        }
    }

    free(input_copy);

    return result;
}

int main() {
    FILE* input_file = fopen("test1.txt", "r");
    if (!input_file) {
        printf("Ошибка: не удалось открыть файл test1.txt\n");
        return 1;
    }

    char buffer[10000];
    char* input_str = NULL;
    size_t total_len = 0;

    while (fgets(buffer, sizeof(buffer), input_file)) {
        size_t len = strlen(buffer);
        char* new_input = realloc(input_str, total_len + len + 1);
        if (!new_input) {
            free(input_str);
            fclose(input_file);
            return 1;
        }
        input_str = new_input;
        strcpy(input_str + total_len, buffer);
        total_len += len;
    }

    fclose(input_file);

    if (total_len > 0 && input_str[total_len - 1] == '\n') {
        input_str[total_len - 1] = '\0';
    }

    char* result = solve(input_str);

    FILE* output_file = fopen("result.txt", "w");
    if (output_file && result) {
        fprintf(output_file, "%s\n", result);
        fclose(output_file);
    }

    free(result);
    free(input_str);

    printf("Результат записан в файл result.txt\n");

    return 0;
}