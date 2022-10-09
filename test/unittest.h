//
//  unittest.h
//  
//  Unit test module
//
//  Authored by Vincent ~ (vno16) and Natalie Kim (ski102) on 07 Oct 2022
//

#ifndef UNITTEST_H
#define UNITTEST_H

#include <string.h>
#include <stdio.h>

typedef enum {
    OK = 0,
    FAIL = 1,
    FATAL = 2
} Testcode_t;

typedef struct {
    const char* desc;
    Testcode_t (*exec)(void);
} Unit_t;


Unit_t unit(const char* desc, Testcode_t (*exec)(void));

void test_all(Unit_t units[], size_t len);

#endif