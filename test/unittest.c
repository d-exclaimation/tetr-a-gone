//
//  unittest.c
//  
//  Unit test module
//
//  Authored by vno16 and ski102 on 07 Oct 2022
//

#include "unittest.h"


Unit_t unit(const char* desc, Testcode_t (*exec)(void))
{
    return (Unit_t) {
        desc, exec
    };
}

void test_all(Unit_t units[], size_t len)
{
    Testcode_t code = OK;
    size_t success = 0;

    printf("Running test:\n");
    printf("\n");

    for (size_t i = 0; i < len; i++) {
        Unit_t unit = units[i];
        if (unit.desc == NULL) {
            printf("[TEST]: Running \"Test #%zu\" ....", i);
        } else {
            printf("[TEST]: Running \"%s\" ....", unit.desc);
        }
        code = (*unit.exec)();
        switch (code) {
        case FAIL:
            printf("FAIL\n");
            break;
        case FATAL:
            printf("FATAL\n");
            return;
        default:
            printf("OK\n");
            success++;
        }
    }
    printf("\n");
    printf("Success: %zu/%zu\n", success, len);
}
