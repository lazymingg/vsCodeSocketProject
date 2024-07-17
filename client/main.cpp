#include <winsock2.h>
#include <ws2tcpip.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "include/fileService.h"
#include "include/client.h"
using namespace std;
#pragma comment(lib, "ws2_32.lib")

int main()
{
    Client client;
    client.run();
}
