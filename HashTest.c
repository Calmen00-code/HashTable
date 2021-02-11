#include <stdio.h>
#include <string.h>
#include <math.h>
#include "header.h"
#include "Hash.h"
#include "Math.h"

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

    char *resize_1 = "RESIZE", *resize_2 = "RESIZE2", *resize_3 = "RESIZE3", *resize_4 = "RESIZE4", *resize_5 = "RESIZE5", *resize_6 = "RESIZE6";

    /* These are all the value calculated for Load Factor to compare with TOL_LF */
    double lf_1 = 0.1818, lf_2 = 0.3636, lf_3 = 0.6363;
    /*double lf_4 = 0.5454, lf_5 = 0.4545, lf_6 = 0.3636, lf_7 = 0.2727, lf_8 = 0.1818, lf_9 = 0.0909, lf_10 = 0.0;*/
    double loadFactor = 0.0;

    HashTable *hash = createHash( capacity );
    HashEntry *hashArr = NULL;

/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("TEST Create Hash: ");

    if ( hash != NULL )
    {
        if ( hash->size == 11 )
            printf("%sPASSED%s\n\n", GRN, RESET);
        else
            printf("%sFAILED%s\n\n", RED, RESET);
    }

/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("%sTEST put%s\n\n", UBLUE, RESET);
    put( hash, "TEST", str, 's' );       /* Hash Index is 1 for table size of 11 */ 
    put( hash, "TEST2", str_2, 's' );    /* Hash Index is 7 for table size of 11 */

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

    printf("count: ");
    if ( hash->count == 2 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("Load Factor: ");
    if ( absolute( lf_1 - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("Size: ");
    if ( hash->size == 11 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("\n");

/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("%sTEST put Collission%s\n\n", UBLUE, RESET);
    put( hash, "ddx", collission1, 's');     /* Hash Index is 1 for table size of 11, Collide with str */ 
    put( hash, "dddF", collission2, 's' );    /* Hash Index is 7 for table size of 11, Collide with str_2 */
    
    hashArr = hash->hashArray;

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

    printf("count: ");
    if ( hash->count == 4 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("Load Factor: ");
    if ( absolute( lf_2 - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("Size: ");
    if ( hash->size == 11 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("\n");

/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("%sTEST put Existing Key%s\n\n", UBLUE, RESET);

    printf("Key 'TEST': ");
    put( hash, "TEST", str, 's' );            /* Hash Index is 1 for table size of 11 */     

    printf("Key 'TEST2': ");
    put( hash, "TEST2", str_2, 's' );         /* Hash Index is 7 for table size of 11 */

    printf("Key 'ddx': ");
    put( hash, "ddx", collission1, 's' );     /* Hash Index is 1 for table size of 11, Collide with str */ 

    printf("Key 'dddF': ");
    put( hash, "dddF", collission2, 's' );    /* Hash Index is 7 for table size of 11, Collide with str_2 */

    printf("Size: ");
    if ( hash->size == 11 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);
 
    printf("\n");

/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("TEST put Circular Rotation: ");

    /* Both of these value will result in the same position which is 10 */
    put( hash, "A", &ch_1, 'c' );    /* This was stored initially as it is 10 */ 
    put( hash, "6", &ch_2, 'c' );    /* This will result in 10 too, but 10 is occupied therefore circular to 0 */
    put( hash, "L", &ch_3, 'c' );    /* Result in 10, but 10, 0, 1, and 2 are occupied therefore it will be at idx 3 */
    
    hashArr = hash->hashArray;

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
                    if ( strcmp( col_test1, "ddx" ) == 0 )
                    {
                        if ( strcmp( col_test2, "dddF" ) == 0 )
                        {
                            if ( test_ch3 == 'L' )
                                printf("%sPASSED%s\n", GRN, RESET);
                            else
                                printf("%sFAILED%s\n", RED, RESET);
                        }
                        else
                            printf("%sFAILED%s\n", RED, RESET);
                    }
                    else
                        printf("%sFAILED%s\n", RED, RESET);
                }
                else
                    printf("%sFAILED%s\n", RED, RESET);
            }
            else
                printf("%sFAILED%s\n", RED, RESET);
        }
        else
            printf("%sFAILED%s\n", RED, RESET);
    }
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("count: ");
    if ( hash->count == 7 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("Load Factor: ");
    if ( absolute( lf_3 - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("Size: ");
    if ( hash->size == 11 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

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

    printf("get Invalid: ");
    get( hash, "Invalid" );     /* Using unknown key (key that was not inserted) */

/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("%sTEST Print Hash%s\n\n", UBLUE, RESET); 
    printHash( hash );
 
/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("%sTEST RESIZE%s\n\n", UBLUE, RESET);

    printf("Increase: ");
    put( hash, "RESIZE", resize_1, 's' );       /* Hash Index is 4 for table size of 11 */
    put( hash, "RESIZE2", resize_2, 's' );      /* Hash Index is 10 for table size of 23 */ 
    put( hash, "RESIZE3", resize_3, 's' );       /* Hash Index is 11 for table size of 23 */
    if ( hash->size == 23 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sActual Size: %d%s\n", RED, hash->size, RESET);
        printf("%sLoad Factor: %f%s\n\n", RED, hash->lf, RESET); 
    }
    put( hash, "RESIZE4", resize_4, 's' );      /* Hash Index is 12 for table size of 23 */ 
    put( hash, "RESIZE5", resize_5, 's' );      /* Hash Index is 13 for table size of 23 */ 
    put( hash, "RESIZE6", resize_6, 's' );      /* Hash Index is 14 for table size of 23 */ 

    printf("TEST count: ");
    if ( hash->count == 13 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    printf("\n");
    printHash( hash );

/* ------------------------------------------------------- */

    printf("=====================================================\n\n");
    printf("%sTEST remove%s\n\n", UBLUE, RESET);

    printf("\n");
    printHash( hash );

    hashArr = hash->hashArray;

    printf("Remove TEST: ");
    strcpy( test, (char *)(removeHash( hash, "TEST" )) );
    if ( strcmp( test, "TEST" ) == 0 )
    {
        hashArr = hash->hashArray;
        if ( hashArr[21].state == -1 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }

    printf("Load Factor: ");
    loadFactor = 12.0 / 23.0;
    if ( absolute( loadFactor - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("Remove TEST2: ");
    strcpy( test_2, (char *)(removeHash( hash, "TEST2" )) );
    if ( strcmp( test_2, "TEST2" ) == 0 )
    {
        hashArr = hash->hashArray;
        if ( hashArr[2].state == -1 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }

    printf("Load Factor: ");
    loadFactor = 11.0 / 23.0;
    if ( absolute( loadFactor - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("Remove ddx: ");
    strcpy( col_test1, (char *)(removeHash( hash, "ddx" )) );
    if ( strcmp( col_test1, "ddx" ) == 0 )
    {
        hashArr = hash->hashArray;
        if ( hashArr[2].state == -1 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }

    printf("Load Factor: ");
    loadFactor = 10.0 / 23.0;
    if ( absolute( loadFactor - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("Remove dddF: ");
    strcpy( col_test2, (char *)(removeHash( hash, "dddF" )) );
    if ( strcmp( col_test2, "dddF" ) == 0 )
    {
        hashArr = hash->hashArray;
        if ( hashArr[3].state == -1 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }

    printf("Load Factor: ");
    loadFactor = 9.0 / 23.0;
    if ( absolute( loadFactor - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("Remove A: ");
    test_ch1 = *((char *)(removeHash( hash, "A" )));
    if ( test_ch1 == 'A' )
    {
        hashArr = hash->hashArray;
        if ( hashArr[19].state == -1 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }

    printf("Load Factor: ");
    loadFactor = 8.0 / 23.0;
    if ( absolute( loadFactor - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    /* Test if hash table will shuffle to start when is the index is at last */
    printf("Remove 6: ");                                   
    test_ch2 = *((char *)(removeHash( hash, "6" )));
    if ( test_ch2 == '6' )
    {
        hashArr = hash->hashArray;
        if ( hashArr[8].state == -1 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }

    printf("Load Factor: ");
    loadFactor = 7.0 / 23.0;
    if ( absolute( loadFactor - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("Remove L: ");
    test_ch3 = *((char *)(removeHash( hash, "L" )));
    if ( test_ch3 == 'L' )
    {
        hashArr = hash->hashArray;
        if ( hashArr[7].state == -1 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }

    printf("Load Factor: ");
    loadFactor = 6.0 / 23.0;
    if ( absolute( loadFactor - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("Remove RESIZE: ");
    strcpy( test, (char *)(removeHash( hash, "RESIZE" )) );
    if ( strcmp( test, "RESIZE" ) == 0 )
    {
        hashArr = hash->hashArray;
        if ( hashArr[6].state == -1 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }

    printf("Load Factor: ");
    loadFactor = 5.0 / 23.0;
    if ( absolute( loadFactor - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("Remove RESIZE2: ");
    strcpy( test, (char *)(removeHash( hash, "RESIZE2" )) );
    if ( strcmp( test, "RESIZE2" ) == 10 )
    {
        hashArr = hash->hashArray;
        if ( hashArr[6].state == -1 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }

    printf("Load Factor: ");
    loadFactor = 4.0 / 23.0;
    if ( absolute( loadFactor - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("Remove RESIZE3: ");
    strcpy( test, (char *)(removeHash( hash, "RESIZE3" )) );
    if ( strcmp( test, "RESIZE3" ) == 0 )
    {
        hashArr = hash->hashArray;
        if ( hashArr[11].state == -1 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }

    printf("Load Factor: ");
    loadFactor = 3.0 / 23.0;
    if ( absolute( loadFactor - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("Remove RESIZE4: ");
    strcpy( test, (char *)(removeHash( hash, "RESIZE4" )) );
    if ( strcmp( test, "RESIZE4" ) == 0 )
    {
        hashArr = hash->hashArray;
        if ( hashArr[12].state == -1 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }

    printf("Load Factor: ");
    loadFactor = 2.0 / 23.0;
    if ( absolute( loadFactor - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    /*                                                        *
     *  The hash table will keep shrinking starting from here *
     *                                                        */

    printf("Remove RESIZE5: ");
    strcpy( test, (char *)(removeHash( hash, "RESIZE5" )) );        /* Shrink to 13 */
    if ( strcmp( test, "RESIZE5" ) == 0 )
    {
        hashArr = hash->hashArray;
        if ( hashArr[12].state == -1 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
            printf("%sFAILED%s\n", RED, RESET);
    }

    printf("Load Factor: ");
    loadFactor = 1.0 / 23.0;
    if ( absolute( loadFactor - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("Remove RESIZE6: ");
    strcpy( test, (char *)(removeHash( hash, "RESIZE6" )) );            /* Shrink to 7 */
    if ( strcmp( test, "RESIZE6" ) == 0 )
    {
        hashArr = hash->hashArray;
        if ( hashArr[2].state == -1 )
            printf("%sPASSED%s\n", GRN, RESET);
        else
        {
            printf("%sFAILED%s\n", RED, RESET);
            printf("%shashArr[0].state = %d%s\n", RED, hashArr[2].state, RESET);
            printf("hashArr[2].data = %s\n", (char *)(hashArr[2].data));
        }
    }
    else
        printf("%sReturn Data: %s%s\n", RED, test, RESET);

    printf("Load Factor: ");
    loadFactor = 0.0 / 13.0;

    if ( absolute( loadFactor - hash->lf ) <= TOL_LF )
        printf("%sPASSED%s\n\n", GRN, RESET);
    else
    {
        printf("%sFAILED%s\n", RED, RESET);
        printf("%sLoad Factor: %f%s\n", RED, getLoadFactor( hash ), RESET );
        printf("%sComparison Load Factor - Actual Load Factor: %f%s\n\n", RED, absolute( loadFactor - hash->lf ), RESET );
    }

    printf("count: ");
    if ( hash->count == 0 )
        printf("%sPASSED%s\n", GRN, RESET);
    else
        printf("%sFAILED%s\n", RED, RESET);

    freeHash( hash );
    return 0;
}
