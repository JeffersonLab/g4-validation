// this test
#include "EventAction.hh"

// geant4
#include "G4AnalysisManager.hh"

// c++
using namespace std;

namespace pim_absorption {

    EventAction::EventAction() : G4UserEventAction() {}

    EventAction::~EventAction() {}

    void EventAction::BeginOfEventAction(const G4Event *event) {
        pids.clear();
        kines.clear();
    }

    void EventAction::EndOfEventAction(const G4Event *event) {

        auto analysisManager = G4AnalysisManager::Instance();

        for (auto pidsMapIndex: pids) {

            int trkID = pidsMapIndex.first;
            int pid = pidsMapIndex.second;
            int kine = kines[trkID];

            analysisManager->FillNtupleDColumn(0, pid);
            analysisManager->FillNtupleDColumn(1, kine);

//		if (fabs(pid) == 12 || fabs(pid) == 14 ) {
//			cout << "EEE trackID: " << trkID << ", pid: " << pid << ", kine: " << kine << endl;
//		}
            analysisManager->AddNtupleRow();

        }

    }

    void EventAction::AddPid(int trkID, int pid) {
        pids[trkID] = pid;
    }

// writing the last value of kinetic energy
    void EventAction::AddKine(int trkID, double kine) {
        kines[trkID] = kine;
    }

}