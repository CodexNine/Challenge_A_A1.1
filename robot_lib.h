#ifndef ROBOT_LIB
#define ROBOT_LIB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#elif defined __WIN32__ || defined _WIN32
#include <winsock2.h>
#include <Ws2tcpip.h>
#endif

#ifdef _MSC_VER
#pragma comment( lib, "ws2_32.lib")
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define SIMULATOR_IP_ADDRESS "epo2srv1.ewi.tudelft.nl"
#define SIMULATOR_PORT_STR "5001"
#define BUFFER_SIZE 1024

#define ROB_DELIM '\n'
#define SIMULATOR_OK 0
#define SIMULATOR_ERROR -1

int robot_lib_connect(char* ip, int* stations, char challenge, char* seed);
int robot_lib_write_byte(char in);
int robot_lib_ready_read_byte();
int robot_lib_read_byte(char* out);
int robot_lib_disconnect();

#endif
