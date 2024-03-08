#include "header.h"

int main() {
    // initialize the variables
    Tasks tasks[20];
    int totalTasks = 0;
    int currentTask = 0;
    Workers workers[20];
    int totalWorkers = 0;
    int currentWorker = 0;

    // run the program in sequence
    tasksInData(tasks, totalTasks);
    workersInData(workers, totalTasks);
    workerPerformance(tasks, currentTask, workers, currentWorker);
    writeData(tasks, totalTasks, workers, totalWorkers);

    return 0;
}
