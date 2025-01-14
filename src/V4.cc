#include "V4.h"

// CLHEP includes
// Namespace includes physical constants
// and system of units
#include <CLHEP/Vector/ThreeVector.h>
#include "CLHEP/Units/PhysicalConstants.h"

using namespace std;

// V3 functions
V3::V3(double X, double Y, double Z) {
	x = X;
	y = Y;
	z = Z;
}

void V3::init(double X, double Y, double Z) {
	x = X;
	y = Y;
	z = Z;
}

// print components on screen 
void V3::l()        ///< print components on screen
{
	cout << "\t x = " << x;
	cout << "\t y = " << y;
	cout << "\t z = " << z << endl;
}

ostream &operator<<(ostream &stream, V3 V) {
	stream << " (" << V.x << ", " << V.y << ", " << V.z << ")";
	return stream;
}

// return modulus
double V3::mod()   ///< return modulus
{ return sqrt(x * x + y * y + z * z); }

// return theta of vector (radians) - use Hep3Vector
double V3::theta() ///< return theta of vector (radians) - use Hep3Vector
{
	CLHEP::Hep3Vector V(x, y, z);
	return V.theta();
}

// return phi of vector - use Hep3Vector but translates to 0 - 360
double V3::phi()  ///< return phi of vector (radians) - use Hep3Vector
{
	// Hep3Vector returns phi from -180 to 180.
	CLHEP::Hep3Vector V(x, y, z);
	double phi = V.phi();
	if (phi >= 0) return phi;
	else return 2 * CLHEP::pi + phi;
}

// return phi of vector - use Hep3Vector
double V3::phiH()  ///< return phi of vector (radians) - use Hep3Vector
{
	// Hep3Vector returns phi from -180 to 180. 
	CLHEP::Hep3Vector V(x, y, z);
	return V.phi();
}

// set 3 vector given modulus, theta and phi
void V3::set(double mod, double theta, double phi)  ///< set 3 vector given modulus, theta and phi
{
	x = mod * sin(theta) * cos(phi);
	y = mod * sin(theta) * sin(phi);
	z = mod * cos(theta);
}

// scale magnitude of 3 vector
V3 V3::operator*(double scale) ///< scale magnitude of 3 vector
{
	V3 scaled(
			x * scale,
			y * scale,
			z * scale
	);
	return scaled;
}

// scale magnitude of 3 vector
V3 V3::operator/(double scale) ///< scale magnitude of 3 vector
{
	V3 scaled(
			x / scale,
			y / scale,
			z / scale
	);
	return scaled;
}

// sum of 3-vectors
V3 V3::operator+(V3 second_v3)  ///< sum of 3-vectors
{
	V3 added(
			second_v3.x + x,
			second_v3.y + y,
			second_v3.z + z
	);
	return added;
}

// difference of 3-vectors
V3 V3::operator-(V3 diff)  ///< difference of 3-vectors
{
	V3 subtracted(
			x - diff.x,
			y - diff.y,
			z - diff.z
	);

	return subtracted;
}

// dot product
double V3::operator*(V3 prod)  ///< dot product
{
	double s = 0;

	s += x * prod.x;
	s += y * prod.y;
	s += z * prod.z;

	return s;
}


// Rotation of 3 vector in 3D space around X-axis of angle theta
V3 V3::Xrot(double theta) {
	double R[3][3];      // Rotation matrix
	V3 res;               // result

	// Rotation matrix
	R[0][0] = 1;
	R[1][0] = 0;
	R[2][0] = 0;

	R[0][1] = 0;
	R[1][1] = cos(theta);
	R[2][1] = -sin(theta);

	R[0][2] = 0;
	R[1][2] = sin(theta);
	R[2][2] = cos(theta);

	res.x = R[0][0] * x + R[0][1] * y + R[0][2] * z;
	res.y = R[1][0] * x + R[1][1] * y + R[1][2] * z;
	res.z = R[2][0] * x + R[2][1] * y + R[2][2] * z;
	return res;
}

// Rotation of 3 vector in 3D space around Y-axsis of angle theta
V3 V3::Yrot(double theta) {
	double R[3][3];      // Rotation matrix
	V3 res;               // result

	// Rotation matrix	
	R[0][0] = cos(theta);
	R[1][0] = 0;
	R[2][0] = sin(theta);

	R[0][1] = 0;
	R[1][1] = 1;
	R[2][1] = 0;

	R[0][2] = -sin(theta);
	R[1][2] = 0;
	R[2][2] = cos(theta);


	res.x = R[0][0] * x + R[0][1] * y + R[0][2] * z;
	res.y = R[1][0] * x + R[1][1] * y + R[1][2] * z;
	res.z = R[2][0] * x + R[2][1] * y + R[2][2] * z;
	return res;
}

