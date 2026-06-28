/*
* ValiantCore Kernel
* Copyright (C) 2026 Bigpower
* SPDX-License-Identifier: GPL-2.0-only
*/
#include "include/kernel.h"
#include <stdint.h>

extern uint64_t read_cntpct_el0(void);

static uint64_t timer_freq   = 0;
static uint64_t timer_ticks  = 0;

static inline uint64_t read_cntfrq_el0(void) {
    uint64_t val;
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(val));
    return val;
}

/* Created by Finn Dev */
static inline void write_cntp_tval_el0(uint64_t val) {
    asm volatile ("msr cntp_tval_el0, %0" : : "r"(val));

/* Powered By ValiantCore Aarch64 */
}

static inline void write_cntp_ctl_el0(uint64_t val) {
   asm volatile ("msr cntp_ctl_el0, %0" : : "r"(val));
}

/* This is about as much code as I can write on the Android virtual keyboard. */
void timer_init(uint32_t hz) {
   timer_freq = read_cntfrq_el0();

   uint64_t interval = timer_freq / hz;
   write_cntp_tval_el0(interval);

   write_cntp_ctl_el0(1);
}

/* The timer64.c file can be thought of as analogous to pit.c on x86. */
void timer_handler(void) {
 timer_ticks++;

 uint64_t interval = timer_freq / 1000;
 write_cntp_tval_el0(interval);
}


uint64_t timer_get_ticks(void) {
     return timer_ticks;
}

uint64_t timer_get_freq(void) {
     return timer_freq;
}

/*----------------------------------------------------
*  timer_sleep_ms -- Same logic as pit_sleep(ms) on x86
* -----------------------------------------------------*/
void timer_sleep_ms(uint32_t ms) {
    uint64_t start = read_cntpct_el0();
    uint64_t target = (timer_freq * ms) / 1000;

    while ((read_cntpct_el0() - start) < target) {
        asm volatile ("nop");
    }
}
/* ---------------The End----------------------*/
 
