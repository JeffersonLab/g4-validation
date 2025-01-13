// this test
#include "EventAction.hh"
#include "fluxHit.hh"

// geant4
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
// units
#include "G4SystemOfUnits.hh"

// c++
using namespace std;

namespace rga {

EventAction::EventAction() {
	// set printing per
	G4RunManager::GetRunManager()->SetPrintProgress(1);
}

void EventAction::BeginOfEventAction(const G4Event *event) {

}

void EventAction::EndOfEventAction(const G4Event *event) {

	auto analysisManager = G4AnalysisManager::Instance();

	// HitsCollections of This Event
	G4HCofThisEvent *HCsThisEvent = event->GetHCofThisEvent();
	if (!HCsThisEvent) return;

	auto theOnlyHC = HCsThisEvent->GetHC(0);

	for (size_t hitIndex = 0; hitIndex < theOnlyHC->GetSize(); hitIndex++) {

		auto hit = static_cast<FluxHit *>(theOnlyHC->GetHit(hitIndex));
		auto time = hit->getTime();
		auto localPos = hit->getWorldPos();
		auto pid = hit->getParticleID();
		auto momentum = hit->getMomentum();

		// theta is the angle between the momentum vector and the z-axis
		double theta =localPos.theta();

		if (theta / deg < 5.0) continue;

			analysisManager->FillNtupleDColumn(0, pid);

			analysisManager->FillNtupleDColumn(1, localPos.x());
			analysisManager->FillNtupleDColumn(2, localPos.y());
			analysisManager->FillNtupleDColumn(3, localPos.z());

			analysisManager->FillNtupleDColumn(4, momentum.x());
			analysisManager->FillNtupleDColumn(5, momentum.y());
			analysisManager->FillNtupleDColumn(6, momentum.z());



	}
	analysisManager->AddNtupleRow();
}


}
