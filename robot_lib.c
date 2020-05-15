//MinGW will not compile unless windows version flag is manually set.
#if defined __MINGW32__ || defined __MINGW64__
#define _WIN32_WINNT 0x0600
#endif

#include "robot_lib.h"
#include <time.h>

#ifdef __linux__
int sock = 0;
#elif defined __WIN32__ || defined _WIN32
SOCKET sock = 0;
#endif

/*
 * The three functions below are intended for internal use only, and not exposed in robot_lib.h
 */
/* Automatic opens browser to right link */
void auto_redirect(char *buf)
{

    char temp[BUFFER_SIZE] = "\0";


    for(int i = 0; i < BUFFER_SIZE; i++)
    {

        if( buf[i] == ' ')
        {

            for(int z = i; z <= BUFFER_SIZE; z++)
            {
                buf[z] = '\0';
            }

            strcpy(temp,"START ");
            strcat(temp,buf);
            printf("%s", temp);
            system(temp);

            return;
        }

    }

}



int robot_lib_ready_read()
{

#ifdef __linux__
	int count;
	ioctl(sock, FIONREAD, &count);
#elif defined __WIN32__ || defined _WIN32
	unsigned long count;
	ioctlsocket(sock, FIONREAD, &count);
#endif
	return count;
}

int robot_lib_read(char* out, int size)
{
#ifdef __linux__
	int count = read(sock, out, size);
#elif defined __WIN32__ || defined _WIN32
	int count = recv(sock, out, size, 0);
#endif
	if (count != size)
	{
		printf("\nSimulator: read Failed \n");
		return SIMULATOR_ERROR;
	}
	else
	{
		return SIMULATOR_OK;
	}
}

int robot_lib_write(char* in, int size)
{
	if (send(sock, in, size, 0) != size)
	{
		printf("\nSimulator: write Failed \n");
		return SIMULATOR_ERROR;
	}
	else
	{
		return SIMULATOR_OK;
	}
}


/*
 * Accepts buffer, a maximum buffer size, and a delimiter character.
 * Returns number of characters read.
 * WILL BLOCK!  Intended to be used in scenarios when we want to wait for data anyway.
 */
int read_until_delim(char* buf, int bufsize, char delim)
{
	if (bufsize < 2) return SIMULATOR_ERROR;
	int count = 0;
	char latest = 0;
	do
	{
		//will block until byte read
		robot_lib_read_byte(&latest);
		buf[count] = latest;
		count++;
	} while (latest != delim && count < bufsize - 1);
	buf[count] = 0; //null terminator :)
	return count;
}

/*
 * param: Accepts an array of stations to visit CURRENTLY REQUIRED TO BE 3
 * Returns:SIMULATOR_ERROR if initialization fails.
 */
int robot_lib_get_init_data(int* visit)
{
	char buf[BUFFER_SIZE];

	//This will be the link.
	if (read_until_delim(buf, BUFFER_SIZE, ROB_DELIM) == SIMULATOR_ERROR) return SIMULATOR_ERROR;
	printf("\n%s", buf);

    auto_redirect(buf);

	//This will be a list of targets.
	if (read_until_delim(buf, BUFFER_SIZE, ROB_DELIM) == SIMULATOR_ERROR ||
	    (sscanf(buf, "%d %d %d", &visit[0], &visit[1], &visit[2]) != 3))
		return SIMULATOR_ERROR;

	printf("Visiting stations %d, %d, %d\n", visit[0], visit[1], visit[2]);

	return SIMULATOR_OK;
}

/*
  Connect to the server
  returns: SIMULATOR_OK if connection succeeded, SIMULATOR_ERROR if not.
  After return, stations will contain the three stations to visit.
*/
int robot_lib_connect(char* ip, int* stations, char challenge, char* seed)
{
	int gen_seed = 0;
	struct sockaddr_in serv_addr;
	if (ip == NULL) ip = SIMULATOR_IP_ADDRESS;
	//Use current timestamp as seed if you just want a random seed.
	if(seed == NULL)
	{
		gen_seed = 1;
		time_t t;

		//Below line really does need sizeof multiplication, but this throws lint errors
		seed = malloc(sizeof(time_t) * sizeof(char) +1); // NOLINT
		sprintf(seed, "%ld", time(&t));
	}
#if defined __WIN32__ || defined _WIN32
	WSADATA winsockdata;
	int errornum;
	if ((errornum = WSAStartup(MAKEWORD(2, 2), &winsockdata)) != 0)
	{
		printf("\nWinsock not initialized, error number %d\n", errornum);
	}
#endif

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\nSimulator: socket creation error.\n");
		return SIMULATOR_ERROR;
	}

	struct addrinfo* result;
	int res;
	if ((res = getaddrinfo(ip, SIMULATOR_PORT_STR, NULL, &result)))
	{
		printf("\nFailure finding address info, error = %d\n", res);
		return SIMULATOR_ERROR;
	}
	char stuff[256];
	getnameinfo(result->ai_addr, result->ai_addrlen, stuff, sizeof(stuff), NULL, 0, NI_NUMERICHOST);
	printf("\n address is %s\n", stuff);
	if ((res = connect(sock, result->ai_addr, result->ai_addrlen)))
	{
		printf("Failure making connection, error = %d\n", res);
		return SIMULATOR_ERROR;
	}
	char final[BUFFER_SIZE];
	final[0] = challenge;
	final[1] = 0;
	strcat(final, seed);
	strcat(final, "\n");
	robot_lib_write(final, (int) strlen(final));
	if (gen_seed) free(seed);
	return robot_lib_get_init_data(stations);
}

/*
 * Cleanly closes the active socket (will terminate connection to the server).
 */
int robot_lib_disconnect()
{
	int errnum;
	#ifdef __linux__
	if((errnum = close(sock)))
	{
		printf("Error %d closing socket!\n", errnum);
		return SIMULATOR_ERROR;
	}
	#elif defined __WIN32__ || defined _WIN32
	if((errnum = shutdown(sock, SD_BOTH)))
	{
		printf("Error %d shutting socket down, attempting to continue\n", errnum);
	}
	if((errnum = closesocket(sock)))
	{
		printf("Error %d closing socket, attempting to continue to WSA shutdown\n", errnum);
	}
	if((errnum = WSACleanup()))
	{
		printf("Error %d on WSACleanup, this shouldn't happen unless you called this twice in a row.\n", errnum);
		return SIMULATOR_ERROR;
	}
	#endif
	return SIMULATOR_OK;
}


/*
  Write a single character to the socket
*/
int robot_lib_write_byte(char in)
{
	return robot_lib_write(&in, 1);
}

/*
 * Checks to see if (at least) one byte is ready to be read from the socket, and returns SIMULATOR_OK if so.
 * This function will not block.
 */
int robot_lib_ready_read_byte()
{
	return robot_lib_ready_read() > 0 ? SIMULATOR_OK : SIMULATOR_ERROR;
}

/*
  Read a single character from the socket.  This function will block (wait) if no data is available.
*/

int robot_lib_read_byte(char* out)
{
	return robot_lib_read(out, 1);
}
