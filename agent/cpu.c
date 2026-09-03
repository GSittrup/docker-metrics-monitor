#include "cpu.h"
#include <inttypes.h>
#include <stdio.h>

int cpu_read_stats(struct cpu_stats *out_stats) {

  FILE *fp = fopen("/proc/stat", "r");

  if (fp == NULL)
    return -1;

  char buffer[256];
  fgets(buffer, sizeof(buffer), fp);

  int matches =
      sscanf(buffer, "cpu %lu %lu %lu %lu %lu %lu %lu %lu", &(*out_stats).user,
             &(*out_stats).nice, &(*out_stats).system, &(*out_stats).idle,
             &(*out_stats).iowait, &(*out_stats).irq, &(*out_stats).softirq,
             &(*out_stats).steal);

  fclose(fp);

  if (matches < 8)
    return -1;

  return 0;
}
