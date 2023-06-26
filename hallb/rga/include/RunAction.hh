#ifndef RunAction_h
#define RunAction_h 1

// geant4
#include "G4UserRunAction.hh"

namespace pim_absorption {

    class RunAction : public G4UserRunAction {
    public:
        RunAction();

        virtual ~RunAction();

        virtual void BeginOfRunAction(const G4Run *);

        virtual void EndOfRunAction(const G4Run *);
    };

}

#endif

