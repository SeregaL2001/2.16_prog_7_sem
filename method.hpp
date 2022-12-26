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

#define NEWTON_METHOD_START_VALUE -0.57670298529662

typedef struct Point
{
    double t;
    double x;
    double p;
    struct Point *next;
} Point;

void push_back(Point **last, double t_, double x_, double p_); // добавление элемента в конец списка  
void clear_list(Point **head); // очистка списка 
void print_list(const Point *head); // печать списка в терминале 
void fprint_list(const Point *head, FILE *fp); // печать списка в файл 
