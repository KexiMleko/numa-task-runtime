# numa-task-runtime

NUMA-aware task scheduling runtime to be written in C++ targeting dual-socket x86 hardware. Master's thesis project at the Faculty of Technical Sciences, University of Novi Sad.

## Goals

- Topology-aware work stealing across NUMA nodes
- Lock-free task queues with explicit C++ memory ordering
- NUMA-local memory allocation for task data
- Cycle-accurate benchmarking against naive scheduling strategies on real hardware

## Status

In design and early implementation phase.

## Hardware Target

Dual-socket Intel Xeon E5-2640 v2, 440GB DDR3 across 2 NUMA nodes connected via QPI. See [docs/hardware.md](docs/hardware.md) for full specifications.

## Documentation

- [Hardware specification and topology](docs/hardware.md)
- [Design decisions and rationale](docs/design.md)

## Key References

- Williams, *C++ Concurrency in Action*
- Yan Solihin, *Fundamentals of Parallel Multicore Architecture*
