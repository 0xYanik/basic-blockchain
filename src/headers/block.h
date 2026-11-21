#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"

typedef struct {
    int id;
    transaction Transaction;
    char hash[256];
    char previousHash[256];
    time_t timestamp;

}block;

block block_core;


#endif