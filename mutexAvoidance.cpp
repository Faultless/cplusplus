#include <map>
#include <thread>
#include "mutexAvoidance.hpp"

using namespace std;

pthread_mutex_t *createMutexes(int nR) {
    pthread_mutex_t mutexes[nR];

    for(int i = 0; i < nR; i++) {
        mutexes[i] = PTHREAD_MUTEX_INITIALIZER;
    }

    return mutexes;
}

MutexAvoidance::MutexAvoidance(int numThread, int numRequest, map<int, int> maxRequests) {
    nT = numThread;
    nR = numRequest;
    mutexes = createMutexes(nR);
    maximumRequests = maxRequests;
}

void MutexAvoidance::requestNormal(int mutexId) {
    pthread_mutex_lock(&mutexes[mutexId]);
}

void MutexAvoidance::releaseNormal(int mutexId) {
    pthread_mutex_unlock(&mutexes[mutexId]);
}