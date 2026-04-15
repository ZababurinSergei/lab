#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

long long solve_problem(ifstream& input) {
    int N;
    input >> N;

    long long current_water = 0;
    long long last_time = 0;

    for (int i = 0; i < N; i++) {
        long long T, V;
        input >> T >> V;

        // Уменьшаем воду за прошедшее время
        long long elapsed = T - last_time;
        current_water = max(0LL, current_water - elapsed);

        // Доливаем новую воду
        current_water += V;

        // Обновляем время последнего долива
        last_time = T;
    }

    return current_water;
}

int main() {
    ifstream input_file("test1.txt");
    if (!input_file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл test1.txt" << endl;
        return 1;
    }

    long long result = solve_problem(input_file);
    input_file.close();

    ofstream output_file("result.txt");
    if (!output_file.is_open()) {
        cerr << "Ошибка: не удалось создать файл result.txt" << endl;
        return 1;
    }

    output_file << result << endl;
    output_file.close();

    cout << "Результат: " << result << endl;

    return 0;
}