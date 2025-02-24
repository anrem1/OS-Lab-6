#include "types.h"
#include "stat.h"
#include "user.h"

float atof(const char* s) {
    float integer = 0;
    float fraction = 0;
    float power = 1;
    int sign = 1;
    int i = 0;
    
    if (s[0] == '-') {
        sign = -1;
        i++;
    }
    
    while (s[i] != '\0' && s[i] != '.') {
        integer = integer * 10 + (s[i] - '0');
        i++;
    }
    
    if (s[i] == '.') {
        i++;
        while (s[i] != '\0') {
            fraction = fraction * 10 + (s[i] - '0');
            power *= 10;
            i++;
        }
    }
    
    return sign * (integer + fraction / power);
}

float av(float *arr, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

void sort(float *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

float sqrt(float number) {
    if (number < 0) {
        return -1;  
    }
    float x = number;
    float y = 1.0;
    float epsilon = 0.00001;  
    while (x - y > epsilon || y - x > epsilon) {
        x = (x + y) / 2;
        y = number / x;
    }
    return x;
}

float stdDev(float *arr, int n, float mean) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (arr[i] - mean) * (arr[i] - mean);
    }
    return sqrt(sum / n);
}

float med(float *arr, int n) {
    if (n % 2 == 0) {
        return (arr[n / 2 - 1] + arr[n / 2]) / 2;
    } else {
        return arr[n / 2];
    }
}

float get_min(float *arr, int n) {
    return arr[0];
}

float get_max(float *arr, int n) {
    return arr[n-1];
}

void printFloat(int fd, float num) {
    int intPart = (int)num;
    int fracPart = (int)((num - intPart) * 1000 + 0.5);
    
    if (num < 0 && intPart == 0) {
        printf(fd, "-");
    }
    
    if (fracPart < 0) fracPart = -fracPart;
    if (fracPart < 10) {
        printf(fd, "%d.00%d", intPart, fracPart);
    } else if (fracPart < 100) {
        printf(fd, "%d.0%d", intPart, fracPart);
    } else {
        printf(fd, "%d.%d", intPart, fracPart);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(1, "Need at least one argument\n");
        exit();
    }
    
    float numbers[argc - 1];
    for (int i = 1; i < argc; i++) {
        numbers[i - 1] = atof(argv[i]);
    }
    
    int n = argc - 1;
    sort(numbers, n);
    float avg = av(numbers, n);
    float stddev = stdDev(numbers, n, avg);
    float median = med(numbers, n);
    float min = get_min(numbers, n);
    float max = get_max(numbers, n);
   
    printf(1, "Average: ");
    printFloat(1, avg);
    printf(1, "\nStandard Deviation: ");
    printFloat(1, stddev);
    printf(1, "\nMedian: ");
    printFloat(1, median);
    printf(1, "\nMin: ");
    printFloat(1, min);
    printf(1, "\nMax: ");
    printFloat(1, max);
    printf(1, "\n");
   
    exit();
}