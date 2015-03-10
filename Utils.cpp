#include "Utils.h"

#include "PQueue.h"

#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

void * ADS::allocateArray (unsigned int uiLen, unsigned int uiElementSize)
{
    return calloc (uiLen, uiElementSize);
}

void * ADS::reallocateArray (void *pArray, unsigned int uiCurrLen,
                             unsigned int uiNewLen, unsigned int uiElementSize)
{
    if (uiNewLen <= uiCurrLen)
        return pArray;

    pArray = realloc (pArray, uiNewLen*uiElementSize);
    unsigned int uiDiff = uiNewLen - uiCurrLen;
    memset (((char*)pArray)+(uiCurrLen*uiElementSize), NULL, uiDiff*uiElementSize);
    return pArray;
}

void ADS::setArray (int iDefValue, void *pArray, unsigned int uiLen,
                    unsigned int uiElementSize)
{
    memset (pArray, iDefValue, uiLen*uiElementSize);
}

void ADS::deallocate (void **ppPtr)
{
    free (*ppPtr);
    ppPtr = NULL;
}

void ADS::emptyQueue (PQueue *pQueue)
{
    if (pQueue == NULL)
        return;

    while (!pQueue->isEmpty())
        delete pQueue->pop();
}

bool ADS::isNumber (const char *pszString)
{
    for (int i = (int) strlen (pszString)-1; i >= 0; i--)
        if (!isdigit (pszString[i]))
            return false;
    return true;
}

bool ADS::isPowerOf2 (unsigned int value)
{
    return ((value != 0) && !(value & (value - 1)));
}

void ADS::log (const char *pszMsg, ...)
{
    #ifdef ENABLE_DBG_OUTPUT
        va_list vargs;
        va_start (vargs, pszMsg);
        time_t now = time (NULL);
        struct tm *ptm = localtime (&now);
	fprintf (stdout, "%02d:%02d:%02d - ", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
        vfprintf (stdout, pszMsg, vargs);
        fflush (stdout);
        va_end (vargs);
    #endif
}

unsigned int ADS::minimum (unsigned int ui1, unsigned int ui2)
{
    if (ui1 < ui2)
        return ui1;
    return ui2;
}

long long int ADS::getCurrentTimeInMilliseconds()
{
    struct timeval t;
    if (gettimeofday (&t,0) == -1)
        return 0;

    return (long long int)t.tv_sec* (long long int) 1000 +
           (long long int)t.tv_usec / (long long int) 1000;
}

float ADS::random (unsigned int uiMax)
{
    static bool initWithSeed = true;
    if (initWithSeed) {
        srand (getCurrentTimeInMilliseconds());
        initWithSeed = false;
    }
    return random ((unsigned int) 0, uiMax);
}

float ADS::random (unsigned int uiMin, unsigned int uiMax)
{
    float r = (float)rand() / (float)RAND_MAX;
    return uiMin + r * (uiMax - uiMin);
}

char * ADS::strDup (const char *pszString)
{
    if (pszString == NULL)
        return NULL;

    unsigned int uiLen = strlen (pszString);
    if (uiLen == 0)
        return NULL;

    char *pszCpy = (char *) calloc (uiLen+1, sizeof (char));
    if (pszCpy == NULL)
        return NULL;

    memcpy (pszCpy, pszString, uiLen * sizeof(char));
    return pszCpy;
}


