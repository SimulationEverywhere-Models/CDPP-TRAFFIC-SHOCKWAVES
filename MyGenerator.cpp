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

/** include files **/
#include "MyGenerator.h"       // base header
#include "message.h"       // class InternalMessage 
#include "mainsimu.h"      // class Simulator
#include "distri.h"        // class Distribution 
#include "strutil.h"       // str2Value( ... )

/*******************************************************************
* Function Name: MyGenerator
* Description: constructor
********************************************************************/
MyGenerator::MyGenerator( const string &name )
: Atomic( name )
, out( addOutputPort( "out" ) )
{
	try
	{
		dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );
		MASSERT( dist ) ;
		for ( register int i = 0; i < dist->varCount(); i++ )
		{
			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar( i ) ) ) ;
			dist->setVar( i, str2Value( parameter ) ) ;
		}

		if( MainSimulator::Instance().existsParameter( description(), "initial" ) )
			initial = str2Int( MainSimulator::Instance().getParameter( description(), "initial" ) );
		else
			initial = 0;

		if( MainSimulator::Instance().existsParameter( description(), "increment" ) )
			increment = str2Int( MainSimulator::Instance().getParameter( description(), "increment" ) );
		else
			increment = 1;

	} catch( InvalidDistribution &e )
	{
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	} catch( MException &e )
	{
		MTHROW( e ) ;
	}
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &MyGenerator::initFunction()
{
	pid = initial;
	holdIn( active, Time::Zero ) ;
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &MyGenerator::internalFunction( const InternalMessage & )
{
	holdIn( active, Time( static_cast< float >( fabs( distribution().get() ) ) ) ) ;
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &MyGenerator::outputFunction( const InternalMessage &msg )
{
	Time threshold1(0,0,2,0);
	Time threshold2(0,0,5,0);
	sendOutput( msg.time(), out, pid ) ;
	if(msg.time() > threshold1 )
	{
		dist->setVar( 0, 2 ) ;
	}
	else if (msg.time() > threshold2 )
	{
		dist->setVar( 0, 5 ) ;
	}
	pid += increment;
	return *this ;
}

MyGenerator::~MyGenerator()
{
	delete dist;
}
