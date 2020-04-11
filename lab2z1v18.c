#include <stdio.h>
#include <math.h>
#include <conio.h>

#define true 1
#define false 0
#define err -2000123000
#define max 2147483646
typedef struct
{
    double inet, vlc, oth, sms, mms, abr;
} user;

double stod1(char s[1000])
{
    int i = 0, o = false;
    double sm = 0;
    if (s[0] == '-')
    {
        o = true;
        i++;
    }
    if (s[0] == '\0' || s[0] == '\n')
        return 0;
    while (s[i] != '\0' && s[i] != '\n')
    {
        if (s[i] >= '0' && s[i] <= '9')
            sm = sm * 10 + (s[i] - '0');
        else
            return err;
        if (sm >= max / 100)
            return err;
        i++;
    }
    if (o == true)
        return -1 * sm;
    else
        return sm;
}

void problem1()
{
    FILE *fp = fopen("tarif.txt", "r");
    int n, m, i, j,o,f;
    char s[1000];
    user u;
    double a[20][12], b[20];
    char name[20][1000];
    if (fp != NULL)
        printf("Succesfully loaded tariffs\n");
    else
    {
        printf("error while loading tariffs\n");
        return;
    }
    fscanf(fp, "%d%d", &n, &m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            fscanf(fp, "%lf", &a[i][j]);
        fscanf(fp, "%s", name[i]);
    }
    fclose(fp);
    f = false;
    while (true)
    {
        printf("1. Enter data about user\n");
        printf("2. Calculate optimal tariff for this user\n");
        printf("3. Information about tariffs\n");
        printf("4. Contact information of velcom company\n");
        printf("5. Exit from the program\n");
        
        o = getch();
        if (o == '1')
        {
            printf("Enter please average amount per month of:\n");
            printf("1. Internet using(MB): ");
            scanf("%s", s);
            u.inet = stod1(s);
            if (u.inet < 0)
            {
                printf("error\n");
                continue;
            }
            printf("2. Call time in VELCOM(Minutes): ");
            scanf("%s", s);
            u.vlc = stod1(s);
            if (u.vlc < 0)
            {
                printf("error\n");
                continue;
            }
            printf("3. Call time in other networks(Minutes): ");
            scanf("%s", s);
            u.oth = stod1(s);
            if (u.oth < 0)
            {
                printf("error\n");
                continue;
            }
            printf("4. Amount of SMS: ");
            scanf("%s", s);
            u.sms = stod1(s);
            if (u.sms < 0)
            {
                printf("error\n");
                continue;
            }
            printf("5. MMS count: ");
            scanf("%s", s);
            u.mms = stod1(s);
            if (u.mms < 0)
            {
                printf("error\n");
                continue;
            }
            printf("6.Call time to other countries(Minutes): ");
            scanf("%s", s);
            u.abr = stod1(s);
            if (u.abr < 0)
            {
                printf("error\n");
                continue;
            }
            f = true;
            printf("User profile has been succesfully changed \n");
        }
        else if (o == '2')
        {
            if (f == false)
                printf("There is no data about user\n");
            else
            {
                int pz[20];
                for (i = 0; i < n; i++)
                {
                    b[i] = a[i][6];
                    if (a[i][0] != -1 && u.inet > a[i][0])
                        b[i] += (u.inet - a[i][0]) * a[i][1];
                    if (a[i][4] != -1 && u.sms > a[i][4])
                        b[i] += (u.sms - a[i][4]) * a[i][9];
                    if (a[i][5] != -1 && u.mms > a[i][5])
                        b[i] += (u.mms - a[i][5]) * a[i][10];
                    if (a[i][2] != -1 && u.vlc > a[i][2])
                        b[i] += (u.vlc - a[i][2]) * a[i][7];
                    if (a[i][3] != -1 && u.oth > a[i][3])
                        b[i] += (u.oth - a[i][3]) * a[i][8];
                    b[i] += u.abr * a[i][11];
                }                
                for (i = 0; i < n; i++)
                    pz[i] = i;
                for (i = 0; i < n; i++)
                    for (j = i + 1; j < n; j++)
                        if (b[pz[i]] < b[pz[j]])
                        {
                            int x = pz[i];
                            pz[i] = pz[j];
                            pz[j] = x;
                        }
                for (i = 0; i < n; i++)
                    printf("tariff %s will cost %lf rubles\n\n", name[pz[i]], b[pz[i]]);
            }
        }
        else if (o == '3')
        {
            for (i = 0; i < n; i++)
            {
                printf("************\n%d. Tariff name: %s\n", i, name[i]);
                if (a[i][0] == -1)
                    printf("Unlimited internet\n");
                else
                    printf("Internet(MB): %lf\n", a[i][0]);
                printf("Cost of 1 over used MB: %lf\n", a[i][1]);
                if (a[i][2] == -1)
                    printf("Unlimited minutes within Velcome\n");
                else
                    printf("Minutes within velcome: %lf\n", a[i][2]);
                if (a[i][3] == -1)
                    printf("Unlimited minutes to other networks\n");
                else
                    printf("Minutes to other networks: %lf\n", a[i][3]);
                if (a[i][4] == -1)
                    printf("Unlimited SMS\n");
                else
                    printf("SMS count: %lf\n", a[i][4]);
                if (a[i][5] == -1)
                    printf("Unlimited MMS\n");
                else
                    printf("MMS count: %lf\n", a[i][5]);
                printf("Subscription fee: %lf\n", a[i][6]);
                printf("Cost of 1 minute overused  within Velcome: %lf\n", a[i][7]);
                printf("Cost of 1 minute overused to other networks: %lf\n", a[i][8]);
                printf("Cost of 1 SMS over limit : %lf\n", a[i][9]);
                printf("Cost of 1 MMS over limit : %lf\n", a[i][10]);
                printf("Cost of 1 call minute to other country: %lf\n", a[i][11]);
            }

            printf("\n^        ^        ^        ^        ^\n");
            printf("|        |        |        |        |\n");
            printf("Information about all Velcome tariffs\n");
        }
        else if (o == '4')
        {
            printf("tariffs: https://www.a1.by/ru/plans/c/b2ctariffs\n");
            printf("150 - number of contact center(for free in Belarus)\n");
            printf("71000 (0.03 ruble)\n");
            printf("+375 29 6 000 150 (cost depends on roaming)\n");
            printf("email address 150@A1.by\n");
            printf("more contact information: https://www.a1.by/ru/company/mobile-services-contacts\n");
            printf("web site: http://www.velcom.by/\n");
        }
        else if (o == '5')
            break;
        else
            printf("Wrong operation\n");
        printf("\n------------------\n");
    }
    printf("Do novyh vstrech");
}