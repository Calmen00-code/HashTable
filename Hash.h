#ifndef HASH
#define HASH

typedef struct HashEntry
{
    char key[STR];
    void *data;
    int state;
}HashEntry;

typedef struct HashTable
{
    HashEntry *hashArray;
    int size;
    int count;
}HashTable;

HashTable* createHash( int );
void put( HashTable*, char[], void* );
void* get( HashTable *, char[] );
void* removeHash( char[] );
int getLoadFactor();

#endif
