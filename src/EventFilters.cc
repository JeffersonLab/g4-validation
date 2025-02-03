// this test
#include "EventFilters.hh"

EventFilters::EventFilters(double beam_e, double target_mass)  {

	beam = V4(0.0, 0.0, beam_e, beam_e);      // Incident Electron Four momentum (in GeV)
	target = V4(0.0, 0.0, 0.0, target_mass);  // Target Mass (in GeV)
}


// if there is at least one electron that have minW GeV < W < maxW GeV
// the theta angle cut is hardcoded to 1 degree
double EventFilters::inclusive_electron(FluxHit *hit) {


	auto pid = hit->getParticleID();

	// only consider electrons
	if (pid == 11) {
		auto momentum = hit->getMomentum() / CLHEP::GeV;
		auto localPos = hit->getWorldPos();

		// theta is the angle with respect to the z axis of the position on the scoring sphere
		double theta = localPos.theta();

		V4 e(momentum.x(), momentum.y(), momentum.z(), pid);  // 4 vector of electron
		q = beam - e;     // virtual photon 4-vector
		H = q + target;   // Outgoing Hadrons 4-vector

		double W = sqrt(H.mass());


		if (W > minW && W < maxW && theta / CLHEP::degree > minTheta) return W;

	}


	return 0;
}
