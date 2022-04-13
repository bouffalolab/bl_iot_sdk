#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <openthread-core-config.h>
#include <openthread/config.h>
#include <openthread/platform/logging.h>
#include <openthread/platform/toolchain.h>
#include <openthread/cli.h>

void otPlatLog(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aFormat, ...)
{
    va_list ap;
    va_start(ap, aFormat);
    otCliPlatLogv(aLogLevel, aLogRegion, aFormat, ap);
    va_end(ap);
}

void otPlatLogLine(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aLogLine)
{
    otPlatLog(aLogLevel, aLogRegion, "%s\r\n", aLogLine);
}
