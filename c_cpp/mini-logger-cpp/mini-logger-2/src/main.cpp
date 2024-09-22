#include "logger.h"

int main()
{
    LFATAL(1, "hello world\n");

    LWARN(false, "sup ", "mo fo\n");
    LWARN(true, "hello ", 324, "\n");

    Logger::ChangeOutputType(OutputType::ALL, "log-test-2.txt");

    LINFO(false, "DOOM ENGINE v0\n");

    LINFO(false, "this will not work.\n");
    LFATAL("AAAAAAAAAAAAAAAAAAA|\n");
    LDEBUG(true, "debug debug\n");

    LWARN(true, "sup", " mo fo again\n");

    LINFO(false, "info info info.\n");

    LINFO(true, "this will show up\n");
    LDEBUG(true, "this will not show up\n");
    LERROR(true, "this will not show up either\n");
}