#include <stdio.h>
#include <math.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Rus");
    float a;
    float b;
    float c;
    printf("������� ����������� ����������� ���� ax^2+bx+c=0\n");
    printf("������� ����������� a: ");
    scanf("%f", &a);
    printf("������� ����������� b: ");
    scanf("%f", &b);
    printf("������� ����������� c: ");
    scanf("%f", &c);
    if ((int) a == 0){
        if ((int) b == 0){printf("x - ����� �����");}
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
        else{printf("��� �������������� ������\n");}
    }
    return 0;
}
