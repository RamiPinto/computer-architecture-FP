/*
* nasteroids-par
*
*Universidad Carlos III de Madrid
*Bachelor's Degree in Computer Science and Engineering
*Computer Architecture - Main Programming Assigment
*
*Created on November 29, 2017, 12:00 AM
*/

/*
* @author: Daniel Martín Blázquez, Ramiro Pinto Prieto
* @version: 1.0
*/

#include <iostream>
#include <vector>		//Vectors
#include <fstream>
#include <random>		//random nmber generator
#include <iomanip>	//setprecision
#include <cstdlib> //Exit, exit failure
#include <cmath> //Math functions
#include <omp.h> //omp_set_num_threads
using namespace std;

//Constants of the program
const double gravConst=6.674e-5;
const double timeInterval=0.1;
const double minimumDistance=2.0;
const double width=200.0;
const double height=200.0;
const double rayWidth=4.0;
const double m=1000.0;
const double sdm=50.0;
const int n_Threads=4;

/*Function that checks that input arguments are in correct format and fullfil all the requirements */
bool checker(int argc, char * argv[]){
	//Check number of arguments
	if(argc!=6){
		return true;
	}
	bool bResult=false;
	string arguments[6];
	#pragma omp parallel
	{
		//Transform arguments to string to check easier
		#pragma omp for
		for(unsigned int i = 0; i < 6; i++){
			arguments[i] = string(argv[i]);
		}

		//Integer positive arguments check
		#pragma omp for
		for(unsigned int i = 1; i<4; i++){
			string::size_type sz;
			int result=stoi(arguments[i], &sz);
			if(arguments[i].substr(sz).length()!=0||result<0){
				bResult=true;
			}
		}

		//Seed argument check
		#pragma omp single
		{
		string::size_type sz;
		int result=stoi(arguments[5], &sz);
		if(arguments[5].substr(sz).length()!=0||result<=0){
			bResult=true;
		}
		}

		//Double argument check
		#pragma omp single
		{
		string::size_type sz;
		double resultd;
		resultd=stod(arguments[4], &sz);
		if(arguments[4].substr(sz).length()!=0||resultd<0||resultd>height){
			bResult=true;
		}
		}
	}
	return bResult;
}

class Asteroid {
	double xPosition;
	double yPosition;
	double mass;
	double xVelocity;
	double yVelocity;

public:
	//Constructors
	Asteroid(double, double, double);
	Asteroid();
	//Member functions
	double getXPosition();
	double getYPosition();
	double getMass();
	double getXVelocity();
	double getYVelocity();
	void setXVelocity(double);
	void setYVelocity(double);
	void updatePosition();
};

Asteroid::Asteroid(double x, double y, double m){
	xPosition=x;
	yPosition=y;
	xVelocity=0.0;
	yVelocity=0.0;
	mass=m;
}

Asteroid::Asteroid(){
	xPosition=0.0;
	yPosition=0.0;
	xVelocity=0.0;
	yVelocity=0.0;
	mass=0.0;
}

double Asteroid::getXPosition(){
	return xPosition;
}
double Asteroid::getYPosition(){
	return yPosition;
}
double Asteroid::getMass(){
	return mass;
}
double Asteroid::getXVelocity(){
	return xVelocity;
}
double Asteroid::getYVelocity(){
	return yVelocity;
}
void Asteroid::setXVelocity(double x){
	xVelocity=x;
}
void Asteroid::setYVelocity(double y){
	yVelocity=y;
}

void Asteroid::updatePosition(){
	xPosition=xPosition+xVelocity*timeInterval;
	yPosition=yPosition+yVelocity*timeInterval;

	//Rebound effect
	#pragma omp parallel
	{

	#pragma omp single
	if(xPosition<0){
		xPosition=2.0;
		xVelocity*=-1;
	}

	#pragma omp single
	if(yPosition<0){
		yPosition=2.0;
		yVelocity*=-1;
	}

	#pragma omp single
	if(xPosition>width){
		xPosition=width-2;;
		xVelocity*=-1;
	}

	#pragma omp single
	if(yPosition>width){
		yPosition=width-2;;
		yVelocity*=-1;
	}
	}
}


class Planet {
	double xPosition;
	double yPosition;
	double mass;
public:
	//Constructors
	Planet(double, double, double);
	Planet();
	//Membre functions
	double getXPosition();
	double getYPosition();
	double getMass();
};

