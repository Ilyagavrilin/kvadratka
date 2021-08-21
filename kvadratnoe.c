#include <stdio.h>
#include <math.h>
#include <locale.h>

float linear_solution(float a, float b){ /* ax + b = 0*/
    float x = -b/a;
    return x;
}
void disc_solution(float D, float a, float b){
    float x1  = (-b + sqrt(D))/(2*a);
    float x2  = (-b - sqrt(D))/(2*a);
    printf("x1 = %f x2 = %f\n", x1, x2);
}

int main(){
    setlocale(LC_ALL, "Rus");
    float a;
    float b;
    float c;
    printf("Решение квадратного уравненения вида ax^2+bx+c=0\n");
    printf("введите коэффициент a: ");
    scanf("%f", &a);
    printf("введите коэффициент b: ");
    scanf("%f", &b);
    printf("введите коэффициент c: ");
    scanf("%f", &c);
    if ((int) a == 0){
        if ((int) b == 0){printf("x - любое число");}
        else{printf("x = %f\n", linear_solution(b, c));}
    }
    else{
        float D = pow(b, 2) - 4 * a * c;
        if (D>= 0){
            if (D > 0){disc_solution(D, a, b);}
            else{printf("x = %f\n", -b/(2*a));}
        }
        else{printf("Нет действительных корней\n");}
    }
    return 0;
}
