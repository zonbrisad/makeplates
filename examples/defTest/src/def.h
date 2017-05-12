/**
 * -----------------------------------------------------------------
 * @file  def.h
 * @brief Makeplate common definitions file.
 *
 *
 * @author Peter Malmberg <peter.malmberg@gmail.com>
 *
 * License MIT
 * -----------------------------------------------------------------
 */

// Includes ---------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


#ifndef DEF_H_
#define DEF_H_



// Types ------------------------------------------------------------------
#ifndef bool
typedef uint8_t bool;
#endif

typedef signed char         schar;
typedef unsigned char       uchar;
typedef unsigned int        uint;
typedef unsigned short      ushort;
typedef unsigned long       ulong;


#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif


#ifndef ulong
#define ulong uint32_t
#endif
 

// Type min/max -------------------------------------------------------------

#ifndef MINSCHAR
#define MINSCHAR       ((schar)(-MAXSCHAR - 1))   ///< Signed character min value.
#endif
#ifndef MAXSCHAR
#define MAXSCHAR       ((schar)127)               ///< Signed character max value.
#endif

#ifndef MINUCHAR
#define MINUCHAR       ((uchar)0)                 ///< Unsigned character min value.
#endif
#ifndef MAXUCHAR
#define MAXUCHAR       ((uchar)255)               ///< Unsigned character max value.
#endif

#ifndef MINCHAR
#define MINCHAR        ((char)0)                  ///< Character min value (assuming unsigned).
#endif
#ifndef MAXCHAR
#define MAXCHAR        ((char)255)                ///< Character max value (assuming unsigned).
#endif

#ifndef MINSSHORT
#define MINSSHORT      ((short)(-MAXSSHORT - 1))  ///< Signed short integer min value.
#endif
#ifndef MAXSSHORT
#define MAXSSHORT      ((short)32767)             ///< Signed short integer max value.
#endif

#ifndef MINUSHORT
#define MINUSHORT      ((ushort)0)                ///< Unsigned short integer min value.
#endif
#ifndef MAXUSHORT
#define MAXUSHORT      ((ushort)65535)            ///< Unsigned short integer max value.
#endif

#ifndef MINSHORT
#define MINSHORT       ((short)(-MAXSHORT - 1))   ///< Short integer min value.
#endif
#ifndef MAXSHORT
#define MAXSHORT       ((short)32767)             ///< Short integer max value.
#endif

#ifndef MINSINT
#define MINSINT        ((int)(-MAXSINT - 1))      ///< Signed integer min value.
#endif
#ifndef MAXSINT
#define MAXSINT        ((int)2147483647)          ///< Signed integer max value.
#endif

#ifndef MINUINT
#define MINUINT        ((uint)0)                  ///< Unsigned integer min value.
#endif
#ifndef MAXUINT
#define MAXUINT        ((uint)4294967295)         ///< Unsigned integer max value.
#endif

#ifndef MININT
#define MININT         ((int)(-MAXINT - 1))       ///< Integer min value.
#endif
#ifndef MAXINT
#define MAXINT         ((int)2147483647)          ///< Integer max value.
#endif

#ifndef MINSLONG
#define MINSLONG       ((long)(-MAXSLONG - 1L))   ///< Signed long integer min value.
#endif
#ifndef MAXSLONG
#define MAXSLONG       ((long)2147483647)         ///< Signed long integer max value.
#endif

#ifndef MINULONG
#define MINULONG       ((ulong)0)                 ///< Unsigned long integer min value.
#endif
#ifndef MAXULONG
#define MAXULONG       ((ulong)4294967295)        ///< Unsigned long integer max value.
#endif

#ifndef MINLONG
#define MINLONG        ((long)(-MAXLONG - 1L))    ///< Long integer min value.
#endif
#ifndef MAXLONG
#define MAXLONG        ((long)2147483647)         ///< Long integer max value.
#endif


#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#undef  MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

#undef  MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

#undef  ABS
#define ABS(a)     (((a) < 0) ? -(a) : (a))

#undef  CLAMP
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#undef  isWithin
#define isWithin(val, min, max) ((val>=min) && (val<=max))

#undef  isOutside
#define isOutside(val, min, max) (!isWithin(val, min, max))

#ifndef NULL
#define NULL            (void)0
#endif

// Bit manipulation ---------------------------------------------------------

#define BIT_IS_SET(v, bit)   ((v) & (bit))
#define BIT_IS_CLEAR(v, bit) !(BIT_IS_SET(v, bit))

#define BIT_SET(v, bit)      ((v) |= (bit))
#define BIT_CLEAR(v, bit)    ((v) &= ~(bit))

