#ifndef _EMBEDDED_DEBUG_LIB_H
#define _EMBEDDED_DEBUG_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* Debug levels */
#define __DEBUG_OFF__               (0x00)
#define __DEBUG_FATAL__             (0x01)
#define __DEBUG_ERROR__             (0x02)
#define __DEBUG_WARN__              (0x04)
#define __DEBUG_INFO__              (0x08)
#define __DEBUG_DBG__               (0x16)
#define __DEBUG_TRACE__             (0x32)
#define __DEBUG_ALL__               (0xFF)

/* Set log level */
#define SET_LOG_LEVEL               (__DEBUG_ALL__)

/* Tags */
#define __FATAL_TAG__               "[F]"
#define __ERROR_TAG__               "[E]"
#define __WARN_TAG__                "[W]"
#define __INFO_TAG__                "[I]"
#define __DBG_TAG__                 "[D]"
#define __TRACE_TAG__               "[T]"


/* Set extra flags */
#define __ENABLE_LINE__             (1)
#define __ENABLE_FUNC__             (1)
#define __ENABLE_COLOR__            (1)

/* Arg presets */
#define LINE_ARG_FMT                "[%u]"
#define FUNC_ARG_FMT                "[%s]"

/* Tag Colors */
#define __FATAL_COLOR__             "\033[1;31m"
#define __ERROR_COLOR__             "\033[0;31m"
#define __WARN_COLOR__              "\033[33m"
#define __INFO_COLOR__              "\033[34m"
#define __DBG_COLOR__               "\033[32m"
#define __TRACE_COLOR__             "\033[0m"


/* Attach debug function like printf ( must support variable args...) */
#define DEBUG_FUNC(...) printf(__VA_ARGS__)
#define DEBUG_LOGGER(COLOR, TAG, ...)               \
    {                                               \
        if (__ENABLE_COLOR__)                       \
        {                                           \
            DEBUG_FUNC(COLOR);                      \
        }                                           \
        DEBUG_FUNC(TAG);                            \
        if (__ENABLE_FUNC__)                        \
        {                                           \
            DEBUG_FUNC(FUNC_ARG_FMT, __FUNCTION__); \
        }                                           \
        if (__ENABLE_LINE__)                        \
        {                                           \
            DEBUG_FUNC(LINE_ARG_FMT, __LINE__);     \
        }                                           \
        DEBUG_FUNC(__VA_ARGS__);                    \
        if (__ENABLE_COLOR__)                       \
        {                                           \
            DEBUG_FUNC(__TRACE_COLOR__);            \
        }                                           \
    }

#if ((SET_LOG_LEVEL > __DEBUG_OFF__) && (SET_LOG_LEVEL >= __DEBUG_FATAL__))
#define DEBUG_FATAL(...) DEBUG_LOGGER(__FATAL_COLOR__, __FATAL_TAG__, __VA_ARGS__)
#else
#define DEBUG_FATAL(...)
#endif

#if ((SET_LOG_LEVEL > __DEBUG_OFF__) && (SET_LOG_LEVEL >= __DEBUG_ERROR__))
#define DEBUG_ERROR(...) DEBUG_LOGGER(__ERROR_COLOR__, __ERROR_TAG__, __VA_ARGS__)
#else
#define DEBUG_ERROR(...)
#endif

#if ((SET_LOG_LEVEL > __DEBUG_OFF__) && (SET_LOG_LEVEL >= __DEBUG_WARN__))
#define DEBUG_WARN(...) DEBUG_LOGGER(__WARN_COLOR__, __WARN_TAG__, __VA_ARGS__)
#else
#define DEBUG_WARN(...)
#endif

#if ((SET_LOG_LEVEL > __DEBUG_OFF__) && (SET_LOG_LEVEL >= __DEBUG_INFO__))
#define DEBUG_INFO(...) DEBUG_LOGGER(__INFO_COLOR__, __INFO_TAG__, __VA_ARGS__)
#else
#define DEBUG_INFO(...)
#endif

#if ((SET_LOG_LEVEL > __DEBUG_OFF__) && (SET_LOG_LEVEL >= __DEBUG_DBG__))
#define DEBUG_DBG(...) DEBUG_LOGGER(__DBG_COLOR__, __DBG_TAG__, __VA_ARGS__)
#else
#define DEBUG_DBG(...)
#endif

#if ((SET_LOG_LEVEL > __DEBUG_OFF__) && (SET_LOG_LEVEL >= __DEBUG_TRACE__))
#define DEBUG_TRACE(...) DEBUG_LOGGER(__TRACE_COLOR__, __TRACE_TAG__, __VA_ARGS__)
#else
#define DEBUG_TRACE(...)
#endif
#endif