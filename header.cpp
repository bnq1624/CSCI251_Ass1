#include "header.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <ctime>

using namespace std;

// read the file "Tasks.txt"
void tasksInData(Tasks tasks[], int& totalTasks) {
    ifstream inData;
    inData.open("Tasks.txt");

    if(inData.fail()) {
        cout << "This file could not be opened." << endl;
        return;
    }

    string line;
    int currentTask = 0;            // access task-by-task
    int currentAssignedWorker = 0;  // access each worker from the list

    // read the input of the input file
    while(currentTask < 20 && getline(inData, line)) {
        istringstream iss(line);    // read inputs stored in 'line' until reach a whitespace
        char delimiter = ',';
        char delimiter1 = ':';

        // read the input of each line
        iss >> tasks[currentTask].taskId >> delimiter;
        getline(iss, tasks[currentTask].description, delimiter);  // description has white space
        iss >> tasks[currentTask].uncertainty >> delimiter
        >> tasks[currentTask].difficulty >> delimiter;
        getline(iss, tasks[currentTask].literalStr, delimiter1);  // read the 'workers' string before delimiter1

        // read the workersIdList
        string str1;
        tasks[currentTask].currentAssignedWorker = 0;

        while(getline(iss, str1, delimiter) && tasks[currentTask].currentAssignedWorker < 20) {
            tasks[currentTask].workersIdList[tasks[currentTask].currentAssignedWorker] = stoi(str1);
            tasks[currentTask].currentAssignedWorker++;
        }

        // total number of assigned workers of each tasks is
        // the final value of currentAssignedWorker after finished the loop
        tasks[currentTask].workersIdList[tasks[currentTask].currentAssignedWorker]= tasks[currentTask].currentAssignedWorker;

        currentTask++;
    }

    // totalTasks is the total number of tasks in file
    totalTasks = currentTask;

    inData.close();
}



// read the workersIdList
void workersInData(Workers workers[], int& totalWorkers) {
    ifstream inData;
    inData.open("Workers.txt");

    if(inData.fail()) {
        cout << "This file could not be opened.";
        return;
    }

    string line;
    int currentWorker = 0;

    while(currentWorker < 20 && getline(inData, line)) {
        istringstream iss(line);
        char delimiter = ',';

        string str;
        getline(iss, str, delimiter);
        workers[currentWorker].workerId = stoi(str);

        getline(iss, workers[currentWorker].name, delimiter);

        getline(iss, str, delimiter);
        workers[currentWorker].variability = stoi(str);

        getline(iss, str, '\n'); // Read until the end of line
        workers[currentWorker].ability = stoi(str);

        currentWorker++;
    }

    totalWorkers = currentWorker;

    inData.close();
}



// calculate worker performance and his/her average performance
int workerPerformance(Tasks tasks[], int currentTask, Workers workers[], int currentWorker) {
    int mean = workers[currentWorker].ability - tasks[currentTask].difficulty;
    int stddev = tasks[currentTask].uncertainty + workers[currentWorker].variability;

    default_random_engine defEng(time(0));
    normal_distribution<double> normal(mean, stddev);

    int totalWorkerPerformance = 0;
    for(size_t draw = 0; draw < 5; draw++) {
        double randomPerformance = normal(defEng);

        // add all of 5 draws to get total
        totalWorkerPerformance += randomPerformance;
    }

    // divide the total by 5 to get the average
    double averagePerformance = totalWorkerPerformance / 5.0;
    int finalAveragePerformance = int(averagePerformance);

    return finalAveragePerformance;
}



// output
void writeData(Tasks tasks[], int totalTasks, Workers workers[], int totalWorkers) {
    ofstream outData;
    outData.open("Output.txt");

    if(outData.fail()) {
        cout << "This file could not be opened." << endl;
        return;
    }

    for(int i = 0; i < totalTasks - 1; i++) {   // totalTasks retrieve from taskInData
        outData << "==========================================================" << endl;

        outData << "processing taskId: " << tasks[i].taskId << endl;
        outData << "description      : " << tasks[i].description << endl;
        outData << "uncertainty      : " << tasks[i].uncertainty << endl;
        outData << "difficulty       : " << tasks[i].difficulty << endl;
        outData << "workers          : ";

        // display the workers id list of each task
        for(int j = 0; j < tasks[i].currentAssignedWorker; j++) {
            outData << tasks[i].workersIdList[j];

            if (j < tasks[i].currentAssignedWorker - 1) {
                outData << ",";
            }else {
                outData << " ";
            }
        }

        outData << endl << endl;

        for(int j = 0; j < tasks[i].currentAssignedWorker; j++) {
            outData << "----------------------------------------------------------" << endl;
            outData << "Trial: workers: " << tasks[i].workersIdList[j] << endl;
            outData << "----------------------------------------------------------" << endl << endl;

            int averagePerformance = workerPerformance(tasks, i, workers, tasks[i].workersIdList[j]);
            outData << "The average performance is " << averagePerformance << endl;
            if(averagePerformance > 50) {
                outData << "Assignment of task " << tasks[i].taskId << " to worker " << tasks[i].workersIdList[j] << " succeeds" << endl << endl;
                break;      // if the current worker succeeds, then move to the next task
            }else {
                outData << "Assignment of task " << tasks[i].taskId << " to worker " << tasks[i].workersIdList[j] << " fails" << endl << endl;
            }
        }
    }
    outData.close();
}
