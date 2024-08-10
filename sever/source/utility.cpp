#include "../include/utility.h"

bool sendBuffer(SOCKET clientSocket, char *buffer, int buffer_size)
{
    // Send buffer size first
    int result = send(clientSocket, (char *)&buffer_size, sizeof(buffer_size), 0);
    if (result == 0)
    {
        std::cerr << "Connection closed by the peer." << std::endl;
        // Handle connection closure:
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }
    else if (result == SOCKET_ERROR)
    {
        int errorCode = WSAGetLastError();
        std::cerr << "Failed to send data with error: " << errorCode << std::endl;

        // Handle specific error codes
        if (errorCode == WSAEWOULDBLOCK)
        {
            std::cerr << "Non-blocking socket would block, try again later." << std::endl;
        }
        else if (errorCode == WSAECONNRESET)
        {
            std::cerr << "Connection reset by peer." << std::endl;
            // Add reconnection logic here if needed
        }
        else
        {
            std::cerr << "Other error, closing socket." << std::endl;
        }

        // Return false on error
        return false;
    }

    // Now send the actual buffer data
    result = send(clientSocket, buffer, buffer_size, 0);
    if (result == 0)
    {
        std::cerr << "Connection closed by the peer while sending data." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }
    else if (result == SOCKET_ERROR)
    {
        int errorCode = WSAGetLastError();
        std::cerr << "Failed to send data with error: " << errorCode << std::endl;
        if (errorCode == WSAEWOULDBLOCK)
        {
            std::cerr << "Non-blocking socket would block, try again later." << std::endl;
        }
        else if (errorCode == WSAECONNRESET)
        {
            std::cerr << "Connection reset by peer." << std::endl;
        }
        else
        {
            std::cerr << "Other error, closing socket." << std::endl;
        }

        // Return false on error
        return false;
    }

    return true; // Return true if all data was sent successfully
}

bool recvBuffer(SOCKET clientSocket, char* &buffer)
{
    // Nhận kích thước của buffer trước
    int buffer_size = 0;
    int result = recv(clientSocket, (char *)&buffer_size, sizeof(buffer_size), 0);
    if (result == 0)
    {
        std::cerr << "Connection closed by the peer." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }
    else if (result == SOCKET_ERROR)
    {
        int errorCode = WSAGetLastError();
        std::cerr << "Failed to receive data with error: " << errorCode << std::endl;

        // Xử lý các mã lỗi cụ thể
        if (errorCode == WSAEWOULDBLOCK)
        {
            std::cerr << "Non-blocking socket would block, try again later." << std::endl;
        }
        else if (errorCode == WSAECONNRESET)
        {
            std::cerr << "Connection reset by peer." << std::endl;
        }
        else
        {
            std::cerr << "Other error, closing socket." << std::endl;
        }

        return false;
    }
    buffer = new char[buffer_size];
    // Sau khi nhận được kích thước, nhận toàn bộ buffer
    result = recv(clientSocket, buffer, buffer_size, 0);
    if (result == 0)
    {
        std::cerr << "Connection closed by the peer while receiving data." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }
    else if (result == SOCKET_ERROR)
    {
        int errorCode = WSAGetLastError();
        std::cerr << "Failed to receive data with error: " << errorCode << std::endl;

        // Xử lý các mã lỗi cụ thể
        if (errorCode == WSAEWOULDBLOCK)
        {
            std::cerr << "Non-blocking socket would block, try again later." << std::endl;
        }
        else if (errorCode == WSAECONNRESET)
        {
            std::cerr << "Connection reset by peer." << std::endl;
        }
        else
        {
            std::cerr << "Other error, closing socket." << std::endl;
        }

        return false;
    }

    return true; // Trả về true nếu nhận thành công toàn bộ dữ liệu
}
