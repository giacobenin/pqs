#ifndef ADS_DYNAMIC_ARRAY_H
#define ADS_DYNAMIC_ARRAY_H

#include <stddef.h>
#include <stdio.h>
#include "Utils.h"

/**
 * DArray.h
 *
 * Implementation of a dynamic array with configurable first index.
 *
 * author: Giacomo Benincasa    (me@gbenin.casa)
 */
namespace ADS
{
    template<class T>
    class DArray
    {
        public:
            /* Creates an array of T of length uiLen where
               the first index of the first element is
               uiStartIndex.
               defaulValue value is the default value assigned
               to the elements of the array */
            explicit DArray (unsigned int uiLen,
                             unsigned int uiStartIndex=0, bool bCanGrow=true);
            virtual ~DArray (void);

            /* add element at position uiIndex and replace
               the element at the current position (if any)
               with the current one. The formed element is
               returned */
            T add (unsigned int uiIndex, T element);

            /* Returns the element at position uiIndex */
            T get (unsigned int uiIndex);

            /* Removes and returns the element at position uiIndex
               if any, returns NULL otherwise */
            T remove (unsigned int uiIndex);

            /* Returns the length of the array */
            unsigned int size (void);

            void display (void);

        private:
            bool checkBound (unsigned int uiIndex);
            bool grow (unsigned int uiLastIndex);
            unsigned int shiftIndex (unsigned int uiIndex);

        private:
            bool _bCanGrow;
            unsigned int _uiLen;    /* Length of the array */
            unsigned int _uiOff;    /* The index of the first element */
            T *_pDArray;
    };

    template <class T>
    DArray<T>::DArray (unsigned int uiLen,
                       unsigned int uiStartIndex, bool bCanGrow)
    {
        _uiLen = uiLen;
        _uiOff = uiStartIndex;
        _bCanGrow = bCanGrow;
        if (uiLen == 0)
            _pDArray = NULL;
        else
            _pDArray = (T *) allocateArray (uiLen, sizeof (T));
    }

    template <class T>
    DArray<T>::~DArray()
    {
        deallocate ((void **)&_pDArray);
    }

    template <class T> T
    DArray<T>::add (unsigned int uiIndex, T element)
    {
        if (!checkBound (shiftIndex (uiIndex)))
            return NULL;
        T tmp = _pDArray[shiftIndex (uiIndex)];
        _pDArray[shiftIndex (uiIndex)] = element;
        return tmp;
    }

    template <class T>
    T DArray<T>::get (unsigned int uiIndex)
    {
        if (!checkBound (shiftIndex (uiIndex)))
            return NULL;
        return _pDArray[shiftIndex (uiIndex)];
    }

    template <class T>
    T DArray<T>::remove (unsigned int uiIndex)
    {
        T tmp = get (uiIndex);
        if (tmp == NULL)
            return NULL;
        _pDArray[shiftIndex (uiIndex)] = NULL;
        return tmp;
    }

    template <class T>
    unsigned int DArray<T>::size()
    {
        return _uiLen;
    }

    template <class T>
    bool DArray<T>::checkBound (unsigned int uiIndex)
    {
        if (uiIndex < _uiOff)
            return false;
        if (uiIndex >= _uiLen) {
            if (_bCanGrow)
                return grow (uiIndex);
            else
                return false;
        }

        return true;
    }

    template <class T>
    bool DArray<T>::grow (unsigned int uiLastIndex)
    {
        unsigned int uiNewLen = uiLastIndex - _uiOff + 1;
        _pDArray = (T*) reallocateArray (_pDArray, _uiLen, uiNewLen, sizeof (T));
        if (_pDArray == NULL)
            return false;
        _uiLen = uiNewLen;
        return true;
    }

    template <class T>
    unsigned int DArray<T>::shiftIndex (unsigned int uiIndex)
    {
        return (uiIndex - _uiOff);
    }

    template <class T>
    void DArray<T>::display (void)
    {
        for (unsigned int i = 0; i < size(); i++)
            printf ("%u ", get (i));
        printf ("\n");
    }
}

#endif /* ADS_ARRAY_H */


