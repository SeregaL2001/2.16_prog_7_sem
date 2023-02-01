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
    Point *prev = NULL;
    while ((*head)->next) {
        prev = (*head);
        (*head) = (*head)->next;
        free(prev);
    }
    free(*head);
}

// норма Федоренко 
double norma_fedorenko(double *J, double F0, double F1)
{
    double kappa_0, kappa_1;

    kappa_0 = pow(J[0], 2) + pow(J[1], 2);
    kappa_1 = pow(J[2], 2) + pow(J[3], 2);

    return sqrt(pow(F0, 2) / kappa_0 + pow(F1, 2) / kappa_1);
}

// система ОДУ для задачи Коши 
Koef F(double t, Koef Y, double alpha)
{
    Koef ret;
    ret.x1 = Y.x2;
    ret.x2 = Y.p2 - 2. * Y.x1 * sin(M_PI/(4. + alpha * pow(t, 2.)));
    ret.p1 = Y.x1 + 2. * Y.p2 * sin(M_PI / (4. + alpha * pow(t, 2.)));
    ret.p2 = (-1.) * Y.p1;
    return ret;
}


Koef mult_koef(Koef Y, double b, Koef X, double a)
{
    Koef ret;
    ret.x1 = b * Y.x1 + a * X.x1;
    ret.x2 = b * Y.x2 + a * X.x2;
    ret.p1 = b * Y.p1 + a * X.p1;
    ret.p2 = b * Y.p2 + a * X.p2;
    return ret;
}

Koef h_koef(double h, Koef Y)
{
    Koef ret;
    ret.x1 = h * Y.x1;
    ret.x2 = h * Y.x2;
    ret.p1 = h * Y.p1;
    ret.p2 = h * Y.p2;
    return ret;
}

// подсчет Евклидовой нормы для 4ырех элементов 
double norma_koef(Koef Y)
{
    return sqrt(Y.x1 * Y.x1 + Y.x2 * Y.x2 + Y.p1 * Y.p1 + Y.p2 * Y.p2);
}

