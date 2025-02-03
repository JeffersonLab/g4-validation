// this test
#include "EventAction.hh"
#include "EventFilters.hh"
#include "fluxHit.hh"
#include "g4globals.hh"

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

//void EventAction::BeginOfEventAction(const G4Event *event) {
//
//}

void EventAction::EndOfEventAction(const G4Event *event) {

	auto analysisManager = G4AnalysisManager::Instance();

	// HitsCollections of This Event
	G4HCofThisEvent *HCsThisEvent = event->GetHCofThisEvent();
	if (!HCsThisEvent) return;

	auto theOnlyHC = HCsThisEvent->GetHC(0);
	auto eventFilter = new EventFilters(g4_globals::beam_energy, g4_globals::target_mass); // set in RGA main


	for (size_t hitIndex = 0; hitIndex < theOnlyHC->GetSize(); hitIndex++) {

		auto hit = static_cast<FluxHit *>(theOnlyHC->GetHit(hitIndex));
		double W = eventFilter->inclusive_electron(hit);

		if (W == 0) continue;

		//auto time = hit->getTime();
		auto localPos = hit->getWorldPos();
		auto pid = hit->getParticleID();
		auto momentum = hit->getMomentum();

		analysisManager->FillNtupleDColumn(0, pid);

		analysisManager->FillNtupleDColumn(1, localPos.x());
		analysisManager->FillNtupleDColumn(2, localPos.y());
		analysisManager->FillNtupleDColumn(3, localPos.z());

		analysisManager->FillNtupleDColumn(4, momentum.x());
		analysisManager->FillNtupleDColumn(5, momentum.y());
		analysisManager->FillNtupleDColumn(6, momentum.z());

		analysisManager->FillH1(0, W);

	}


	analysisManager->AddNtupleRow();
}


}
