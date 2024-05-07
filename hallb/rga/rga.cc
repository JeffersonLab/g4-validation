// rga
// #include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

// physics
#include "extPhysics.hh"

// geant4
#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UIExecutive.hh"
#include "G4UIcommand.hh"
#include "G4VisExecutive.hh"

using namespace std;

namespace rga {

    void PrintUsage() {

        G4cerr << G4endl;
        G4cerr << " Usage: " << G4endl;
        G4cerr << G4endl;
        G4cerr
                << "  rga [-m macro ] [-u UIsession] [-t nThreads] [-p physList ]  [-v | --verbose ] [-h | --help] [ -pap | --printAvailablePhysics ]"
                << G4endl;
        G4cerr << G4endl;
        G4cerr << " The default physList is FTFP_BERT. " << G4endl;
        G4cerr << " It can be replaced by any of the available physics modules and compounded with additional physics constructors. " << G4endl;
        G4cerr << " For example: " << G4endl;
        G4cerr << G4endl;
        G4cerr << "  -p FTFP_BERT_EMX  would replace the standard e.m. physics with G4EmStandardPhysics_option3" << G4endl;
        G4cerr << "  -p QGSP_BERT+G4OpticalPhysics would use QGSP_BERT and G4OpticalPhysics" << G4endl;
        G4cerr << "  -p QGSP_FTFP_BERT+G4RadioactiveDecayPhysics+G4OpticalPhysics would use QGSP_FTFP_BERT, G4RadioactiveDecayPhysics and G4OpticalPhysics"
               << G4endl;
        G4cerr << G4endl;
        G4cerr << " To print all geant4 available physics modules and constructors use the -pap option " << G4endl;
    }

}


int main(int argc, char **argv) {

    G4String macro;
    G4String session;
    G4int nThreads = 4;
    G4int verbosity = 0;
    G4bool verboseBestUnits = true;

    string physListString = "FTFP_BERT";
    bool printAvailablePhysics = false;

    for (G4int i = 1; i < argc; i = i + 2) {
        G4String g4argv(argv[i]);
        if (g4argv == "-m") macro = argv[i + 1];
        else if (g4argv == "-u") session = argv[i + 1];
        else if (g4argv == "-p") physListString = argv[i + 1];
        else if (g4argv == "-t") {
            nThreads = G4UIcommand::ConvertToInt(argv[i + 1]);
        } else if (g4argv == "-v" || g4argv == "--verbose") {
            ++verbosity;  // verbose flag doesn't take an argument
            --i;         // don't increment argc by two, just the one
        } else if (g4argv == "-pap" || g4argv == "--printAvailablePnysics") {
            printAvailablePhysics = true;
            --i;         // don't increment argc by two, just the one
        } else if (G4String(argv[i]) == "-vDefault") {
            verboseBestUnits = false;
            --i;  // this option is not followed with a parameter
        } else if (g4argv == "-h" || g4argv == "--help") {
            rga::PrintUsage();
            return 1;
        } else {
            rga::PrintUsage();
            return 1;
        }
    }

    // Detect interactive mode (if no macro provided) and define UI session
    G4UIExecutive *ui = nullptr;
    if (!macro.size()) {
        ui = new G4UIExecutive(argc, argv, session);
    }

    // Optionally: choose a different Random engine...
    // G4Random::setTheEngine(new CLHEP::RanecuEngine);

    // Use G4SteppingVerboseWithUnits
    if (verboseBestUnits) {
        G4int precision = 8;
        G4SteppingVerbose::UseBestUnit(precision);
    }

    // Construct the default run manager
    auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
    if (nThreads > 0) {
        runManager->SetNumberOfThreads(nThreads);
    }

    // Set mandatory initialization classes
    auto detConstruction = new rga::DetectorConstruction();
    runManager->SetUserInitialization(detConstruction);

    auto gphysics = new GPhysics(printAvailablePhysics, physListString);
    runManager->SetUserInitialization(gphysics->getPhysList());

    auto actionInitialization = new rga::ActionInitialization(detConstruction);
    runManager->SetUserInitialization(actionInitialization);

    // Initialize visualization
    auto visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    auto UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    if (macro.size()) {
        // batch mode
        G4String command = "/control/execute ";
        UImanager->ApplyCommand(command + macro);
    } else {
        // interactive mode : define UI session
        // assuming the existence of init_vis and gui
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;
}
