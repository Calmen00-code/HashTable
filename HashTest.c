#include <stdio.h>
#include <string.h>
#include <math.h>
#include "header.h"
#include "Hash.h"

#define GRN "\033[0;32m"
#define RED "\033[0;31m"
#define UBLUE "\033[4;34m"
#define RESET "\033[0m"

int main()
{
    int capacity = 10;
    char ch_1 = 'A', ch_2 = '6', ch_3 = 'L';
    char test_ch1, test_ch2, test_ch3;

    char str[STR] = "TEST", str_2[STR] = "TEST2";   
    char test[STR] = "", test_2[STR] = "";

    char collission1[STR] = "ddx", collission2[STR] = "dddF";
    char col_test1[STR] = "", col_test2[STR] = "";

    HashTable *hash = createHash( capacity );
    HashEntry *hashArr = NULL;

/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("TEST Create Hash: ");
    if ( hash->size == 11 )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
        printf("%sFAILED%s\n\n", RED, RESET);

/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("%sTEST put%s\n\n", UBLUE, RESET);
    put( hash, "TEST", str );       /* Hash Index is 1 for table size of 11 */ 
    put( hash, "TEST2", str_2 );    /* Hash Index is 7 for table size of 11 */

    hashArr = hash->hashArray;
    strcpy( test, (char *)(hashArr[1].data) );
    strcpy( test_2, (char *)(hashArr[7].data) );

    printf("put 'TEST': ");
    if ( strcmp( test, "TEST" ) == 0 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("put 'TEST2': ");
    if ( strcmp( test_2, "TEST2" ) == 0 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("\n");

/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("%sTEST put Collission%s\n\n", UBLUE, RESET);
    put( hash, "ddx", collission1 );     /* Hash Index is 1 for table size of 11, Collide with str */ 
    put( hash, "dddF", collission2 );    /* Hash Index is 7 for table size of 11, Collide with str_2 */
    
    printf("Collision with 'TEST': ");
    strcpy( test, (char *)(hashArr[1].data) ); 
    if ( strcmp( test, "TEST" ) == 0 )  /* The data for hashArr[1].data should remain after collision */
    {
        strcpy( test, (char *)(hashArr[2].data) );
        if ( strcmp( test, "ddx" ) == 0 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }
        
    printf("Collision with 'TEST2': ");
    strcpy( test_2, (char *)(hashArr[7].data) );
    if ( strcmp( test_2, "TEST2" ) == 0 ) /* The data for hashArr[1].data should remain after collision */
    {
        strcpy( test_2, (char *)(hashArr[8].data) );
        if ( strcmp( test_2, "dddF" ) == 0 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }
    printf("\n");

/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("%sTEST put Existing Key%s\n\n", UBLUE, RESET);

    printf("Key 'TEST': ");
    put( hash, "TEST", str );            /* Hash Index is 1 for table size of 11 */     

    printf("Key 'TEST2': ");
    put( hash, "TEST2", str_2 );         /* Hash Index is 7 for table size of 11 */

    printf("Key 'ddx': ");
    put( hash, "ddx", collission1 );     /* Hash Index is 1 for table size of 11, Collide with str */ 

    printf("Key 'dddF': ");
    put( hash, "dddF", collission2 );    /* Hash Index is 7 for table size of 11, Collide with str_2 */
    
    printf("\n");

/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("TEST put Circular Rotation: ");

    /* Both of these value will result in the same position which is 10 */
    put( hash, "A", &ch_1 );    /* This was stored initially as it is 10 */ 
    put( hash, "6", &ch_2 );    /* This will result in 10 too, but 10 is occupied therefore circular to 0 */
    put( hash, "L", &ch_3 );    /* Result in 10, but 10, 0, 1, and 2 are occupied therefore it will be at idx 3 */
    
    test_ch1 = *((char *)(hashArr[10].data));   
    test_ch2 = *((char *)(hashArr[0].data));
    strcpy( test, (char *)(hashArr[1].data) );      /* Occupied Initially with: 'TEST' */
    strcpy( col_test1, (char *)(hashArr[2].data) ); /* Occupied Initially with: 'ddx' (Collission of 'TEST') */
    strcpy( test_2, (char *)(hashArr[7].data) );    /* Occupied Initially with: 'TEST2' */
    strcpy( col_test2, (char *)(hashArr[8].data) ); /* Occupied Initally with: dddF (Collission of 'TEST2') */
    test_ch3 = *((char *)(hashArr[3].data));        

    if ( test_ch1 == 'A' )
    {
        if ( test_ch2 == '6' )
        {
            if ( strcmp( test, "TEST" ) == 0 )
            {
                if ( strcmp( test_2, "TEST2" ) == 0 )
                {
                    if ( test_ch3 == 'L' )
                        printf("%sPASSED%s\n", GRN, RESET);
                    else
                        printf("%sFAILED%s\n", RED, RESET);
                }
            }
        }
    }
    printf("\n");
 
/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("%sTEST get%s\n\n", UBLUE, RESET);

    printf("get TEST: ");
    strcpy( test, (char *)(get( hash, "TEST" )) );
    if ( strcmp( test, "TEST" ) == 0 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("get TEST2: ");
    strcpy( test_2, (char *)(get( hash, "TEST2" )) );
    if ( strcmp( test_2, "TEST2" ) == 0 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("get ddx: ");
    strcpy( col_test1, get( hash, "ddx" ) );
    if ( strcmp( col_test1, "ddx" ) == 0 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("get dddF: ");
    strcpy( col_test2, get( hash, "dddF" ) );
    if ( strcmp( col_test2, "dddF" ) == 0 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("get A: ");
    test_ch1 = *((char *)(get( hash, "A" )));
    if ( test_ch1 == 'A' )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("get 6: ");
    test_ch2 = *((char *)(get( hash, "6" )));
    if ( test_ch2 == '6' )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("get L: ");
    test_ch3 = *((char *)(get( hash, "L" ))); 
    if ( test_ch3 == 'L' )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    return 0;
}