// Rotation of 3 vector in 3D space around Z-axsis of angle theta
V3 V3::Zrot(double theta) {
	double R[3][3];      // Rotation matrix
	V3 res;               // result

	// Rotation matrix	
	R[0][0] = cos(theta);
	R[1][0] = -sin(theta);
	R[2][0] = 0;

	R[0][1] = sin(theta);
	R[1][1] = cos(theta);
	R[2][1] = 0;

	R[0][2] = 0;
	R[1][2] = 0;
	R[2][2] = 1;

	res.x = R[0][0] * x + R[0][1] * y + R[0][2] * z;
	res.y = R[1][0] * x + R[1][1] * y + R[1][2] * z;
	res.z = R[2][0] * x + R[2][1] * y + R[2][2] * z;
	return res;
}


// %%%%%%%%%%%%
// V4 functions
// %%%%%%%%%%%%
V4::V4(double X, double Y, double Z, double T) {
	V3::init(X, Y, Z);
	t = T;
}

void V4::init(double a, double b, double c, double d) {
	V3::init(a, b, c);
	t = d;
}

// print components on screen
void V4::l()   ///< print components on screen
{
	cout << "\t t = " << t << "  ";
	V3::l();
}

ostream &operator<<(ostream &stream, V4 V) {
	stream << " (" << V.x << ", " << V.y << ", " << V.z << ", " << V.t << ")";
	return stream;
}


// return square of mass of vector
double V4::mass() ///< return square of mass of vector
{ return t * t - pow(mod(), 2); }


// return sqrt(mom^2+mass^2)
double energy(V3 mom, double mass) ///< return sqrt(mom^2+mass^2)
{ return sqrt(mom.mod() * mom.mod() + mass * mass); }


// scale magnitude of 4 vector
V4 V4::operator*(double scale) ///< scale magnitude of 4 vector
{
	V4 scaled(
			x *scale,
			y *scale,
			z *scale,
			t *scale
	);
	return scaled;
}

// scale magnitude of 4 vector
V4 V4::operator/(double scale) ///< scale magnitude of 4 vector
{
	V4 scaled(
			x / scale,
			y / scale,
			z / scale,
			t / scale
	);
	return scaled;
}


//  sum of 4-vectors
V4 V4::operator+(V4 add)  ///< sum of 4-vectors
{
	V4 added(
			add.x + x,
			add.y + y,
			add.z + z,
			add.t + t
	);
	return added;
}

// difference of 4-vectors
V4 V4::operator-(V4 diff) ///< difference of 4-vectors
{
	V4 subtracted(
			x - diff.x,
			y - diff.y,
			z - diff.z,
			t - diff.t
	);

	return subtracted;
}

// dot product of 4-vectors
double V4::operator*(V4 prod)  ///< dot product of 4-vectors
{
	double s = 0;

	s += t * prod.t;
	s -= x * prod.x;
	s -= y * prod.y;
	s -= z * prod.z;

	return s;
}

// returns the cos of the angles between two 3-vectors
double Vcosangle(V3 a, V3 b) ///< returns the cos of the angles between two 3-vectors
{
	double s, m;
	s = a * b;
	m = a.mod() * b.mod();
	return s / m;
}

// returns the cos of the angles between two 4-vectors
double Vcosangle(V4 a, V4 b) ///< returns the cos of the angles between two 4-vectors
{
	double s, m;
	s = a.t * b.t - a * b;
	m = a.mod() * b.mod();
	return s / m;
}


int sector(V4 p) {
	int sect = (int) ((p.phi() / CLHEP::degree + 30) / 60 + 1);
	if (sect == 7) sect = 1;
	return sect;
}

