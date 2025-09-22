#include <list>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/socket.h>
#include <malloc.h>
#include <math.h>
#include <sys/stat.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <locale>
#include <string>
#include <codecvt>
#include <cassert>
#include "oxorany.hpp"
#include <regex>
#include <stdarg.h>

#define _BYTE uint8_t
#define _WORD uint16_t
#define _DWORD uint32_t
#define _QWORD uint64_t

size_t &_lxy_oxor_any_::X()
{
    static size_t x = 0;
    return x;
}

size_t &_lxy_oxor_any_::Y()
{
    static size_t y = 0;
    return y;
}
