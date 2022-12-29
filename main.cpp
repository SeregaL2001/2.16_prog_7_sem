#include "method.hpp"

int main(int argc, char *argv[])
{
    double h, alpha, x2, p1, p2, B;
    double error;
    Point *head = (Point *)malloc(sizeof(head));

    printf("Введите параметр a: ");
    scanf("%lf", &alpha);

    x2 = find_x2_or_p1(X_10, P_2, alpha, 0);
    p1 = find_x2_or_p1(X_10, P_2, alpha, 1);

     RungeKutta(&head, X_10, x2, p1, P_2, alpha, 0);

    printf("Integral = %.11f\n", Integral(head));

    clear_list(&head);
    return 0;
}