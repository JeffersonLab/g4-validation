#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

namespace rga {

ActionInitialization::ActionInitialization(DetectorConstruction *detConstruction) :
        G4VUserActionInitialization(),
        fDetConstruction(detConstruction) {}


void ActionInitialization::BuildForMaster() const {
    auto eventAction = new EventAction;
    SetUserAction(new RunAction(eventAction));
}

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction);

    auto eventAction = new EventAction;
    SetUserAction(eventAction);

    SetUserAction(new RunAction(eventAction));
    SetUserAction(new SteppingAction(fDetConstruction, eventAction));
}

}
