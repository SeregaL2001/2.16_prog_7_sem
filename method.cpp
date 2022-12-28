#include "method.hpp"

// добавление элемента в конец списка  
void push_back(Point **last, double t_, double x_, double p_) {
    Point *pt = (Point*)malloc(sizeof(Point));
    pt->t = t_;
    pt->x = x_;
    pt->p = p_;
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
void print_list(const Point *head) {
    while (head) {
        printf("%le %le %le\n", head->t, head->x, head->p);
        head = head->next;
    }
}

// печать списка в файл 
void fprint_list(const Point *head, FILE *fp) {
    while (head) {
        fprintf(fp, "%lf %lf %lf\n", head->t, head->x, head->p);
        head = head->next;
    }
}

// x_1' = x_2
double f1(double x_1, double x_2, double p_1, double p_2, double t, double alpha)
{
    return x_2;
}

// x_2' = p_2 - 2x_1*sin(...)
double f2(double x_1, double x_2, double p_1, double p_2, double t, double alpha)
{
    double g = 4 + alpha * t * t;
    return p_2 - 2 * x_1 * sin(PI/g);
}

// p_1' = x_1 + 2 * p_2 * sin(....);
double f3(double x_1, double x_2, double p_1, double p_2, double t, double alpha)
{
    double g =  4 + alpha * t * t;
    return x_1 + 2 * p_2 * sin(PI/g);
}

// p_2' = -p_1
double f4(double x_1, double x_2, double p_1, double p_2, double t, double alpha)
{
    return (-1) * p_1;
}