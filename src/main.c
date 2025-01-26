#include <ch554.h>
#include <debug.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define SFR_P1 0x90
#define SFR_P3 0xB0

// Pin map:
SBIT(OE_N, SFR_P1, 0);      // OE_N         P1.0   Enable USB switch output (active low)
SBIT(REBOOT_N, SFR_P1, 5);  // REBOOT_N     P1.5   Reboot button input (low when pressed)
SBIT(POWER_EN, SFR_P1, 6);  // POWER_EN     P1.6   Enable power to DUT (active high)
SBIT(SEL, SFR_P3, 0);       // SEL          P3.0   Select USB switch output (keep low)
SBIT(BOOT_EN_N, SFR_P3, 1); // BOOT_EN_N    P3.1   Enable DUT boot resistor (active low)
SBIT(ACTIVE_N, SFR_P3, 2);  // ACTIVE_N     P3.2   Status LED output (active low)

void hw_init() {
    // REBOOT is an input
    REBOOT_N = 1;
    // Quasi-bidirectional, Pn_MOD_OC = 1, Pn_DIR_PU = 1
    P1_MOD_OC = P1_MOD_OC | (1<<5);
    P1_DIR_PU = P1_DIR_PU |	(1<<5);

    // POWER_EN, OE_N, BOOT_EN_N, SEL are outputs
    BOOT_EN_N = 1; // Release pull-up on D+ line
    POWER_EN = 1; // Enable USB power
    OE_N = 0; // Enable USB data lines
    SEL = 0; // Configure USB mux

    // Output mode: Pn_MOD_OC = 0, Pn_DIR_PU = 1
    P1_MOD_OC = P1_MOD_OC & ~((1<<0) | (1<<6));
    P1_DIR_PU = P1_DIR_PU |	((1<<0) | (1<<6));
    P3_MOD_OC = P3_MOD_OC & ~((1<<2) | (1<<0) | (1<<1));
    P3_DIR_PU = P3_DIR_PU |	((1<<2) | (1<<0) | (1<<1));

    ACTIVE_N = 0; // Turn on status LED
}

void reboot_sequence() {
    ACTIVE_N = 1; // Turn off status LED

    OE_N = 1; // Disable USB data lines
    POWER_EN = 0; // Disable USB power

    mDelaymS(500);   // Give the target time to power down

    BOOT_EN_N = 0; // Enable pull-up on D+ line
    POWER_EN = 1; // Enable USB power
    OE_N = 0; // Enable USB data lines

    mDelaymS(500);   // Give the target time to boot into bootloader

    BOOT_EN_N = 1; // Release pull-up on D+ line

    ACTIVE_N = 0; // Turn on status LED
}

void main() {
    CfgFsys();          // Configure oscillator

    hw_init();

    while (true) {
        if(REBOOT_N == 0) {
            reboot_sequence();
        }
    }
}
