#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
long double qpow(long double x, int n);
long double ob(long double x, int n);
long double epsil(long double x, long double eps);
long double fabsolute(long double x) {
    if (x < 0)return x * -1;
    return x;
}

void main() {
    int n; long double x, eps;
    printf("vvedite n,x,epsilon \n");
    scanf("%d %Lf %Lf", &n, &x, &eps);
    if (n < 1) {
        printf("Incorrect Value of n \n");
        return;
    }
    printf("ob: %Lf  eps: %Lf \n", ob(x, n), epsil(x, eps));
    return;
}
long double ob(long double x, int n) { //summirovanie cheres x,n
    int k;
    long double f1 = qpow(x, 2) * 2;
    long double sum = f1;
    long double xx2 = x * x * 2;
    long double prevf = f1;
    for (k = 2; k <= n; k++) {
        long double fconst = xx2 / k;
        long double thisf = prevf * fconst;
        sum += thisf;
        prevf = thisf;
    }
    return sum;
}
long double epsil(long double x, long double eps) { //solve cheres epsilon
    long double prev_res = qpow(x, 2) * 2; long double sum = prev_res;
    long double this_res = prev_res * x * x;
    while (fabsolute(this_res - prev_res) >= eps) {
        sum += this_res;
        prev_res = this_res;
        this_res = prev_res * x * x;
    }
    return sum;
}
long double qpow(long double x, int n) {
    int i; long double res = 1;
    for (i = 1; i <= n; i++) {
        res *= x;
    }
    return res;
}
