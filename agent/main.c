#include <stdio.h>
#include "cpu.h" 

int main(void)
{
  struct cpu_stats stats = {0};
  if(cpu_read_stats(&stats) != 0) {
    fprintf(stderr, "Error: couldnt read /proc/stat\n");
    return 1;
  }

  printf("user: %lu, nice: %lu, system: %lu, idle: %lu, iowait: %lu, irq: %lu, softirq: %lu, steal: %lu\n",
         stats.user, stats.nice, stats.system, stats.idle, stats.iowait, stats.irq, stats.softirq, stats.steal);

  return 0;
}
