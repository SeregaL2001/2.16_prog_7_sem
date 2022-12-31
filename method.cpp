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

void matr_plus_mult(double &B1, double &B2, double P2_1, double X1_1, double *D)
{
    B1 = B1 - (D[0] * X1_1 + D[1] * P2_1);
    B2 = B2 - (D[2] * X1_1 + D[3] * P2_1);
}

void revers_matr(double *M)
{
    double A = M[0];
    double B = M[1];
    double C = M[2];
    double D = M[3];
    double puf = A * D - B * C;

    M[0] = D / puf;
    M[1] = (-B) / puf;
    M[2] = (-C) / puf;
    M[3] = A / puf;
}

double norma_2(double a, double b)
{
    return sqrt(a * a + b * b);
}

double norma_4(double x1, double x2, double p1, double p2)
{
    return sqrt(x1 * x1 + x2 * x2 + p1 * p1 + p2 * p2);
}

double norma_fedorenko(double *J, double F0, double F1)
{
    double kappa_0, kappa_1;

    kappa_0 = pow(J[0], 2) + pow(J[1], 2);
    kappa_1 = pow(J[2], 2) + pow(J[3], 2);

    return sqrt(pow(F0, 2) / kappa_0 + pow(F1, 2) / kappa_1);
}

void RungeKutta(Point **head, double x1_0, double x2_0, double p1_0, double p2_0, double alpha)
{

}

double Integral(Point *head, double alpha)
{
    double f_a, f_b, t_1, t_0;
    double res = 0;
    while (head->next)
    {
        t_1 = head->next->t;
        t_0 = head->t;
        f_a = pow(head->x1, 2.) + pow(head->p2, 2.);
        f_b = pow(head->next->x1, 2.) + pow(head->next->p2, 2.);

        res = res + (f_a + f_b) * (t_1 - t_0) / 2.;
        head = head->next;
    }
    return res;
}

// поиск недостающих краевых пристрелкой методом Ньютона 
void find_x2_or_p1(double &B1, double &B2, double alpha)
{

}