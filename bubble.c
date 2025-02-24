#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char* argv[])
{
    // Print input arguments
    for (int c = 1; c < argc; c++)
    {
        printf(1, "arg[%d] = %s\n", c, argv[c]);
    }

    // Ensure valid number of arguments
    if (argc > 11)
    {
        printf(1, "Too many arguments, must be less than 10 numbers.\n");
        exit();
    }

    // Convert arguments to integers
    int numbers[argc - 1];  // Store actual integer values
    for (int i = 1; i < argc; i++)
    {
        numbers[i - 1] = atoi(argv[i]);
    }

    // Bubble Sort Algorithm (Sorting actual integers)
    for (int i = 0; i < argc - 2; i++)
    {
        for (int j = 0; j < argc - 2 - i; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                // Swap numbers
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    // Print sorted numbers
    printf(1, "Sorted numbers:\n");
    for (int i = 0; i < argc - 1; i++)
    {
        printf(1, "%d ", numbers[i]);
    }
    printf(1, "\n");

    exit();
}
