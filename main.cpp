#include "method.hpp"


int main(int argc, char *argv[])
{
    double alpha, x2_0, p1_0;
    double p2_1, x1_1, x2_1, p1_1;
    double error;
    Point *head = (Point*)malloc(sizeof(head));

    printf("Alpha: ");
    scanf("%lf", &alpha);

    find_x2_or_p1(p1_0, x2_0, alpha);

    RungeKutta();
    
    printf("p1(0) = %.9f; x2(0) = %.9f\n", p1_0, x2_0);
    // printf("p2(1) = %.9f; p1(1) = %.9f\n", p2_1, p1_1);
    // printf("x1(1) = %.9f; x2(1) = %.9f\n", x1_1, x2_1);

    printf("Integral = %.11f\n", Integral(head, alpha));

    clear_list(&head);
    return 0;
}