// rga
// #include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "g4globals.hh"

// modular physics
#include "extPhysics.hh"

// geant4
#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UIExecutive.hh"
#include "G4UIcommand.hh"
#include "G4VisExecutive.hh"

#include <unistd.h>  // needed for get_pid

using namespace std;

namespace rga {

void PrintUsage() {

	G4cerr << G4endl;
	G4cerr << " Usage: " << G4endl;
	G4cerr << G4endl;
	G4cerr
			<< "  rga [-n number of events] [-m batch macro ] [-u UIsession ] [-t nThreads] [-p physList ] [-h | --help] "
			<< "[ -pap | --printAvailablePhysics ] [-beam beam_eneregy] [-target target_mass] [-o output file] "
			<< "[ -seed #] "
			<< G4endl;
	G4cerr << G4endl;
	G4cerr << "  > The default number of threads is equal to the number of available CPU cores. " << G4endl;
	G4cerr << "  > The default physList is \"FTFP_BERT\". " << G4endl;
	G4cerr << "    It can be replaced by any of the available physics modules "
		   << " and compounded with additional physics constructors. " << G4endl;
	G4cerr << "    For example: " << G4endl;
	G4cerr << G4endl;
	G4cerr << "     -p FTFP_BERT_EMX  would replace the standard e.m. physics with G4EmStandardPhysics_option3"
		   << G4endl;
	G4cerr << "     -p QGSP_BERT+G4OpticalPhysics would use QGSP_BERT and G4OpticalPhysics" << G4endl;
	G4cerr
			<< "     -p QGSP_FTFP_BERT+G4RadioactiveDecayPhysics+G4OpticalPhysics would use "
			<< " QGSP_FTFP_BERT, G4RadioactiveDecayPhysics and G4OpticalPhysics"
			<< G4endl << G4endl;
	G4cerr << " The beam energy and target mass can be set with the -beam and -target options. "
		   << "Both options are in GeV" << G4endl;
	G4cerr << " The seeds initialize the random engine. Set to 0 to use CPU clock and process ID. "
		   << G4endl;
	G4cerr << " To print all Geant4 available physics modules and constructors use the -pap option "
		   << G4endl << G4endl;
}

}


int main(int argc, char **argv) {

	G4String session = "tcsh";
	G4String macro;
	G4int nThreads = 0;
	G4int nEvents = 0;
	G4String output_file = "rga.root";
	G4int seed = 0;

	string physListString = "FTFP_BERT";
	bool printAvailablePhysics = false;

	for (G4int i = 1; i < argc; i = i + 2) {
		G4String g4argv(argv[i]);
		if (g4argv == "-n") nEvents = G4UIcommand::ConvertToInt(argv[i + 1]);
		else if (g4argv == "-m") macro = argv[i + 1];
		else if (g4argv == "-u") session = argv[i + 1];
		else if (g4argv == "-p") physListString = argv[i + 1];
		else if (g4argv == "-o") output_file = argv[i + 1];
		else if (g4argv == "-seed") seed = G4UIcommand::ConvertToInt(argv[i + 1]);
		else if (g4argv == "-t") {
			nThreads = G4UIcommand::ConvertToInt(argv[i + 1]);
		} else if (g4argv == "-pap" || g4argv == "--printAvailablePhysics") {
			printAvailablePhysics = true;
			--i;  // this option is not followed with a parameter
		} else if (g4argv == "-h" || g4argv == "--help") {
			rga::PrintUsage();
			return 1;
		} else if (g4argv == "-beam") {
			g4_globals::beam_energy = atof(argv[i + 1]);
		} else if (g4argv == "-target") {
			g4_globals::target_mass = atof(argv[i + 1]);
		} else {
			rga::PrintUsage();
			return 1;
		}
	}

	if (seed == 0) {
		double timed = time(NULL);
		double clockd = clock();
		double getpidi = (double) getpid();
		seed = (G4int)(timed - clockd - getpidi);
	}

	// if beam is not set, use 11 GeV
	if (g4_globals::beam_energy == 0) {
		g4_globals::beam_energy = 11.0;
	}

	// if target is not set, use 0.938 GeV
	if (g4_globals::target_mass == 0) {
		g4_globals::target_mass = 0.938;
	}

	// print all used options
	cout << " > rga executable - using options: " << endl;
	cout << "   - Number of events:: " << nEvents << endl;
	cout << "   - Number of threads: " << nThreads << endl;
	cout << "   - Physics List: " << physListString << endl;
	cout << "   - Beam Energy: " << g4_globals::beam_energy << " GeV" << endl;
	cout << "   - Target mass: " << g4_globals::target_mass << " GeV" << endl;
	cout << "   - Output file: " << output_file << endl;


	// Detect interactive mode (if no macro provided) and define UI session
	G4UIExecutive *ui = nullptr;
	if (!macro.size()) {
		// the version with additional argument does not seem to work
		ui = new G4UIExecutive(argc, argv);
	}

	// Optionally: choose a different Random engine...
	G4Random::setTheEngine(new CLHEP::RanecuEngine);
	G4Random::setTheSeed(seed);

	// Use G4SteppingVerboseWithUnits
	G4int precision = 4;
	G4SteppingVerbose::UseBestUnit(precision);

	// Construct the default run manager
	auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
	if (nThreads > 0) {
		runManager->SetNumberOfThreads(nThreads);
	} else {
		int allThreads = G4Threading::G4GetNumberOfCores();
		runManager->SetNumberOfThreads(allThreads);
	}

	// Set mandatory initialization classes
	runManager->SetUserInitialization(new rga::DetectorConstruction());

	auto gphysics = new GPhysics(printAvailablePhysics, physListString);
	runManager->SetUserInitialization(gphysics->getPhysList());

	auto actionInitialization = new rga::ActionInitialization(output_file);
	runManager->SetUserInitialization(actionInitialization);

	// Get the pointer to the User Interface manager
	auto UImanager = G4UImanager::GetUIpointer();


	// if nEvents > 0 then run in batch mode
	if (nEvents  > 0 ) {
		UImanager->ApplyCommand("/run/initialize");
		UImanager->ApplyCommand("/run/printProgress 500");
		UImanager->ApplyCommand("/tracking/verbose 0");
		UImanager->ApplyCommand("/vis/verbose errors");

		G4String command = "/run/beamOn " + std::to_string(nEvents);
		UImanager->ApplyCommand(command);

	} else {
		// G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
		auto visManager = new G4VisExecutive;
		// G4VisManager* visManager = new G4VisExecutive("Quiet");
		visManager->Initialize();

		if (macro.size()) {
			// batch mode
			G4String command = "/control/execute ";
			UImanager->ApplyCommand(command + macro);
		} else {
			// assuming the existence of init_vis and gui
			UImanager->ApplyCommand("/control/execute init_vis.mac");
			ui->SessionStart();
			delete ui;
		}

		delete visManager;
	}
	delete runManager;

}
