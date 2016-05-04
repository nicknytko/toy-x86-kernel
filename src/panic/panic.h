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
void kpanic( const char* szError );

#define PANIC_STR1( x ) #x
#define PANIC_STR2( x ) PANIC_STR1( x )
#define PANIC( x ) kpanic( __FILE__ ":" PANIC_STR2(__LINE__) "; " x )
#define ASSERT( x ) if (!(x)){ PANIC( "Assert failed: " #x ); }

#endif
