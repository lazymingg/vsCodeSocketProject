#ifndef FILESERVICE_H
#define FILESERVICE_H

// Include any necessary libraries or headers
#include <fstream>
#include <cstring>
#include <iostream>
#include <filesystem>
#include <cstdint>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include "file.h"
#include <vector>
namespace fs = std::filesystem;
using namespace std;

// Declare your functions or classes here
class FileService
{
    private:
    vector<File> fileArr;
public:
    FileService();
    ~FileService();
    void setFileArr();
    void sendFileArr(SOCKET clientSocket);
    char *serializeFileArr(int &buffer_size);
    void receiveFileArr(SOCKET serverSocket);
    vector<File> deserializeFileArr(char *buffer, int buffer_size);
    vector<File> getFileArr();

};
#endif // FILESERVICE_H