#include "types.h"
#include "stat.h"
#include "user.h"

// #include <stddef.h> // For NULL


// Function prototypes
void sort(int *arr, int n);
float calculate_average(int *arr, int n);
float calculate_standard_deviation(int *arr, int n, float mean);
int calculate_median(int *arr, int n);
int find_min(int *arr, int n);
int find_max(int *arr, int n);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf(1, "Usage: printstats <num1> <num2> ... <numN>\n");
        exit();
    }

    int numbers[argc - 1];
    for (int i = 1; i < argc; i++)
    {
        numbers[i - 1] = atoi(argv[i]); // Convert input to integers
    }

    int n = argc - 1;

    // Compute statistics
    float avg = calculate_average(numbers, n);
    float stddev = calculate_standard_deviation(numbers, n, avg);
    int median = calculate_median(numbers, n);
    int min = find_min(numbers, n);
    int max = find_max(numbers, n);

    // Print results
    printf(1, "Average: %d.%d\n", (int)avg, (int)((avg - (int)avg) * 100));
    printf(1, "Standard Deviation: %d.%d\n", (int)stddev, (int)((stddev - (int)stddev) * 100));
    
    printf(1, "Median: %d\n", median);
    printf(1, "Min: %d\n", min);
    printf(1, "Max: %d\n", max);
    

    exit();
}

float calculate_average(int *arr, int n)
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
        return -1;  // Return -1 for invalid input (Xv6 does not handle floating-point errors well)
    }

    float x = number;
    float y = 1.0;
    float epsilon = 0.00001;  // Precision threshold

    while (x - y > epsilon || y - x > epsilon) {
        x = (x + y) / 2;
        y = number / x;
    }

    return x;
}


float calculate_standard_deviation(int *arr, int n, float mean)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (arr[i] - mean) * (arr[i] - mean);
    }
    return sqrt(sum / n);
}

int calculate_median(int *arr, int n)
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

int find_min(int *arr, int n)
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

int find_max(int *arr, int n)
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
