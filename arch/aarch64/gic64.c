/*
* ValiantCore Kernel
* Copyright (C) 2026 bigpower
* SPDX-License-Identifier: GPL-2.0-only
*/

#include "include/kernel.h"
#include <stdint.h>

#define GIC_DIST_BASE 0x08000000UL
#define GIC_CPU_BASE  0x08010000UL

#define GICD_CTLR        0x000
#define GICD_ISENABLER   0x100
#define GICD_ICENABLER   0x180
#define GICD_IPRIORITYR  0x400
#define GICD_ITARGETSR   0x800
#define GICD_ICFGR       0xC00

#define GICC_CTRL        0x00
#define GICC_PWR         0x004
#define GICC_IAR         0x00C
#define GICC_EOIR        0x010

#define MAX_IRQS         1020


/* ------- MMIO read/write helpers ---------------*/
static inline void mmio_write32(addr_t addr, uint32_t val) {
   *(volatile uint32_t *)addr = val;
}

static inline uint32_t mmio_read32(addr_t addr) {
   return *(volatile uint32_t *)addr;
}
/*The `addr` variable is `uint32_t` (32-bit), but `GIC_DIST_BASE` is `0x08000000UL`—this address needs to fit into a 64-bit pointer on AArch64. Truncating it to `uint32_t` could result in the loss of upper bits, creating a risk of writing to the wrong address on actual hardware (while it doesn't cause issues in QEMU's standard address range right now because `0x08000000` fits within 32 bits, it isn't best practice, so we use `addr_t` instead).*/


void gic_init(void) {
  mmio_write32(GIC_DIST_BASE + GICD_CTLR, 0x01);
  mmio_write32(GIC_CPU_BASE  + GICC_CTRL, 0x01);
  mmio_write32(GIC_CPU_BASE  + GICC_PWR,  0xFF);
}

/*============================================================================
* ValiantCore Aarch64 gic.c It can be thought of as analogous to pic.c on x86.
* ============================================================================*/
void gic_enable_irq(uint32_t irq) {
   if (irq >= MAX_IRQS) return;

   uint32_t reg_offset = (irq / 32) * 4;
   uint32_t bit        = irq % 32;

   addr_t addr = GIC_DIST_BASE + GICD_ISENABLER + reg_offset;
   mmio_write32(addr,  (1U << bit));
}

/*==============================================*/
void gic_set_priority(uint32_t irq, uint8_t priority) {
    if (irq >= MAX_IRQS) return;

    addr_t addr = GIC_DIST_BASE + GICD_IPRIORITYR + irq;
    *(volatile uint8_t *)addr = priority;
}
/* ==========================================================
* By Finn Dev
* I no longer use the name Bigpower; I use my own name, Finn.
=============================================================*/
void gic_set_target(uint32_t irq, uint8_t cpu_mask) {
    if (irq >= MAX_IRQS) return;

    addr_t addr = GIC_DIST_BASE + GICD_ITARGETSR + irq;
    *(volatile uint8_t *)addr = cpu_mask;
}

/* ===========================================================================================================
*  Even though I don't speak Turkish, I try to provide support in Turkish—as you've likely seen in the files.
*=============================================================================================================*/
uint32_t gic_acknowledge(void) {
    return mmio_read32(GIC_CPU_BASE + GICC_IAR) & 0x3FF;
}

/*------------------------------------------------*/
void gic_end_of_interrupt(uint32_t irq) {
   mmio_write32(GIC_CPU_BASE + GICC_EOIR, irq);
}
/*--------------The End--------------------------*/
