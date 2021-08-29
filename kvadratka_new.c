/*! \file
* \brief This program solve square equations ax^2 + bx + c = 0
* Program can works with non complex coefficients, has self test unit. Can accept equations while user don't type n(no)
* \author Ilya Gavrilin
*/

#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

enum SolutionResult {
    INFINITIVE    =  8,
    ZERO_ANS      =  0,
    ONE_ANS       =  1,
    TWO_ANS       =  2,
};

enum TypeErrors {
    ERR_ROOTS_VAL =  11,
    ERR_NROOTS    =  33,
    ERROR         =  -1,
};

/*! \function int input(double *factor, char name);
*   \brief inputs double number, write on display name of variable, returns true if scan is ok, other case false
*   \param [in] name Accepts name of variable, and writes it on display
*   \param [out] factor Input double writes to this variable
*   \return 1 if param wrote into factor, else 0
*/
int input(double *factor, char name);

/*! \brief function tests if double number is zero
*   \param [in] val accepts number
*   \return 1 if absolute val is lover than epsilon, 0 in other cases
*   \warning epsilon can be changed in the description of function, default epsilon = 10e-8
 */
int is_zero(double val);

/*! \brief function tests that abs(val1-val2) less than epsilon, works without math.h
*   \return TRUE if fabs(val1 - val2) less than epsilon, False in other cases
*   \param [in] val1, val2 values to analysis their equality
*   \warning epsilon can be changed in the description of function, default epsilon = 10e-8
*/
int is_equal(double val1, double val2);

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
*   \param [in] num value which need to cut numbers
*   \param [in] precision value of signs after dot in input number
*   \return number with cut signs after dot
*/
double num_cutter(double num, int precision);

/*! \brief checks if input number is NAN
*   \param [in] x number needed to check
*   \return TRUE if x is NAN, else FALSE
*/
int is_nan(double val);

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
int SquareTests();

int Asker();

/*! \brief function which prints on display information about failed test
*/
void FailViewer(double a, double b, double c, int test_num, double x1_t, double x2_t,
double x1_r, double x2_r, int nroots_t, int nroots_r, int ERR_CODE);

/*! @brief void function which cleans stdin buffer before reading input data
*/
void CleanBuffer();

/*! \brief if user agreed, runs Tests()
*/
int testRunner();



int main() {
    if (testRunner() == ERROR) {
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

        CleanBuffer();
        printf("Enter coefficient %c: ", name);

        while (scanf("%lf", link) != 1) {
            printf("Wrong type of input data, please try again. \n");
            CleanBuffer();
        }
        return TRUE;
}

int is_zero (double val) {
    const double precision = 10e-8;//precision in test
    return (val > -precision && val < precision);
}

int is_equal(double val1, double val2) {
    const double precision = 10e-8;
    double delta = val1-val2;
    return (delta > -precision && delta < precision);
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
    if (x == NULL) {
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
    do {
        if (Solver() == ERROR) {
                return ERROR;
        }

        printf("Continue program? Y/N \n");

    } while (Asker() == TRUE);

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
    return floor(num * pow(10, precision)) / pow(10, precision);

}

int is_nan(double x) {
    return x != x;
}

void FailViewer(double a, double b, double c, int test_num, double x1_t, double x2_t,
                double x1_r, double x2_r, int nroots_t, int nroots_r, int ERR_CODE) {
    printf("Program failed on test %d.\n", test_num);
    printf("Equation: %.3lf x^2 + %.3lf x + %.3lf = 0.\n", a, b, c);
    if (ERR_CODE == ERR_NROOTS) {
        printf("Fail in number of roots. Expected: %d. Returned: %d.\n", nroots_t, nroots_r);
    }
    else if (ERR_CODE == ERR_ROOTS_VAL) {
        printf("Fail in value of roots.\n");
        printf("x1. Expected: %.3lf. Returned: %.3lf.\n", x1_t, x1_r);
        printf("x2. Expected: %.3lf. Returned: %.3lf.\n", x2_t, x2_r);
    }
    else {
        printf("Unknown type of error.\n");
    }
}

int SquareTests() {

    const int NumberTests = 10;

    double a[NumberTests]    =    {0, 0, 0, -2, 1,  0, 0,  1, -1,  0.1   };
    double b[NumberTests]    =    {0, 0, 1,  4, 0,  2, 0,  4,  0,  4     };
    double c[NumberTests]    =    {0, 1, 0,  0, 0, -6, 1,  3,  4,  0.6   };
    double r_x1[NumberTests] =    {0, 0, 0,  0, 0,  3, 0, -1, -2, -0.151 };
    double r_x2[NumberTests] =    {0, 0, 0,  2, 0,  0, 0, -3,  2, -39.850};
    int    res[NumberTests]  =    {8, 0, 1,  2, 1,  1, 0,  2,  2,  2     };

    int result = 0;

    for (int i = 0; i < NumberTests; i++) {
        int ERR_TYPE = 0;
        double x1 = NAN;
        double x2 = NAN;

        result = Square_solution(a[i], b[i], c[i], &x1, &x2);

        if (result != res[i]) {
            ERR_TYPE = ERR_NROOTS;
        }
        else if ((res[i] == 0 || res[i] == 8) && (!is_nan(x1) || !is_nan(x2))) {
            ERR_TYPE = ERR_ROOTS_VAL;
        }
        else if (res[i] == 1 && (!is_equal(num_cutter(x1, 3), r_x1[i]) || !is_nan(x2))) {
            ERR_TYPE = ERR_ROOTS_VAL;
        }
        else if (res[i] == 2 &&
        (!is_equal(num_cutter(x1, 3), r_x1[i])
            || !is_equal(num_cutter(x2, 3), r_x2[i]) || result != res[i])) {
            ERR_TYPE = ERR_ROOTS_VAL;
        }


        if (ERR_TYPE != 0) {
            FailViewer(a[i], b[i], c[i], i + 1, r_x1[i], r_x2[i], x1, x2, res[i], result, ERR_TYPE);
            return 0;
        }

    }
    return 1;
}

void CleanBuffer() {
    int buff_elem = 0;
    while (buff_elem != '\n' && buff_elem != EOF) {
        buff_elem = getchar();
    }
}

int Asker() {
    const char answer_yes = 'y';
    const char answer_no = 'n';
    char answer = 0;

    scanf("%s", &answer);

    if (lower(answer) == answer_yes) {
        return TRUE;
    }
    else if (lower(answer) == answer_no){
        return FALSE;
    }
    else {
        printf("Wrong answer, program finished. \n");
        return ERROR;
    }
}

int testRunner() {
    printf("Run tests?(Y/N) \n");
    if (Asker() == TRUE) {
        if (!SquareTests()) {
            printf("Error in tests.\n");
            return ERROR;
        }
        else {
            printf("Tests successfully passed.\n");
        }
    }
    else if (Asker()) {
        return 0;
    }
    else {
        printf("Wrong answer, program finished.\n");
        return ERROR;
    }
}
