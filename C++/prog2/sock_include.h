#ifndef SOCK_INC
#define SOCK_INC

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using std::thread;
using namespace this_thread;
using namespace chrono;

#define END return 0

#endif