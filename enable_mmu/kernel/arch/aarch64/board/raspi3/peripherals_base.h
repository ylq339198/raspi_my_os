#ifndef PERIPHERALS_BASE
#define PERIPHERALS_BASE
#include "memlayout.h"

#ifndef KERNEL_BASE
#define KERNEL_BASE 0x0
#endif

#define MMIO_BASE (KERNEL_BASE + 0x3F000000)

#endif // PERIPHERALS_BASE
