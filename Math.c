#include "Math.h"
#include "header.h"

/*
FUNCTION: absolute
IMPORT: num (Double)
EXPORT: num (Double)
PURPOSE: Returns the positive value of num
*/
double absolute( double num )
{
    if ( num < 0 )
        num = num * -1.0;

    return num;
}

/*
FUNCTION: math_sqrt
IMPORT: num (Double)
EXPORT: squareRoot (Double)
PURPOSE: Returns a square root value of num
*/
double math_sqrt( double num )
{
    double t;
    double squareRoot = num / 2.0;

    do
    {
        t = squareRoot;
        squareRoot = (t + (num/t)) / 2.0;
    } while ( absolute( t - squareRoot ) >= TOL ); 

    return squareRoot;
}

/*
FUNCTION: nextOdd
IMPORT: num (Integer)
EXPORT: num (Integer)
PURPOSE: Returns the next odd number from the IMPORT data
*/
int nextOdd( int num )
{
    /* num = num + 1 if num is an even number */
    if ( num % 2 == 0 )
        ++num;
    else
        num += 2;

    return num;
}

/*
FUNCTION: nextPrime
IMPORT: num (Integer)
EXPORT: prime (Integer)
PURPOSE: Returns the next prime number from the IMPORT data
*/
int nextPrime( int num )
{
    int isPrime = FALSE; 
    int prime = num, ii = 0;

    /* The next smallest prime for any number smaller than 1 is 2 */
    if ( num <= 1 )
        prime = 2;
    else
    {
        while ( isPrime == FALSE )
        {
            prime = nextOdd( prime ); /* Prime number value is always odd except for value 2 */
            ii = prime - 1;           /* ii as a divisor */
            isPrime = TRUE;           /* Will check if it is FALSE */

            while ( isPrime == TRUE && ii >= 2 )
            {
                if ( prime % ii == 0 )
                    isPrime = FALSE;
                else
                    --ii;
            }
        }
    }
    return prime;
}
