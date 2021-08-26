/*! \file
* \brief This program solve square equations ax^2 + bx + c = 0
* Program can works with non complex coefficients, has self test unit. Can accept equations while user don't type n(no)
*/

#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0


const int ERROR = -1;
const int INFINITIVE = 8;
const int ZERO_ANS = 0;
const int ONE_ANS = 1;
const int TWO_ANS = 2;

/*! \brief inputs double number, write on display name of variable, returns true if scan is ok, other case false
*   \param [in] name Accepts name of variable, and writes it on display
*   \param [out] factor Input double writes to this variable
*   \return 1 if param wrote into factor, else 0
*/
int input(double *factor, char name);

/*! \brief function tests if double number is zero
*   \param [in] val accepts number
*   \return 1 if absolute val is lover than eps, 0 in other cases
 */
int is_zero(double val);

/*! \brief solution of linear equation(ax + b = 0)
*   \param [in] a, b coefficients of input linear equations
*   \param [out] x root of linear equation
*   \return number of roots, or Error
*/
int Linear_solution(double a, double b, double *x);

/*! \brief solution of square equation(ax^2 + bx + c = 0)
*   \param [in] a, b, c coefficients of input square equation
*   \param [out] x1, x2 roots of square equation
*   \return number of roots, or Error
*   \warning can't works with complex coefficients, don't solve equations with complex roots
*/
int Square_solution(double a, double b, double c, double *x1, double *x2);

/*! \brief runs main program
*   \return false in cause of error, else 0*/
int Solver();

/*! \brief cuts number after dot in double number
*   \param [in] num value witch need to cut numbers
*   \param [in] precision value of signs after dot in input number
*   \return number with cut signs after dot
*/
double num_cutter(double num, int precision);

/*! \brief cheks if input number is NAN
*   \param [in] x number needed to check
*   \return TRUE if x is NAN, else FALSE
*/
int is_nan(double x);

/*! \brief makes letter to lower
*   \param [in] letter input letter
*   \return input letter, but lower
*/
int lower(char letter);

/*! \brief ask user for solving new equation
*   \return Error if function doesn't finished right
*/
int ProgramContinuer();

/*! \brief unit tests
*   \return Error if tests don't finished, and writes number of failed test
*/
int Tests();

int testRunner();



int main() {
    if (testRunner() == ERROR) {
        printf("Error in tests.\n");
        return 0;
    }


    printf ("This program can solve square equations ax^2+bx+c=0.\n");

    if (ProgramContinuer() == ERROR) {
        printf("Error in solving equation.\n");
        return 0;
    }

    return 0;
}


int input (double *link , char name) {
        if (link == NULL) {
            return FALSE;
        }

        printf("Enter coefficient %c: ", name);

        if (scanf("%lf", link) == 1) {
            return TRUE;
        } else {
            return FALSE;
        }
}

int is_zero (double val) {
    const double precision = 10e-8;///<precision in test
    return (val > -precision && val < precision);
}


int lower(char letter) {
    if (letter >= 65 && letter <= 90) {
        return letter + 32;
    }
    else if (letter >= 97 && letter <= 122) {
        return letter;
    }
    else {
        return ERROR;
    }
}

// ax + b = 0
int Linear_solution (double a, double b, double *x) {
    if (x == NULL){
        return ERROR;
    }
    if (is_zero(a) && is_zero(b)) {
        return INFINITIVE;
    }
    else if (is_zero(a) && !is_zero(b)) {
        return ZERO_ANS;
    }
    else {
        *x = -b/a;
        return ONE_ANS;
    }
}

