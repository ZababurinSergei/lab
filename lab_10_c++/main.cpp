#include <cstdio>
#include <cstring>
#include <cwchar>
#include <clocale>
#include <cwctype>

// Функция проверки, является ли символ буквой/цифрой (частью слова)
bool is_word_char(wchar_t c) {
    return iswalnum(c) || c == L'-' || c == L'\''; // буквы, цифры, дефис, апостроф
}

// Функция проверки, является ли символ знаком препинания
bool is_punctuation(wchar_t c) {
    return c == L'.' || c == L',' || c == L'!' || c == L'?' ||
           c == L';' || c == L':' || c == L'\"' || c == L')' ||
           c == L'(' || c == L']' || c == L'[' || c == L'}';
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    wchar_t str[1000], result[1000] = L"";
    wchar_t ch;
    int i, j = 0;
    int word_start, word_end;

    wprintf(L"Введите строку: ");
    fgetws(str, sizeof(str)/sizeof(wchar_t), stdin);
    size_t len = wcslen(str);
    if (len > 0 && str[len-1] == L'\n') {
        str[len-1] = L'\0';
    }

    wprintf(L"Введите символ: ");
    wscanf(L"%lc", &ch);

    len = wcslen(str);
    i = 0;

    while (i < len) {
        // Копируем пробелы
        while (i < len && str[i] == L' ') {
            result[j++] = L' ';
            i++;
        }

        if (i >= len) break;

        // Начало слова (первая буква/цифра)
        word_start = i;

        // Находим конец слова (до пробела или до конца строки)
        while (i < len && str[i] != L' ') {
            i++;
        }
        word_end = i;

        // Проверяем первую букву слова (пропуская знаки препинания в начале)
        int first_letter_pos = word_start;
        while (first_letter_pos < word_end && is_punctuation(str[first_letter_pos])) {
            first_letter_pos++;
        }

        // Если слово начинается с заданного символа
        if (first_letter_pos < word_end && str[first_letter_pos] == ch) {
            // Удаляем слово, но сохраняем знаки препинания в начале и в конце

            // Копируем знаки препинания в начале (до буквы)
            for (int k = word_start; k < first_letter_pos; k++) {
                result[j++] = str[k];
            }

            // Пропускаем само слово (буквы)
            // Ищем конец слова (последнюю букву)
            int last_letter_pos = word_end - 1;
            while (last_letter_pos >= first_letter_pos && is_punctuation(str[last_letter_pos])) {
                last_letter_pos--;
            }

            // Копируем знаки препинания в конце (после букв)
            int punct_pos = last_letter_pos + 1;
            while (punct_pos < word_end && is_punctuation(str[punct_pos])) {
                result[j++] = str[punct_pos];
                punct_pos++;
            }
        } else {
            // Сохраняем слово целиком
            for (int k = word_start; k < word_end; k++) {
                result[j++] = str[k];
            }
        }
    }
    result[j] = L'\0';

    // Удаляем лишние пробелы в начале и в конце
    wchar_t final_result[1000] = L"";
    int start = 0;
    while (result[start] == L' ') start++;

    int end = wcslen(result) - 1;
    while (end > start && result[end] == L' ') end--;

    if (start <= end) {
        wcsncpy(final_result, result + start, end - start + 1);
        final_result[end - start + 1] = L'\0';
    }

    wprintf(L"\nСтрока после удаления слов, начинающихся с '%lc':\n%ls\n", ch, final_result);

    wprintf(L"\nИсходная строка (слова с указанием длины):\n");
    i = 0;
    len = wcslen(str);
    while (i < len) {
        // Пропускаем пробелы
        while (i < len && str[i] == L' ') {
            i++;
        }

        if (i >= len) break;

        word_start = i;
        // Находим конец слова (до пробела)
        while (i < len && str[i] != L' ') {
            i++;
        }
        word_end = i;

        // Подсчитываем только буквы и цифры (без знаков препинания)
        int letter_count = 0;
        for (int k = word_start; k < word_end; k++) {
            if (is_word_char(str[k]) && !is_punctuation(str[k])) {
                letter_count++;
            }
        }

        // Выводим слово целиком и его длину (количество букв)
        wprintf(L"%d %.*ls ", letter_count, word_end - word_start, str + word_start);
    }
    wprintf(L"\n");

    return 0;
}