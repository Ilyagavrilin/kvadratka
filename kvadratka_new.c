#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0


/* inputs double number, write on display name of variable, returns true/false */
int input(double *factor, char name);

/* if number is zero returns true, other returns false */
int is_zero(double num);

/*solution of linear equation(ax + b = 0), write answer in variable x,
can operate with a == 0 and/or b == 0, returns number of roots (8 means infinity),  error code is -1*/
int Linear_solution(double a, double b, double *x);

/*solution of kvadratic equation(ax^2 + bx + c = 0), write answer in variable x1 and x2,
 if answer is the only one writes it in x1, x2 don't changes,
can operate with a == 0 and/or b == 0 and/or c == 0, returns number of roots(0, 1 ,2, 8) (8 means infinity), error code is -1*/
int Kvadratic_solution(double a, double b, double c, double *x1, double *x2);

/* runs main program, returns false in cause of error*/
int Movement();

/* works only for 6 digits, idk why*/
double num_cutter(double num, int precision);

int Tests();


int main() {
    if (!Tests()) {
            printf("Error.\n");
            return 0;}
    else {
        printf("Tests successfully passed.\n");
    }
    if (Movement() != -1) return 0;
    else {
        printf("Error.\n");
        return 0;
    }
}

int input(double *factor, char name) {
        if (factor == NULL) {
            printf("No declared variable factor.\n");
            return FALSE;
        }
        printf("Enter coefficient %c:", name);
        if (scanf("%lf", factor) == 1) {
            return TRUE;
        }
        else {
            printf("Wrong format in input data.\n");
            return FALSE;
        }
}


int is_zero(double num) {
        if (num > -(10e-8) && num < 10e-8){
            return TRUE;
        }
        else {
            return FALSE;
        }
}


int Linear_solution(double a, double b, double *x) {
    if (x == NULL){
        printf("Error in solving linear equation.\n");
        return -1;
    }
    if (is_zero(a) && is_zero(b)) {
        return 8;
    }
    else if (is_zero(a) && !is_zero(b)) {
        return 0;
    }
    else {
        *x = -b/a;
        return 1;
    }
}


int Kvadratic_solution(double a, double b, double c, double *x1, double *x2) {
    if ((x1 == NULL) || (x2 == NULL) || (x1 == x2)) {
        printf("Error in input variable.\n");
        return -1;
    }

    if (is_zero(a)) {
        if (is_zero(b)) {
            if (is_zero(c)) return 8;

            else return 0;
        }
        else {
            return Linear_solution(b, c, x1);
        }
    }
    else {
        double D = pow(b, 2) - 4 *a * c;

        if (D > 0) {
            *x1 = (-b + sqrt(D)) / (2 * a);
            *x2 = (-b - sqrt(D)) / (2 * a);

            return 2;
        }
        else if (is_zero(D)) {
            *x1 = -b/(2*a);
            return 1;
        }

        else {
            return 0;
        }
    }

}


int Movement() {
    double a = 0;
    double b = 0;
    double c = 0;

    double x1 = 0;
    double x2 = 0;

    char A = 'a';
    char B = 'b';
    char C = 'c';

    printf("This program can solve kvadratic equations ax^2+bx+c=0.\n");
    if (!input(&a, A) || !input(&b, B) || !input(&c, C)) {
      return -1;
    }

    int res = 0;
    res = Kvadratic_solution(a, b, c, &x1, &x2);

    if (res == 8){printf("X - each rational number.\n");}
    else if (res == 0) printf("No rational roots.\n");
    else if (res == 1) printf("x = %.3lf\n", x1);
    else if (res == 2) printf("x1 = %.3lf, x2 = %.3lf\n", x1, x2);
    else{return -1;}

    return 0;
}


double num_cutter(double num, int precision) {
    return floor(num * pow(10, precision))/pow(10, precision);

}


 int Tests(){
    double a[7] =    {0, 1,  0, 0,  1, -1,  0.1};
    double b[7] =    {0, 0,  2, 0,  4,  0,  4};
    double c[7] =    {0, 0, -6, 1,  3,  4,  0.6};
    double r_x1[7] = {0, 0,  3, 0, -1, -2, -0.151};
    double r_x2[7] = {0, 0,  0, 0, -3,  2, -39.850};
    int res[7] =     {8, 1,  1, 0,  2,  2,  2};

    int result = 0;

    for (int i = 0; i < 7; i++) {
        double x1 = 0;
        double x2 = 0;

        result = Kvadratic_solution(a[i], b[i], c[i], &x1, &x2);

        if (!is_zero(num_cutter(x1, 3)-r_x1[i]) || !is_zero(num_cutter(x2, 3)-r_x2[i]) || result != res[i]) {
            printf("Code failed on test %d.\n", i + 1);
            return 0;
        }
    }
    return 1;
}
