#include <winsock2.h>
#include <ws2tcpip.h>
#include <filesystem>
#include <iostream>
#include <cstring>
#include <fstream>
#include "include/fileService.h"
#include "include/sever.h"
#include "include/file.h"
using namespace std;
#pragma comment(lib, "ws2_32.lib")



int main()
{
    Sever sever;
    sever.run();
    return 0;
}