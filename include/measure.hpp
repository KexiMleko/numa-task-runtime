#pragma once
#include <cpuid.h>
#include <cstdint>
#include <sys/cdefs.h>
#include <x86intrin.h>

#define CPUID_FENCE asm volatile("cpuid" : : "r"(0) : "ax","bx", "cx", "dx","memory")
#define COMPILER_FENCE asm volatile("" ::: "memory")

static inline __attribute__((always_inline)) void
measure_start(uint64_t &time_buffer) {
  unsigned int aux;
  CPUID_FENCE;
  COMPILER_FENCE;
  time_buffer = __rdtsc();
}

static inline __attribute__((always_inline)) uint64_t
measure_end(uint64_t start) {
  unsigned int aux;
  uint64_t end = __rdtscp(&aux);
  COMPILER_FENCE;
  CPUID_FENCE;
  return end - start;
}
static inline __attribute__((always_inline)) void warmup_measure_icache() {
  uint64_t tmp1, tmp2;
  measure_start(tmp1);
  measure_end(tmp1);
  measure_start(tmp2);
  measure_end(tmp2);
}

#undef CPUID_FENCE
#undef COMPILER_FENCE
