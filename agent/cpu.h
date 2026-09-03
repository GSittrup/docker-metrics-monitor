#ifndef CPU_H
#define CPU_H

#include <stdint.h>

struct cpu_stats {
  uint64_t user;
  uint64_t nice;
  uint64_t system;
  uint64_t idle;
  uint64_t iowait;
  uint64_t irq;
  uint64_t softirq;
  uint64_t steal;
};

int cpu_read_stats(struct cpu_stats *out_stats);

double cpu_calculated_usage(const struct cpu_stats *prev,
                            const struct cpu_stats *current);

#endif
