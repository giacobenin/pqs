#ifndef ADS_UTILS_H
#define ADS_UTILS_H

#include <stdlib.h>

namespace ADS
{
    class PQueue;

    void * allocateArray (unsigned int uiLen, unsigned int uiElementSize);
    void * reallocateArray (void *pArray, unsigned int uiCurrLen,
                            unsigned int uiNewLen, unsigned int uiElementSize);
    void setArray (int iDefValue, void *pArray, unsigned int uiLen,
                   unsigned int uiElementSize);
    void deallocate (void **ppPtr);

    template <class T>
    void deallocateObjPtrArray (T ***pppPtr, unsigned int uiLen)
    {
        for (unsigned int i = 0; i < uiLen; i++)
            delete (*pppPtr)[i];
        free (*pppPtr);
        pppPtr = NULL;
    }

    void emptyQueue (PQueue *pQueue);
    bool isNumber (const char *pszString);
    bool isPowerOf2 (unsigned int value);
    void log (const char *pszMsg, ...);
    unsigned int minimum (unsigned int ui1, unsigned int ui2);
    float random (unsigned int uiMax);
    float random (unsigned int uiMin, unsigned int uiMax);
    char * strDup (const char *pszString);
    template<class T> void swap (T *&pEl1, T *&pEl2)
    {
        T *pTmp = pEl1;
        pEl1 = pEl2;
        pEl2 = pTmp;
    }
}

#endif /* ADS_UTILS_H */


