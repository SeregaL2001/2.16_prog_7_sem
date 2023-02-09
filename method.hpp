#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h> // установка бибилиотеки языков для VScode 
#include <string.h>
#include <float.h>

#define EPS 1e-13
#define EPS1 1e-10
#define P11 0 // p1(1) = 0
#define X21 0 // x2(1) = 0
#define DELTA 1e-6

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define NEWTON_METHOD_START_B1 -0.274772803
#define NEWTON_METHOD_START_B2 -1.22565282

typedef struct Point
{
    double t;
    double x1;
    double x2;
    double p1;
    double p2;
    struct Point *next;
} Point;

typedef struct Koef
{
    double x1;
    double x2;
    double p1;
    double p2;
} Koef;

void push_back(Point **last, double t_, double x_, double p_); // добавление элемента в конец списка  
void clear_list(Point **head); // очистка списка 
void print_list(const Point *head); // печать списка в терминале 
void fprint_list(const Point *head, FILE *fp); // печать списка в файл 

void revers_matrix(double *M);
double norma_fedorenko(double *J, double F0, double F1);

Koef F(double t, Koef Y, double alpha); // система ОДУ для задачи Коши 
Koef mult_koef(Koef Y, double b, Koef X, double a); 
Koef h_koef(double h, Koef Y);
double norma_koef(Koef Y);

void RungeKutta(Point **head, double B1, double B2, double &P2_0, double &X1_0, double &X2_1, double &P1_1, double alpha); // метод Рунге Кутты пятого порядка, с формулами построенными Инглэндом стр 31-32 Арушанян
void RungeKutta_sup(Point** head, double B1, double B2, double alpha, double &X2_1, double &P1_1); // вспомогательный РК для метода Ньютона 
void calc_p10_n_x20(double &B1_return, double &B2_return, double X2_1, double P1_1, double alpha); // поиск краевого условия методом пристрелки с помощью Ньютона
double Integral(Point *head); // подсчет интеграла 