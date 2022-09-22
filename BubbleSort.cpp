#include "include.h"

void bubblesort(std::string a[], int size)
{
  for (int i = 0; i < size; i++) {
    int flag = false;
    for (int j = 0; j < (size - i - 1); j++) {
      if (lower(a[j]) > lower(a[j + 1])) {
        flag = true;
        std::string temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
    if (flag == false) {
      break;
    }
  }
}

double bubblesortTimer(std::string a[], int size)
{
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    bubblesort(a,size);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double > >(t2 - t1);
    return time_span.count();
}