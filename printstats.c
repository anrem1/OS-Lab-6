#include "types.h"
#include "stat.h"
#include "user.h"

float av(int *arr, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return (float)sum / n;
}

void sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
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


float stdDev(int *arr, int n, float mean)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (arr[i] - mean) * (arr[i] - mean);
    }
    return sqrt((float)sum / n);
}

int med(int *arr, int n)
{
    sort(arr, n);
    if (n % 2 == 0)
    {
        return (arr[n / 2 - 1] + arr[n / 2]) / 2;
    }
    else
    {
        return arr[n / 2];
    }
}

int get_min(int *arr, int n)
{
    int min = 2147483647;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

int get_max(int *arr, int n)
{
    int max = -2147483648;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf(1, "Need at least one argument");
        exit();
    }

    int numbers[argc - 1];
    for (int i = 1; i < argc; i++)
    {
        numbers[i - 1] = atoi(argv[i]); 
    }

    int n = argc - 1;

    float avg = av(numbers, n);
    float stddev = stdDev(numbers, n, avg);
    int median = med(numbers, n);
    int min = get_min(numbers, n);
    int max = get_max(numbers, n);

    
    printf(1, "Average: %d.%d\n", (int)avg, (int)((avg - (int)avg) * 100));
    printf(1, "Standard Deviation: %d.%d\n", (int)stddev, (int)((stddev - (int)stddev) * 100));
    
    printf(1, "Median: %d\n", median);
    printf(1, "Min: %d\n", min);
    printf(1, "Max: %d\n", max);
    

    exit();
}