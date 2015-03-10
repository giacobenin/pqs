#ifndef ADS_COMPARATOR_H
#define ADS_COMPARATOR_H

namespace ADS
{
    /*
     * Comparator for non-pointer types
     */
    template<class T>
    class Comparator
    {
        public:
            /* Returns true if el1 is greater than el2 */
            static bool greaterThan (T el1, T el2);

            /* Returns true if el1 is less than el2 */
            static bool lessThan (T el1, T el2);

            /* Returns true if el1 and el2 are equals */
            static bool equals (T el1, T el2);
    };

    /*
     * Comparator for pointer types
     */
    template<class T>
    class ObjPointerComparator
    {
        public:
            /* Returns true if el1 is greater than el2 */
            static bool greaterThan (T *pEl1, T *pEl2);

            /* Returns true if el1 is less than el2 */
            static bool lessThan (T *pEl1, T *pEl2);

            /* Returns true if el1 and el2 are equals */
            static bool equals (T *pEl1, T *pEl2);
    };

    template<class T>
    bool Comparator<T>::greaterThan (T el1, T el2)
    {
        return el1 > el2;
    }

    template<class T>
    bool Comparator<T>::lessThan (T el1, T el2)
    {
        return el1 < el2;
    }

    template<class T>
    bool Comparator<T>::equals (T el1, T el2)
    {
        return el1 == el2;
    }

    template<class T>
    bool ObjPointerComparator<T>::greaterThan (T *pEl1, T *pEl2)
    {
        return *pEl1 > *pEl2;
    }

    template<class T>
    bool ObjPointerComparator<T>::lessThan (T *pEl1, T *pEl2)
    {
        return *pEl1 < *pEl2;
    }

    template<class T>
    bool ObjPointerComparator<T>::equals (T *pEl1, T *pEl2)
    {
        return *pEl1 == *pEl2;
    }
}

#endif /* ADS_COMPARATOR_H */


