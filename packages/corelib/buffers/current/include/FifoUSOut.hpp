/***************************************************************************
  tag: Peter Soetens  Mon Jan 19 14:11:20 CET 2004  FifoUSOut.hpp 

                        FifoUSOut.hpp -  description
                           -------------------
    begin                : Mon January 19 2004
    copyright            : (C) 2004 Peter Soetens
    email                : peter.soetens@mech.kuleuven.ac.be
 
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
 
 
 
#ifndef FIFOUSOUT_HPP
#define FIFOUSOUT_HPP


#include "WriteInterface.hpp"
#include <cstdio>

namespace ORO_CoreLib
{

    /**
     * A FifoUSOut is meant for writing to a realtime fifo from
     * (not realtime) userspace. 
     *
     * @see FifoUSIn
     * @see FifoRTIn
     */
    class FifoUSOut
        : public WriteInterface
    {

    public:
        /**
         * Open a fifo with number <fNr> for writing.
         * 
         * @param fNr
         *        The fifo number
         */
        FifoUSOut( unsigned int fNr);

        /**
         * Close the fifo.
         */
        virtual ~FifoUSOut();

        int write( const char* buf, size_t write_length);

    private:
        FILE *fifo;
        unsigned int fifoNr;
    };
}

#endif