// Special character definitions --------------------------------------------

#define NUL             0
#define SOH             1
#define STX             2
#define ETX             3
#define EOT             4
#define ENQ             5
#define ACK             6
#define BEL             7
#define BS              8
#define HT              9
#define LF              10
#define VT              11
#define FF              12
#define CR              13
#define SO              14
#define SI              15
#define DLE             16
#define DC1             17
#define DC2             18
#define DC3             19
#define DC4             20
#define NAK             21
#define SYN             22
#define ETB             23
#define CAN             24
#define EM              25
#define SUB             26
#define ESC             27
#define FS              28
#define GS              29
//#define RS            30
//#define US              31


//  Unix Signal signals -------------------------------------------------

#define SIGHUP          1       // Hangup
#define SIGINT          2       // Interrupt
#define SIGQUIT         3       // Quit and dump core
#define SIGILL          4       // Illegal instruction
#define SIGTRAP         5       // Trace/breakpoint trap
#define SIGABRT         6       // Process aborted
#define SIGBUS          7       // Bus error: "access to undefined portion of memory object"
#define SIGFPE          8       // Floating point exception: "erroneous arithmetic operation"
#define SIGKILL         9       // Kill (terminate immediately)
#define SIGUSR1         10      // User-defined 1
#define SIGSEGV         11      // Segmentation violation
#define SIGUSR2         12      // User-defined 2
#define SIGPIPE         13      // Write to pipe with no one reading
#define SIGALRM         14      // Signal raised by alarm
#define SIGTERM         15      // Termination (request to terminate)
#define SIGCHLD         17      // Child process terminated, stopped (or continued*)
#define SIGCONT         18      // Continue if stopped
#define SIGSTOP         19      // Stop executing temporarily
#define SIGTSTP         20      // Terminal stop signal
#define SIGTTIN         21      // Background process attempting to read from tty ("in")
#define SIGTTOU         22      // Background process attempting to write to tty ("out")
#define SIGURG          23      // Urgent data available on socket
#define SIGXCPU         24      // CPU time limit exceeded
#define SIGXFSZ         25      // File size limit exceeded
#define SIGVTALRM       26      // Signal raised by timer counting virtual time: "virtual timer expired"
#define SIGPROF         27      // Profiling timer expired
//#define SIGPOLL         29      // Pollable event
#define SIGSYS          31      // Bad syscall


// ANSI color codes ---------------------------------------------------------

#define E_OK            "\033[0;32m"
#define E_WARN          "\033[33;01m"
#define E_ERROR         "\033[31;01m"

#define E_BLACK         "\033[0;300m"
#define E_RED           "\033[0;31m"
#define E_GREEN         "\033[0;32m"
#define E_YELLOW        "\033[0;33m"
#define E_BLUE          "\033[0;34m"
#define E_MAGENTA       "\033[0;35m"
#define E_CYAN          "\033[0;36m"
#define E_GRAY          "\033[0;37m"
#define E_DARKGRAY      "\033[1;30m"
#define E_BR_RED        "\033[1;31m"
#define E_BR_GREEN      "\033[1;32m"
#define E_BR_YELLOW     "\033[1;33m"
#define E_BR_BLUE       "\033[1;34m"
#define E_BR_MAGENTA    "\033[1;35m"
#define E_BR_CYAN       "\033[1;36m"
#define E_WHITE         "\033[1;37m"

#define E_ON_BLACK      "\033[40m"
#define E_ON_RED        "\033[41m"
#define E_ON_GREEN      "\033[42m"
#define E_ON_YELLOW     "\033[43m"
#define E_ON_BLUE       "\033[44m"
#define E_ON_MAGENTA    "\033[45m"
#define E_ON_CYAN       "\033[46m"
#define E_ON_WHITE      "\033[1;47m"

// ANSI Text attributes
#define E_ATTR_BOLD      "\e[1m"
#define E_ATTR_LOWI      "\e[2m"
#define E_ATTR_UNDERLINE "\e[4m"
#define E_ATTR_BLINK     "\e[5m"
#define E_ATTR_REVERSE   "\e[7m"


#define E_END           "\033[0m"
#define E_CLEAR         "\033[2J"
#define E_RESET         "\033c"

#define E_WONR "\33[1;47\033[1;31m"

// ANSI movement codes ------------------------------------------------------

#define E_CUR_RETURN  "\033[;0F"      // cursor return
#define E_CUR_UP      "\033[;0A"      // cursor up
#define E_CUR_DOWN    "\033[;0B"      // cursor down
#define E_CUR_FORWARD "\033[;0C"      // cursor forward
#define E_CUR_BACK    "\033[;0D"      // cursor back

