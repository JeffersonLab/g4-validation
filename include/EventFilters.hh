#ifndef EventFilters_h
#define EventFilters_h 1

#include "V4.h"
#include "fluxHit.hh"


class EventFilters {

public:
	EventFilters(double beam_e, double target_mass);

	~EventFilters() = default;

	// return W if it passes the filter, 0 otherwise
    double inclusive_electron(FluxHit *hit);

private:

	// 4 vectors
	V4 beam;   // Incident Electron
	V4 target; // Target
	V4 q;      // virtual photon
	V4 H;      // Outgoing Hadrons


	// inclusive electron filter variables
	double minTheta=2.0 ; // in degrees
	double minW=0.5;      // in GeV
	double maxW=4.0;      // in GeV

};


#endif
