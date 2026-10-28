#include <stdio.h>

int main(){
    int n_rows, n_seats, k;

    printf("Enter the number of rows followed by the number of seats:\n");
    scanf("%d %d", &n_rows, &n_seats);

    printf("\nEnter the number of customers, k, who want to sit together.\n");
    scanf("%d", &k);

    int all_seats[n_rows][n_seats];
    int i, j;
    //Input Status of all Seats
    printf("\nEnter the status of each seat below. (0 for available and 1 for booked), one row per line.\n");
    for(i = 0; i < n_rows; i++){

        printf("\nFor Row %d,\n", i);
        for(j = 0; j < n_seats; j++){
            scanf("%d", &all_seats[i][j]);
        }
    }

    //Counting Available Seats
    int total_avail_in_rows[n_rows], all_avail_seats = 0;
    
    for(i = 0; i < n_rows; i++){
        int count_avail_in_row = 0;

        for(j = 0; j < n_seats; j++){
            if (!all_seats[i][j]) count_avail_in_row++;
        }
        total_avail_in_rows[i] = count_avail_in_row;
        all_avail_seats += count_avail_in_row;
    }

    //Display Available Seat Counts
    printf("\nFree Seats in each row: ");
    for(i = 0; i < n_rows; i++){
        printf("%d ", total_avail_in_rows[i]);
    }
    printf("\tTotal free: %d\n", all_avail_seats);

    //Searching Rows
    int middle_row = n_rows / 2;
    int order[n_rows];
    int pos = 0;
    order[pos++] = middle_row;
    for(int d = 1; d <= n_rows; d++){
        if (middle_row - d >= 0) order[pos++] = middle_row - d;
        if (middle_row + d < n_rows) order[pos++] = middle_row + d;
    }

    //find block of consecutive available seats
    int count, starting_seat, last_seat, row, block_found = 0;
    for(i = 0; i < n_rows && !block_found; i++){
        row = order[i];
        count = 0;
        for(j = 0; j < n_seats; j++){
            if (!all_seats[row][j] && count < k) count++;
            else count = 0;
            if (count == k){
                starting_seat = j - k + 1;
                last_seat = j;
                block_found = 1;
                break;
            }
        } 
    }

    //Change seats in block to occupied
    if (block_found){
        for(j = starting_seat; j <= last_seat; j++){
            all_seats[row][j] = 1;
        }
        //Counting Updated Seats
        int total_avail_in_rows[n_rows], all_avail_seats = 0;
        for(i = 0; i < n_rows; i++){
            int count_avail_in_row = 0;

            for(j = 0; j < n_seats; j++){
                if (!all_seats[i][j]) count_avail_in_row++;
            }
            total_avail_in_rows[i] = count_avail_in_row;
            all_avail_seats += count_avail_in_row;
        }

        //Display Updated Seat Counts
        printf("\n\nUpdated Arrangment After Adding Seats occupied by Group:\nFree Seats in each row: ");
        for(i = 0; i < n_rows; i++){
            printf("%d ", total_avail_in_rows[i]);
        }
        printf("\tTotal free: %d\n", all_avail_seats);
        }
    else printf("\nSorry, could not find %d consecutive seats in any row.\n", k);

    if (block_found) printf("\nGroup of %d seated in row %d, Seats %d to %d.\n", k, row, starting_seat, last_seat);

    //display Seat Numbers
    printf("    ");
    for(j = 0; j < n_seats; j++){
        printf("%d   ", j);
    }
    printf("\n");

    //display Seat Arrangment
    for(i = 0; i < n_rows; i++){

        //display row numbers
        printf("%d   ", i);
        for(j = 0; j < n_seats; j++){
            if (!all_seats[i][j]) printf("_   ");
            else printf("X   ");
        }
        printf("\n");
    }

}
