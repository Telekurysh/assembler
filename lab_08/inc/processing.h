#ifndef LAB_09_PROCESSING_H
#define LAB_09_PROCESSING_H

#include <stdio.h>
#include <time.h>

#define COUNT 10000

/* 32bit - float */
float sum_32_bit_nums(float a, float b);
float mul_32_bit_nums(float a, float b);

float asm_sum_32_bit_nums(float a, float b);
float asm_mul_32_bit_nums(float a, float b);

void print_32_bit_result();
void asm_print_32_bit_result();

/* 64bit - double */
double sum_64_bit_nums(double a, double b);
double mul_64_bit_nums(double a, double b);

double asm_sum_64_bit_nums(double a, double b);
double asm_mul_64_bit_nums(double a, double b);

void print_64_bit_result();
void asm_print_64_bit_result();

void sin_compare();

#endif //LAB_09__PROCESSING_H