// ax^2 + bx + c = 0
int Square_solution (double a, double b, double c, double *x1, double *x2) {
    if ((x1 == NULL) || (x2 == NULL) || (x1 == x2)) {
        return ERROR;
    }

    if (is_zero(a)) {
        // bx + c = 0;

        if (is_zero(b)) {
            if (is_zero(c)) return INFINITIVE;

            else return ZERO_ANS;
        }
        else {
            return Linear_solution(b, c, x1);
        }
    }
    else {
        // ax^2 + bx + c = 0
        const double D = b * b - 4 * a * c;

        if (D > 0) {
            const double sq_D = sqrt (D);

            *x1 = (-b + sq_D) / (2 * a);
            *x2 = (-b - sq_D) / (2 * a);

            return TWO_ANS;
        }
        else if (is_zero (D)) {
            *x1 = -b / (2 * a);
            return ONE_ANS;
        }
        else {
            return ZERO_ANS;
        }
    }

}

int ProgramContinuer() {
    const char answer_yes = 'y';
    const char answer_no = 'n';
    char answer = 0;

    do {
        if (Solver() == ERROR) {
                return ERROR;
        }

        printf("Continue program? Y/N \n");
        scanf("%s", &answer);

        if (answer == answer_no) {
            printf("Program finished.\n");
            break;
        }
        else if (answer == answer_yes) {
            continue;
        }
        else {
            printf("Wrong answer, program finished.\n");
            break;
        }
    } while (lower(answer) == answer_yes);
    return 0;
}

int Solver() {
    double a = 0;
    double b = 0;
    double c = 0;

    double* form[3] = {&a, &b, &c};
    char name[3] = {'a', 'b', 'c'};

    for (int i = 0; i < 3; i++) {
        if (input(form[i], name[i]) == FALSE) {
            return ERROR;
        }
        }

    double x1 = NAN;
    double x2 = NAN;
    int numberRoots = 0;

    numberRoots = Square_solution (a, b, c, &x1, &x2);

    switch (numberRoots) {
        case ZERO_ANS: printf ("No rational roots.\n");
                       break;

        case ONE_ANS:  printf("x = %.3lf\n", x1);
                       break;

        case TWO_ANS:  printf ("x1 = %.3lf, x2 = %.3lf\n", x1, x2);
                       break;

        default:       return ERROR;
                       break;
    }

    return 0;
}


double num_cutter(double num, int precision) {
    return floor(num * pow(10, precision))/pow(10, precision);

}


int is_nan(double x) {
    return x != x;
}

 int Tests() {
    double a[7] =    {0, 1,  0, 0,  1, -1,  0.1   };
    double b[7] =    {0, 0,  2, 0,  4,  0,  4     };
    double c[7] =    {0, 0, -6, 1,  3,  4,  0.6   };
    double r_x1[7] = {0, 0,  3, 0, -1, -2, -0.151 };
    double r_x2[7] = {0, 0,  0, 0, -3,  2, -39.850};
    int res[7] =     {8, 1,  1, 0,  2,  2,  2     };

    int result = 0;

    for (int i = 0; i < 7; i++) {
        double x1 = NAN;
        double x2 = NAN;

        result = Square_solution(a[i], b[i], c[i], &x1, &x2);

        if ((res[i] == 0 || res[i] == 8) && (!is_nan(x1) || !is_nan(x2))) {
            printf("Code failed on test %d.\n", i + 1);
            return 0;
        }
        else if (res[i] == 1 && (!is_zero(num_cutter(x1, 3)-r_x1[i]) || !is_nan(x2))) {
            printf("Code failed on test %d.\n", i + 1);
            return 0;
        }
        else if (res[i] == 2 &&
        (!is_zero(num_cutter(x1, 3)-r_x1[i]) || !is_zero(num_cutter(x2, 3)-r_x2[i]) || result != res[i])) {
            printf("Code failed on test %d.\n", i + 1);
            return 0;
        }
    }
    return 1;
}

int testRunner() {
    const char answer_yes = 'y';
    const char answer_no = 'n';
    char answer = 0;

    printf("Run tests?(Y/N) \n");
    scanf("%s", &answer);
    if (lower(answer) == answer_yes) {
        if (!Tests()) {
            printf("Error in tests.\n");
            return ERROR;
        } else {
            printf("Tests successfully passed.\n");
        }
    }
    else if (lower(answer) != answer_no) {
        printf("Error in answer.\n");
        return ERROR;
    }
    return 0;
}
