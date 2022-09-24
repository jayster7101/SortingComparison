#include "include.h"
void selectionsort(std::string a[], int to)
{
    for(int i = 0;i < to; i++)
    {
        int min = min_pos(a, i, to);
        swap(a[min],a[i]);
    }
}

int min_pos(std::string a[], int from , int to)
{
    int min_pos = from;
    std::string b;
    std::string c;
    for(int i = from+1; i <= to; i++)
    {


        if ( lower(a[min_pos]) > lower(a[i])) min_pos = i;
    }
    return min_pos;
}




double selectionsortTimer(std::string a[], int to)
{
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    selectionsort(a,to);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double > >(t2 - t1);
    return time_span.count();
}