// метод РК основной
void RungeKutta(Point **head, double B1, double B2, double &P2_1, double &X1_1, double &X2_1, double &P1_1, double alpha)
{
    double border = 0.001;
    double lower_border = EPS;
    double h = border;

    Koef next, half_next;
    Koef k1, k2, k3, k4, k5, k6;
    Koef y, y0;

    double start_t;
    double half_next_t;

    Point *last;

    Point *pt = (Point*)malloc(sizeof(Point));
    pt->t = 0.;
    pt->x1 = 1.;
    pt->x2 = B2;
    pt->p1 = B1;
    pt->p2 = 0.;
    pt->next = NULL;
    (*head) = pt;
    last = pt;

    bool halt;
    double check;

    double puff;

    while ((1. - last->t - h) > EPS)
    {
        halt = true;
        while (halt) 
        {
            y.x1 = last->x1;
            y.x2 = last->x2;
            y.p1 = last->p1;
            y.p2 = last->p2;
            start_t = last->t;

            // двигаемся на шаг h из начала 
            k1 = h_koef(h, F(start_t, y, alpha));
            k2 = h_koef(h, F(start_t + 0.5 * h, mult_koef(y, 1., k1, 0.5), alpha));
            k3 = h_koef(h, F(start_t + 0.5 * h, mult_koef(y, 1., mult_koef(k1, 1., k2, 1.), 0.25), alpha));
            k4 = h_koef(h, F(start_t + h, mult_koef(y, 1., mult_koef(k2, 1., k3, -2.), -1.), alpha));
            k5 = h_koef(h, F(start_t + (2. / 3.) * h, mult_koef(y, 1., mult_koef(k1, 7., mult_koef(k2, 10., k4, 1.), 1.), 1. / 27.), alpha));
            k6 = h_koef(h, F(start_t + 0.2 * h, mult_koef(y, 1., mult_koef(k1, 28., mult_koef(k2, -125., mult_koef(k3, 546., mult_koef(k4, 54., k5, -378.), 1.), 1.), 1.), 0.0016), alpha));

            next = mult_koef(y, 1., mult_koef(k1, 1. / 24., mult_koef(k4, 5. / 48., mult_koef(k5, 27. / 56., k6, 125. / 336.), 1.), 1.), 1.);

            // двигаемся на шаг h/2 из начала 
            k1 = h_koef(h * 0.5, F(start_t, y, alpha));
            k2 = h_koef(h * 0.5, F(start_t + 0.25 * h, mult_koef(y, 1., k1, 0.5), alpha));
            k3 = h_koef(h * 0.5, F(start_t + 0.25 * h, mult_koef(y, 1., mult_koef(k1, 1., k2, 1.), 0.25), alpha));
            k4 = h_koef(h * 0.5, F(start_t + 0.5 * h, mult_koef(y, 1., mult_koef(k2, 1., k3, -2.), -1.), alpha));
            k5 = h_koef(h * 0.5, F(start_t + (1. / 3.) * h, mult_koef(y, 1., mult_koef(k1, 7., mult_koef(k2, 10., k4, 1.), 1.), 1. / 27.), alpha));
            k6 = h_koef(h * 0.5, F(start_t + 0.1 * h, mult_koef(y, 1., mult_koef(k1, 28., mult_koef(k2, -125., mult_koef(k3, 546., mult_koef(k4, 54., k5, -378.), 1.), 1.), 1.), 0.0016), alpha));

            half_next = mult_koef(y, 1., mult_koef(k1, 1. / 24., mult_koef(k4, 5. / 48., mult_koef(k5, 27. / 56., k6, 125. / 336.), 1.), 1.), 1.);
            half_next_t = start_t + 0.5 * h;
            y = half_next;

            // двигаемся еще на шаг h/2 из полученной точки 
            k1 = h_koef(h * 0.5, F(half_next_t, y, alpha));
            k2 = h_koef(h * 0.5, F(half_next_t + 0.25 * h, mult_koef(y, 1., k1, 0.5), alpha));
            k3 = h_koef(h * 0.5, F(half_next_t + 0.25 * h, mult_koef(y, 1., mult_koef(k1, 1., k2, 1.), 0.25), alpha));
            k4 = h_koef(h * 0.5, F(half_next_t + 0.5 * h, mult_koef(y, 1., mult_koef(k2, 1., k3, -2.), -1.), alpha));
            k5 = h_koef(h * 0.5, F(half_next_t + (1. / 3.) * h, mult_koef(y, 1., mult_koef(k1, 7., mult_koef(k2, 10., k4, 1.), 1.), 1. / 27.), alpha));
            k6 = h_koef(h * 0.5, F(half_next_t + 0.1 * h, mult_koef(y, 1., mult_koef(k1, 28., mult_koef(k2, -125., mult_koef(k3, 546., mult_koef(k4, 54., k5, -378.), 1.), 1.), 1.), 0.0016), alpha));

            half_next = mult_koef(y, 1., mult_koef(k1, 1. / 24., mult_koef(k4, 5. / 48., mult_koef(k5, 27. / 56., k6, 125. / 336.), 1.), 1.), 1.);
            check = (32. * norma_koef(mult_koef(next, 1., half_next, -1.))) / 31.;

            // выбор шага 
            if (check <= EPS) {
                halt = false;
                push_back(&last, start_t + h, next.x1, next.x2, next.p1, next.p2);

                if ((check < (EPS * 0.03125)) && (h * 2. <= border)) {
                    h = 2. * h;
                }
            }
            else if (h * 0.5 < lower_border) {
                halt = false;
                push_back(&last, start_t + h, next.x1, next.x2, next.p1, next.p2);
            }
            else {
                h /= 2.;
            }

        }
    }

    h = 1. - last->t;
    if (h > EPS) {
        y.x1 = last->x1;
        y.x2 = last->x2;
        y.p1 = last->p1;
        y.p2 = last->p2;
        start_t = last->t;

        k1 = h_koef(h, F(start_t, y, alpha));
        k2 = h_koef(h, F(start_t + 0.5 * h, mult_koef(y, 1., k1, 0.5), alpha));
        k3 = h_koef(h, F(start_t + 0.5 * h, mult_koef(y, 1., mult_koef(k1, 1., k2, 1.), 0.25), alpha));
        k4 = h_koef(h, F(start_t + h, mult_koef(y, 1., mult_koef(k2, 1., k3, -2.), -1.), alpha));
        k5 = h_koef(h, F(start_t + (2. / 3.) * h, mult_koef(y, 1., mult_koef(k1, 7., mult_koef(k2, 10., k4, 1.), 1.), 1. / 27.), alpha));
        k6 = h_koef(h, F(start_t + 0.2 * h, mult_koef(y, 1., mult_koef(k1, 28., mult_koef(k2, -125., mult_koef(k3, 546., mult_koef(k4, 54., k5, -378.), 1.), 1.), 1.), 0.0016), alpha));
        next = mult_koef(y, 1., mult_koef(k1, 1. / 24., mult_koef(k4, 5. / 48., mult_koef(k5, 27. / 56., k6, 125. / 336.), 1.), 1.), 1.);

        push_back(&last, 1., next.x1, next.x2, next.p1, next.p2);
    }

    P2_1 = last->p2;
    X1_1 = last->x1;

    X2_1 = last->x2;
    P1_1 = last->p1;
}

// вспомогательный РК для метода пристрелки Ньютона
void RungeKutta_sup(Point** head, double B1, double B2, double alpha, double &P2_1, double &P1_1)
{
   
}

// рещение Итерационной процедуры Ньютона в многомерном случае в явном виде см скрин 
void matr_plus_mult(double &B1, double &B2, double P2_1, double X1_1, double *D)
{
    B1 = B1 - (D[0] * X1_1 + D[1] * P2_1);
    B2 = B2 - (D[2] * X1_1 + D[3] * P2_1);
}

// поиск обратной матрицы 
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

// поиск недостающих краевых пристрелкой методом Ньютона 
void calc_p10_n_x20(double& B1_return, double& B2_return, double P2_1, double P1_1, double alpha)
{
 
}