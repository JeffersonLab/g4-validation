// this test
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

// geant4
#include "G4RunManager.hh"

namespace pim_absorption {

    SteppingAction::SteppingAction(const DetectorConstruction *detectorConstruction, EventAction *eventAction)
            : G4UserSteppingAction(),
              fDetConstruction(detectorConstruction),
              fEventAction(eventAction) {}

    SteppingAction::~SteppingAction() {}

    void SteppingAction::UserSteppingAction(const G4Step *step) {

        auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

        auto vacuumDetectorPV = fDetConstruction->getVacuumDetectorPV();

        if (volume != vacuumDetectorPV) return;

        auto thisTrack = step->GetTrack();
        int trkID = thisTrack->GetTrackID();
        int PDGE = thisTrack->GetDefinition()->GetPDGEncoding();
        double KE = thisTrack->GetKineticEnergy();
        int mpid = thisTrack->GetParentID();


        if (mpid != 0) {

//		if (fabs(PDGE) == 12 || fabs(PDGE) == 14 ) {
//			std::cout << "SSS trackID: " << trkID << ", PDGE: " << PDGE << ", kine: " << KE << std::endl;
//		}

            fEventAction->AddPid(trkID, PDGE);
            fEventAction->AddKine(trkID, KE);
        }

    }

}