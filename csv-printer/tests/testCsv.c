#include "csvPrinter.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testIsNumber()
{
    assert(isNumber("123") == 1);
    assert(isNumber("-45.67") == 1);
    assert(isNumber("0") == 1);
    assert(isNumber("abc") == 0);
    assert(isNumber("12a") == 0);
    assert(isNumber("") == 0);
    printf("testIsNumber пройден\n");
}

int main()
{
    testIsNumber();
    printf("Все тесты пройдены\n");
    return 0;
}
