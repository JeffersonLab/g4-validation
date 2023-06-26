#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

namespace pim_absorption {


    RunAction::RunAction() : G4UserRunAction() {
        // Create analysis manager
        // The choice of analysis technology is done via selectin of a namespace in Analysis.hh
        auto analysisManager = G4AnalysisManager::Instance();
        G4cout << "Using " << analysisManager->GetType() << G4endl;

        // Create directories
        analysisManager->SetVerboseLevel(1);
        analysisManager->SetNtupleMerging(true);

        // Note: merging ntuples is available only with Root output

        // Book histograms, ntuple
        analysisManager->CreateNtuple("pima", "pim absorbtion test");
        analysisManager->CreateNtupleDColumn("pid");
        analysisManager->CreateNtupleDColumn("kine");
        analysisManager->FinishNtuple();

    }

    RunAction::~RunAction() {
    }

    void RunAction::BeginOfRunAction(const G4Run * /*run*/) {
        // Get analysis manager
        auto analysisManager = G4AnalysisManager::Instance();

        // Open an output file
        G4String fileName = "pima.root";               // file opening command moved to the class constructor
        analysisManager->OpenFile(fileName);
    }


    void RunAction::EndOfRunAction(const G4Run * /*run*/) {
        // print histogram statistics
        auto analysisManager = G4AnalysisManager::Instance();


        // save histograms & ntuple
        analysisManager->Write();
        analysisManager->CloseFile();
    }


}
