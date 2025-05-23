/* 2) Структура содержит информацию о книгах: количество страниц (число), название (указатель), 
вложенную структуру – имя автора (строка фиксированной длины) и количество томов. 
Найти книги с заданным названием. 
Удалить книги с заданным количеством страниц.

 Примак Алексей 02.05.*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_AUTHOR_NAME 50
#define MAX_TITLE 100

typedef struct {
    char имя[MAX_AUTHOR_NAME];
    int количество_томов;
} Автор;

typedef struct {
    int количество_страниц;
    char* название;
    Автор автор;
} Книга;

int длина_строки(const char* строка) {
    int длина = 0;
    while (строка[длина] != '\0') {
        длина++;
    }
    return длина;
}

void копировать_строку(char* куда, const char* откуда) {
    while (*откуда) {
        *куда = *откуда;
        куда++;
        откуда++;
    }
    *куда = '\0';
}

int сравнить_строки(const char* строка1, const char* строка2) {
    while (*строка1 && (*строка1 == *строка2)) {
        строка1++;
        строка2++;
    }
    return *(unsigned char*)строка1 - *(unsigned char*)строка2;
}

void очистить_буфер() {
    while (getchar() != '\n');
}

void ввод_книги(Книга* книга) {
    char temp[MAX_TITLE];

    printf("\nВведите название книги: ");
    scanf_s(" %[^\n]", temp, MAX_TITLE);
    очистить_буфер();
    книга->название = malloc(длина_строки(temp) + 1);
    if (книга->название == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    копировать_строку(книга->название, temp);

    printf("Введите количество страниц: ");
    while (scanf_s("%d", &книга->количество_страниц) != 1 || книга->количество_страниц < 1) {
        очистить_буфер();
        printf("Ошибка ввода! Введите корректное количество страниц: ");
    }

    printf("Введите имя автора: ");
    scanf_s(" %[^\n]", книга->автор.имя, MAX_AUTHOR_NAME);
    очистить_буфер();

    printf("Введите количество томов: ");
    while (scanf_s("%d", &книга->автор.количество_томов) != 1 || книга->автор.количество_томов < 1) {
        очистить_буфер();
        printf("Ошибка ввода! Введите корректное количество томов: ");
    }
}

void вывод_книги(const Книга* книга) {
    printf("\nНазвание: %s\n", книга->название);
    printf("Количество страниц: %d\n", книга->количество_страниц);
    printf("Автор: %s\n", книга->автор.имя);
    printf("Количество томов: %d\n", книга->автор.количество_томов);
}

void поиск_книги(Книга* книги, int количество, const char* название) {
    int найдено = 0;
    for (int i = 0; i < количество; i++) {
        if (сравнить_строки(книги[i].название, название) == 0) {
            printf("\nКнига найдена:");
            вывод_книги(&книги[i]);
            найдено = 1;
        }
    }
    if (!найдено) {
        printf("\nКнига с названием \"%s\" не найдена.\n", название);
    }
}

void удалить_книгу(Книга** книги, int* количество, int страницы) {
    for (int i = 0; i < *количество; i++) {
        if ((*книги)[i].количество_страниц == страницы) {
            free((*книги)[i].название);
            for (int j = i; j < *количество - 1; j++) {
                (*книги)[j] = (*книги)[j + 1];
            }
            (*количество)--;

            Книга* новые_книги = realloc(*книги, (*количество) * sizeof(Книга));
            if (новые_книги == NULL && *количество > 0) {
                printf("\nОшибка выделения памяти при удалении книги!\n");
                exit(1);
            }
            *книги = новые_книги;

            printf("\nКнига с %d страницами удалена.\n", страницы);
            return;
        }
    }
    printf("\nКнига с %d страницами не найдена.\n", страницы);
}

void показать_меню() {
    printf("\nМеню:\n");
    printf("1. Добавить книгу\n");
    printf("2. Просмотреть все книги\n");
    printf("3. Найти книгу по названию\n");
    printf("4. Удалить книгу по количеству страниц\n");
    printf("5. Выход\n");
}

int main() {
    setlocale(LC_ALL, "rus");

    int количество_книг = 0;
    Книга* книги = NULL;
    int выбор;

    while (1) {
        показать_меню();
        printf("\nВыберите действие: ");
        scanf_s("%d", &выбор);
        очистить_буфер();

        if (выбор == 5) break;

        switch (выбор) {
        case 1: {
            Книга* новые_книги = realloc(книги, (количество_книг + 1) * sizeof(Книга));
            if (новые_книги == NULL) {
                printf("\nОшибка выделения памяти!\n");
                exit(1);
            }
            книги = новые_книги;
            ввод_книги(&книги[количество_книг]);
            количество_книг++;
            break;
        }
        case 2:
            if (количество_книг == 0) {
                printf("\nСписок книг пуст.\n");
            }
            else {
                for (int i = 0; i < количество_книг; i++) {
                    вывод_книги(&книги[i]);
                }
            }
            break;
        case 3: {
            char название[MAX_TITLE];
            printf("\nВведите название книги: ");
            scanf_s(" %[^\n]", название, MAX_TITLE);
            очистить_буфер();
            поиск_книги(книги, количество_книг, название);
            break;
        }
        case 4: {
            int страницы;
            printf("\nВведите количество страниц: ");
            while (scanf_s("%d", &страницы) != 1 || страницы < 1) {
                очистить_буфер();
                printf("Ошибка ввода! Введите корректное количество страниц: ");
            }
            удалить_книгу(&книги, &количество_книг, страницы);
            break;
        }
        default:
            printf("\nНеверный выбор. Попробуйте снова.\n");
        }
    }

    for (int i = 0; i < количество_книг; i++) {
        free(книги[i].название);
    }
    free(книги);

    printf("\nПрограмма завершена.\n");
    return 0;
}
