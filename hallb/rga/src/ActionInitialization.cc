#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

namespace rga {


void ActionInitialization::BuildForMaster() const {
    auto eventAction = new EventAction;
    SetUserAction(new RunAction(eventAction, output_file));
}

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction);

    auto eventAction = new EventAction;
    SetUserAction(eventAction);

    SetUserAction(new RunAction(eventAction, output_file));

    SetUserAction(new SteppingAction());
}

}
