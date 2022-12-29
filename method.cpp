#include "method.hpp"

// добавление элемента в конец списка  
void push_back(Point **last, double t_, double x1_,  double x2_, double p1_, double p2_) {
    Point *pt = (Point*)malloc(sizeof(Point));
    pt->t = t_;
    pt->x1 = x1_;
    pt->x2 = x2_;
    pt->p1 = p1_;
    pt->p2 = p2_;
    pt->next = NULL;
    (*last)->next = pt;
    (*last) = pt;
}

// очистка полученного списка  
void clear_list(Point **head) {
    Point* prev = NULL;
    while ((*head)->next) {
        prev = (*head);
        (*head) = (*head)->next;
        free(prev);
    }
    free(*head);
}

// печать списка в терминале 
// void print_list(const Point *head) {
//     while (head) {
//         printf("%le %le %le\n", head->t, head->x1, head->x2, head->p1, head->p2);
//         head = head->next;
//     }
// }

// печать списка в файл 
// void fprint_list(const Point *head, FILE *fp) {
//     while (head) {
//         fprintf(fp, "%lf %lf %lf\n", head->t, head->x1, head->x2, head->p1, head->p2);
//         head = head->next;
//     }
// }

// x_1' = x_2
double f1(double t, double x1, double x2, double p1, double p2, double alpha)
{
    return x2;
}

// x_2' = p_2 - 2x_1*sin(...)
double f2(double t, double x1, double x2, double p1, double p2, double alpha)
{
    double g = 4 + alpha * t * t;
    return p2 - 2 * x1 * sin(PI/g);
}

// p_1' = x_1 + 2 * p_2 * sin(....);
double f3(double t, double x1, double x2, double p1, double p2, double alpha)
{
    double g =  4 + alpha * t * t;
    return x1 + 2 * p2 * sin(PI/g);
}

// p_2' = -p_1
double f4(double t, double x1, double x2, double p1, double p2, double alpha)
{
    return (-1) * p1;
}

