/*
File:    Formula.cpp
Project: CMSC 202 Project 5, Fall 2018
Author:  Adam Hereth
Data:    12/4/2018
Section: 12
Email:   ahereth1@umbc.edu
*/

#include "Formula.h"

Formula::Formula()
{
  SetValues("",1,220);
}

ostream& operator<<(ostream& output, const Formula& o)
{
  output << o.ToString() << " ";
  if(!o.GetIsCrashed())
    {
      output << o.GetName() << " (#" << o.GetNumber() << ") going "
	     << o.GetSpeed() << "MPH";
    }
  else
    output << o.GetName() << " crashed and is out of the race.";

  return output;
}
