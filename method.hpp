#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h> // установка бибилиотеки языков для VScode 
#include <string.h>
#include <float.h>

#define EPS 1e-13
#define EPS1 1e-10
#define X0 1 // x(0) = 1 
#define P_1 0 // p(1) = 0

#define PI 3.14159265358979323846

#define NEWTON_METHOD_START_VALUE_x_20 -1.225652821
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

void push_back(Point **last, double t_, double x_, double p_); // добавление элемента в конец списка  
void clear_list(Point **head); // очистка списка 
void print_list(const Point *head); // печать списка в терминале 
void fprint_list(const Point *head, FILE *fp); // печать списка в файл 

double f1(double x1, double x2, double p1, double p2, double t, double alpha); // правая часть первого уравнения краевой задачи 
double f2(double x1, double x2, double p1, double p2, double t, double alpha); // правая часть 2ого уравнения краевой задачи 
double f3(double x1, double x2, double p1, double p2, double t, double alpha); // правая часть 3его уравнения краевой задачи 
double f4(double x1, double x2, double p1, double p2, double t, double alpha); // правая часть 4ого уравнения краевой задачи 

double RungeKutta(Point** head, double x1_0, double x2_0, double p1_0, double p2_0, double alpha); // метод Рунге Кутты пятого порядка, с формулами построенными Инглэндом стр 31-32 Арушанян 
double find_p0(double x0, double alpha); // поиск краевого условия методом пристрелки с помощью Ньютона 
double Integral(Point* head); // подсчет интеграла 