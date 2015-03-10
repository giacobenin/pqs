#ifndef ADS_STOP_WATCH_H
#define ADS_STOP_WATCH_H

#include <time.h>

namespace ADS
{
    class StopWatch
    {
        public:
            StopWatch (void);
            ~StopWatch (void);

            void startWatch (void);
            long long int stopWatch (void);

        private:
            clock_t _start;
    };
}

#endif /* ADS_STOP_WATCH_H */


