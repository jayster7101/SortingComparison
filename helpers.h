#include "include.h"

#ifndef HELPERS_H
#define HELPERS_H

std::string get_file_name(); // gets the file name
void process_data(); // process data without removing words
int load_data(std::string [], std::string **);// process data and removes certain words && passes address of pointer 
//int load_data(std::string []);// process data and removes certain words && passes address of pointer 
std::string* words_to_remove(); // returns pointer to array of the words to remove 
void run_time_call(std::string [], std::string**, bool, double[]);
int* pick_algo();
void display_list(int);
void copy(std::string[], std::string *, int);
void run_algo();// runs all algos and records all times

void swap(std::string&, std::string&); // swaps the postion of two values 


#endif