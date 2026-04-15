#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

string solve(const string& input_str) {
    // Парсим входную строку
    size_t space_pos = input_str.find(' ');
    string A = input_str.substr(0, space_pos);
    string B = input_str.substr(space_pos + 1);

    // Убираем возможные символы новой строки
    if (!A.empty() && A.back() == '\n') A.pop_back();
    if (!B.empty() && B.back() == '\n') B.pop_back();

    // Массив для отметки использованных цифр (0-9)
    bool digit_used[10] = {false};

    // Собираем уникальные цифры из B
    vector<char> unique_digits;
    for (char c : B) {
        int digit = c - '0';
        if (!digit_used[digit]) {
            digit_used[digit] = true;
            unique_digits.push_back(c);
        }
    }

    // Сортируем уникальные цифры по убыванию
    sort(unique_digits.rbegin(), unique_digits.rend());

    // Сбрасываем массив использованных цифр для процесса замены
    fill(digit_used, digit_used + 10, false);

    string result = A;
    int unique_count = unique_digits.size();

    // Идём по цифрам A слева направо (от старшего разряда к младшему)
    for (int i = 0; i < result.length(); i++) {
        // Ищем максимальную доступную цифру из B, которая больше текущей
        int best_index = -1;

        for (int j = 0; j < unique_count; j++) {
            int digit_val = unique_digits[j] - '0';
            if (!digit_used[digit_val] && unique_digits[j] > result[i]) {
                best_index = j;
                break; // Первая подходящая — самая большая, так как массив отсортирован
            }
        }

        // Если нашли подходящую цифру, заменяем
        if (best_index != -1) {
            result[i] = unique_digits[best_index];
            digit_used[unique_digits[best_index] - '0'] = true;
        }
    }

    return result;
}

int main() {
    // Открываем файл для чтения
    ifstream input_file("test1.txt");
    if (!input_file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл test1.txt" << endl;
        return 1;
    }

    // Читаем весь файл в строку
    string input_str;
    string line;
    while (getline(input_file, line)) {
        if (!input_str.empty()) input_str += "\n";
        input_str += line;
    }
    input_file.close();

    // Вызываем solve
    string result = solve(input_str);

    // Записываем результат в файл
    ofstream output_file("result.txt");
    if (!output_file.is_open()) {
        cerr << "Ошибка: не удалось создать файл result.txt" << endl;
        return 1;
    }
    output_file << result << endl;
    output_file.close();

    cout << "Результат записан в файл result.txt" << endl;

    return 0;
}