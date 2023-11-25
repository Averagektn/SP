#pragma once

#include <queue>
#include <string>
#include <Windows.h>

using namespace std;

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

    void Enqueue(const T& item)
    {
        EnterCriticalSection(&criticalSection);

        q.push(item);

        LeaveCriticalSection(&criticalSection);
    }

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

    int Size()
    {
        return q.size();
    }

    bool IsEmpty()
    {
        return q.empty();
    }

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