Planet::Planet(double x, double y, double m){
	xPosition=x;
	yPosition=y;
	mass=m;
}

Planet::Planet(){
	xPosition=0.0;
	yPosition=0.0;
	mass=0.0;
}

double Planet::getXPosition(){
	return xPosition;
}
double Planet::getYPosition(){
	return yPosition;
}
double Planet::getMass(){
	return mass;
}

class Universe {
	double pos_ray;
	vector<Asteroid> asteroids;
	vector<Planet> planets;
public:
	// Constructor
	Universe(int, int, double, int);
	//Member functions
	void initialPrint(string, int, int);
	void finalPrint(string);
	void updateVelocities();
	void laserExecution();
	void performIteration();
};

Universe::Universe(int n_asteroids, int n_planets, double ray, int seed){
	pos_ray=ray;
	asteroids.resize(n_asteroids);
	planets.resize(n_planets);

	// Random distributions
	default_random_engine re{seed};
	uniform_real_distribution<double> xdist{0.0, std::nextafter(width,
	std :: numeric_limits<double>::max())};
	uniform_real_distribution<double> ydist{0.0, std::nextafter(height,
	std :: numeric_limits<double>::max())};
	normal_distribution<double> mdist{m, sdm};

	#pragma omp parallel
	{
	//Initialize asteroids
	#pragma omp for
	for(unsigned int i=0; i<asteroids.size(); i++){
		double x = xdist(re);
		double y = ydist(re);
		double m_r = mdist(re);
		asteroids[i]=Asteroid(x, y, m_r);
	}

	//Initialize planets
	#pragma omp for
	for(unsigned int i=0; i<planets.size(); i++){
		unsigned int order = i%4;
		double x=0;
		double y=0;
		double m_r=0;
		switch(order){
			case 0 :
				y = ydist(re);
				m_r = mdist(re);
				planets[i]=Planet(0, y, 10*m_r);
			break;

			case 1 :
				x = xdist(re);
				m_r = mdist(re);
				planets[i]=Planet(x, 0, 10*m_r);
			break;

			case 2 :
				y = ydist(re);
				m_r = mdist(re);
				planets[i]=Planet(width, y, 10*m_r);
			break;

			case 3 :
				x = xdist(re);
				m_r = mdist(re);
				planets[i]=Planet(x, height, 10*m_r);
			break;

			default :
				cerr<<"[ERROR] Error while setting planets possition"<<endl;
				exit(EXIT_FAILURE);
			break;
		}
	}
	}
}

/*Print init_conf.txt*/
void Universe::initialPrint(string file, int iterations, int seed){
	ofstream in_file (file, ios::out | ios::trunc);

	if (in_file.is_open()){
		in_file<<fixed;
		in_file << asteroids.size() << " " << iterations << " " << planets.size() << " " << setprecision(3) << pos_ray << " " << seed << "\r\n";

		for(unsigned int ac=0; ac<asteroids.size(); ac++){
			in_file << fixed;
			in_file << setprecision(3) << asteroids[ac].getXPosition() << " " << setprecision(3) << asteroids[ac].getYPosition();
			in_file << " " << setprecision(3) <<  asteroids[ac].getMass() << "\r\n";
		}

		for(unsigned int pc=0; pc<planets.size(); pc++){
			in_file << fixed;
			in_file << setprecision(3) << planets[pc].getXPosition() << " " << setprecision(3) << planets[pc].getYPosition();
			in_file << " " << setprecision(3) << planets[pc].getMass() << "\r\n";
		}

		in_file << fixed;
		in_file << "0.000 " << setprecision(3) << pos_ray << "\r\n";
		in_file.close();
	}
}

/*Print out.txt*/
void Universe::finalPrint(string file){
	ofstream in_file (file, ios::out | ios::trunc);

	if (in_file.is_open()){
		for(unsigned int ac=0; ac<asteroids.size(); ac++){
			in_file << fixed;
			in_file << setprecision(3) << asteroids[ac].getXPosition() << " " << setprecision(3) << asteroids[ac].getYPosition();
			in_file << " " << setprecision(3) <<  asteroids[ac].getXVelocity() << " " << setprecision(3) << asteroids[ac].getYVelocity();
			in_file << " " << setprecision(3) << asteroids[ac].getMass() << "\r\n";
		}
	}
}

