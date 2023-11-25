#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <fstream>
#include <Windows.h>

#include "AtomicQueue.h"

using namespace std;

// Data for sorting threads
struct ThreadData
{
    AtomicQueue<string>* q;
    AtomicQueue<string>* result;
};

// Initialization of the queue from file
void getQ(string fileName, AtomicQueue<string>& q) 
{
    std::ifstream inputFile(fileName);

    if (inputFile.is_open()) 
    {
        std::string line;

        while (getline(inputFile, line)) 
        {
            q.Enqueue(line);
        }

        inputFile.close();
    }
    else 
    {
        std::cout << "File wasn't open" << std::endl;
    }
}

// Sorting algorithm for threads
DWORD WINAPI sortStrings(LPVOID lpParam)
{
    ThreadData* threadData = static_cast<ThreadData*>(lpParam);
    string line;

    while (!threadData->q->Dequeue(line))
    {
        sort(line.begin(), line.end());

        threadData->result->Enqueue(line);
    }

    delete threadData;

    return 0;
}

// Writing results to file and console
void Output(string fileName, AtomicQueue<string> q)
{
    cout << q.ToString();
    ofstream outputFile(fileName);
    if (outputFile.is_open())
    {
        outputFile << q.ToString();
        outputFile.close();
        cout << "String successfully written to file" << endl;
    }
    else
    {
        cout << "Failed to open the file" << endl;
    }
}

int main()
{
    int numThreads;
    string fileName;

    AtomicQueue<string> q;
    AtomicQueue<string> result;

    cout << "Enter file path" << endl;
    cin >> fileName;
    cout << "Emter number of threads" << endl;
    cin >> numThreads;

    HANDLE* threads = new HANDLE[numThreads];
    ThreadData** threadData = new ThreadData* [numThreads];

    getQ(fileName, q);

    for (int i = 0; i < numThreads; i++)
    {
        threadData[i] = new ThreadData();
        threadData[i]->q = &q;
        threadData[i]->result = &result;

        threads[i] = CreateThread(NULL, 0, sortStrings, threadData[i], 0, NULL);
    }

    WaitForMultipleObjects(numThreads, threads, TRUE, INFINITE);

    for (int i = 0; i < numThreads; ++i)
    {
        if (threads[i] != NULL) 
        {
            CloseHandle(threads[i]);
        }
    }

    Output(fileName, result);

    delete[] threads;
    delete[] threadData;

    return 0;
}
