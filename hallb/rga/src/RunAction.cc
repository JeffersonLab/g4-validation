#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4HadronicProcessStore.hh"
#include "G4NistManager.hh"
#include "G4Element.hh"


// for debugging
using std::cout;
using std::endl;

namespace rga {


RunAction::RunAction(EventAction *eventAction)
        : fEventAction(eventAction) {    // Create analysis manager


    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetDefaultFileType("root");
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetNtupleMerging(true);


    // Open an output file
    G4String experiment = "rga";
    G4String fileName = experiment + ".root";
    analysisManager->SetFileName(fileName);

    G4cout << "Using " << analysisManager->GetType() << " analysisManager type " << G4endl;

	// Book W histograms
	analysisManager->CreateH1("W", "W", 100, 0., 4);  // h1 Id = 0


	// Book ntuple
    if (fEventAction) {
        analysisManager->CreateNtuple("rga", "rga physics validation");
        analysisManager->CreateNtupleDColumn("pid");
		analysisManager->CreateNtupleDColumn("x");
		analysisManager->CreateNtupleDColumn("y");
		analysisManager->CreateNtupleDColumn("z");
		analysisManager->CreateNtupleDColumn("px");
        analysisManager->CreateNtupleDColumn("py");
        analysisManager->CreateNtupleDColumn("pz");
        analysisManager->FinishNtuple();
    }

}


void RunAction::BeginOfRunAction(const G4Run * /*run*/) {

   //  Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    // Reset histograms from previous run
    analysisManager->Reset();

    // Open an output file
    // The default file name is set in RunAction::RunAction(),
    // it can be overwritten in a macro
    analysisManager->OpenFile();
}


void RunAction::EndOfRunAction(const G4Run * /*run*/) {

    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile(false);

}


}
