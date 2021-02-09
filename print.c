#include <stdio.h>
#include "print.h"

printFunc getFunc( char type )
{
    printFunc printPtr;

    if ( type == 'c' )
        printPtr = &printCharacter;
    else if ( type == 's' )
        printPtr = &printString;
    else if ( type == 'i' )
        printPtr = &printInteger;
    else if ( type == 'd' )
        printPtr = &printDouble;
    else if ( type == 'f' )
        printPtr = &printFloat;

    return printPtr;
}

void printString( void *data )
{
    char *str = (char *)data;
    printf("%s ", str);
}

void printInteger( void *data )
{
    int *iNum = (int *)data;
    printf("%d ", *iNum);
}

void printFloat( void *data )
{
    float *fNum = (float *)data;
    printf("%f ", *fNum);
}

void printDouble( void *data )
{
    double *dNum = (double *)data;
    printf("%f ", *dNum);
}

void printCharacter( void *data )
{
    char *ch = (char *)data;
    printf("%c ", *ch);
}
