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


    RunAction::RunAction() : G4UserRunAction() {
        // Create analysis manager
        // The choice of analysis technology is done via selectin of a namespace in Analysis.hh
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->SetVerboseLevel(1);
        // Note: merging ntuples is available only with Root output
        analysisManager->SetNtupleMerging(true);


        // Open an output file
        G4String fileName = "rga.root";               // file opening command moved to the class constructor
        analysisManager->OpenFile(fileName);
        G4cout << "Using " << analysisManager->GetType() << " analysisManager type " << G4endl;

        // Book histograms
        analysisManager->CreateH2("elasticXS", "Elastic Cross Section", 12000, 0, 12000, 100, 0., 1);   // id 0: - elastic cross section
        analysisManager->CreateH2("inelasticXS", "Inelastic Cross Section", 12000, 0, 12000, 100, 0., 31); // id 1: - inelastic cross section

        // Book ntuple
        analysisManager->CreateNtuple("rga", "rga physics validation");
        analysisManager->CreateNtupleDColumn("pid");
        analysisManager->CreateNtupleDColumn("kine");
        analysisManager->CreateNtupleDColumn("elastic");
        analysisManager->FinishNtuple();

    }

    RunAction::~RunAction() {
    }

    void RunAction::BeginOfRunAction(const G4Run * /*run*/) {
    }


    void RunAction::EndOfRunAction(const G4Run * /*run*/) {

        // print histogram statistics

        if (isMaster) {
            auto analysisManager = G4AnalysisManager::Instance();

            G4HadronicProcessStore *hadstore = G4HadronicProcessStore::Instance();
            G4Material *lh2Mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_lH2");
            const G4Element *element = lh2Mat->GetElement(0);

            for (int i = 0; i < 1200; i++) {
                G4double energy = i * 10 * MeV;
                G4double elXS = hadstore->GetElasticCrossSectionPerAtom(G4Electron::Electron(), energy, element, lh2Mat);
                G4double InelXS = hadstore->GetInelasticCrossSectionPerAtom(G4Electron::Electron(), energy, element, lh2Mat);

                analysisManager->FillH2(0, i*10, elXS/microbarn);
                analysisManager->FillH2(1, i*10, InelXS/microbarn);

                // G4cout << "InelXS 10 GeV p on Pb " << G4BestUnit(elXS, "Surface") << G4endl;


//                analysisManager->FillNtupleDColumn(0, InelXS);
//                analysisManager->FillNtupleDColumn(1, InelXS);
//                analysisManager->FillNtupleDColumn(2, InelXS);
//                analysisManager->AddNtupleRow();
//
//                // save histograms & ntuple

            }
            analysisManager->Write();
            analysisManager->CloseFile();

        }


    }


}
