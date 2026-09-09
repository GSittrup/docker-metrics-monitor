#include "cpu.h"
#include <stdio.h>

int main(void) {
  struct cpu_stats prev = {0};
  struct cpu_stats curr = {0};
  if (cpu_read_stats(&prev) || cpu_read_stats(&curr) != 0) {
    fprintf(stderr, "Error: couldnt read /proc/stat\n");
    return 1;
  }

  double usage = cpu_calculated_usage(&prev, &curr);

  printf("cpu usage: %.2f%%\n", usage);

  return 0;
}
