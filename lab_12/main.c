#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>   // для getcwd()

#define MAX_PATH 500

int main() {
    setlocale(LC_ALL, "Russian");

    FILE *inputFile = NULL;
    FILE *outputFile = NULL;
    char inputFilename[MAX_PATH];
    char outputFilename[MAX_PATH];
    char currentDir[MAX_PATH];
    int ch;
    int found = 0;

    printf("=============================================\n");
    printf("  Программа: удаление символов кроме латинских\n");
    printf("  Вариант 9\n");
    printf("=============================================\n\n");

    // Получаем и показываем текущую рабочую директорию
    if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
        printf("Текущая рабочая директория: %s\n\n", currentDir);
    } else {
        printf("Ошибка получения текущей директории\n\n");
    }

    // Ввод имени файла
    printf("Введите имя входного файла: ");
    fgets(inputFilename, MAX_PATH, stdin);
    inputFilename[strcspn(inputFilename, "\n")] = '\0';

    printf("Введите имя выходного файла: ");
    fgets(outputFilename, MAX_PATH, stdin);
    outputFilename[strcspn(outputFilename, "\n")] = '\0';

    printf("\nПоиск файла '%s'...\n\n", inputFilename);

    // Пробуем открыть файл в текущей директории
    printf("Попытка 1: %s\n", inputFilename);
    inputFile = fopen(inputFilename, "r");
    if (inputFile != NULL) {
        printf("✓ Файл найден в текущей директории!\n\n");
        found = 1;
    } else {
        printf("✗ Файл не найден\n");

        // Пробуем в родительской директории
        char parentPath[MAX_PATH];
        snprintf(parentPath, sizeof(parentPath), "../%s", inputFilename);
        printf("Попытка 2: %s\n", parentPath);
        inputFile = fopen(parentPath, "r");
        if (inputFile != NULL) {
            printf("✓ Файл найден в родительской директории (корень проекта)!\n\n");
            found = 1;
        } else {
            printf("✗ Файл не найден\n");
        }
    }

    // Если файл не найден
    if (!found) {
        printf("\nОШИБКА: Файл '%s' не найден!\n", inputFilename);
        printf("\nРекомендации:\n");
        printf("1. Создайте файл в текущей директории:\n");
        printf("   cd \"%s\"\n", currentDir);
        printf("   echo \"Hello World! Привет мир!\" > %s\n", inputFilename);
        printf("\n2. Или скопируйте файл из корня проекта:\n");
        printf("   cp ../%s .\n", inputFilename);
        printf("\n3. Или укажите полный путь к файлу при вводе\n");
        return 1;
    }

    // Открываем выходной файл
    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Ошибка открытия выходного файла");
        fclose(inputFile);
        return 1;
    }

    // Обработка файла
    printf("=============================================\n");
    printf("  РЕЗУЛЬТАТ (только латинские буквы)\n");
    printf("=============================================\n\n");

    int totalChars = 0;
    int latinChars = 0;

    while ((ch = fgetc(inputFile)) != EOF) {
        totalChars++;

        // Сохраняем только латинские буквы
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            putchar(ch);
            fputc(ch, outputFile);
            latinChars++;
        }
        // Сохраняем перевод строки для читаемости
        else if (ch == '\n') {
            putchar('\n');
            fputc('\n', outputFile);
        }
    }

    printf("\n\n=============================================\n");
    printf("  СТАТИСТИКА\n");
    printf("=============================================\n");
    printf("Всего символов:  %d\n", totalChars);
    printf("Латинских букв:  %d\n", latinChars);
    printf("Удалено:         %d\n", totalChars - latinChars);
    printf("\nРезультат сохранен в: %s\n", outputFilename);

    fclose(inputFile);
    fclose(outputFile);

    printf("\nПрограмма завершена!\n");

    return 0;
}