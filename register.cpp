/*******************************************************************
*
*  DESCRIPTION: Atomic Model User Equipment (MessageQueue)
*
*  AUTHOR: Tao Zhang
*
*  DATE: 20/10/2014
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "MyGenerator.h"


void MainSimulator::registerNewAtomics()
{
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<MyGenerator>() , "MyGenerator" ) ;
}
