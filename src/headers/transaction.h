#ifndef HELL_H
#define HELL_H
#include <time.h>
#include <string>


typedef struct {
    int id;
    char sender[50];
    char destination[50];
    std::string data;
    char hash[65];
    time_t timestamp;
}transaction;

//transaction *transaction_core = NULL;


















#endif




