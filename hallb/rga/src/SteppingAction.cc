// this test
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

// geant4
#include "G4RunManager.hh"

namespace rga {




void SteppingAction::UserSteppingAction(const G4Step *step) {

    G4ThreeVector   pos   = step->GetPostStepPoint()->GetPosition();      ///< Global Coordinates of interaction
    G4Track*        track = step->GetTrack();

    if(fabs(pos.x()) > max_x_pos ||
       fabs(pos.y()) > max_y_pos ||
       fabs(pos.z()) > max_z_pos ) {

//		std::cout << " Out of limits reached for track " << track->GetDefinition()->GetParticleName() ;
//        std::cout << " Track killed" << std::endl;

        track->SetTrackStatus(fStopAndKill);   ///< Killing track if outside of interest region
    }

    // sometimes a track get stuck into a magnetic field infinite loop
    if(track->GetCurrentStepNumber() > 1000) {
 //       std::cout << " GetCurrentStepNumber " << track->GetCurrentStepNumber() << std::endl;
        track->SetTrackStatus(fStopAndKill);
    }
}

}
