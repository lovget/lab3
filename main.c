/* 1) Определить, является ли число чётным, не выполняя деления и не используя
 операцию взятия остатка от деления.
 Примак Алексей 01.05.*/
#include <stdio.h>
#include <locale.h>

typedef struct {
    unsigned is_even : 1; 
} Number;

int main() {
    setlocale(LC_ALL, "rus");

    int value;
    char extra_char;
    int input_result;

    do {
        printf("Введите целое число: ");
        input_result = scanf_s("%d", &value);

        extra_char = getchar();
        if (input_result == 1 && extra_char == '\n') {
            break;
        }
        else {
            printf("Ошибка ввода! Введите только одно целое число.\n");

            while (extra_char != '\n' && extra_char != EOF) {
                extra_char = getchar();
            }
        }
    } while (1);

    Number number = { .is_even = (value & 1) == 0 }; 

    if (number.is_even) {
        printf("Число %d является четным.\n", value);
    }
    else {
        printf("Число %d является нечетным.\n", value);
    }

    return 0;
}
