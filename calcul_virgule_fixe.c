#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 64
#define N 16 
#define PI 3.141592
#define M1 32000
#define M2 270

/* 16bits = 65535 (Unsigned)
Pas de quantification (-1 et 1): 2/65535 =~ 3.05e-5 => M1 = 1/3.025e-5 =~ 32000
Pas de quantification (-120 et 120): 240/65535 =~ 3.66e-3 => M2 = 1/3.66e-3 =~ 270
*/

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

short int fp2fix(double M, double x){
    return floor(M*x);
}

double fix2fp(double M, short int x){
    return (x/M);
}

void gen_tab_theta2(int n,double* Tab_Theta_d,short int* Tab_Theta){
    for (int i = 0; i < n; i++)
    {
        Tab_Theta[i]=fp2fix(M2,Tab_Theta_d[i]);
    }
}

void gen_tab_A2(int n,double* Tab_A_d, short int* Tab_A){
    for (int i = 0; i < n; i++)
    {
        Tab_A[i] = fp2fix(M1,Tab_A_d[i]);
    } 
}

void cordic2(short int  phi, short int* Tab_Theta, short int* Tab_A,int n,short int * x,short int * y){
    short int  alpha, theta, x_new, y_new,x1,y1;
    x_new = 0;
    y_new = 0;
    x1 = Tab_A[n-1];
    y1 = 0;
    alpha = 0;
    theta = Tab_Theta[0];
    //printf("i |  alpha  |  theta  |   x_short   |   y_short   |   x_double   |   y_double   | \n");
    for (int i = 0; i < n; i++)
    {
        //printf("%d | %.4i | %.4i | %.4i | %.4i | %.4f | %.4f | \n",i,alpha, theta, x1, y1,fix2fp(M1,x1),fix2fp(M1,y1));
        if (alpha < phi)
        {
            x_new = x1 - (y1>>i);
            y_new = y1 + (x1>>i);
            alpha = alpha + theta; 
        }
        else
        {
            x_new = x1 + (y1>>i);
            y_new = y1 - (x1>>i);
            alpha = alpha - theta; 
        }
        x1 = x_new;
        y1 = y_new;
        theta = Tab_Theta[i+1];

    }
    *x = x1;
    *y = y1;

    //printf("######## \n");
    //printf("short int => codic2 : xn = %i | yn = %i \n",*x,*y);

}

void test2(int n){
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
    
    short Tab_Theta2[N],Tab_A2[N];
    gen_tab_theta2(N,Tab_Theta,Tab_Theta2);
    gen_tab_A2(N,Tab_A,Tab_A2);

    double x,y = 0.0;
    double Angle = 0.0;

    short int x_,y_ = 0.0;
    short int Angle_ = 0.0;
    for (double Angle=0;Angle<=90;Angle++){
        Angle_ = fp2fix(M2,Angle);
        x_ = fp2fix(M1,x);
        y_ = fp2fix(M1,y);
        cordic2(Angle_,Tab_Theta2,Tab_A2,n,&x_,&y_);
        if ((Angle == 60) && (n == 8)){
            x = fix2fp(M1,x_);
            y = fix2fp(M1,y_);
            //printf("%i , %i \n",x_,y_);
        }
        //printf("%f , %f \n",x,y);
        //printf("Angle = %f \n",Angle);
        x = fix2fp(M1,x_);
        y = fix2fp(M1,y_);
        fprintf(fptr,"%.40f | %.40f \n",fabs(cos(DegToRad(Angle))-x),fabs(sin(DegToRad(Angle))-y));
    }
    fclose(fptr);
}

int main(void){
    
    double Tab_Theta[T],Tab_A[T];
    gen_tab_theta(T,Tab_Theta);
    gen_tab_A(T,Tab_A,Tab_Theta);

    short int Tab_Theta2[N],Tab_A2[N];
    gen_tab_theta2(N,Tab_Theta,Tab_Theta2);
    gen_tab_A2(N,Tab_A,Tab_A2);

    for (int n = 1; n <= N; n++)
    {
        test2(n);
    }
    return 0;
}