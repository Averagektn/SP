#pragma once

#include <queue>
#include <string>
#include <Windows.h>

using namespace std;

// Thread safe queue with atomic operations
template<typename T>
class AtomicQueue
{
public:
    AtomicQueue()
    {
        InitializeCriticalSection(&criticalSection);
    }

    ~AtomicQueue()
    {
        DeleteCriticalSection(&criticalSection);
    }

    // Adds element to the queue
    void Enqueue(const T& item)
    {
        EnterCriticalSection(&criticalSection);

        q.push(item);

        LeaveCriticalSection(&criticalSection);
    }

    // Removes element from queue if it is not empty to elem parameter, otherwise returns false
    bool Dequeue(T& elem)
    {
        bool isEmpty = true;

        EnterCriticalSection(&criticalSection);
        if (!q.empty())
        {
            elem = q.front();
            q.pop();
            isEmpty = false;
        }
        LeaveCriticalSection(&criticalSection);

        return isEmpty;
    }

    // Counts current size of the queue NOT THREAD SAFE TO USE
    int Size()
    {
        return q.size();
    }

    // Checks if queue is empty NOT THREAD SAFE TO USE
    bool IsEmpty()
    {
        return q.empty();
    }

    // Converts elements to string. Only for primitive types
    string ToString()
    {
        string res;
        string line;
        queue<T> q_copy = q;

        while (!q_copy.empty())
        {
            res.append(q_copy.front() + "\n");
            q_copy.pop();
        }

        return res;
    }

private:
    CRITICAL_SECTION criticalSection;
    queue<T> q;
};
