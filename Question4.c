#include <stdio.h>


int getValidDays() {
    int n_days;
    do {
        printf("Enter the number of festival days.\n");
        scanf("%d", &n_days);
        
        if (n_days > 7 || n_days < 1) 
            printf("\nInvalid Input.\n");
        else 
            return n_days;
    } while (n_days > 7 || n_days < 1);
}

float calculateDailySales(int dayNumber) {
    int n_orders, order_price;
    float total = 0, highest = 0;

    printf("\n\nDay %d - Enter the number of customer orders received: ", dayNumber + 1);
    scanf("%d", &n_orders);

    printf("Enter the order amounts:\n");
    for (int i = 0; i < n_orders; i++) {
        do {
            scanf("%d", &order_price);
            if (order_price <= 0) 
                printf("\nEnter amount more than 0 for order %d.\n", i + 1);
        } while (order_price <= 0);

        total += order_price;
        if (order_price > highest) 
            highest = order_price;
    }
    float average = total / n_orders;

    printf("\nFor Day %d:\nTotal Sales = %.2f,\nAverage: %.2f,\nHighest order amount: %.2f",
        dayNumber + 1, total, average, highest);
    return (float)total;
}

int findHighestSalesDay(int numberOfDays,float dailySales[numberOfDays]) {
    float highest = 0, day_number = 0;
    for (int i = 0; i < numberOfDays; i++) {
        if (dailySales[i] > highest) {
            highest = dailySales[i];
            day_number = i + 1;
        }
    }
    return day_number;
}

void displayBarChart(int numberOfDays, float dailySales[numberOfDays]) {
    int i, j, n_stars;
    for(i = 0; i < numberOfDays; i++) {
        printf("\nDay %d: ", i + 1);
        n_stars = dailySales[i] / 100;
        for (j = 0; j < n_stars; j++) {
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main() {
    float total = 0;
    const int festival_days = getValidDays();
    float dailySales[festival_days];

    int i;
    for(i = 0; i < festival_days; i++) {
        dailySales[i] = calculateDailySales(i);
        total += dailySales[i];
    }
    
    int highest_total_day = findHighestSalesDay(festival_days, dailySales);

    printf("\n\n====== FESTIVAL SUMMARY ======\n");
    printf("\nTotal festival sales: Rs. %.2f\n", total);
    printf("\nDay with highest sales: Day %d\n", highest_total_day);
    printf("\nHighest daily sales: Rs. %.2f\n", dailySales[highest_total_day - 1]);

    printf("\n\n====== DAILY SALES BAR CHART ======\n\n");
    displayBarChart(festival_days, dailySales);
}
