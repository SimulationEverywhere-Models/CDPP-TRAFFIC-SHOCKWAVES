/*******************************************************************
*
*  DESCRIPTION: class MyGenerator
*
*  AUTHOR: Tao Zhang
*
*
*  DATE: 6/11/2014
*
*******************************************************************/

#ifndef __MYGENERATOR_H
#define __MYGENERATOR_H

/** include files **/
#include "atomic.h"     // class Atomic
#include "except.h"     // class InvalidMessageException

/** forward declarations **/
class Distribution ;

/** declarations **/
class MyGenerator : public Atomic
{
public:
	MyGenerator( const string &name = "MyGenerator" );				  // Default constructor

	~MyGenerator();

	virtual string className() const
		{return "MyGenerator";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & )
			{throw InvalidMessageException();}

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	int pid;
	int initial, increment;
	Port &out ;
	Distribution *dist ;

	Distribution &distribution()
			{return *dist;}
			
};	// class MyGenerator


#endif   //__MYGENERATOR_H
