#include "Utils.h"

#include "PQueue.h"

#include <ctype.h>
#include <string.h>

#ifdef ENABLE_DBG_OUTPUT
    #include <stdarg.h>
#endif

#include <ctime>

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
    memset (static_cast<char*>(pArray)+(uiCurrLen*uiElementSize), NULL, uiDiff*uiElementSize);
    return pArray;
}

void ADS::setArray (int iDefValue, void *pArray, unsigned int uiLen,
                    unsigned int uiElementSize)
{
    memset (pArray, iDefValue, uiLen*uiElementSize);
}

void ADS::deallocate (void **ppPtr)
{
    if (ppPtr != NULL && *ppPtr != NULL) {
        free (*ppPtr);
        ppPtr = NULL;
    }
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
    for (int i = static_cast<int>(strlen (pszString))-1; i >= 0; i--)
        if (!isdigit (pszString[i]))
            return false;
    return true;
}

bool ADS::isPowerOf2 (unsigned int value)
{
    if (value == 0) {
        return false;
    }
    return !(value & (value - 1));
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

float ADS::random (unsigned int uiMax)
{
    static bool initWithSeed = true;
    if (initWithSeed) {
        srand (static_cast<unsigned int>(time (NULL)));
        initWithSeed = false;
    }
    return random (static_cast<unsigned int>(0), uiMax);
}

float ADS::random (unsigned int uiMin, unsigned int uiMax)
{
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return uiMin + r * (uiMax - uiMin);
}

char * ADS::strDup (const char *pszString)
{
    if (pszString == NULL)
        return NULL;

    unsigned int uiLen = strlen (pszString);
    if (uiLen == 0)
        return NULL;

    char *pszCpy = static_cast<char *>(calloc (uiLen+1, sizeof (char)));
    if (pszCpy == NULL)
        return NULL;

    memcpy (pszCpy, pszString, uiLen * sizeof(char));
    return pszCpy;
}

