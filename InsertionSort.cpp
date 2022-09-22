#include "include.h"
void insertionsort(std::string a[], int size)
{
    for(int i = 1; i < size; i++)
    {   
        std::string temp = a[i];
        int j = i - 1;
        while(j >= 0 && lower(a[j]) > lower(temp))
        {   
            a[j+1] = a[j];
            j = j - 1;
        }
        a[j+1] = temp;
    }
}

double insertionsortTimer(std::string a[], int size)
{
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    insertionsort(a,size);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double > >(t2 - t1);
    return time_span.count();
}