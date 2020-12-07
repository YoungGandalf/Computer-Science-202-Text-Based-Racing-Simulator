/*
File:    Racer.cpp
Project: CMSC 202 Project 5, Fall 2018
Author:  Adam Hereth
Data:    12/4/2018
Section: 12
Email:   ahereth1@umbc.edu
*/

#include "Racer.h"

//assign values to racer
Racer::Racer()
{
  m_name = "Racer";
  m_number = 1;
  m_speed = 100;
  m_isCrashed = false;
}

Racer::Racer(string name, int num, int speed)
{
  m_name = name;
  m_number = num;
  m_speed = speed;
}

void Racer::SetValues(string name, int num, int speed)
{
  m_name = name;
  m_number = num;
  m_speed = speed;
}
string Racer::GetName() const
{
  return m_name;
}
void Racer::SetName(string name)
{
  m_name = name;
}
int Racer::GetNumber() const
{
  return m_number;
}
void Racer::SetNumber(int num)
{
  m_number = num;
}
int Racer::GetSpeed() const
{
  return m_speed;
}
void Racer::SetSpeed(int speed)
{
  m_speed = speed;
}
bool Racer::GetIsCrashed() const
{
  return m_isCrashed;
}
void Racer::SetIsCrashed(bool crash)
{
  m_isCrashed = crash;
}

//doesn't need to be implemented since the child classes will be using it
ostream& operator<<(ostream& output, const Racer& o)
{
}

