// this test
#include "EventFilters.hh"
#include "fluxHit.hh"

EventFilters::EventFilters(G4VHitsCollection *hitsCollection, double beam_e, double target_mass) : hc(hitsCollection) {

	beam = V4(0.0, 0.0, beam_e, beam_e);      // Incident Electron Four momentum
	target = V4(0.0, 0.0, 0.0, target_mass);  // Target Mass
}


// if there is at least one electron that have minW GeV < W < maxW GeV
bool EventFilters::inclusive_electron(double minW, double maxW) {

	for (size_t hitIndex = 0; hitIndex < hc->GetSize(); hitIndex++) {

		auto hit = static_cast<FluxHit *>(hc->GetHit(hitIndex));

		auto pid = hit->getParticleID();

		// only consider electrons
		if (pid == 11) {
			auto momentum = hit->getMomentum()/CLHEP::GeV;

			V4 e(momentum.x(), momentum.y(), momentum.z(), pid);  // 4 vector of electron
			q = beam - e;     // virtual photon 4-vector
			H = q + target;  // Outgoing Hadrons 4-vector

			double W =  sqrt(H.mass())/CLHEP::GeV;

			if (W > minW && W < maxW) return true;

		}


	}

	return false;
}
