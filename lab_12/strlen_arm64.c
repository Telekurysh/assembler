#include <stdio.h>

int my_strlen(const char *str)
{
    int len;
    asm volatile (
        "mov x0, %[str]\n"      // Помещаем адрес на строку в регистр X0
        "mov x1, #0\n"          // Обнуляем регистр X1 (счетчик длины строки)

    "next:\n"
        "ldrb w2, [x0], #1\n"   // Загружаем байт из строки в W2 и автоматически увеличиваем X0
        "cbz x2, end\n"        // Проверяем, является ли байт нулевым (конец строки)
        "add x1, x1, #1\n"     // Увеличиваем счетчик
        "b next\n"             // Переходим к следующему байту строки

    "end:\n"
        "mov %[len], x1\n"     // Переносим значение счетчика в переменную len
        : [len] "=r" (len)     // Выходное значение len
        : [str] "r" (str)      // Входное значение str
        : "x0", "x1", "w2", "w4"     // Регистры, используемые в инлайн-ассемблере
    );

    return len;
}

int main()
{
    int len;
    char temp[32] = "\0";
    char messg[] = "Hello, world!";

    len = my_strlen(messg);
    printf("String length = %d\n", len);

    return 0;
}
