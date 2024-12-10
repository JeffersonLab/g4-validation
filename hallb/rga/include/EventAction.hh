#ifndef EventAction_h
#define EventAction_h 1

// c++
#include <vector>
#include <map>

// geant4
#include "G4UserEventAction.hh"

namespace rga {

class EventAction : public G4UserEventAction {
public:
    EventAction();

    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event *event) override;

    void EndOfEventAction(const G4Event *event) override;


private:


};
}
#endif
