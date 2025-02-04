#ifndef RunAction_h
#define RunAction_h 1

// rga
#include "EventAction.hh"

// geant4
#include "G4UserRunAction.hh"
#include "G4String.hh"

namespace rga {

class RunAction : public G4UserRunAction {
public:
    RunAction(EventAction *eventAction, G4String of);

    ~RunAction() override = default;

    void BeginOfRunAction(const G4Run*) override;

    void EndOfRunAction(const G4Run*) override;

private:
    EventAction *fEventAction = nullptr;
	G4String output_file;

};

}

#endif
