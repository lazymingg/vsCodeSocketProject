#include "../include/sever.h"


using namespace std;
using namespace chrono;
Sever::Sever()
{
    // Khởi tạo Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "WSAStartup failed" << std::endl;
        exit(1);
    }

    // Tạo một socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        exit(1);
    }

    // Gán địa chỉ cho socket
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cerr << "Bind failed" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        exit(1);
    }

    // Lắng nghe các kết nối từ client
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cerr << "Listen failed" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        exit(1);
    }

    std::cout << "Server is listening on port 8080..." << std::endl;
}

Sever ::~Sever()
{
    closesocket(serverSocket);
    WSACleanup();
}





void HandleClient(SOCKET ClientSocket)
{
    int iResult;

    Controller controller(ClientSocket);
    controller.run();


    // check if the client has shut down the connection
    iResult = recv(ClientSocket, (char*)&iResult, sizeof(iResult), 0);
    if (iResult == 0)
	{
		std::cerr << "Connection closed by client" << std::endl;
		closesocket(ClientSocket);
		return;
	}
    // Shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        return;
    }

    // Cleanup
    closesocket(ClientSocket);
}


void Sever::run()
{
    vector<thread> clientThreads;
    mutex clientThreadsMutex;

    while (true)
    {
        clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET)
        {
            std::cerr << "Accept failed" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            exit(1);
        }

        cout << "Client connected" << endl;

        lock_guard<mutex> lock(clientThreadsMutex);
        clientThreads.push_back(thread(HandleClient, clientSocket));
    }
}