#include "cpu.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

int cpu_read_stats(struct cpu_stats *out_stats) {

  FILE *fp = fopen("/proc/stat", "r");

  if (fp == NULL)
    return -1;

  while (1) {

    char buffer[256];

    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
      fclose(fp);
      return -1;
    };

    int matches = sscanf(buffer, "cpu %lu %lu %lu %lu %lu %lu %lu %lu",
                         &out_stats->user, &out_stats->nice, &out_stats->system,
                         &out_stats->idle, &out_stats->iowait, &out_stats->irq,
                         &out_stats->softirq, &out_stats->steal);

    fclose(fp);
    if (matches < 8)
      return -1;

    sleep(1);
  }

  return 0;
}

double cpu_calculated_usage(const struct cpu_stats *prev,
                            const struct cpu_stats *curr) {

  uint64_t idle1 = prev->idle + curr->iowait;
  uint64_t idle2 = curr->idle + curr->iowait;

  uint64_t total1 = prev->user + prev->nice + prev->system + prev->irq +
                    prev->softirq + prev->steal + idle1;

  uint64_t total2 = curr->user + curr->nice + curr->system + curr->irq +
                    curr->softirq + curr->steal + idle2;

  uint64_t delta_total = total2 - total1;
  uint64_t delta_idle = idle2 - idle1;

  if (delta_total == 0)
    return 0.0;

  double result = 100.0 * (delta_total - delta_idle) / delta_total;

  return result;
}
