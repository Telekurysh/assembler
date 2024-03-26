#include <stdio.h>
#include <time.h>

#define REPEATS_COUNT 1e7

float c_scalar_prod(const float *a, const float *b, size_t n)
{
    float res = 0;

    for (size_t i = 0; i < n; ++i)
        res += a[i] * b[i];

    return res;
}

float sse_scalar_prod(float *src_a, float *src_b, size_t n)
{
    float tmp, res = 0;
    __float128 *a = (__float128 *)src_a;
    __float128 *b = (__float128 *)src_b;

    for (size_t i = 0; i < n; i += sizeof(__float128) / sizeof(float), a++, b++)
{       
        // "movaps xmm0, %1\n\t" - загрузить первые 128 бит (4 числа типа float) из массива src_a в регистр xmm0.
        // "movaps xmm1, %2\n\t" - загрузить первые 128 бит (4 числа типа float) из массива src_b в регистр xmm1.
        // "mulps xmm0, xmm1\n\t" - перемножить содержимое xmm0 и xmm1 и сохранить результат в xmm0.
        // "haddps xmm0, xmm0\n\t" - выполнить горизонтальное сложение для первых двух элементов xmm0, сохранить результат в первый элемент xmm0.
        // "haddps xmm0, xmm0\n\t" - выполнить горизонтальное сложение для последних двух элементов xmm0, сохранить результат в первый элемент xmm0.
        // "movss %0, xmm0\n\t" - сохранить первый элемент xmm0 (содержащий сумму квадратов четырех чисел) в переменную tmp.
        __asm__(
            "movaps xmm0, %1\n\t" // перемещаем 128 битные числа в регистр
            "movaps xmm1, %2\n\t"
            "mulps xmm0, xmm1\n\t" //перемножаем икладём в mulps
            "haddps xmm0, xmm0\n\t" 
            "haddps xmm0, xmm0\n\t" // горизонтальное сложение упакованных float
            "movss %0, xmm0\n\t"
            : "=m"(tmp)
            : "m"(*a), "m"(*b)
            : "xmm0", "xmm1"
        )
        res += tmp;
    }

    return res;
}

int main(void)
{
    float a = 1e3;
    float b = 1e-3;
    float c = 0.0;
    float d = 5.0;

    const size_t n = 16;
    float vec_a[16] = {a, b, c, d, a, b, d, c, b, a, c, d, a, b, c, d};
    float vec_b[16] = {d, c, b, a, d, a, b, d, c, b, a, c, d, a, b, b};

    clock_t start = clock();
    printf("The time of the scalar product of 16-dimensional vectors (%zu times):\n", (size_t)REPEATS_COUNT);
    for (size_t i = 0; i < REPEATS_COUNT; i++)
    {
        c_scalar_prod(vec_a, vec_b, n);
    }
    clock_t time_c = clock() - start;

    printf("C:   %zu ms\n", time_c);

    start = clock();
    for (size_t i = 0; i < REPEATS_COUNT; i++)
    {
        sse_scalar_prod(vec_a, vec_b, n);
    }
    clock_t time_asm = clock() - start;
    printf("Asm: %zu ms\n", time_asm);

    if (sse_scalar_prod(vec_a, vec_b, n) == c_scalar_prod(vec_a, vec_b, n))
        printf("\nThe results are the same.\n");
    else
        printf("\nThe results are different.\n");

    printf("\nAssembler implementation is %lf times faster than C implementation.\n", (double)time_c / time_asm);

    return 0;
}
