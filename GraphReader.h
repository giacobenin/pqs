#ifndef ADS_GRAPH_READER_H
#define ADS_GRAPH_READER_H

#include <stddef.h>

#include "Graph.h"

/**
 * GraphReader.h
 *
 * Reads files containin graph in the format
 *
 * V1  V2  C1
 * V3  V4  C2 
 * ...
 *      *
 *
 * Where each line is a direct edge between the Vx and Vy verteces (assumed to
 * be ints), and Cz is the cost of directed edge.
 * The file terminates with a line containing only the "*" character.
 *
 * author: Giacomo Benincasa    (me@gbenin.casa)
 */

#include <string>

namespace ADS
{
    class GraphReader
    {
        public:
            /* If pszFileName is NULL, it reads from stdin */
            GraphReader (const char *pszFileName=NULL);
            virtual ~GraphReader (void);

            bool read (Graph<unsigned int> *pGraph);

        private:
            const std::string _fileName;
    };
}

#endif /* ADS_GRAPH_READER_H */


