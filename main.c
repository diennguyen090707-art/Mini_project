#include <stdio.h>
#include "constants.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

float get_random_temp(float min, float max) {
    float scale = rand() / (float) RAND_MAX; 
    return min + scale * (max - min);
}

int get_random_hum(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int num_sensors = DEFAULT_NUM_SENSORS;
    int sampling_sec = DEFAULT_SAMPLING_SEC;
    int interval_hrs = DEFAULT_INTERVAL_HRS;

    // --- SỬA LỖI 2: Logic xử lý tham số an toàn hơn ---
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 < argc) {
                num_sensors = atoi(argv[i + 1]);
                if (num_sensors <= 0) {
                    fprintf(stderr, "Error %02d: Invalid number of sensors\n", ERR_INVALID_ARGUMENT);
                    return ERR_INVALID_ARGUMENT;
                }
                i++; // Nhảy qua giá trị số để đến tham số tiếp theo
            } else {
                fprintf(stderr, "Error %02d: Missing value for -n\n", ERR_INVALID_COMMAND);
                return ERR_INVALID_COMMAND;
            }
        } 
        else if (strcmp(argv[i], "-s") == 0) {
            if (i + 1 < argc) {
                sampling_sec = atoi(argv[i + 1]);
                if (sampling_sec < MIN_SAMPLING_SEC) {
                    fprintf(stderr, "Error %02d: Invalid sampling time\n", ERR_INVALID_ARGUMENT);
                    return ERR_INVALID_ARGUMENT;
                }
                i++;
            } else {
                fprintf(stderr, "Error %02d: Missing value for -s\n", ERR_INVALID_COMMAND);
                return ERR_INVALID_COMMAND;
            }
        } 
        else if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                interval_hrs = atoi(argv[i + 1]);
                if (interval_hrs < MIN_INTERVAL_HRS) {
                    fprintf(stderr, "Error %02d: Invalid interval time\n", ERR_INVALID_ARGUMENT);
                    return ERR_INVALID_ARGUMENT;
                }
                i++;
            } else {
                fprintf(stderr, "Error %02d: Missing value for -i\n", ERR_INVALID_COMMAND);
                return ERR_INVALID_COMMAND;
            }
        }
    }

    // In thông báo debug
    printf("Config: Sensors=%d, Sampling=%ds, Interval=%dh\n", num_sensors, sampling_sec, interval_hrs);

    FILE *fp = fopen("D:\\Dien\\Năm 2\\Kỹ thuật lập trình\\groupID_mini_project_20251\\task_1\\th_sensor.csv", "w");
    if (fp == NULL) {
        fprintf(stderr, "Error %02d: Cannot create file\n", ERR_FILE_ACCESS_DENIED);
        return ERR_FILE_ACCESS_DENIED;
    }

    // Tính toán thời gian
    time_t now = time(NULL);
    long interval_seconds = (long)interval_hrs * 3600;
    time_t start_time = now - interval_seconds;

    // Ghi Header
    fprintf(fp, "id,time,temperature,humidty\n");

    char time_str[30];
    struct tm *time_info;
    time_t current_t;

    // Vòng lặp chính
    for (current_t = start_time; current_t <= now; current_t += sampling_sec) {
        
        time_info = localtime(&current_t);
        strftime(time_str, sizeof(time_str), "%Y:%m:%d %H:%M:%S", time_info);

        int id;
        for (id = 1; id <= num_sensors; id++) {
            float temp = get_random_temp(TEMP_MIN, TEMP_MAX);
            int hum = get_random_hum(HUM_MIN, HUM_MAX);

            fprintf(fp, "%d,%s,%.1f,%d\n", id, time_str, temp, hum);
        }
    }

    printf("Task 1 completed successfully! Data written to th_sensor.csv\n");
    fclose(fp);
    
    return SUCCESS;
}