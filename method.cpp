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
void print_list(const Point *head) {
    while (head) {
        printf("%le %le %le\n", head->t, head->x1, head->x2, head->p1, head->p2);
        head = head->next;
    }
}

// печать списка в файл 
void fprint_list(const Point *head, FILE *fp) {
    while (head) {
        fprintf(fp, "%lf %lf %lf\n", head->t, head->x1, head->x2, head->p1, head->p2);
        head = head->next;
    }
}

// x_1' = x_2
double f1(double x1, double x2, double p1, double p2, double t, double alpha)
{
    return x2;
}

// x_2' = p_2 - 2x_1*sin(...)
double f2(double x1, double x2, double p1, double p2, double t, double alpha)
{
    double g = 4 + alpha * t * t;
    return p2 - 2 * x1 * sin(PI/g);
}

// p_1' = x_1 + 2 * p_2 * sin(....);
double f3(double x1, double x2, double p1, double p2, double t, double alpha)
{
    double g =  4 + alpha * t * t;
    return x1 + 2 * p2 * sin(PI/g);
}

// p_2' = -p_1
double f4(double x1, double x2, double p1, double p2, double t, double alpha)
{
    return (-1) * p1;
}

double RungeKutta(Point** head, double x1_0, double x2_0, double p1_0, double p2_0, double alpha)
{
    double h = 1;
    double next_t, next_x1, next_x2, next_p1, next_p2;
    double next_t_2, next_x1_2, next_x2_2, next_p1_2, next_p2_2;
    double k1[4], k2[4], k3[4], k4[4], k5[4], k6[4];
    Point* last;
    Point *pt = (Point*)malloc(sizeof(Point));
    
    pt->t = 0;
    pt->x1 = x1_0;
    pt->x2 = x2_0;
    pt->p1 = p1_0;
    pt->p2 = p2_0;
    pt->next = NULL;
    (*head) = pt;
    last = pt;

}