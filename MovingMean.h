/* 
 * File:   MovingMean.h
 *
 * Author: Giacomo Benincasa    (me@gbenin.casa)
 *
 * Created on October 30, 2011, 1:22 AM
 */

#ifndef ADS_MOVING_MEAN_H
#define	ADS_MOVING_MEAN_H

namespace ADS
{
    template<class T>
    class MovingMean
    {
        public:
            MovingMean (void);
            virtual ~MovingMean (void);

            void add (T val);
            double getMean (void);
            void reset (void);

        private:
            T _total;
            unsigned long int _uiNValues;
    };

    template<class T>
    MovingMean<T>::MovingMean()
    {
        reset();
    }

    template<class T>
    MovingMean<T>::~MovingMean()
    {
    }

    template<class T>
    void MovingMean<T>::add (T val)
    {
        _total += val;
        _uiNValues++;
    }

    template<class T>
    double MovingMean<T>::getMean()
    {
        if (_uiNValues == 0)
            return 0;
        return (_total / _uiNValues);
    }

    template<class T>
    void MovingMean<T>::reset()
    {
        _total = 0;
        _uiNValues = 0;
    }
}

#endif	/* ADS_MOVING_MEAN_H */

