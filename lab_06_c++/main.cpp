#include <cstdio>
#include <cstdlib>
#include <cmath>

int main() {
    int n;
    int *arr;
    int neg_count = 0;

    printf("Введите количество элементов массива: ");
    scanf("%d", &n);

    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    printf("Введите %d целых чисел:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Find minimum absolute value element
    int min_abs = abs(arr[0]);
    int min_abs_idx = 0;

    for (int i = 1; i < n; i++) {
        if (abs(arr[i]) < min_abs) {
            min_abs = abs(arr[i]);
            min_abs_idx = i;
        }
    }

    // Count negative elements
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) neg_count++;
    }

    printf("\nКоличество отрицательных элементов: %d\n", neg_count);

    // Display minimum absolute value element before replacement
    printf("Минимальный по модулю элемент: %d (индекс %d)\n", arr[min_abs_idx], min_abs_idx);

    // Replace sign of minimum absolute value element
    arr[min_abs_idx] = -arr[min_abs_idx];

    // Display the changed element
    printf("Элемент после замены знака: %d\n", arr[min_abs_idx]);

    printf("Массив после замены знака:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}