double RungeKutta(Point** head, double x1_0, double x2_0, double p1_0, double p2_0, double alpha, int check)
{
    double h = 1;
    double next_t, next_x1, next_x2, next_p1, next_p2;
    double next_t_2, next_x1_2, next_x2_2, next_p1_2, next_p2_2;
    double k1[4], k2[4], k3[4], k4[4], k5[4], k6[4];

    Point *pt = (Point*)malloc(sizeof(Point));
    Point *last;

    pt->t = 0;
    pt->x1 = x1_0;
    pt->x2 = x2_0;
    pt->p1 = p1_0;
    pt->p2 = p2_0;
    pt->next = NULL;
    (*head) = pt;
    last = pt;

    while (1 - last->t > EPS)
    {
        if (h > 1 - last->t)
            h = 1 - last->t;
        do
        {
            // с шагом h ---------------------------------------------------------------------------------------------------------------------
            k1[0] = h * f1(last->t, last->x1, last->x2, last->p1, last->p2, alpha);
            k1[1] = h * f2(last->t, last->x1, last->x2, last->p1, last->p2, alpha);
            k1[2] = h * f3(last->t, last->x1, last->x2, last->p1, last->p2, alpha);
            k1[3] = h * f4(last->t, last->x1, last->x2, last->p1, last->p2, alpha);

            k2[0] = h * f1(last->t + (1. / 2) * h, last->x1 + (1. / 2) * k1[0], last->x2 + (1. / 2) * k1[1], last->p1 + (1. / 2) * k1[2], last->p1 + (1. / 2) * k1[3], alpha);
            k2[1] = h * f2(last->t + (1. / 2) * h, last->x1 + (1. / 2) * k1[0], last->x2 + (1. / 2) * k1[1], last->p1 + (1. / 2) * k1[2], last->p1 + (1. / 2) * k1[3], alpha);
            k2[2] = h * f3(last->t + (1. / 2) * h, last->x1 + (1. / 2) * k1[0], last->x2 + (1. / 2) * k1[1], last->p1 + (1. / 2) * k1[2], last->p1 + (1. / 2) * k1[3], alpha);
            k2[3] = h * f4(last->t + (1. / 2) * h, last->x1 + (1. / 2) * k1[0], last->x2 + (1. / 2) * k1[1], last->p1 + (1. / 2) * k1[2], last->p1 + (1. / 2) * k1[3], alpha);

            k3[0] = h * f1(last->t + (1. / 2) * h, last->x1 + (1. / 4) * (k1[0] + k2[0]), last->x1 + (1. / 4) * (k1[1] + k2[1]), last->p1 + (1. / 4) * (k1[2] + k2[2]), last->p2 + (1. / 4) * (k1[3] + k2[3]), alpha);
            k3[1] = h * f2(last->t + (1. / 2) * h, last->x1 + (1. / 4) * (k1[0] + k2[0]), last->x1 + (1. / 4) * (k1[1] + k2[1]), last->p1 + (1. / 4) * (k1[2] + k2[2]), last->p2 + (1. / 4) * (k1[3] + k2[3]), alpha);
            k3[2] = h * f3(last->t + (1. / 2) * h, last->x1 + (1. / 4) * (k1[0] + k2[0]), last->x1 + (1. / 4) * (k1[1] + k2[1]), last->p1 + (1. / 4) * (k1[2] + k2[2]), last->p2 + (1. / 4) * (k1[3] + k2[3]), alpha);
            k3[3] = h * f4(last->t + (1. / 2) * h, last->x1 + (1. / 4) * (k1[0] + k2[0]), last->x1 + (1. / 4) * (k1[1] + k2[1]), last->p1 + (1. / 4) * (k1[2] + k2[2]), last->p2 + (1. / 4) * (k1[3] + k2[3]), alpha);

            k4[0] = h * f1(last->t + h, last->x1 + (-k2[0] + 2 * k3[0]), last->x2 + (-k2[1] + 2 * k3[1]), last->p1 + (-k2[2] + 2 * k3[2]), last->p2 + (-k2[2] + 2 * k3[3]), alpha);
            k4[1] = h * f2(last->t + h, last->x1 + (-k2[0] + 2 * k3[0]),  last->x2 + (-k2[1] + 2 * k3[1]), last->p1 + (-k2[2] + 2 * k3[2]), last->p2 + (-k2[2] + 2 * k3[3]), alpha);
            k4[2] = h * f3(last->t + h, last->x1 + (-k2[0] + 2 * k3[0]),  last->x2 + (-k2[1] + 2 * k3[1]), last->p1 + (-k2[2] + 2 * k3[2]), last->p2 + (-k2[2] + 2 * k3[3]), alpha);
            k4[3] = h * f4(last->t + h, last->x1 + (-k2[0] + 2 * k3[0]),  last->x2 + (-k2[1] + 2 * k3[1]), last->p1 + (-k2[2] + 2 * k3[2]), last->p2 + (-k2[2] + 2 * k3[3]), alpha);

            k5[0] = h * f1(last->t + (2. / 3) * h, last->x1 + (1. / 27) * (7 * k1[0] + 10 * k2[0] + k4[0]), last->x2 + (1. / 27) * (7 * k1[1] + 10 * k2[1] + k4[1]), last->p1 + (1. / 27) * (7 * k1[2] + 10 * k2[2] + k4[2]), last->p2 + (1. / 27) * (7 * k1[3] + 10 * k2[3] + k4[3]), alpha);
            k5[1] = h * f2(last->t + (2. / 3) * h, last->x1 + (1. / 27) * (7 * k1[0] + 10 * k2[0] + k4[0]), last->x2 + (1. / 27) * (7 * k1[1] + 10 * k2[1] + k4[1]), last->p1 + (1. / 27) * (7 * k1[2] + 10 * k2[2] + k4[2]), last->p2 + (1. / 27) * (7 * k1[3] + 10 * k2[3] + k4[3]), alpha);
            k5[2] = h * f3(last->t + (2. / 3) * h, last->x1 + (1. / 27) * (7 * k1[0] + 10 * k2[0] + k4[0]), last->x2 + (1. / 27) * (7 * k1[1] + 10 * k2[1] + k4[1]), last->p1 + (1. / 27) * (7 * k1[2] + 10 * k2[2] + k4[2]), last->p2 + (1. / 27) * (7 * k1[3] + 10 * k2[3] + k4[3]), alpha);
            k5[3] = h * f4(last->t + (2. / 3) * h, last->x1 + (1. / 27) * (7 * k1[0] + 10 * k2[0] + k4[0]), last->x2 + (1. / 27) * (7 * k1[1] + 10 * k2[1] + k4[1]), last->p1 + (1. / 27) * (7 * k1[2] + 10 * k2[2] + k4[2]), last->p2 + (1. / 27) * (7 * k1[3] + 10 * k2[3] + k4[3]), alpha);

            k6[0] = h * f1(last->t + (1. / 5) * h, last->x1 + (1. / 625) * (28 * k1[0] - 125 * k2[0] + 546 * k3[0] + 54 *k4[0] - 378 * k5[0]), last->x2 + (1. / 625) * (28 * k1[1] - 125 * k2[1] + 546 * k3[1] + 54 *k4[1] - 378 * k5[1]), last->p1 + (1. / 625) * (28 * k1[2] - 125 * k2[2] + 546 * k3[2] + 54 * k4[2] - 378 * k5[2]), last->p2 + (1. / 625) * (28 * k1[3] - 125 * k2[3] + 546 * k3[3] + 54 * k4[3] - 378 * k5[3]), alpha);
            k6[1] = h * f2(last->t + (1. / 5) * h, last->x1 + (1. / 625) * (28 * k1[0] - 125 * k2[0] + 546 * k3[0] + 54 *k4[0] - 378 * k5[0]), last->x2 + (1. / 625) * (28 * k1[1] - 125 * k2[1] + 546 * k3[1] + 54 *k4[1] - 378 * k5[1]), last->p1 + (1. / 625) * (28 * k1[2] - 125 * k2[2] + 546 * k3[2] + 54 * k4[2] - 378 * k5[2]), last->p2 + (1. / 625) * (28 * k1[3] - 125 * k2[3] + 546 * k3[3] + 54 * k4[3] - 378 * k5[3]), alpha);
            k6[2] = h * f2(last->t + (1. / 5) * h, last->x1 + (1. / 625) * (28 * k1[0] - 125 * k2[0] + 546 * k3[0] + 54 *k4[0] - 378 * k5[0]), last->x2 + (1. / 625) * (28 * k1[1] - 125 * k2[1] + 546 * k3[1] + 54 *k4[1] - 378 * k5[1]), last->p1 + (1. / 625) * (28 * k1[2] - 125 * k2[2] + 546 * k3[2] + 54 * k4[2] - 378 * k5[2]), last->p2 + (1. / 625) * (28 * k1[3] - 125 * k2[3] + 546 * k3[3] + 54 * k4[3] - 378 * k5[3]), alpha);
            k6[3] = h * f2(last->t + (1. / 5) * h, last->x1 + (1. / 625) * (28 * k1[0] - 125 * k2[0] + 546 * k3[0] + 54 *k4[0] - 378 * k5[0]), last->x2 + (1. / 625) * (28 * k1[1] - 125 * k2[1] + 546 * k3[1] + 54 *k4[1] - 378 * k5[1]), last->p1 + (1. / 625) * (28 * k1[2] - 125 * k2[2] + 546 * k3[2] + 54 * k4[2] - 378 * k5[2]), last->p2 + (1. / 625) * (28 * k1[3] - 125 * k2[3] + 546 * k3[3] + 54 * k4[3] - 378 * k5[3]), alpha);
            // значение в точках с шагом h
            next_t = last->t + h;
            next_x1 = last->x1 + k1[0] / 24 + 5 * k4[0] / 48 + 27 * k5[0] / 56 + 125 * k6[0] / 336; // формула (87)
            next_x2 = last->x2 + k1[1] / 24 + 5 * k4[1] / 48 + 27 * k5[1] / 56 + 125 * k6[1] / 336;
            next_p1 = last->p1 + k1[2] / 24 + 5 * k4[2] / 48 + 27 * k5[2] / 56 + 125 * k6[2] / 336;
            next_p2 = last->p2 + k1[3] / 24 + 5 * k4[3] / 48 + 27 * k5[3] / 56 + 125 * k6[3] / 336;

            // переходим к шагу h/2 ---------------------------------------------------------------------------------------------------------
            k1[0] = (h / 2) * f1(last->t, last->x1, last->x2, last->p1, last->p2, alpha);
            k1[1] = (h / 2) * f2(last->t, last->x1, last->x2, last->p1, last->p2, alpha);
            k1[2] = (h / 2) * f3(last->t, last->x1, last->x2, last->p1, last->p2, alpha);
            k1[3] = (h / 2) * f4(last->t, last->x1, last->x2, last->p1, last->p2, alpha);

            k2[0] = (h / 2) * f1(last->t + (1. / 2) * (h / 2), last->x1 + (1. / 2) * k1[0], last->x2 + (1. / 2) * k1[1], last->p1 + (1. / 2) * k1[2], last->p1 + (1. / 2) * k1[3], alpha);
            k2[1] = (h / 2) * f2(last->t + (1. / 2) * (h / 2), last->x1 + (1. / 2) * k1[0], last->x2 + (1. / 2) * k1[1], last->p1 + (1. / 2) * k1[2], last->p1 + (1. / 2) * k1[3], alpha);
            k2[2] = (h / 2) * f3(last->t + (1. / 2) * (h / 2), last->x1 + (1. / 2) * k1[0], last->x2 + (1. / 2) * k1[1], last->p1 + (1. / 2) * k1[2], last->p1 + (1. / 2) * k1[3], alpha);
            k2[3] = (h / 2) * f4(last->t + (1. / 2) * (h / 2), last->x1 + (1. / 2) * k1[0], last->x2 + (1. / 2) * k1[1], last->p1 + (1. / 2) * k1[2], last->p1 + (1. / 2) * k1[3], alpha);

            k3[0] = (h / 2) * f1(last->t + (1. / 2) * (h / 2), last->x1 + (1. / 4) * (k1[0] + k2[0]), last->x1 + (1. / 4) * (k1[1] + k2[1]), last->p1 + (1. / 4) * (k1[2] + k2[2]), last->p2 + (1. / 4) * (k1[3] + k2[3]), alpha);
            k3[1] = (h / 2) * f2(last->t + (1. / 2) * (h / 2), last->x1 + (1. / 4) * (k1[0] + k2[0]), last->x1 + (1. / 4) * (k1[1] + k2[1]), last->p1 + (1. / 4) * (k1[2] + k2[2]), last->p2 + (1. / 4) * (k1[3] + k2[3]), alpha);
            k3[2] = (h / 2) * f3(last->t + (1. / 2) * (h / 2), last->x1 + (1. / 4) * (k1[0] + k2[0]), last->x1 + (1. / 4) * (k1[1] + k2[1]), last->p1 + (1. / 4) * (k1[2] + k2[2]), last->p2 + (1. / 4) * (k1[3] + k2[3]), alpha);
            k3[3] = (h / 2) * f4(last->t + (1. / 2) * (h / 2), last->x1 + (1. / 4) * (k1[0] + k2[0]), last->x1 + (1. / 4) * (k1[1] + k2[1]), last->p1 + (1. / 4) * (k1[2] + k2[2]), last->p2 + (1. / 4) * (k1[3] + k2[3]), alpha);

            k4[0] = (h / 2) * f1(last->t + (h / 2), last->x1 + (-k2[0] + 2 * k3[0]), last->x2 + (-k2[1] + 2 * k3[1]), last->p1 + (-k2[2] + 2 * k3[2]), last->p2 + (-k2[2] + 2 * k3[3]), alpha);
            k4[1] = (h / 2) * f2(last->t + (h / 2), last->x1 + (-k2[0] + 2 * k3[0]),  last->x2 + (-k2[1] + 2 * k3[1]), last->p1 + (-k2[2] + 2 * k3[2]), last->p2 + (-k2[2] + 2 * k3[3]), alpha);
            k4[2] = (h / 2) * f3(last->t + (h / 2), last->x1 + (-k2[0] + 2 * k3[0]),  last->x2 + (-k2[1] + 2 * k3[1]), last->p1 + (-k2[2] + 2 * k3[2]), last->p2 + (-k2[2] + 2 * k3[3]), alpha);
            k4[3] = (h / 2) * f4(last->t + (h / 2), last->x1 + (-k2[0] + 2 * k3[0]),  last->x2 + (-k2[1] + 2 * k3[1]), last->p1 + (-k2[2] + 2 * k3[2]), last->p2 + (-k2[2] + 2 * k3[3]), alpha);

            k5[0] = (h / 2) * f1(last->t + (2. / 3) * (h / 2), last->x1 + (1. / 27) * (7 * k1[0] + 10 * k2[0] + k4[0]), last->x2 + (1. / 27) * (7 * k1[1] + 10 * k2[1] + k4[1]), last->p1 + (1. / 27) * (7 * k1[2] + 10 * k2[2] + k4[2]), last->p2 + (1. / 27) * (7 * k1[3] + 10 * k2[3] + k4[3]), alpha);
            k5[1] = (h / 2) * f2(last->t + (2. / 3) * (h / 2), last->x1 + (1. / 27) * (7 * k1[0] + 10 * k2[0] + k4[0]), last->x2 + (1. / 27) * (7 * k1[1] + 10 * k2[1] + k4[1]), last->p1 + (1. / 27) * (7 * k1[2] + 10 * k2[2] + k4[2]), last->p2 + (1. / 27) * (7 * k1[3] + 10 * k2[3] + k4[3]), alpha);
            k5[2] = (h / 2) * f3(last->t + (2. / 3) * (h / 2), last->x1 + (1. / 27) * (7 * k1[0] + 10 * k2[0] + k4[0]), last->x2 + (1. / 27) * (7 * k1[1] + 10 * k2[1] + k4[1]), last->p1 + (1. / 27) * (7 * k1[2] + 10 * k2[2] + k4[2]), last->p2 + (1. / 27) * (7 * k1[3] + 10 * k2[3] + k4[3]), alpha);
            k5[3] = (h / 2) * f4(last->t + (2. / 3) * (h / 2), last->x1 + (1. / 27) * (7 * k1[0] + 10 * k2[0] + k4[0]), last->x2 + (1. / 27) * (7 * k1[1] + 10 * k2[1] + k4[1]), last->p1 + (1. / 27) * (7 * k1[2] + 10 * k2[2] + k4[2]), last->p2 + (1. / 27) * (7 * k1[3] + 10 * k2[3] + k4[3]), alpha);

            k6[0] = (h / 2) * f1(last->t + (1. / 5) * (h / 2), last->x1 + (1. / 625) * (28 * k1[0] - 125 * k2[0] + 546 * k3[0] + 54 *k4[0] - 378 * k5[0]), last->x2 + (1. / 625) * (28 * k1[1] - 125 * k2[1] + 546 * k3[1] + 54 *k4[1] - 378 * k5[1]), last->p1 + (1. / 625) * (28 * k1[2] - 125 * k2[2] + 546 * k3[2] + 54 * k4[2] - 378 * k5[2]), last->p2 + (1. / 625) * (28 * k1[3] - 125 * k2[3] + 546 * k3[3] + 54 * k4[3] - 378 * k5[3]), alpha);
            k6[1] = (h / 2) * f2(last->t + (1. / 5) * (h / 2), last->x1 + (1. / 625) * (28 * k1[0] - 125 * k2[0] + 546 * k3[0] + 54 *k4[0] - 378 * k5[0]), last->x2 + (1. / 625) * (28 * k1[1] - 125 * k2[1] + 546 * k3[1] + 54 *k4[1] - 378 * k5[1]), last->p1 + (1. / 625) * (28 * k1[2] - 125 * k2[2] + 546 * k3[2] + 54 * k4[2] - 378 * k5[2]), last->p2 + (1. / 625) * (28 * k1[3] - 125 * k2[3] + 546 * k3[3] + 54 * k4[3] - 378 * k5[3]), alpha);
            k6[2] = (h / 2) * f2(last->t + (1. / 5) * (h / 2), last->x1 + (1. / 625) * (28 * k1[0] - 125 * k2[0] + 546 * k3[0] + 54 *k4[0] - 378 * k5[0]), last->x2 + (1. / 625) * (28 * k1[1] - 125 * k2[1] + 546 * k3[1] + 54 *k4[1] - 378 * k5[1]), last->p1 + (1. / 625) * (28 * k1[2] - 125 * k2[2] + 546 * k3[2] + 54 * k4[2] - 378 * k5[2]), last->p2 + (1. / 625) * (28 * k1[3] - 125 * k2[3] + 546 * k3[3] + 54 * k4[3] - 378 * k5[3]), alpha);
            k6[3] = (h / 2) * f2(last->t + (1. / 5) * (h / 2), last->x1 + (1. / 625) * (28 * k1[0] - 125 * k2[0] + 546 * k3[0] + 54 *k4[0] - 378 * k5[0]), last->x2 + (1. / 625) * (28 * k1[1] - 125 * k2[1] + 546 * k3[1] + 54 *k4[1] - 378 * k5[1]), last->p1 + (1. / 625) * (28 * k1[2] - 125 * k2[2] + 546 * k3[2] + 54 * k4[2] - 378 * k5[2]), last->p2 + (1. / 625) * (28 * k1[3] - 125 * k2[3] + 546 * k3[3] + 54 * k4[3] - 378 * k5[3]), alpha);
            // промежуточное значение в точках с шагом h/2
            next_t_2 = last->t + (h / 2);
            next_x1_2 = last->x1 + k1[0] / 24 + 5 * k4[0] / 48 + 27 * k5[0] / 56 + 125 * k6[0] / 336;
            next_x2_2 = last->x2 + k1[1] / 24 + 5 * k4[1] / 48 + 27 * k5[1] / 56 + 125 * k6[1] / 336;
            next_p1_2 = last->p1 + k1[2] / 24 + 5 * k4[2] / 48 + 27 * k5[2] / 56 + 125 * k6[2] / 336;
            next_p2_2 = last->p2 + k1[3] / 24 + 5 * k4[3] / 48 + 27 * k5[3] / 56 + 125 * k6[3] / 336;

            //--------------------------------------------------------------------------------------------------------------------------

            k1[0] = (h / 2) * f1(next_t_2, next_x1_2, next_x2_2, next_p1_2, next_p2_2, alpha);
            k1[1] = (h / 2) * f2(next_t_2, next_x1_2, next_x2_2, next_p1_2, next_p2_2, alpha);
            k1[2] = (h / 2) * f3(next_t_2, next_x1_2, next_x2_2, next_p1_2, next_p2_2, alpha);
            k1[3] = (h / 2) * f4(next_t_2, next_x1_2, next_x2_2, next_p1_2, next_p2_2, alpha);

            k2[0] = (h / 2) * f1(next_t_2 + (1. / 2) * (h / 2), next_x1_2 + (1. / 2) * k1[0], next_x2_2 + (1. / 2) * k1[1], next_p1_2 + (1. / 2) * k1[2], next_p2_2 + (1. / 2) * k1[3], alpha);
            k2[1] = (h / 2) * f2(next_t_2 + (1. / 2) * (h / 2), next_x1_2 + (1. / 2) * k1[0], next_x2_2 + (1. / 2) * k1[1], next_p1_2 + (1. / 2) * k1[2], next_p2_2 + (1. / 2) * k1[3], alpha);
            k2[2] = (h / 2) * f3(next_t_2 + (1. / 2) * (h / 2), next_x1_2 + (1. / 2) * k1[0], next_x2_2 + (1. / 2) * k1[1], next_p1_2 + (1. / 2) * k1[2], next_p2_2 + (1. / 2) * k1[3], alpha);
            k2[3] = (h / 2) * f4(next_t_2 + (1. / 2) * (h / 2), next_x1_2 + (1. / 2) * k1[0], next_x2_2 + (1. / 2) * k1[1], next_p1_2 + (1. / 2) * k1[2], next_p2_2 + (1. / 2) * k1[3], alpha);

            k3[0] = (h / 2) * f1(next_t_2 + (1. / 2) * (h / 2), next_x1_2 + (1. / 4) * (k1[0] + k2[0]), next_x2_2 + (1. / 4) * (k1[1] + k2[1]), next_p1_2 + (1. / 4) * (k1[2] + k2[2]), next_p2_2 + (1. / 4) * (k1[3] + k2[3]), alpha);
            k3[1] = (h / 2) * f2(next_t_2 + (1. / 2) * (h / 2), next_x1_2 + (1. / 4) * (k1[0] + k2[0]), next_x2_2 + (1. / 4) * (k1[1] + k2[1]), next_p1_2 + (1. / 4) * (k1[2] + k2[2]), next_p2_2 + (1. / 4) * (k1[3] + k2[3]), alpha);
            k3[2] = (h / 2) * f3(next_t_2 + (1. / 2) * (h / 2), next_x1_2 + (1. / 4) * (k1[0] + k2[0]), next_x2_2 + (1. / 4) * (k1[1] + k2[1]), next_p1_2 + (1. / 4) * (k1[2] + k2[2]), next_p2_2 + (1. / 4) * (k1[3] + k2[3]), alpha);
            k3[3] = (h / 2) * f4(next_t_2 + (1. / 2) * (h / 2), next_x1_2 + (1. / 4) * (k1[0] + k2[0]), next_x2_2 + (1. / 4) * (k1[1] + k2[1]), next_p1_2 + (1. / 4) * (k1[2] + k2[2]), next_p2_2 + (1. / 4) * (k1[3] + k2[3]), alpha);

            k4[0] = (h / 2) * f1(next_t_2 + (h / 2), next_x1_2 + (-k2[0] + 2 * k3[0]), next_x2_2 + (-k2[1] + 2 * k3[1]), next_p1_2 + (-k2[2] + 2 * k3[2]), next_p2_2 + (-k2[2] + 2 * k3[3]), alpha);
            k4[1] = (h / 2) * f2(next_t_2 + (h / 2), next_x1_2 + (-k2[0] + 2 * k3[0]), next_x2_2 + (-k2[1] + 2 * k3[1]), next_p1_2 + (-k2[2] + 2 * k3[2]), next_p2_2 + (-k2[2] + 2 * k3[3]), alpha);
            k4[2] = (h / 2) * f3(next_t_2 + (h / 2), next_x1_2 + (-k2[0] + 2 * k3[0]), next_x2_2 + (-k2[1] + 2 * k3[1]), next_p1_2 + (-k2[2] + 2 * k3[2]), next_p2_2 + (-k2[2] + 2 * k3[3]), alpha);
            k4[3] = (h / 2) * f4(next_t_2 + (h / 2), next_x1_2 + (-k2[0] + 2 * k3[0]), next_x2_2 + (-k2[1] + 2 * k3[1]), next_p1_2 + (-k2[2] + 2 * k3[2]), next_p2_2 + (-k2[2] + 2 * k3[3]), alpha);

            k5[0] = (h / 2) * f1(next_t_2 + (2. / 3) * (h / 2), next_x1_2 + (1. / 27) * (7 * k1[0] + 10 * k2[0] + k4[0]), next_x2_2 + (1. / 27) * (7 * k1[1] + 10 * k2[1] + k4[1]), next_p1_2 + (1. / 27) * (7 * k1[2] + 10 * k2[2] + k4[2]), next_p2_2 + (1. / 27) * (7 * k1[3] + 10 * k2[3] + k4[3]), alpha);
            k5[1] = (h / 2) * f2(next_t_2 + (2. / 3) * (h / 2), next_x1_2 + (1. / 27) * (7 * k1[0] + 10 * k2[0] + k4[0]), next_x2_2 + (1. / 27) * (7 * k1[1] + 10 * k2[1] + k4[1]), next_p1_2 + (1. / 27) * (7 * k1[2] + 10 * k2[2] + k4[2]), next_p2_2 + (1. / 27) * (7 * k1[3] + 10 * k2[3] + k4[3]), alpha);
            k5[2] = (h / 2) * f3(next_t_2 + (2. / 3) * (h / 2), next_x1_2 + (1. / 27) * (7 * k1[0] + 10 * k2[0] + k4[0]), next_x2_2 + (1. / 27) * (7 * k1[1] + 10 * k2[1] + k4[1]), next_p1_2 + (1. / 27) * (7 * k1[2] + 10 * k2[2] + k4[2]), next_p2_2 + (1. / 27) * (7 * k1[3] + 10 * k2[3] + k4[3]), alpha);
            k5[3] = (h / 2) * f4(next_t_2 + (2. / 3) * (h / 2), next_x1_2 + (1. / 27) * (7 * k1[0] + 10 * k2[0] + k4[0]), next_x2_2 + (1. / 27) * (7 * k1[1] + 10 * k2[1] + k4[1]), next_p1_2 + (1. / 27) * (7 * k1[2] + 10 * k2[2] + k4[2]), next_p2_2 + (1. / 27) * (7 * k1[3] + 10 * k2[3] + k4[3]), alpha);

            k6[0] = (h / 2) * f1(next_t_2 + (1. / 5) * (h / 2), next_x1_2 + (1. / 625) * (28 * k1[0] - 125 * k2[0] + 546 * k3[0] + 54 *k4[0] - 378 * k5[0]), next_x2_2 + (1. / 625) * (28 * k1[1] - 125 * k2[1] + 546 * k3[1] + 54 *k4[1] - 378 * k5[1]), next_p1_2 + (1. / 625) * (28 * k1[2] - 125 * k2[2] + 546 * k3[2] + 54 * k4[2] - 378 * k5[2]), next_p2_2 + (1. / 625) * (28 * k1[3] - 125 * k2[3] + 546 * k3[3] + 54 * k4[3] - 378 * k5[3]), alpha);
            k6[1] = (h / 2) * f2(next_t_2 + (1. / 5) * (h / 2), next_x1_2 + (1. / 625) * (28 * k1[0] - 125 * k2[0] + 546 * k3[0] + 54 *k4[0] - 378 * k5[0]), next_x2_2 + (1. / 625) * (28 * k1[1] - 125 * k2[1] + 546 * k3[1] + 54 *k4[1] - 378 * k5[1]), next_p1_2 + (1. / 625) * (28 * k1[2] - 125 * k2[2] + 546 * k3[2] + 54 * k4[2] - 378 * k5[2]), next_p2_2 + (1. / 625) * (28 * k1[3] - 125 * k2[3] + 546 * k3[3] + 54 * k4[3] - 378 * k5[3]), alpha);
            k6[2] = (h / 2) * f2(next_t_2 + (1. / 5) * (h / 2), next_x1_2 + (1. / 625) * (28 * k1[0] - 125 * k2[0] + 546 * k3[0] + 54 *k4[0] - 378 * k5[0]), next_x2_2 + (1. / 625) * (28 * k1[1] - 125 * k2[1] + 546 * k3[1] + 54 *k4[1] - 378 * k5[1]), next_p1_2 + (1. / 625) * (28 * k1[2] - 125 * k2[2] + 546 * k3[2] + 54 * k4[2] - 378 * k5[2]), next_p2_2 + (1. / 625) * (28 * k1[3] - 125 * k2[3] + 546 * k3[3] + 54 * k4[3] - 378 * k5[3]), alpha);
            k6[3] = (h / 2) * f2(next_t_2 + (1. / 5) * (h / 2), next_x1_2 + (1. / 625) * (28 * k1[0] - 125 * k2[0] + 546 * k3[0] + 54 *k4[0] - 378 * k5[0]), next_x2_2 + (1. / 625) * (28 * k1[1] - 125 * k2[1] + 546 * k3[1] + 54 *k4[1] - 378 * k5[1]), next_p1_2 + (1. / 625) * (28 * k1[2] - 125 * k2[2] + 546 * k3[2] + 54 * k4[2] - 378 * k5[2]), next_p2_2 + (1. / 625) * (28 * k1[3] - 125 * k2[3] + 546 * k3[3] + 54 * k4[3] - 378 * k5[3]), alpha);
            // значение в точках с шагом h/2 итоговое 
            next_t_2 = next_t_2 + (h / 2); 
            next_x1_2 = next_x1_2 + k1[0] / 24 + 5 * k4[0] / 48 + 27 * k5[0] / 56 + 125 * k6[0] / 336;
            next_x2_2 = next_x2_2 + k1[1] / 24 + 5 * k4[1] / 48 + 27 * k5[1] / 56 + 125 * k6[1] / 336;
            next_p1_2 = next_p1_2 + k1[2] / 24 + 5 * k4[2] / 48 + 27 * k5[2] / 56 + 125 * k6[2] / 336;
            next_p2_2 = next_p2_2 + k1[3] / 24 + 5 * k4[3] / 48 + 27 * k5[3] / 56 + 125 * k6[3] / 336;

            if (sqrt(pow(next_x1 - next_x1_2,2) + pow(next_x2 - next_x2_2,2) + pow(next_p1 - next_p1_2,2) + pow(next_p2 - next_p2_2,2)) / 31 > EPS) // sqrt(pow(x2_2-x2_1,2)+pow(x1_2-x1_1,2))
                h = h / 2;
            else 
            {
                if (sqrt(pow(next_x1 - next_x1_2,2) + pow(next_x2 - next_x2_2,2) + pow(next_p1 - next_p1_2,2) + pow(next_p2 - next_p2_2,2)) / 31 < EPS / 64)
                    h = h * 2;
                else
                    break;
            }

        }while(1);
        push_back(&last, next_t, next_x1, next_x2, next_p1, next_p1);
    }

  //  printf("x(1) =  %.11f\n", last->x1);

    if(check == 0)
    {
        return last->p1;
    }
    else 
    {
        return last->p2;
    }
}

