#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "rus");

    int число;
    char лишний_символ;
    int результат;

    do {
        printf("Введите целое число: ");
        результат = scanf_s("%d", &число);

        лишний_символ = getchar();
        if (результат == 1 && лишний_символ == '\n') {
            break;
        } else {
            printf("Ошибка ввода! Введите только одно целое число.\n");

            while (лишний_символ != '\n' && лишний_символ != EOF) {
                лишний_символ = getchar();
            }
        }
    } while (1);

    if ((число & 1) == 0) {
        printf("Число %d является четным.\n", число);
    } else {
        printf("Число %d является нечетным.\n", число);
    }

    return 0;
}
