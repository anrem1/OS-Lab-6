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
  
  // // Skip whitespace and commas
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

int sequential_compute(char *filepath, int (*f)(int, int)) {
  int fd;
  int result;
  int number;
  
  // Open file
  fd = open(filepath, O_RDONLY);
  
  if (fd < 0) {
    printf(2, "cannot open %s\n", filepath);
    return -1;
  }
  
  // Read the first number to initialize result
  if (!read_next_number(fd, &result)) {
    printf(2, "file is empty or format error\n");
    close(fd);
    return -1;
  }
  
  // Process the rest of the numbers
  while (read_next_number(fd, &number)) {
    result = f(result, number);
  }
  
  close(fd);
  return result;
}

int add(int a, int b) {
  return a + b;
}

int main(int argc, char *argv[]) {
  char *filename;
  
  if (argc != 2) {
    printf(2, "Error: Expecting %s filename\n", argv[0]);
    exit();
  }
  
  filename = argv[1];
  
  int sum = sequential_compute(filename, add);
  printf(1, "Result: %d\n", sum);
  
  exit();
}