double Integral(Point* head)
{
    double f_a, f_b;
    double res = 0;
    while (head->next)
    {
        f_a = head->x1 * head->x1 + 2 * head->p2 * head->p2;
        f_b = head->next->x1 * head->next->x1 + 2 * head->next->p2 * head->next->p2;
        res = res + (f_a + f_b) * (head->next->t - head->t) / 2;
        head = head->next;
    }
    return res;
}

// поиск недостающих краевых пристрелкой методом Ньютона 
double find_x2_or_p1(double x1_0, double p2_0, double alpha, int mark)
{
    double f_left, f_right;
    double x2 = NEWTON_METHOD_START_VALUE_x_20;
    double p1 = NEWTON_METHOD_START_VALUE_p_10;
    double p1_1, p2_1; 
    Point *head;
    double B[2];
    double A[2][2];

    // цико по альфа чтобы найти наиболее точное значения x2 и p1 при заданном альфа 
    // для этого ввели параметр a с помощью которого вычисляем на соответсвующих шагах x2' и p1' 
    // и постепенно подходим (на 10ом шаге) к искомым значениям x2 и p1
    for (int i = 1; i < 10; i ++ ) {

        double a = i * alpha / 9.;

        do
        {
            head = (Point*)malloc(sizeof(Point));
            p1_1 = RungeKutta(&head, x1_0, x2+DELTA, p1, p2_0, a, 0);
            p2_1 = RungeKutta(&head, x1_0, x2+DELTA, p1, p2_0, a, 1);
            clear_list(&head);
            B[0] = p1_1 - P_1; // вектор B0
            B[1] = p2_1 - P_2; // вектор B1

            head = (Point*)malloc(sizeof(Point));
            p1_1 = RungeKutta(&head, x1_0, x2-DELTA, p1, p2_0, a, 0);
            p2_1 = RungeKutta(&head, x1_0, x2-DELTA, p1, p2_0, a, 1);
            clear_list(&head);
            A[0][0]=(B[0]-(p1_1-P_1))/(2*DELTA); // элемент матрицы A
            A[1][0]=(B[1]-(p2_1-P_2))/(2*DELTA);

            head = (Point*)malloc(sizeof(Point));
            p1_1 = RungeKutta(&head, x1_0, x2, p1 + DELTA, p2_0, a, 0);
            p2_1 = RungeKutta(&head, x1_0, x2, p1 + DELTA, p2_0, a, 1);
            clear_list(&head);
            B[0] = p1_1 - P_1;
            B[1] = p2_1 - P_2; // вектора B

            head = (Point*)malloc(sizeof(Point));
            p1_1 = RungeKutta(&head, x1_0, x2, p1 - DELTA, p2_0, a, 0);
            p2_1 = RungeKutta(&head, x1_0, x2, p1 - DELTA, p2_0, a, 1);
            clear_list(&head);
            A[0][1]=(B[0]-(p1_1-P_1))/(2*DELTA); // 
            A[1][1]=(B[1]-(p2_1-P_2))/(2*DELTA);

            head = (Point*)malloc(sizeof(Point));
            p1_1 = RungeKutta(&head, x1_0, x2, p1, p2_0, a, 0);
            p2_1 = RungeKutta(&head, x1_0, x2, p1, p2_0, a, 1);
            clear_list(&head);
            B[0] = p1_1 - P_1;
            B[1] = p2_1 - P_2; // вектора B
    /*if(norm<tol){printf;break;}*/
            x2-= (A[0][0]*B[0]-A[1][0]*B[1])/(A[1][0]*A[0][1]-A[0][0]*A[1][1]);
            p1+= (A[0][0]*B[1]-A[1][0]*B[0])/(A[1][0]*A[0][1]-A[0][0]*A[1][1]);

            printf("%le\n", x2);
        } while (sqrt(x2*x2 + p1*p1) > EPS); // норму Федоровского нужно по рекомендации преподавателя сделать 
    }


    printf("x2(0) = %.11f\n p1(0) = %.11f\n", x2, p1);
    if(mark == 0)
    {
         return x2;
    }
    else 
    {
        return p1;
    }
}