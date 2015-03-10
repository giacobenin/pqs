#ifndef ADS_BINOMIAL_HEAP_DEGREE_TABLE_H
#define ADS_BINOMIAL_HEAP_DEGREE_TABLE_H

#include "DArray.h"
#include "Node.h"

namespace ADS
{
    template <class T>
    class DegreeTable
    {
        public:
            DegreeTable (void);
            ~DegreeTable (void);

            /* Returns true if the element at position uiPosition
               is not null */
            bool used (unsigned int uiPosition);

            bool add (unsigned int uiPosition, BNode<T> *pNode);
            void remove (unsigned int uiPosition, BNode<T> *&pNode);

            /* Returns the length of the array */
            unsigned int size (void);

        private:
            struct DegreeTableEntry
            {
                BNode<T> *pNode;
            };

            DArray<DegreeTableEntry*> _table;
    };

    template<class T>
    DegreeTable<T>::DegreeTable()
        : _table (1, 0, true)
    {
    }

    template<class T>
    DegreeTable<T>::~DegreeTable()
    {
    }

    template<class T>
    bool DegreeTable<T>::used (unsigned int uiPosition)
    {
        return (_table.get (uiPosition) != NULL);
    }

    template<class T>
    bool DegreeTable<T>::add (unsigned int uiPosition, BNode<T> *pNode)
    {
        DegreeTableEntry *pEntry = _table.get (uiPosition);
        bool bRet = false;
        if (pEntry == NULL) {
            pEntry = new DegreeTableEntry;
            DegreeTableEntry *pTmp = _table.add (uiPosition, pEntry);
            bRet = (pTmp == NULL);
        }

        pEntry->pNode = pNode;

        return bRet;
    }

    template<class T>
    void DegreeTable<T>::remove (unsigned int uiPosition, BNode<T> *&pNode)
    {
        DegreeTableEntry *pEntry = _table.remove (uiPosition);
        pNode = pEntry->pNode;

        delete pEntry;
    }

    template<class T>
    unsigned int DegreeTable<T>::size()
    {
        return _table.size();
    }
}

#endif /* ADS_BINOMIAL_HEAP_DEGREE_TABLE_H */


