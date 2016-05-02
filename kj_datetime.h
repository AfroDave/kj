// `kj_datetime.h`
// public domain - no offered or implied warranty, use at your own risk

#ifndef KJ_DATETIME_H
#define KJ_DATETIME_H

#define KJ_DATETIME_VERSION_MAJOR 0
#define KJ_DATETIME_VERSION_MINOR 1
#define KJ_DATETIME_VERSION_PATCH 0

#define KJ_DATETIME_UTC_ISO_FMT "%04d-%02d-%02dT%02d:%02d:%02dZ"
#define KJ_DATETIME_LOCAL_ISO_FMT "%04d-%02d-%02dT%02d:%02d:%02d%c%02d:%02d"
#define KJ_DATETIME_UTC_EXPAND(dt)                                              \
    (dt)->year, (dt)->month, (dt)->day, (dt)->hour, (dt)->minute, (dt)->second
#define KJ_DATETIME_LOCAL_EXPAND(dt)                                            \
    (dt)->year, (dt)->month, (dt)->day, (dt)->hour, (dt)->minute, (dt)->second, \
    (dt)->tz < 0 ? '-': '+', kj_abs(((dt)->tz / 60)), kj_abs(((dt)->tz % 60))

typedef struct kjDateTime {
    i16 year;
    i16 month;
    i16 day;
    i16 hour;
    i16 minute;
    i16 second;
    i16 millisecond;
    i16 tz;
} kjDateTime;

#if defined(__cplusplus)
extern "C" {
#endif

KJ_API kjDateTime kj_datetime_utc(void);
KJ_API kjDateTime kj_datetime_local(void);

KJ_API u64 kj_time_ms(void);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_DATETIME_IMPLEMENTATION)

#if defined(KJ_SYS_WIN32)

#include <windows.h>

kjDateTime kj_datetime_utc(void) {
    kjDateTime res;
    SYSTEMTIME st = {0};
    GetSystemTime(&st);
    res.year = st.wYear;
    res.month = st.wMonth;
    res.day = st.wDay;
    res.hour = st.wHour;
    res.minute = st.wMinute;
    res.second = st.wSecond;
    res.millisecond = st.wMilliseconds;
    res.tz = 0;
    return res;
}

kjDateTime kj_datetime_local(void) {
    kjDateTime res;
    SYSTEMTIME st = {0};
    GetLocalTime(&st);
    TIME_ZONE_INFORMATION tz = {0};
    switch(GetTimeZoneInformation(&tz)) {
        case 0: {
            res.tz = cast_of(i16, tz.Bias);
        } break;
        case 1: {
            res.tz = cast_of(i16, tz.StandardBias);
        } break;
        case 2: {
            res.tz = cast_of(i16, tz.DaylightBias);
        } break;

    }
    res.year = st.wYear;
    res.month = st.wMonth;
    res.day = st.wDay;
    res.hour = st.wHour;
    res.minute = st.wMinute;
    res.second = st.wSecond;
    res.millisecond = st.wMilliseconds;
    return res;
}

internal u64 kj_time_freq(void) {
    static b32 has_freq = false;
    static LARGE_INTEGER freq = {0};
    if(!has_freq) {
        QueryPerformanceFrequency(&freq);
        has_freq = true;
    }
    return cast_of(u64, freq.QuadPart);
}

internal u64 kj_time(void) {
    static b32 has_base = false;
    static LARGE_INTEGER base = {0};
    if(!has_base) {
        QueryPerformanceCounter(&base);
        has_base = true;
    }
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return (counter.QuadPart - base.QuadPart);
}

u64 kj_time_ms(void) {
    return (kj_time() * 1000) / kj_time_freq();
}

#elif defined(KJ_SYS_LINUX)

#include <time.h>

kjDateTime kj_datetime_utc(void) {
    kjDateTime res;
    time_t time;
    time(&time);
    struct tm* tm = gmtime(&time);
    res.year = 1900 + tm->tm_year;
    res.month = tm->tm_mon + 1;
    res.day = tm->tm_mday;
    res.hour = tm->tm_hour;
    res.minute = tm->tm_min;
    res.second = tm->tm_sec;
    res.millisecond = 0;
    res.tz = 0;
    return res;
}

kjDateTime kj_datetime_local(void) {
    kjDateTime res;
    time_t time;
    time(&time);
    struct tm* tm = localtime(&time);
    res.year = 1900 + tm->tm_year;
    res.month = tm->tm_mon + 1;
    res.day = tm->tm_mday;
    res.hour = tm->tm_hour;
    res.minute = tm->tm_min;
    res.second = tm->tm_sec;
    res.millisecond = 0;
    return res;
}

u64 kj_time_ms(void) {
    static b32 has_base = false;
    static struct timespec base = {0};
    if(!has_base) {
        clock_gettime(CLOCK_MONOTONIC, &base);
        has_base = true;
    }
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ((ts.tv_sec + ts.tv_nsec) - (base.tv_sec + base.tv_nsec)) / 1000000;
}

#else
#error KJ_DATETIME_UNSUPPORTED
#endif

#endif
