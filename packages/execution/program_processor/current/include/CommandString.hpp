/***************************************************************************
  tag: Peter Soetens  Mon Jan 19 14:11:21 CET 2004  CommandString.hpp 

                        CommandString.hpp -  description
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
 
 
#include <corelib/CommandInterface.hpp>

#include <string>

namespace ORO_Execution
{
	using ORO_CoreLib::CommandInterface;

	/**
	 * This command displays a string when executed. 
     * (Currently solely used by jilske for testing purposes.)
	 */
	class CommandString : public CommandInterface
	{
		
		public:
		
			CommandString(std::string s);

   	    	virtual ~CommandString()
   	    	{}	

    	    virtual void execute();

    	    virtual std::string toString();
        
        virtual CommandInterface* clone() const
        {
            return new CommandString( *this );
        }

        private:
        	std::string command;
                
	};

}
