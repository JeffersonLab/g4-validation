
#include "extPhysics.hh"

// c++
using namespace std;

// geant4

// From examples/extended/physicslists/extensibleFactory:
// The extensible factory also allows for the extension of lists by adding
// (using "+" as a separator) or replacing (using "_" as a separator)
// specific physics constructors.  These can be specified by
// pre-defining a short name (e.g. RADIO for G4RadioactiveDecayPhysics) or
// providing the full class name.
#include "G4PhysListFactoryAlt.hh"

// allow ourselves to extend the short names for physics ctor addition/replace
// along the same lines as EMX, EMY, etc
#include "G4PhysListRegistry.hh"

// allow ourselves to give the user extra info about available physics constructors (ctors)
#include "G4PhysicsConstructorFactory.hh"


GPhysics::GPhysics(bool printAll, string physListString) : physList(nullptr) {
	
	G4cout << "Geant4 physics list: <" << physListString << ">" << G4endl;

	if ( printAll ) {
		printAvailable();
		exit(1);
	}
	
	// g4alt::G4PhysListFactoryAlt is the extensible factory
	// including the G4PhysListFactoryAlt.hh header and the line:
	//    using namespace g4alt;
	// would make this a drop-in replacement, but we'll list the explicit
	// namespace here just for clarity
	g4alt::G4PhysListFactory factory;
	physList = factory.GetReferencePhysList(physListString);
	
	if ( ! physList ) {
		G4cerr  << " Error: physics list <" << physListString << "> could not be loaded. Exiting." << G4endl;
		exit(1);
	}
	
}

GPhysics::~GPhysics() {}


// calls PrintAvailablePhysLists
// if verbosity is > 0 calls PrintAvailablePhysicsConstructors
void GPhysics::printAvailable() {
	
	g4alt::G4PhysListFactory factory;
	factory.PrintAvailablePhysLists();
	
	G4cout << " Geant4 available physics constructor that can be added to physicsList:" << G4endl;
	G4PhysicsConstructorRegistry* g4pctorFactory = G4PhysicsConstructorRegistry::Instance();
	g4pctorFactory->PrintAvailablePhysicsConstructors();
}




