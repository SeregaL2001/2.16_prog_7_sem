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

// очистка списка 
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