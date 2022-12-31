#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h> // установка бибилиотеки языков для VScode 
#include <string.h>
#include <float.h>

#define EPS 1e-13
#define EPS1 1e-10
#define P_1 0 // p1(1) = 0
#define P_2 0 // p2(1) = 0
#define X_10 1 //
#define DELTA 1e-6

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define NEWTON_METHOD_START_VALUE_x_20 -1.22565282
#define NEWTON_METHOD_START_VALUE_p_10 -0.274772803

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

void matr_plus_mult(double &B1, double &B2, double P2_1, double X1_1, double *D);
void revers_matr(double *M);
double norma_2(double a, double b);
double norma_4(double x1, double x2, double p1, double p2);
double norma_fedorenko(double *J, double F0, double F1);

void RungeKutta(Point **head, double x1_0, double x2_0, double p1_0, double p2_0, double alpha); // метод Рунге Кутты пятого порядка, с формулами построенными Инглэндом стр 31-32 Арушанян 
void find_x2_or_p1(double &B1, double &B2, double alpha); // поиск краевого условия методом пристрелки с помощью Ньютона 
double Integral(Point *head, double alpha); // подсчет интеграла 