#ifndef EventFilters_h
#define EventFilters_h 1

#include "V4.h"
#include "G4VHitsCollection.hh"


class EventFilters {

public:
	EventFilters(G4VHitsCollection *hitsCollection, double beam_e, double target_mass);

	~EventFilters() = default;

    bool inclusive_electron(double minW, double maxW);

private:

	G4VHitsCollection *hc;

	// 4 vectors
	V4 beam;   // Incident Electron
	V4 target; // Target
	V4 q;      // virtual photon
	V4 H;      // Outgoing Hadrons


};


#endif
