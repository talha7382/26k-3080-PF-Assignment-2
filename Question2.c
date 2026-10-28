#include <stdio.h>

int sum_proper_divisors(int num){
    int sum = 0;
    for(int i = num / 2; i >= 1; i--){
        if (num % i == 0)
            sum += i;
    }
    return sum;
}

int main(){
    int n, count = 0;

    printf("enter n\n");
    scanf("%d", &n);
    printf("\n");

    for(int i = 1; i <= n; i++){
        int j = sum_proper_divisors(i);
        if (j > i && j <= n && sum_proper_divisors(j) == i){
            printf("{%d, %d}\n", i, j);
            count++;
        }
    }

    if (count == 0) 
        printf("\nNo amicable pair found.");
    else 
        printf("\n%d amicable pairs found", count);
}
