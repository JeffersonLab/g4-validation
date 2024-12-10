// this test
#include "EventAction.hh"

// geant4
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

// c++
using namespace std;

namespace rga {

EventAction::EventAction()  {
    // set printing per
    G4RunManager::GetRunManager()->SetPrintProgress(1);
}

void EventAction::BeginOfEventAction(const G4Event *event) {

}

void EventAction::EndOfEventAction(const G4Event *event) {

    // auto analysisManager = G4AnalysisManager::Instance();

}


}
