#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <string>

using namespace std;

// store tasks' information
struct Tasks {
    int taskId;
    string description;
    int uncertainty;
    int difficulty;
    int workersIdList[20];      // maximum workers assigned to each task is 20
    int currentAssignedWorker;
    string literalStr;          // 'workers' string
};

// store workers' information
struct Workers {
    int workerId;
    string name;
    int variability;
    int ability;
};

// read the file "Tasks.txt"
void tasksInData(Tasks tasks[], int& totalTasks);

// read the file "Workers.txt"
void workersInData(Workers workers[], int& totalWorkers);

// calculate worker performance and his/her average performance
int workerPerformance(Tasks tasks[], int currentTask, Workers workers[], int currentWorker);

// output
void writeData(Tasks tasks[], int totalTasks, Workers workers[], int totalWorkers);

#endif // HEADER_H_INCLUDED
