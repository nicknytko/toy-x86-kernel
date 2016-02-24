#ifndef CPUID_H
#define CPUID_H

/* Good documentation on the CPUID instruction can be found here
 * https://en.wikipedia.org/wiki/CPUID
 * http://wiki.osdev.org/CPUID
 */

/** @file cpuid.h
 * @brief CPUID abstraction
 * Provides miscellaneous information about processor
 */

#define CPUID_ECX_SSE3          0x1             /* SSE 3 */
#define CPUID_ECX_PCLMUL        0x2             /* PCLMULQDQ Support */
#define CPUID_ECX_DTES64        0x4             /* 64-bit Debug Store */
#define CPUID_ECX_MONITOR       0x8             /* MONITOR and MWAIT Support */
#define CPUID_ECX_DS_CPL        0x10            /* CPL qualified debug store */
#define CPUID_ECX_VMX           0x20            /* Virtual Machine eXtensions */
#define CPUID_ECX_SMX           0x40            /* Safer Mode Extensions */
#define CPUID_ECX_EST           0x80            /* Enhanced SpeedStep */
#define CPUID_ECX_TM2           0x100           /* Thermal Monitor 2 */
#define CPUID_ECX_SSSE3         0x200           /* Supplemental SSE3 */
#define CPUID_ECX_CID           0x400           /* L1 Context ID */
#define CPUID_ECX_SDBG          0x800           /* Silicon Debug Interface */
#define CPUID_ECX_FMA           0x1000          /* FMA3 (Fused Multiply-add) */
#define CPUID_ECX_CX16          0x2000          /* CMPXCHG16B Instruction */
#define CPUID_ECX_XTPR          0x4000          /* Can disable sending task priority messages */
#define CPUID_ECX_PDCM          0x8000          /* Perfmon and Debug Capability */
#define CPUID_ECX_PCID          0x20000         /* Process Context Identifiers */
#define CPUID_ECX_DCA           0x40000         /* Direct Cache Access for DMA Writes */
#define CPUID_ECX_SSE4_1        0x80000         /* SSE 4.1 */
#define CPUID_ECX_SSE4_2        0x100000        /* SSE 4.2 */
#define CPUID_ECX_X2APIC        0x200000        /* X2APIC Support */
#define CPUID_ECX_MOVBE         0x400000        /* MOVEBE Instruction */
#define CPUID_ECX_POPCNT        0x800000        /* POPCNT Instruction */
#define CPUID_ECX_TSTDEADLINE   0x1000000       /* APIC Supports TSC Deadline Value */
#define CPUID_ECX_AES           0x2000000       /* AES Instruction Set */
#define CPUID_ECX_XSAVE         0x4000000       /* XSAVE, XRESTOR, XSETVB, XGETBV */
#define CPUID_ECX_OSXSAVE       0x8000000       /* XSAVE Enabled By OS */
#define CPUID_ECX_AVX           0x10000000      /* Advanced Vector Extensions */
#define CPUID_ECX_F16C          0x20000000      /* F16C (Half-Precision) FP Support */
#define CPUID_ECX_RDRAND        0x40000000      /* On-Chip RDRAND Support */
#define CPUID_ECX_HYPERVISOR    0x80000000      /* Running On A Hypervisor */

#define CPUID_EDX_FPU           0x1             /* Onboard x87 FPU */
#define CPUID_EDX_VME           0x2             /* Virtual 8086 Extensions */
#define CPUID_EDX_DE            0x4             /* Debugging Extensions */
#define CPUID_EDX_PSE           0x8             /* Page Size Extension */
#define CPUID_EDX_TSC           0x10            /* Time Stamp Counter */
#define CPUID_EDX_MSR           0x20            /* Model-Specific Registers */
#define CPUID_EDX_PAE           0x40            /* Physical Address Extension */
#define CPUID_EDX_MCE           0x80            /* Machine Check Exception */
#define CPUID_EDX_CX8           0x100           /* CMPXCHG8 Instruction */
#define CPUID_EDX_APIC          0x200           /* Onboard APIC Controller */
#define CPUID_EDX_SEP           0x800           /* SYSENTER and SYSEXIT Instructions */
#define CPUID_EDX_MTRR          0x1000          /* Memory Type Range Registers */
#define CPUID_EDX_PGE           0x2000          /* Paging Global Enabled */
#define CPUID_EDX_MCA           0x4000          /* Machine Check Architecture */
#define CPUID_EDX_CMOV          0x8000          /* Conditional Move and FCMOV */
#define CPUID_EDX_PAT           0x10000         /* Page Attribute Table */
#define CPUID_EDX_PSE36         0x20000         /* 36-bit Page Size Extension */
#define CPUID_EDX_PSN           0x40000         /* Processor Serial Number */
#define CPUID_EDX_CLF           0x80000         /* CLFLUSH Instruction */
#define CPUID_EDX_DTES          0x200000        /* Debug Store */
#define CPUID_EDX_ACPI          0x400000        /* Onboard Thermal Control MSRs for ACPI */
#define CPUID_EDX_MMX           0x800000        /* MMX Instructions */
#define CPUID_EDX_FXSR          0x1000000       /* FXSAVE, FXRESTOR */
#define CPUID_EDX_SSE           0x2000000       /* SSE Instructions */
#define CPUID_EDX_SSE2          0x4000000       /* SSE2 Instructions */
#define CPUID_EDX_SS            0x8000000       /* CPU Cache Supports Self-Snoop */
#define CPUID_EDX_HTT           0x10000000      /* Hyperthreading */
#define CPUID_EDX_TM1           0x20000000      /* Automatic CPU Throttling */
#define CPUID_EDX_IA64          0x40000000      /* IA64 Processor Emulating x86 */
#define CPUID_EDX_PBE           0x80000000      /* Pending Break Enable Wakeup Support */

/** Returns a null terminated string containing the name of the CPU vendor
 */
const char* cpuid_getVendor( );

/** Returns all CPU features listed in the ECX register
 */

uint32 cpuid_getECXFeatures( );

/** Returns all CPU features listed in the EDX register
 */

uint32 cpuid_getEDXFeatures( );

/** Returns true if the listed feature exists in the ECX register
 */

bool cpuid_existsECX( uint32 nFeature );

/** Returns true if the listed feature exists in the EDX register
 */

bool cpuid_existsEDX( uint32 nFeature );

#endif
