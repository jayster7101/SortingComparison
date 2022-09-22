#include "include.h"


void quicksort(std::string a[], int from, int to)
{
   if (from >= to) { return; }
   int p = partition(a, from, to);
   quicksort(a, from, p);
   quicksort(a, p + 1, to);
}

int partition(std::string a[], int from, int to)
{
   std::string pivot = a[from];
   int i = from - 1;
   int j = to + 1;
   while (i < j)
   {
      i++; while (lower(a[i]) < lower(pivot)) { i++; }
      j--; while (lower(a[j]) > lower(pivot)) { j--; }
      if (i < j) { swap(a[i], a[j]); }
   }
   return j;
}


double quicksortTimer(std::string a[], int from, int to)
{
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    quicksort(a,from,to);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double > >(t2 - t1);
    return time_span.count();
}