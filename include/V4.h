/// \mainpage The V4 class
/// \section overview Overview
/// The V4 library provides a class for three- and four-vectors.
/// The methods in the class provides the usual information on the vectors
/// and overloads the "+", "-", "*" operators. \n
/// The V4 class utilizes the  <a href="http://proj-clhep.web.cern.ch/proj-clhep/"> CLHEP </a> libraries
/// for some vector operations, and the units system.
/// &copy; <b>Maurizio Ungaro</b>\n
/// 	- <i>home-page:</i> <a href="http://www.jlab.org/~ungaro" target="_blank">Mauree's Page</a>\n
/// 	- <i>e-mail:</i> ungaro@jlab.org\n\n\n
/// \file V4.h
/// Defines the V4 class
/// \author \n &copy; Maurizio Ungaro
/// \author e-mail: ungaro@jlab.org\n\n\n

#ifndef V4_H
#define V4_H

#include "G4ParticleTable.hh"


// C++ includes
#include <iostream>
#include <cmath>

class V3 {
public:
	double x, y, z;

	V3() { x = y = z = 0; }              ///< by default components initialized to zero
	V3(double, double, double);

	void init(double, double, double);

	void set(double, double, double);     ///< set 3 vector given modulus, theta and phi

	void l();                         ///< print components on screen
	double mod();                        ///< return modulus
	double theta();                      ///< return theta of vector
	double phi();                        ///< return phi of vector (0 to 360)
	double phiH();                       ///< return phi of vector (-180 to 180)

	V3 Xrot(double);    ///< Rotates around X
	V3 Yrot(double);    ///< Rotates around T
	V3 Zrot(double);    ///< Rotates around Z

	// Overloading + and - and *
	V3 operator+(V3);             ///< sum of 3-vectors
	V3 operator-(V3);             ///< difference of 3-vectors
	V3 operator*(double);          ///< scale magnitude of 3 vector
	V3 operator/(double);          ///< scale magnitude of 3 vector
	double operator*(V3);          ///< dot product of 3-vectors

	friend std::ostream &operator<<(std::ostream &, V3);
};

class V4 : public V3 {
public:
	double t;

	V4() { x = y = z = t = 0; }                  ///< by default components initialized to zero
	V4(double, double, double, double);

	// V4 from V3 and pid
	V4(double, double, double, int);

	void init(double, double, double, double);

	void beam(double, double);                    ///< Sets 4 vector assuming it's along z axis
	void starget(double);                        ///< Sets 4 vector assuming it's static

	void l();                                 ///< print components on screen
	double mass();                               ///< return square of mass of vector
	double energy(V3 mom, double mass);           ///< return sqrt(mom^2+mass^2)



	// Overloading + and - and *
	V4 operator+(V4);                       ///< sum of 4-vectors
	V4 operator-(V4);                       ///< difference of 4-vectors
	V4 operator*(double);                    ///< scale magnitude of 4 vector
	V4 operator/(double);                    ///< scale magnitude of 4 vector
	double operator*(V4 dprod);              ///< dot product of 4-vectors

	friend std::ostream &operator<<(std::ostream &, V4);
};

double Vcosangle(V3, V3);

double Vcosangle(V4, V4);

V4 res_to_lab(V4 H, V4 x);

V4 lab_to_res(V4 H, V4 x);

// clas specific
int sector(V4 p);

double loc_phi(V4 p);

#endif

