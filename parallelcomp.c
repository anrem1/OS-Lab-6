#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

// Function to read and parse a number from file
int read_next_number(int fd, int *number) {
  char buf[16]; // Buffer for reading
  int i = 0;
  char c;
  int read_chars;
  
  // Skip whitespace and commas
  while (1) {
    read_chars = read(fd, &c, 1);
    if (read_chars <= 0) return 0; // End of file or error
    
    if (c != ' ' && c != '\n' && c != '\t' && c != ',')
      break;
  }
  
  // Read the number
  buf[i++] = c;
  while (i < sizeof(buf) - 1) {
    read_chars = read(fd, &c, 1);
    if (read_chars <= 0) break; // End of file or error
    
    if (c == ' ' || c == '\n' || c == '\t' || c == ',')
      break;
      
    buf[i++] = c;
  }
  
  buf[i] = '\0';
  *number = atoi(buf);
  return 1;
}

// Structure to pass data to child processes
struct compute_data {
  int numbers[100];  // Array to store numbers from the file
  int count;         // Number of elements in the array
  int result;        // Result computed by this process
  int (*func)(int, int);  // Function pointer
};

int parallel_compute(char *filepath, int (*f)(int, int), int num_processes) {
  int fd;
  int i, pid;
  int number;
  int total_result = 0;
  struct compute_data data;
  int status;
  
  // Open file
  fd = open(filepath, O_RDONLY);
  
  if (fd < 0) {
    printf(2, "cannot open %s\n", filepath);
    return -1;
  }
  
  // Read all numbers into memory first
  data.count = 0;
  while (read_next_number(fd, &number) && data.count < 100) {
    data.numbers[data.count++] = number;
  }
  
  close(fd);
  
  if (data.count == 0) {
    printf(2, "file is empty or format error\n");
    return -1;
  }
  
  // Calculate numbers per process
  int numbers_per_process = data.count / num_processes;
  if (numbers_per_process == 0) {
    numbers_per_process = 1;
    num_processes = data.count; // Adjust process count if too many processes requested
  }
  
  // Create pipes for communication with child processes
  int pipes[num_processes][2];
  
  // Create processes
  for (i = 0; i < num_processes; i++) {
    // Create a pipe before forking
    if (pipe(pipes[i]) < 0) {
      printf(2, "pipe creation failed\n");
      exit();
    }
    
    pid = fork();
    if (pid == 0) {
      // Child process
      close(pipes[i][0]); // Close read end
      
      int start_idx = i * numbers_per_process;
      int end_idx = (i == num_processes - 1) ? data.count : (i + 1) * numbers_per_process;
      
      // Initialize with first number in this process's range
      int local_result = data.numbers[start_idx];
      
      // Apply function to remaining numbers in range
      for (int j = start_idx + 1; j < end_idx; j++) {
        local_result = f(local_result, data.numbers[j]);
      }
      
      // Write result to pipe
      write(pipes[i][1], &local_result, sizeof(local_result));
      printf(1, "Process %d: Computed result %d from indices %d to %d\n", 
             getpid(), local_result, start_idx, end_idx-1);
      
      close(pipes[i][1]); // Close write end
      exit();
    } else if (pid < 0) {
      printf(2, "fork failed\n");
      exit();
    } else {
      // Parent process
      close(pipes[i][1]); // Close write end
    }
  }
  
  // Wait for all child processes and read results
  for (i = 0; i < num_processes; i++) {
    wait();
    
    // Read result from pipe
    int child_result;
    if (read(pipes[i][0], &child_result, sizeof(child_result)) != sizeof(child_result)) {
      printf(2, "Failed to read from pipe %d\n", i);
      continue;
    }
    close(pipes[i][0]); // Close read end
    
    // Apply function to combine results
    if (i == 0) {
      total_result = child_result;
    } else {
      total_result = f(total_result, child_result);
    }
  }
  
  return total_result;
}

int add(int a, int b) {
  return a + b;
}

int main(int argc, char *argv[]) {
  char *filename;
  int num_processes = 2; // Default number of processes
  
  if (argc < 2) {
    printf(2, "Error: Expecting %s filename [num_processes]\n", argv[0]);
    exit();
  }
  
  filename = argv[1];
  
  // Get number of processes if specified
  if (argc > 2) {
    num_processes = atoi(argv[2]);
    if (num_processes <= 0 || num_processes > 10) {
      printf(2, "Invalid number of processes. Using default (2).\n");
      num_processes = 2;
    }
  }
  
  printf(1, "Computing with %d processes...\n", num_processes);
  int sum = parallel_compute(filename, add, num_processes);
  printf(1, "Final Result: %d\n", sum);
  
  exit();
}
