#include <stdio.h>
#include <math.h>
#include <string.h>

#define true 1
#define false 0
#define err -2000123000
#define max 2147483646
#define PI 3.14159265358979323846

double myabs(double x)
{
    if (x < 0)
        return -x;
    else
        return x;
}

double stod(char s[1000])
{
    int i = 0, o = false, f = false;
    double sm = 0, d = 1;
    if (s[0] == '-')
    {
        o = true;
        i++;
    }
    if (s[0] == '\0' || s[0] == '\n')
        return 0;
    while (s[i] != '\0' && s[i] != '\n')
    {
        if (f)
            d *= 10;
        if (s[i] >= '0' && s[i] <= '9')
            sm = sm * 10 + (s[i] - '0');
        else if (s[i] == '.' && !f)
            f = true;
        else
            return err;

        if (sm >= max / 100)
            return err;
        i++;
    }
    if (o == true)
        return -1 * sm / d;
    else
        return sm / d;
}

void problem2()
{
    double x, eps, sum = 0, fc = 1, z, xx;
    int i;
    char s1[1000] = {'\0'}, s2[1000] = {'\0'};
    printf("vvedite x and eps\n");
    scanf("%s %s", s1, s2);
    x = stod(s1);
    eps = stod(s2);
    if (x == err || eps == err)
    {
        printf("error");
        return;
    }
    if (eps <= 0 || eps >= 1)
    {
        printf("err: epsilon should be more than 0 and less than 1");
        return;
    }
    if (myabs(x) >= 1000)
    {
        printf("err: x too big");
        return;
    }
    printf("right sin is %lf\n", sin(x));
    while (x > PI + 0.1)
        x -= 2 * PI;
    while (x < PI - 0.1)
        x += 2 * PI;
    z = x, xx = x;
    i = 1;
    while (myabs(z) >= eps)
    {
        if ((i / 2) % 2 == 0)
            sum += z;
        else
            sum -= z;
        fc *= (i + 1) * (i + 2);
        /* if (xx>max/(x*x) || (x*x)>max/(xx) || fc>max/((i+1)*(i+2)) || ((i+1)*(i+2))>max/fc)
         {
             printf ("Run time error");
             return 0;
         }*/
        xx *= x * x;
        z = xx / fc;
        i += 2;
    }
    printf(" my  sin  is %lf\n", sum);
    printf(" actual epsilon is  %lf\n", myabs(sin(x) - sum));
    printf("should be less than %lf\n", eps);
    printf("n = %d", i / 2 + 1);
}