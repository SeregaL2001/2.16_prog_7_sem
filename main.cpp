#include "method.hpp"


int main(int argc, char *argv[])
{
    double alpha, x2_0, p1_0;
    double p2_1, x1_1, x2_1, p1_1;
    double error;
    Point *head = (Point*)malloc(sizeof(head));

    printf("Alpha: ");
    scanf("%lf", &alpha);

    calc_p10_n_x20(p1_0, x2_0, P21, P11, alpha);

    RungeKutta(&head, p1_0, x2_0, p2_1, x1_1, x2_1, p1_1, alpha);

    printf("x2(0) = %.9f; p1(0) = %.9f\n", x2_0, p1_0);
    // printf("p2(1) = %.9f; p1(1) = %.9f\n", p2_1, p1_1);
    // printf("x1(1) = %.9f; x2(1) = %.9f\n", x1_1, x2_1);

    printf("Integral = %.6f\n", Integral(head));

    clear_list(&head);
    return 0;
}