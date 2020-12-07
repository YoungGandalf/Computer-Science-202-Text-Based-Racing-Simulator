/*
File:    Race.h
Project: CMSC 202 Project 5, Fall 2018
Author:  Adam Hereth
Data:    12/4/2018
Section: 12
Email:   ahereth1@umbc.edu
*/

#ifndef RACE_H
#define RACE_H

#include "Racer.h"
#include "Racecar.h"
#include "Truck.h"
#include "Formula.h"
#include "Lqueue.h"

#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

//Constant array for Racer names (regardless of type of racer)
const string RACERS [] = {"Mcdowell","Abdel","Wheeler","Romero","Barton","Wood","Azam","Munoz","Baird","Moon","Cantrell","Kent","Hunter","Reilly","Rivas","Copeland","Sharp","York","Henson","Sweet","Horne","Cook","Vincent","Pearson","Sabir","Palmer","Sanders","Lynn","Merrill","King","Holt","Preston","Zhang","Dominguez","Workman","Roach","Franklin","Walker","Maynard","Burris","Scott","Li","Barrett","Carson","Hutchinson","Sargent","Woodward","Leblanc","Lopez","Chen","Soto","Contreras","Sellers","Espinoza","Pierce","Masood","Giles","Garrison","Garner","Garza","Spencer","Hill","Spence","Maldonado","Hassan","Garrett","Harris","Petersen","Rogers","Hester","Molla","Murphy","Conner","Yassin","Sloan","Long","Terrell","Matthews","Whitley","Kim","Branch","Crane","Browning","Gentry","English","Mayo","Barnes","Molina","Dodson","Mccray","Hines","Malone","Whitehead","Mccarty","Marsh","Fletcher","Fuller","Aguirre","Pacheco","Ozer"};
//Constant array for Racer numbers (regardless of type)
const int RACE_NUMS [] = {73,62,86,78,75,8,65,17,58,17,71,21,64,33,62,95,11,98,34,8,83,37,61,33,86,79,12,17,36,41,84,34,22,5,62,80,46,33,45,45,65,64,50,11,96,27,68,71,25,11,41,2,37,43,75,4,34,86,62,59,92,49,87,27,42,64,5,20,97,11,68,97,32,45,96,43,94,81,17,71,84,99,6,91,68,46,50,44,18,8,67,28,12,10,44,6,92,35,17,58};

const int MAX_RACERS = 100; //Max number of racers in race
const int MIN_RACERS = 2; //Min number of racers in race
const int RAND_SEED = 10; //Constant seed for program (srand(RAND_SEED) in Race const.
const int SPEED_MOD = 15; //Percentage change for each lap (15%)

template <class T>
class Race{
public:
  // Name: Race (Default Constructor)
  // Preconditions: Creates a new race using a specific type of
  //                racer (racecar, truck, or formula 1
  // Postconditions: Asks how many cars in the race, inserts specific racer in race
  //                 and starts race. Also, srand(RAND_SEED) in constructor.
  Race();
  // Name: EnterRace
  // Preconditions: Has a race
  // Postconditions: Pushes the specific racer into the race
  void EnterRace(T newEntrant);
  // Name: StartRace
  // Preconditions: Has a race
  // Postconditions: Manages a race
  // Requests number of laps.
  // For each lap, checks to see if they crash (calls CheckCrash)
  // Then compares speed of each racer, if one racer is faster, swaps racers
  // At the end of chosen number of laps, the winner is who is in front
  void StartRace();
  // Name: GetRandomRacer
  // Preconditions: Has an array of names and numbers
  // Postconditions: Returns a random number from array of names/numbers
  int GetRandomRacer();
  // Name: CheckCrash
  // Preconditions: Has a race
  // Postconditions: Checks if a racer crashes (1/200 chance), if they crash speed = 0
  //          SetIsCrashed changes, Indicates crash, moves crashed racer to end of race
  void CheckCrash(int);
  // Name: RacerSpeed
  // Preconditions: Has a race and racers left in race
  // Postconditions: Calculates updated speed for a specific racer each lap
  void RacerSpeed(int);
  // Name: DisplayRacers
  // Preconditions: Has a race and racers left in race
  // Postconditions: Displays each racer in race (including if they crashed)
  void DisplayRacers();
private:
  Lqueue<T> race;
};

#endif

//***************************************************************************
//***********************Implement Race Here*********************************
template <class T>
Race<T>::Race()
{
  srand(RAND_SEED);
  int racers;
  do
    {
      cout << "How many racers would you like to have?" << endl;
      cin >> racers;
    }while(racers<MIN_RACERS and racers>MAX_RACERS);
    
  for(int i=0;i<racers;i++)
    {
      //creates a templated racer and passes a random index for the RACER array and
      //RACE_NUMS array
      T newRacer(RACERS[GetRandomRacer()],RACE_NUMS[GetRandomRacer()]);
      EnterRace(newRacer);
    }
  StartRace();
}

template <class T>
void Race<T>::EnterRace(T newRacer)
{
  race.Push(newRacer);
}

template <class T>
void Race<T>::StartRace()
{
  cout << "Pole Position" << endl;
  DisplayRacers();

  int laps = 0;
  do
    {
      cout << "How many laps would you like to do?" << endl;
      cin >> laps;
    }while(laps < 0 || laps > 1000);

  for(int lap = 0; lap < laps; lap++)
    {
      cout << "Lap " << lap+1 << endl;
      for(int i=0; i<race.GetSize();i++)
	{
	  RacerSpeed(i);
	  CheckCrash(i);
	}
      for(int i = 1;i<race.GetSize();i++)
	{
	  if(race[i].GetSpeed() > race[i-1].GetSpeed())
	    {
	      race.Swap(i);
	    }
	}
      DisplayRacers();
    }
  cout << "The winner of the race is " << race.Front() << endl;
}

template <class T>
int Race<T>::GetRandomRacer()
{
  int randNum = rand() % 100;
  return randNum;
}

template <class T>
void Race<T>::CheckCrash(int racerNum)
{
  if(rand()% 1000 < 5)
    {
      //sets the racer at that specific index to crash, set speed to 0, output crash and
      //put them at the end of the Lqueue
      race[racerNum].SetIsCrashed(true);
      race[racerNum].SetSpeed(0);
      cout << "Crash!!!" << race[racerNum] << endl;
      race.RemoveInsertEnd(racerNum);
    }
}

template <class T>
void Race<T>::RacerSpeed(int racerNum)
{
  int curSpeed = race[racerNum].GetSpeed();
  double modSpeed = rand()% SPEED_MOD + 1;
  if(rand()% 2)
    //takes the racers speed and increases it
    race[racerNum].SetSpeed(curSpeed + (curSpeed*(modSpeed/100)));
  else
    //takes the racers speed and decreases it
    race[racerNum].SetSpeed(curSpeed - (curSpeed*(modSpeed/100)));
}

template <class T>
void Race<T>::DisplayRacers()
{
  for(int i=0;i<race.GetSize();i++)
      cout << race[i] << endl;
}

//Don't forget to seed srand with 10 srand(RAND_SEED)