/*Calculate velocities according to gravitational forces acting on each asteroid*/
void Universe::updateVelocities(){
	vector<vector<vector<double>>> matrix(asteroids.size(), vector<vector<double>>(asteroids.size(), vector<double>(2)));
	double xForceTotal;
	double yForceTotal;
	for(unsigned int i=0; i<asteroids.size(); i++){
		xForceTotal=0;
		yForceTotal=0;
		#pragma omp parallel for
		for(unsigned int j=0; j<asteroids.size(); j++){
			if(j<=i){
				xForceTotal+=matrix[i][j][0];
				yForceTotal+=matrix[i][j][1];
			}
			else{
				double dist=hypot((asteroids[i].getXPosition() - asteroids[j].getXPosition()), (asteroids[i].getYPosition() - asteroids[j].getYPosition()));
				if(dist>minimumDistance){
					double slope=(asteroids[i].getYPosition() - asteroids[j].getYPosition())/(asteroids[i].getXPosition() - asteroids[j].getXPosition());
					if(!::isinf(slope)&&(slope>1||slope<-1)){
						slope=slope-trunc(slope);
					}
					double alpha=atan(slope);
					double partialForce=(gravConst*asteroids[i].getMass()*asteroids[j].getMass())/pow(dist, 2);
					double xPartialForce=partialForce*cos(alpha);
					double yPartialForce=partialForce*sin(alpha);
					xForceTotal+=xPartialForce;
					yForceTotal+=yPartialForce;
					matrix[j][i][0]=-xPartialForce;
					matrix[j][i][1]=-yPartialForce;
				}
			}
		}

		#pragma omp parallel for
		for(unsigned int j=0; j<planets.size(); j++){
			double dist=hypot((asteroids[i].getXPosition() - planets[j].getXPosition()), (asteroids[i].getYPosition() - planets[j].getYPosition()));
			double slope=(asteroids[i].getYPosition() - planets[j].getYPosition())/(asteroids[i].getXPosition() - planets[j].getXPosition());
			if(!::isinf(slope)&&(slope>1||slope<-1)){
				slope=slope-trunc(slope);
			}
			double alpha=atan(slope);
			double partialForce=(gravConst*asteroids[i].getMass()*asteroids[j].getMass())/pow(dist, 2);
			xForceTotal=partialForce*cos(alpha);
			yForceTotal=partialForce*sin(alpha);
		}
		asteroids[i].setXVelocity(asteroids[i].getXVelocity()+(xForceTotal/asteroids[i].getMass())*timeInterval);
		asteroids[i].setYVelocity(asteroids[i].getYVelocity()+(yForceTotal/asteroids[i].getMass())*timeInterval);
	}
}

void Universe::laserExecution(){
	unsigned int i=0;
	while(i<asteroids.size()){
		if(pos_ray-rayWidth/2<=asteroids[i].getYPosition()&&asteroids[i].getYPosition()<=pos_ray+rayWidth/2){
			asteroids.erase(asteroids.begin()+i);
		}
		else{
			i++;
		}
	}
}

/*Invoke the functions that perform that actions required in each iteration in the corresponding order*/
void Universe::performIteration(){
	updateVelocities();
	#pragma omp parallel for
	for(unsigned int i=0; i<asteroids.size(); i++){
		asteroids[i].updatePosition();
	}
	laserExecution();
}

/*Main method of the program. It checks the input arguments, prints the initial confuration and after performing the required iterations prints the result
in the out.txt*/
int main(int argc, char *argv[]){
	omp_set_num_threads(n_Threads);

    if(checker(argc, argv)){
			cout << "nasteroids-seq: Wrong arguments.\nCorrect use:\nnasteroids-seq num_asteroids num_iterations num_planets pos_ray seed"<< endl;
			return -1;
    }

	string arguments[6];
	#pragma omp parallel for
    for(unsigned int i = 0; i < 6; i++){
		arguments[i] = string(argv[i]);
    }

	int num_asteroids=stoi(arguments[1], nullptr);
	int num_iterations=stoi(arguments[2], nullptr);
	int num_planets=stoi(arguments[3], nullptr);
	double pos_ray=stod(arguments[4], nullptr);
	int seed=stoi(arguments[5], nullptr);

	Universe myUniverse(num_asteroids, num_planets, pos_ray, seed);
	myUniverse.initialPrint("init_conf.txt", num_iterations, seed);

	for(int counter=0; counter<num_iterations; counter++){
		myUniverse.performIteration();
	}

	myUniverse.finalPrint("out.txt");

    return 0;
}
