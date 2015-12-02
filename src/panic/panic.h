#ifndef PANIC_H
#define PANIC_H

/**
 * @file panic.h
 * @brief Kernel panic
 *
 * Kernel panic function
 */

/** Initiates a kernel panic and locks up the system
 * @param szError Reason for error
 */
void kpanic( char* szError );

#endif
