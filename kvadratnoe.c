#include <stdio.h>
#include <math.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Rus");
    float a;
    float b;
    float c;
    printf("Решение квадартного уравнения вида ax^2+bx+c=0\n");
    printf("Введите коэффициент a: ");
    scanf("%f", &a);
    printf("Введите коэффициент b: ");
    scanf("%f", &b);
    printf("Введите коэффициент c: ");
    scanf("%f", &c);
    if ((int) a == 0){
        if ((int) b == 0){printf("x - любое число.");}
        else{printf("x = %f\n", -c/b);}
    }
    else{
        float D = pow(b, 2) - 4 * a * c;
        if (D>= 0){
            if (D > 0){
                float x1  = (-b + sqrt(D))/(2*a);
                float x2  = (-b - sqrt(D))/(2*a);
                printf("x1 = %f x2 = %f\n", x1, x2);
            }
            else{printf("x = %f\n", -b/(2*a));}
        }
        else{printf("Нет действительных корней.\n");}
    }
    return 0;
}
