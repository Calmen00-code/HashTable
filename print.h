#ifndef PRINT
#define PRINT

typedef void(*printFunc)(void*data);

printFunc getFunc( char );
void printString( void *data );
void printInteger( void *data );
void printFloat( void *data );
void printDouble( void *data );
void printCharacter( void *data );

#endif
