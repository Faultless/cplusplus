#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <sys/wait.h>
#include <sys/signal.h>
#include <unistd.h>
#include "mutexAvoidance.hpp"

using namespace std;

void * t0(void * param) {
    MutexAvoidance * m = (MutexAvoidance *) param;
    m->requestNormal(1);
    m->requestNormal(0);
    m->releaseNormal(1);
    m->releaseNormal(0);
}

void * t1(void * param) {
    MutexAvoidance * m = (MutexAvoidance *) param;
    m->requestNormal(0);
    m->requestNormal(1);
    m->releaseNormal(0);
    m->releaseNormal(1);
}

/**
 * Spawns n threads
 */
void spawnThreads(int nT)
{
    thread threads[nT];
    // spawn n threads
    for (int i = 0; i < nT; i++) {
        if(i == 0) threads[i] = thread(t0);
        else if(i == 1) threads[i] = thread(t1);
    }

    // main program waits for all threads to finish
    for (auto& th : threads) {
        th.join();
    }
}

union intMap {
    int nT;
    int nR;
    map<int, int> maxRequests;
};

int main(int argc, char *argv[]) {
    if(argc != 3) {
        cout << "usage: " << argv[0] << "<numberOfThreads> <numberOfMutexes>";
    }
    else {

        int nT = atoi(argv[1]);
        int nR = atoi(argv[2]);

        map<int, int> maxRequests;
        maxRequests[1] = 1;
        maxRequests[2] = 1;

        spawnThreads(nT);
        vector<intMap *> param;

        param.push_back(nT);
    }
    
}