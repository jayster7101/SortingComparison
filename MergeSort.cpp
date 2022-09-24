#include "include.h"

// void merge(std::string a[], int from, int mid, int to)
// {
//     //std::string copy[to];
//     int i1 = from; 
//     int i2 = mid + 1;
//     int j = from; 

//     std::string temp[to];

//     while(i1 <= mid && i2 <= to)
//     {
//         if(lower(a[i1]) <= lower(a[i2]))
//         {
//             temp[j] = a[i1];
//             i1++;
//             j++;
//         }
//         else
//         {
//             temp[j] = a[i2];
//             i2++;
//             j++;
//         }
//     }

//     while(i1 < mid)
//     {
//         temp[j] = a[i1];
//         i1++;
//         j++;
//     }
//     while(i2 < to)
//     {
//         temp[j] = a[i2];
//         i2++;
//         j++;
//     }

//     for (int p = from; p <= to; p++) {
//     a[p] = temp[p];
//   }
// }

void merge(std::string a[], int from, int mid, int to) {
  int i = from;
  int j = mid + 1;
  int k = from;

  /* create temp array */
   //std::string temp[to];
   std::string temp[to];
  //std::string *temp = new std::string[to];

  while (i <= mid && j <= to) {
    if (lower(a[i]) <= lower(a[j])) 
    {
      temp[k] = a[i];
      i++;
      k++;
    } else {
      temp[k] = a[j];
      j++;
      k++;
    }
  }

  /* Copy the remaining elements of first half, if there are any */
  while (i <= mid) {
    temp[k] = a[i];
    i++;
    k++;

  }
  /* Copy the remaining elements of second half, if there are any */
  while (j <= to) {
    temp[k] = a[j];
    j++;
    k++;
  }

  /* Copy the temp array to original array */
  for (int p = from; p <= to; p++) {
    a[p] = temp[p];
  }
   //delete []temp;
  // temp = nullptr;
}
void mergesort(std::string a[], int from, int to)
{
    if(from == to) return ;
    int mid = (from + to) / 2;
    mergesort(a, from, mid);
    mergesort(a, mid + 1, to);
    merge(a, from, mid, to);

}
double mergesortTimer(std::string a[], int from, int to)
{
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    mergesort(a,from, to);
    //delete []a;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double > >(t2 - t1);
    return time_span.count();
}