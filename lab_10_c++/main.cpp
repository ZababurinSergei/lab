#include <cstdio>
#include <cstring>

int main() {
    char str[1000], result[1000] = "";
    char ch;
    int i, j = 0;
    int word_start;

    printf("Введите строку: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; // убираем символ новой строки

    printf("Введите символ: ");
    scanf("%c", &ch);

    int len = strlen(str);
    i = 0;
    while (i < len) {
        while (i < len && str[i] == ' ') {
            result[j++] = ' ';
            i++;
        }

        if (i >= len) break;

        word_start = i;
        while (i < len && str[i] != ' ') i++;

        if (str[word_start] != ch) {
            for (int k = word_start; k < i; k++) {
                result[j++] = str[k];
            }
        }
    }
    result[j] = '\0';

    char final_result[1000] = "";
    int start = 0;
    while (result[start] == ' ') start++;
    if (start > 0) {
        strcpy(final_result, result + start);
    } else {
        strcpy(final_result, result);
    }

    printf("\nСтрока после удаления слов, начинающихся с '%c':\n%s\n", ch, final_result);

    printf("\nСлова с указанием длины:\n");
    i = 0;
    len = strlen(final_result);
    while (i < len) {
        while (i < len && final_result[i] == ' ') i++;

        if (i >= len) break;

        word_start = i;
        while (i < len && final_result[i] != ' ') i++;

        const int word_len = i - word_start;

        printf("%d %.*s ", word_len, word_len, final_result + word_start);
    }
    printf("\n");

    return 0;
}