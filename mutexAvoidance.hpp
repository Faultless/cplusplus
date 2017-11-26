#include <iostream>
#include <map>
#include <thread>

using namespace std;

class MutexAvoidance {
private:
    int nT, nR;
    pthread_mutex_t *mutexes;
    map<int, int> maximumRequests;
public:
    MutexAvoidance(int, int, map<int, int>);
    void requestNormal(int);
    void releaseNormal(int);
};