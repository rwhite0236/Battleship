// ADD COMPLETE HEADER DOCUMENTATION HERE
// Make sure you place your input files in the correct directory.



/*
Author:Raymond White

Date:12/20/20

File Name: battleship_white.cpp

Purpose: What problem does this program solve? Elaborate!
			It reads in degrees and velocities from a projectile
			and calculates the distance and sees if it hits a ship
			or not.

Inputs: What does this program need to take as input?
		This program takes an input file with two numbers
		on a line, first number being the degrees and the
		second number being the velocity of a projectile

Outputs: What does this program produce as output?
		 This program outputs projectile distance,
		 how many projectiles have hit a ship,
		 which ships were hit,
		 how many projectiles missed hitting a target,
		 what ships projectiles sunk.

Assumptions: Does this program make any assumptions?
			This program assumes that all input from the input file 
			are numbers and not other alphanumeric characters.

Error Checking: Does this program have any error checking?
				This program checks if the input file entered by the 
				user exists.
				This program also checks if the numbers from the input
				file are positive.
Be sure to document all libraries, constants, variables & major
steps appropriately throughout this program.

All variables should be declared inside of, (or local to), main.
*/

// Libraries:
#include<iostream>	//allows input from keyboard and output to monitor
#include<iomanip>	//allows output manipulation
#include<fstream>	//allows file input and output to be used
#include<cmath>		//allows the use of math functions e.g. pow
using namespace std;


// Constants: 
const double PI = 3.14159265;
const int AIRCRAFT_CARRIER_DIS = 3030;		//Distance of Aircraft Carrier
const int AIRCRAFT_CARRIER_MAX_HITS = 6;	//Maximum number of hits on Aircraft Carrier
const int BATTLESHIP_DIS = 2000;			//Distance of Battleship
const int BATTLESHIP_MAX_HITS = 5;			//Maximum number of hits on Battleship
const int DESTROYER_DIS = 1900;				//Distance of Destroyer
const int DESTROYER_MAX_HITS = 3;			//Maximum number of hits on Destroyer
const int SUBMARINE_DIS = 1000;				//Distance of Submarine
const int SUBMARINE_MAX_HITS = 2;			//Maximum number of hits on Submarine



// Function prototypes
float RadianCalc(int degrees, double PI);
float DistanceCalc(float radians, float velocity);
void PrintResults(ofstream& dout, int ammoRounds, int aircraftCarrierHits, int battleshipHits, int destroyerHits, int submarineHits, int totalHits,
				int badData, int totalMisses, float hitToRoundRatio, int AIRCRAFT_CARRIER_MAX_HITS, int BATTLESHIP_MAX_HITS, int DESTROYER_MAX_HITS, int SUBMARINE_MAX_HITS);
int TotalHitsAndMisses(int& totalHits, int& totalMisses);
int main()
{
	// Delcare all variables and state what they contain here:
	int degrees;					//holds value for degrees
	float velocity;					//holds value for velocity
	int ammoRounds = 0;				//holds value for amount of rounds fired
	int aircraftCarrierHits = 0;	//holds value for amount of hits on Aircraft Carrier
	int battleshipHits = 0;			//holds value for amount of hits on Battleship
	int destroyerHits = 0;			//holds value for amount of hits on Destroyer
	int submarineHits = 0;			//holds value for amount of hits on Submarine
	int totalMisses = 0;			//holds value for total amount of misses
	int totalHits = 0;				//holds value for total amount of hits
	float radians;					//holds value for radians
	float distance;					//holds value for distance
	float hitToRoundRatio;			//holds value for hit-to-rounds fired ratio
	int badData = 0;				//holds value for total amount of bad data lines in file
	ifstream din;					//input file variable
	ofstream dout;					//output file variable
	string inputFileName;			//user enters input file name
	
	dout << fixed << showpoint << setprecision(2);
	do
	{
		cout << "Please enter the name of the input file." << endl;
		cin >> inputFileName; //User inputs input file name
		din.open(inputFileName.c_str());
		if(!din)
			cout << inputFileName << " is not a valid input file name." << endl;


	} while (!din);//error check for existence of input file
	
	dout.open("battle.log");
	
	
		
		
		din >> degrees >> velocity;//Input file variable reads in degrees and velocity from file



		while(din)
		{

			radians = RadianCalc(degrees, PI);//calculates radians

			distance = DistanceCalc(radians, velocity);//calculates distance


			if (degrees < 0 || velocity < 0 )//error check for negative numbers
			{
				badData++;
				dout << endl;
			}//end of badData
			else if ((int)distance == AIRCRAFT_CARRIER_DIS || (int)distance == AIRCRAFT_CARRIER_DIS - 1 || (int)distance == AIRCRAFT_CARRIER_DIS + 1)
			{
				aircraftCarrierHits++;
				totalHits++;
				ammoRounds++;
				dout << distance <<'m'<< endl;
				if (aircraftCarrierHits > AIRCRAFT_CARRIER_MAX_HITS)//any rounds fired after a ship has sunk will be counted as misses
				{
					aircraftCarrierHits = aircraftCarrierHits - 1;
					TotalHitsAndMisses(totalHits, totalMisses);
				}// end of Aircraft hits
			}// end of Aircraft distance
			else if ((int)distance == BATTLESHIP_DIS || (int)distance == BATTLESHIP_DIS - 1 || (int)distance == BATTLESHIP_DIS + 1)
			{
				battleshipHits++;
				totalHits++;
				ammoRounds++;
				dout << distance <<'m'<< endl;
				if (battleshipHits > BATTLESHIP_MAX_HITS)//any rounds fired after a ship has sunk will be counted as misses
				{
					battleshipHits = battleshipHits - 1;
					TotalHitsAndMisses(totalHits, totalMisses);
				}// end of Battleship hits
			}// end of Battleship distance
			else if ((int)distance == DESTROYER_DIS || (int)distance == DESTROYER_DIS - 1 || (int)distance == DESTROYER_DIS + 1)
			{
				destroyerHits++;
				totalHits++;
				ammoRounds++;
				dout << distance <<'m'<< endl;
				if (destroyerHits > DESTROYER_MAX_HITS)//any rounds fired after a ship has sunk will be counted as misses
				{
					destroyerHits = destroyerHits - 1;
					TotalHitsAndMisses(totalHits, totalMisses);
				}//end of Destroyer hits
			}// end of Destroyer distance
			else if ((int)distance == SUBMARINE_DIS || (int)distance == SUBMARINE_DIS - 1 || (int)distance == SUBMARINE_DIS + 1)
			{
				submarineHits++;
				totalHits++;
				ammoRounds++;
				dout << distance <<'m'<< endl;
				if (submarineHits > SUBMARINE_MAX_HITS)//any rounds fired after a ship has sunk will be counted as misses
				{
					submarineHits = submarineHits - 1;
					TotalHitsAndMisses(totalHits, totalMisses);
				}//end of Submarine hits
			}//end of Submarine hits
			else
			{
				totalMisses++;
				dout << distance <<'m'<< endl;
			}//end of misses

			din >> degrees >> velocity;//LCV


		}//end of while

		hitToRoundRatio = ((float)totalHits / (float)ammoRounds) * 100;//converts hit-to-rounds fired ratio to percentage
		PrintResults(dout, ammoRounds, aircraftCarrierHits, battleshipHits, destroyerHits, submarineHits, totalHits,
			badData, totalMisses, hitToRoundRatio, AIRCRAFT_CARRIER_MAX_HITS, BATTLESHIP_MAX_HITS, DESTROYER_MAX_HITS, SUBMARINE_MAX_HITS);
			//sends output to battle.log
		din.close();
		dout.close();

	

	system ("pause");
	return 0;

} // end main

