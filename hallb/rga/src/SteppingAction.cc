// this test
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

// geant4
#include "G4RunManager.hh"

namespace rga {

    SteppingAction::SteppingAction(const DetectorConstruction *detectorConstruction, EventAction *eventAction)
            : G4UserSteppingAction(),
              fDetConstruction(detectorConstruction),
              fEventAction(eventAction) {}

    SteppingAction::~SteppingAction() {}

    void SteppingAction::UserSteppingAction(const G4Step *step) {

        auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

        auto thisTrack = step->GetTrack();
        int trkID = thisTrack->GetTrackID();
        int PDGE = thisTrack->GetDefinition()->GetPDGEncoding();
        double KE = thisTrack->GetKineticEnergy();
        int mpid = thisTrack->GetParentID();

        if (mpid != 99 ) {
            fEventAction->AddPid(trkID, PDGE);
            fEventAction->AddKine(trkID, KE);
        }

    }

}
