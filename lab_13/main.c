#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* solve(const char* input_str) {
    // Копируем входную строку, так как strtok её изменяет
    char* input_copy = strdup(input_str);
    if (!input_copy) return NULL;

    // Читаем N
    char* token = strtok(input_copy, " \n");
    int N = atoi(token);

    // Массивы для хранения времени и объёмов
    long long* T = (long long*)malloc(N * sizeof(long long));
    long long* V = (long long*)malloc(N * sizeof(long long));

    // Читаем пары T_i, V_i
    for (int i = 0; i < N; i++) {
        token = strtok(NULL, " \n");
        T[i] = atoll(token);
        token = strtok(NULL, " \n");
        V[i] = atoll(token);
    }

    // Моделируем процесс
    long long water = 0;
    long long last_time = 0;

    for (int i = 0; i < N; i++) {
        // Утекание воды с момента последнего долива до текущего
        long long dt = T[i] - last_time;
        water -= dt;
        if (water < 0) water = 0;

        // Долив воды
        water += V[i];
        last_time = T[i];
    }

    // Формируем строку-ответ
    char* result = (char*)malloc(64 * sizeof(char));
    sprintf(result, "%lld", water);

    // Освобождаем память
    free(T);
    free(V);
    free(input_copy);

    return result;
}

int main() {
    // Открываем файл для чтения
    FILE* input_file = fopen("test1.txt", "r");
    if (!input_file) {
        printf("Ошибка: не удалось открыть файл test1.txt\n");
        return 1;
    }

    // Читаем весь файл в строку
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

    if (total_len == 0) {
        free(input_str);
        return 1;
    }

    // Вызываем solve
    char* result = solve(input_str);

    // Открываем файл для записи результата
    FILE* output_file = fopen("result.txt", "w");
    if (!output_file) {
        printf("Ошибка: не удалось создать файл result.txt\n");
        free(result);
        free(input_str);
        return 1;
    }

    // Записываем результат в файл
    if (result) {
        fprintf(output_file, "%s\n", result);
        free(result);
    }

    fclose(output_file);
    free(input_str);

    printf("Результат записан в файл result.txt\n");

    return 0;
}