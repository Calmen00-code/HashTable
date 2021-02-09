#ifndef HASH
#define HASH

#define LOWER_BOUND 0.4
#define UPPER_BOUND 0.7
#define TOL_LF 0.1

typedef struct HashEntry
{
    char key[STR];
    void *data;
    char type;
    int state;
}HashEntry;

typedef struct HashTable
{
    HashEntry *hashArray;
    int size;
    int count;
    double lf;
}HashTable;

HashTable* createHash( int );
void put( HashTable*, char[], void*, char );
void* get( HashTable *, char[] );
void* removeHash( HashTable *, char[] );
double getLoadFactor( HashTable * );
void printHash( HashTable * );

#endif