double loc_phi(V4 p) {
	int s = sector(p) - 1;
	if (p.phi() / CLHEP::degree < 330) return (p.phi() / CLHEP::degree - 60 * s) * CLHEP::degree;
	if (p.phi() / CLHEP::degree >= 330) return (p.phi() / CLHEP::degree - 360) * CLHEP::degree;
	return 0;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Lorentz transformation: x' = Ax, where A = A(beta)
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
V4 lorentz(V4 beta, V4 x) {
	double b[4];       // Beta of transformation
	double xc[4];      // Coordinates in initial system
	double yc[4];      // Coordinates in final system
	double A[4][4];    // Lorentz matrix
	double g;          // gamma = 1/sqrt(1-beta^2)
	V4 y;              // y = x'= Ax

	g = 1 / (sqrt(1 - beta.mod() * beta.mod()));

	b[1] = beta.x;
	b[2] = beta.y;
	b[3] = beta.z;

	xc[0] = x.t;
	xc[1] = x.x;
	xc[2] = x.y;
	xc[3] = x.z;

	// Define Matrix A

	A[0][0] = g;

	for (int i = 1; i < 4; i++) {
		A[0][i] = -g * b[i];
		A[i][0] = -g * b[i];
		for (int j = 1; j < 4; j++) {
			A[i][j] = (g - 1.0) * (b[i]) * (b[j]) / (beta.mod() * beta.mod());
			if (i == j)
				A[i][j] = 1.0 + (g - 1.0) * (b[j]) * (b[j]) / (beta.mod() * beta.mod());
		}
	}


	// Now define y = Ax
	for (int i = 0; i < 4; i++)
		yc[i] = A[i][0] * xc[0] +
				A[i][1] * xc[1] +
				A[i][2] * xc[2] +
				A[i][3] * xc[3];

	y.t = yc[0];
	y.x = yc[1];
	y.y = yc[2];
	y.z = yc[3];

	return y;
}

// %%%%%%%%%
// Rotations
// %%%%%%%%%

// Rotation of 4 vector x around x-axis of angle theta
V4 Xrot(V4 x, double theta) {
	// Rotation matrix
	double R[3][3];
	V4 y;

	R[0][0] = 1;
	R[1][0] = 0;
	R[2][0] = 0;

	R[0][1] = 0;
	R[1][1] = cos(theta);
	R[2][1] = -sin(theta);

	R[0][2] = 0;
	R[1][2] = sin(theta);
	R[2][2] = cos(theta);

	y.x = R[0][0] * x.x + R[0][1] * x.y + R[0][2] * x.z;
	y.y = R[1][0] * x.x + R[1][1] * x.y + R[1][2] * x.z;
	y.z = R[2][0] * x.x + R[2][1] * x.y + R[2][2] * x.z;
	y.t = x.t;

	return y;
}


// Rotation of 4 vector x around y-axis of angle theta
V4 Yrot(V4 x, double theta) {
	// Rotation matrix
	double R[3][3];
	V4 y;

	R[0][0] = cos(theta);
	R[1][0] = 0;
	R[2][0] = sin(theta);

	R[0][1] = 0;
	R[1][1] = 1;
	R[2][1] = 0;

	R[0][2] = -sin(theta);
	R[1][2] = 0;
	R[2][2] = cos(theta);


	y.x = R[0][0] * x.x + R[0][1] * x.y + R[0][2] * x.z;
	y.y = R[1][0] * x.x + R[1][1] * x.y + R[1][2] * x.z;
	y.z = R[2][0] * x.x + R[2][1] * x.y + R[2][2] * x.z;
	y.t = x.t;

	return y;
}


// Rotation of 4 vector x around z-axis of angle theta
V4 Zrot(V4 x, double theta) {
	// Rotation matrix
	double R[3][3];
	V4 y;

	R[0][0] = cos(theta);
	R[1][0] = -sin(theta);
	R[2][0] = 0;

	R[0][1] = sin(theta);
	R[1][1] = cos(theta);
	R[2][1] = 0;

	R[0][2] = 0;
	R[1][2] = 0;
	R[2][2] = 1;

	y.x = R[0][0] * x.x + R[0][1] * x.y + R[0][2] * x.z;
	y.y = R[1][0] * x.x + R[1][1] * x.y + R[1][2] * x.z;
	y.z = R[2][0] * x.x + R[2][1] * x.y + R[2][2] * x.z;
	y.t = x.t;

	return y;
}

// If x is in the resonance CM, having momentum H,
// then it returns x in the LAB
V4 res_to_lab(V4 H, V4 x) {
	V4 boost;
	V4 z;                                    // Result of boost
	V4 tmp;                                  // First rotation
	V4 y;                                    // Result

	// First, calculus of boost == speed of center of mass with component z only.
	// Energy is not important, set to 0;

	boost.t = boost.x = boost.y = 0;
	boost.z = -H.mod() / H.t;

	z = lorentz(boost, x);             // Perform the boost
	tmp = Yrot(z, H.theta());         // Rotation of -theta(H) in order to overlap z' axis with z axis
	y = Zrot(tmp, -H.phi() - CLHEP::pi);      // Rotation of -phi(H) in order to overlap x' axis with x axis

	return y;
}

// If x is in the Lab, and the resonance has momentum H,
// then it returns x in the resonance
V4 lab_to_res(V4 H, V4 x) {
	V4 boost;
	V4 z;                                    // Result of boost
	V4 tmp;                                  // First rotation
	V4 y;                                    // Result

	// Inverse of the above operation

	boost.t = boost.x = boost.y = 0;
	boost.z = H.mod() / H.t;

	tmp = Zrot(x, H.phi() + CLHEP::pi);  // Rotation of phi(H) +180 in order to overlap x' axis with x axis
	y = Yrot(tmp, -H.theta());     // Rotation of -theta(H) in order to overlap z' axis with z axis

	z = lorentz(boost, y);

	return z;
}

// V4 from V3 and pid
V4::V4(double px, double py, double pz, int pid) {

	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle(pid);

	double mass = particle->GetPDGMass() / CLHEP::GeV;

	double energy2 = px * px + py * py + pz * pz + mass * mass;

	t = sqrt(energy2);
	x = px;
	y = py;
	z = pz;
}





















