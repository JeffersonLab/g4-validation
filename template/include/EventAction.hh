#ifndef EventAction_h
#define EventAction_h 1

// c++
#include <vector>
#include <map>

// geant4
#include "G4UserEventAction.hh"

namespace pim_absorption {

    class EventAction : public G4UserEventAction {
    public:
        EventAction();

        virtual ~EventAction();

        virtual void BeginOfEventAction(const G4Event *event);

        virtual void EndOfEventAction(const G4Event *event);

        void AddPid(int trkID, int pid);

        void AddKine(int trkID, double kine);

    private:
        // key is track id
        std::map<int, int> pids;
        std::map<int, double> kines;
    };
}
#endif


