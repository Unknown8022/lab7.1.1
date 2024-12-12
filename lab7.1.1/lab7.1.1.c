#include <stdio.h>
#include <math.h>

#define STEP 0.1 
#define START -1  
#define END 1     
double ch(double x) 
{
    return (exp(x) + exp(-x)) / 2;
}
// Метод прямокутників
double integral_rectangle(double (*func)(double), double a, double b, double step) 
{
    double sum = 0.0;
    for (double x = a; x < b; x += step) 
    {
        sum += func(x) * step;
    }
    return sum;
}
// Метод трапецій
double integral_trapezoid(double (*func)(double), double a, double b, double step) 
{
    double sum = 0.0;
    for (double x = a; x < b; x += step) 
    {
        sum += (func(x) + func(x + step)) * step / 2;
    }
    return sum;
}
// Метод Сімпсона
double integral_simpson(double (*func)(double), double a, double b, double step) 
{
    double sum = 0.0;
    int n = (b - a) / step;
    if (n % 2 != 0) n++; 
    double h = (b - a) / n;
    for (int i = 0; i <= n; i++)
    {
        double x = a + i * h;
        if (i == 0 || i == n)
            sum += func(x);
        else if (i % 2 == 0)
            sum += 2 * func(x);
        else
            sum += 4 * func(x);
    }
    return sum * h / 3;
}
int main()
{
    FILE* file = fopen("output.txt", "w");
    if (file == NULL) 
    {
        printf("Error open file.\n");
        return 1;
    }
    double x, y, prev_y, next_y;
    double integral_rect, integral_trap, integral_simp;
    fprintf(file, "x ");
    for (x = START; x <= END; x += STEP) 
    {
        fprintf(file, "%.2f ", x);
    }
    fprintf(file, "\n");
    fprintf(file, "y ");
    for (x = START; x <= END; x += STEP) 
    {
        y = ch(x);
        fprintf(file, "%.3f ", y);
    }
    fprintf(file, "\n");
    fprintf(file, "Extrema ");
    for (x = START; x <= END; x += STEP) 
    {
        y = ch(x);
        prev_y = ch(x - STEP);
        next_y = ch(x + STEP);
        if (y > prev_y && y > next_y) 
        {
            fprintf(file, "Max ");
        }
        else if (y < prev_y && y < next_y) 
        {
            fprintf(file, "Min ");
        }
        else {
            fprintf(file, "--- ");
        }
    }
    fprintf(file, "\n");
    integral_rect = integral_rectangle(ch, START, END, STEP);
    integral_trap = integral_trapezoid(ch, START, END, STEP);
    integral_simp = integral_simpson(ch, START, END, STEP);
    fprintf(file, "Integral [%.2f, %.2f]\n", START, END);
    fprintf(file, "Rectangle: %.5f\n", integral_rect);
    fprintf(file, "Trapezoid: %.5f\n", integral_trap);
    fprintf(file, "Simpson: %.5f\n", integral_simp);
    fclose(file);
    printf("Saved in output.txt\n");
    return 0;
}
