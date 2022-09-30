#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 64
#define PI 3.141592

double RadToDeg(double rad){
    return rad * 180/PI;
}

double DegToRad(double deg){
    return deg * PI/180;   
}

void gen_tab_theta(int n,double* Tab_Theta){
    for (int i = 0; i < n; i++)
    {
        Tab_Theta[i]=RadToDeg(atan(pow(2,-i)));
    }
}

void gen_tab_A(int n, double* Tab_A, double* Tab_Theta){
    Tab_A[0]=cos(DegToRad(Tab_Theta[0]));

    for (int i = 1; i < n; i++)
    {
        Tab_A[i] = Tab_A[i-1]* cos(DegToRad(Tab_Theta[i]));
    } 
}

void cordic(double phi, double* Tab_Theta, double* Tab_A,int n,double* x,double* y ){
    double alpha, theta, x_new, y_new,x1,y1,d;
    x_new = 0;
    y_new = 0;
    x1=Tab_A[n-1];
    y1= 0;
    d = 1;
    alpha = 0;
    theta = Tab_Theta[0];
    //printf("i |   alpha   |   theta  |     x    |     y    | \n");
    for (int i = 0; i < n; i++)
    {
        //printf("%d | %.4f | %.4f | %.4f | %.4f | \n",i,alpha, theta, x1, y1);
        if (alpha < phi)
        {
            x_new = x1 - y1 * d;
            y_new = y1 + x1 * d;
            alpha = alpha + theta; 
        }
        else
        {
            x_new = x1 + y1 * d;
            y_new = y1 - x1 * d;
            alpha = alpha - theta; 
        }
        x1 = x_new;
        y1 = y_new;
        d = d/2;
        theta = Tab_Theta[i+1];

    }
    *x = x1;
    *y = y1;

    //printf("######## \n");
    //printf("codic : xn = %.4f | yn = %.4f \n",*x,*y);
}

void test(int n){
    FILE *fptr;
    
    char c[16];
    sprintf(c,"%d",n);
    char str[] = ".\\data\\angle";
    strcat(str, c);
    strcat(str, ".txt");
    //printf("%s",str);

    fptr = fopen(str,"w");
    
    double Tab_Theta[T],Tab_A[T];
    gen_tab_theta(T,Tab_Theta);
    gen_tab_A(T,Tab_A,Tab_Theta);

    double x,y = 0.0;
    double Angle = 0.0;
    
    for (double Angle=0;Angle<=90;Angle++){
        cordic(Angle,Tab_Theta,Tab_A,n,&x,&y);
        //printf("%f , %f \n",x,y);
        //printf("Angle = %f \n",Angle);
        fprintf(fptr,"%.40f | %.40f \n",fabs(cos(DegToRad(Angle))-x),fabs(sin(DegToRad(Angle))-y));
    }
    fclose(fptr);
}

int main(void){
    
    double Tab_Theta[T],Tab_A[T];
    gen_tab_theta(T,Tab_Theta);
    gen_tab_A(T,Tab_A,Tab_Theta);

    for (int n = 1; n <= T; n++)
    {
        test(n);
    }
    return 0;
}