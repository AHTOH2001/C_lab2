#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    char name[125];
    double amount, sum_of_products, sum_of_delivery, price_for_one;
} Order;

void reference() {
    printf("%s", "Минск, Дзержинского, 19, ст метро «Грушевка», магазин eFruit. LOTS987654321\n");
}

double from_str_to_double(char s[125]) {
    if (s[0] == '-') {
        printf("%s", "Are you stupid??? It's a SHOP!!! Should be positive! EVERETHING\n");
        return -1;
    }
    int i = 0, sum = 0;
    while (s[i] != '\0') {
        if (s[i] <= '9' && s[i] >= '0'&& sum<INT_MAX/100) {
            sum = sum * 10 + (s[i] - '0');
            i++;
        } else {
            printf("%s", "Are you stupid??? Should be NUMBER!\n");
            return -1;
        }
    }
    return sum;
}

double delivery(Order order) {
    double res = 0;
    if (order.amount < 5) {
        res = 1;
    } else if (order.amount >= 5 && order.amount <= 20) {
        res = 3;
    } else {
        res = 10 + (order.amount - 20) * 2;
    }
    return res;
}

void count_total(Order my_order, double data[3]) {
    if (strcmp(my_order.name, "mandarin") == 0) {
        my_order.sum_of_products += my_order.amount * data[0];
    } else if (strcmp(my_order.name, "peaches") == 0) {
        my_order.sum_of_products += my_order.amount * data[1];
    } else {
        my_order.sum_of_products += my_order.amount * data[2];
    }
}

void for_file(FILE *f, char name[125]) {
    f = fopen("warehouse.txt", "w+");
    if (f != NULL) {
        printf("ok\n");
    } else {
        printf("It looks like there are some problems \n");
    }
}

int main() {
    FILE *fp;
    FILE *fp1;
    fp = fopen("data.txt", "r+");
    fp1 = fopen("warehouse.txt", "w+");
    if (fp != NULL && fp1 != NULL) {
        //printf("ok\n");
    } else {
        printf("It looks like there are some problems \n");
        return 0;
    }
    double data[3],flag_for_discounts = 0, flag_of_order = 0;
    fscanf(fp, "%lf %lf %lf", &data[0], &data[1], &data[2]);
    Order my_order;
    my_order.sum_of_products = 0;
    my_order.price_for_one = 0;
    my_order.amount = 0;
    char command[100];
    while (1) {
        printf("%s", "Enter command(contacts,make_an_order,quit,count_total_price_of_purchase,show_the_busket) \n ");
        scanf("%s", command);
        if (strcmp(command, "quit") == 0) {
            puts("Thank you! Goodbye");
            break;
        }
        if (strcmp(command, "contacts") == 0) {
            reference();
        }
        if (strcmp(command, "make_an_order") == 0) {
            fp1 = fopen("warehouse.txt", "a+");
            if (fp1 == NULL) {
                printf("It looks like there are some problems \n");
                return 0;
            }
            char s[125];
            puts("Enter name of product (mandarin,peaches,grape)");
            scanf(" %s", my_order.name);
            if (strcmp(my_order.name, "mandarin") == 0) {
                my_order.price_for_one = data[0];
                   flag_of_order = 1;
            } else if (strcmp(my_order.name, "peaches") == 0) {
                my_order.price_for_one = data[1];
                   flag_of_order = 1;
            } else if(strcmp(my_order.name, "grape") == 0){
                my_order.price_for_one = data[2];
                   flag_of_order = 1;
            } else{
                printf("%s", "There is no such product!\n");
                continue;
            }
            fprintf(fp1, "Name of product: %s  ", my_order.name);
            puts("Enter amount of product");
            scanf("%s", s);
            my_order.amount = from_str_to_double(s);
            if(my_order.amount != -1){
            fprintf(fp1, "Amount of %s:  %lf   ", my_order.name, my_order.amount);
            fprintf(fp1, "Price for one %s:  %.4lf\n", my_order.name, my_order.price_for_one);
            fclose(fp1);
            }

        }
        if (strcmp(command, "count_total_price_of_purchase") == 0) {
if(flag_of_order){

            char answer[125];
            my_order.sum_of_products = my_order.amount * my_order.price_for_one;
if (my_order.sum_of_products > 100) {
                my_order.sum_of_products *= 0.9;
                flag_for_discounts = 1;
            }
            printf("%s   %lf\n","Sum_of_products : " ,my_order.sum_of_products);
            puts("Do you need delivery? yes /no \n");
            scanf("%s", answer);
            if (strcmp(answer, "yes") == 0) {
              
                my_order.sum_of_delivery = delivery(my_order);
                printf("%s  %lf\n", "The delivery cost is: ", my_order.sum_of_delivery);

            if (flag_for_discounts){
                printf("%s","You've got a discount: 10%\n");
            }
            printf("%s  %lf\n", "The total amount is: ", my_order.sum_of_delivery+my_order.sum_of_products);
        }
} else{
    printf("%s","Make an order, please! \n");
}
        }
        if (strcmp(command, "show_the_busket") == 0) {

            double sum_;

            fp1 = fopen("warehouse.txt", "r");
            if (fp1 != NULL) {
                printf("ok\n");
            } else {
                printf("It looks like there are some problems \n");
                return 0;
            }
            while (!feof(fp1)) {
                char s[125];
                fgets(s, 100, fp1);
                if (!feof(fp1))
                    printf("%s \n ", s);
            }
        }

    }
    fclose(fp);
    fclose(fp1);
    return 0;
}