#define E_HIDE_CURSOR "\033[?25l"     // hide cursor
#define E_SHOW_CURSOR "\033[?25h"     // show cursor


// Debugging ----------------------------------------------------------------

// Filename without path
//#define FILEX (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define WHEREARG  __LINE__, __FUNCTION__
#define DEBUGPRINT2(...)       fprintf(stderr, __VA_ARGS__)

#ifdef DEBUGPRINT
#undef DEBUGPRINT
#define DEBUGSTR  E_BR_GREEN"DBG  "E_WHITE"%4d"E_BR_CYAN" %-25s"E_END": "
#define DEBUGPRINT(_fmt, ...)  DEBUGPRINT2(DEBUGSTR _fmt, WHEREARG, ##__VA_ARGS__)
#define DEBUGPRINT_COND(cond, _fmt, ...) if (cond) DEBUGPRINT2(DEBUGSTR _fmt, WHEREARG, ##__VA_ARGS__)
#define DEBUG_DO(f) f
#else
#define DEBUGPRINT(_fmt, ...)
#define DEBUGPRINT_COND(cond, _fmt, ...)
#define DEBUG_DO(f)
#endif

#ifdef ERRORPRINT
#undef ERRORPRINT
#define ERRORSTR  E_BR_RED"ERR  "E_WHITE"%4d"E_BR_CYAN" %-25s"E_END": "
#define ERRORPRINT(_fmt, ...)  DEBUGPRINT2(ERRORSTR _fmt, WHEREARG, ##__VA_ARGS__)
#define ERRORPRINT_COND(cond, _fmt, ...)  if (cond) DEBUGPRINT2(ERRORSTR _fmt, WHEREARG, ##__VA_ARGS__)
#define ERROR_DO(f) f
#else
#define ERRORPRINT(_fmt, ...)
#define ERRORPRINT_COND(cond, _fmt, ...)
#define ERROR_DO(f)
#endif

#ifdef WARNINGPRINT
#undef WARNINGPRINT
#define WARNINGSTR  E_BR_YELLOW"WARN "E_WHITE"%4d"E_BR_CYAN" %-25s"E_END": "
#define WARNINGPRINT(_fmt, ...)  DEBUGPRINT2(WARNINGSTR _fmt, WHEREARG, ##__VA_ARGS__)
#define WARNINGPRINT_COND(cond, _fmt, ...) if (cond) DEBUGPRINT2(WARNINGSTR _fmt, WHEREARG, ##__VA_ARGS__)
#define WARNING_DO(f) f
#else
#define WARNINGPRINT(_fmt, ...)
#define WARNINGPRINT_COND(cond, _fmt, ...)
#define WARNING_DO(f)
#endif

#ifdef INFOPRINT
#undef INFOPRINT
#define INFOSTR  E_BR_BLUE"INFO "E_WHITE"%4d"E_BR_CYAN" %-25s"E_END": "
#define INFOPRINT(_fmt, ...) DEBUGPRINT2(INFOSTR _fmt, WHEREARG, ##__VA_ARGS__)
#define INFOPRINT_COND(cond, _fmt, ...) if (cond) DEBUGPRINT2(INFOSTR _fmt, WHEREARG, ##__VA_ARGS__)
#define INFO_DO(f) f
#else
#define INFOPRINT(_fmt, ...)
#define INFOPRINT_COND(cond, _fmt, ...)
#define INFO_DO(f)
#endif

#ifdef FATALPRINT
#undef FATALPRINT
#define FATALSTR  "\n\n\n"E_BR_RED"############### FATAL ERROR ###############"E_WHITE"%4d"E_BR_CYAN" %-25s"E_END": "
#define FATALPRINT(_fmt, ...) DEBUGPRINT2(INFOSTR _fmt, WHEREARG, ##__VA_ARGS__)
#define FATALPRINT_COND(cond, _fmt, ...) if (cond) DEBUGPRINT2(FATALSTR _fmt, WHEREARG, ##__VA_ARGS__)
#define FATAL_DO(f) f
#else
#
#define FATALPRINT(_fmt, ...)
#define FATALPRINT_COND(cond, _fmt, ...)
#define FATAL_DO(f)
#endif





// Misc ---------------------------------------------------------------------

// For removing unused variable/parameter warning from compiler output
#define UNUSED_PARAM(p)		(void)p
#define UNUSED(p)         UNUSED_PARAM(p)


// Create a string from a definition
#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)


#endif	/* DEF_H */

