#include <stdio.h>

void input_temperatures(int n_sensors, int hourly_readings, int array[n_sensors][hourly_readings]){
    int i, j;
    for(i = 0; i < n_sensors; i++){
        printf("\nSensor %d: ", i + 1);
        for(j = 0; j < hourly_readings; j++){
            scanf("%d", &array[i][j]);
        }
        printf("\n");
    }
}

void sensor_analysis(int sensors, int sensor, int hourly_reading, int array[sensors][hourly_reading], float averages[sensors]){
    int total = 0, max = 0, critical_count = 0, warning_count = 0, streak = 0;
	
	int j, min = array[sensor][0];
    for(j = 0; j < hourly_reading; j++){
        total += array[sensor][j];
        if (array[sensor][j] > max) max = array[sensor][j];
        if (array[sensor][j] < min) min = array[sensor][j];
        if (array[sensor][j] >= 40) critical_count++;
        if (array[sensor][j] >= 35 && array[sensor][j] <= 39) warning_count++;
        if (array[sensor][j] >= 35) streak++;
        else if (j < hourly_reading - 1) streak = 0;
    }

    float avg = total * 1.0 / hourly_reading * 1.0;
    averages[sensor] = avg;

    printf("\nSensor %d: Total=%d   Avg=%.2f   Max=%d   Min=%d\n"
        "Critical=%d   Warning=%d   Longest hot streak=%d\n",
        sensor + 1, total, avg, max, min, critical_count, warning_count, streak);
}

void max_avg(int sensors, float averages[sensors]){
    float highest_avg = 0;
    int sensor = 0, i;
    for(i = 0; i < sensors; i++){
        if (averages[i] > highest_avg){
            highest_avg = averages[i];
            sensor = i + 1;
        }
    }
    printf("\n\nHighest Average: Sensor %d (%.2f)", sensor, highest_avg);
}

int main(){
    int n_sensors, hourly_readings;

    
    printf("\nEnter the number of sensors and of hourly_readings.\n");
    scanf("%d %d", &n_sensors, &hourly_readings);
    
    int readings[n_sensors][hourly_readings];
    float averages[n_sensors];
	
	
	input_temperatures(n_sensors, hourly_readings, readings);
	int i;
    for(i = 0; i < n_sensors; i++){
        sensor_analysis(n_sensors, i, hourly_readings, readings, averages);
    }

    max_avg(n_sensors, averages);
}
