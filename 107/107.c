#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <tgmath.h>

double summationd(double a, double r, double n)
{
    return a * (1.0 - pow(r, n)) / (1.0 - r);
}

long long summation(long long a, long long num, long long dem, long long n)
{
    double r;

    if (dem == num)
        return a * n;

    r = ((double) num) / ((double) dem);

    return llrint(summationd(a, r, n));
}

int main(int argc, char **argv)
{
    char line[256];
    long long a, b;
    long long r0, r1;
    long long N, n;
    long long l, r;
    double c, d;

    do {
        fgets(line, 256, stdin);
        sscanf(line, "%lld %lld", &a, &b);

        if (a == 0 && b == 0) {
            break;
        }

        if (b == 1) {
            N = 1;
        } else {
            c = log(a) / log(b);

            d = -1.0;

            l = 2;
            r = a;

            do {
                N = (l + r) / 2;

                if (l == N)
                    break;

                d = log(N + 1) / log(N);

                if (d < c)
                    r = N;
                else
                    l = N;
            } while (1);
        }

        n = llrint(1.0 + log(a) / log(N + 1));

        r0 = summation(1, N, 1, n - 1);
        r1 = summation(a, N, N + 1, n);

        printf("%lld %lld\n", r0, r1);
    } while (1);

    return EXIT_SUCCESS;
}