float RadianCalc(int degrees, double PI)
{
	float radians;	//holds value for calculate radians
	radians = ((float)degrees * (float)PI) / 180.0f;//calculates and converts degrees to radians
	return radians;//sends radians value to function call


}//end of RadianCalc function
//Purpose:		To calculate and convert degrees to radians.
//Precondition:	degrees must hold a value.
//Post:			Returns radians value to function call.

float DistanceCalc(float radians, float velocity)
{
	float distance;//holds value for calculated distance
	distance = (pow(velocity, 2.0f) * sin(2.0f * radians)) / 32.2f;//calculates distance
	return distance;//sends distance value to function call

}//end of DistanceCalc function
//Purpose:		To calculate the distance of each round fired.
//Precondition: radians and velocity must have values.
//Post:			Returns the calculated distance value to function call.

void PrintResults(ofstream& dout, int ammoRounds, int aircraftCarrierHits, int battleshipHits, int destroyerHits, int submarineHits, int totalHits, 
					int badData, int totalMisses, float hitToRoundRatio, int AIRCRAFT_CARRIER_MAX_HITS, int BATTLESHIP_MAX_HITS, int DESTROYER_MAX_HITS, int SUBMARINE_MAX_HITS)
{
	
	dout << ammoRounds << " rounds of ammo expended." << endl;
	dout << aircraftCarrierHits <<" out of "<< AIRCRAFT_CARRIER_MAX_HITS << " hits on Aircraft Carrier." << endl;
	dout << battleshipHits << " out of " << BATTLESHIP_MAX_HITS << " hits on Battleship." << endl;
	dout << destroyerHits << " out of " << DESTROYER_MAX_HITS <<" hits on Destroyer." << endl;
	dout << submarineHits << " out of " << SUBMARINE_MAX_HITS <<" hits on Submarine." << endl;
	dout << totalHits << " total hits." << endl;
	dout << badData << " lines of bad data in the file." << endl;
	dout << totalMisses << " rounds missed." << endl;
	dout << hitToRoundRatio << "% hit rate." << endl;
	if (aircraftCarrierHits >= AIRCRAFT_CARRIER_MAX_HITS)
		dout << "Aircraft Carrier sunk!" << endl;


	else if (battleshipHits >= BATTLESHIP_MAX_HITS)
		dout << "Battleship sunk!" << endl;

	else if (destroyerHits >= DESTROYER_MAX_HITS)
		dout << "Destroyer sunk!" << endl;

	else if (submarineHits >= SUBMARINE_MAX_HITS)
		dout << "Submarine sunk!" << endl;
	else;
	cout << "Output has been sent to battle.log. Have a nice day!" << endl;
}//end of PrintResults function
//Purpose:		To output the total amount of rounds fired, hits on each of the ships, total hits overall,
//				total amount of misses, total lines of bad data, hit-to-rounds fired ratio, and if any
//				ships were sunk to an output file.
//Precondition: None, these values do not need values.
//Post:			Outputs previously stated information to the output file battle.log.

int TotalHitsAndMisses(int& totalHits, int& totalMisses)
{
	totalHits = totalHits - 1;	//will adjust hit counter accordingly to not go over maximum ship hit value
	totalMisses++;				//will move extra hits to ships to misses
	return totalHits;			//sends totalHits value to function call
	return totalMisses;			//sends totalMisses value to function call
}//end of TotalHitsAndMisses function
//Purpose:		To calculate the total amount of hits and misses for the rounds fired.
//Precondition:	totalHits and totalMisses must have values.
//Post:			Returns the total hits and misses value to the function call.