#ifndef PhysicsList_h
#define PhysicsList_h 1

// geant4
#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"

class PhysicsList: public G4VModularPhysicsList
{
public:
	PhysicsList();
	~PhysicsList();
	
	// Non-virtual methods in G4VModularPhysicsList.  Just call the
	// method with the same name in G4VModularPhysicsList.
	void RegisterPhysics(G4VPhysicsConstructor* g) {
		G4VModularPhysicsList::RegisterPhysics(g);
	}

protected:
	// Construct particle and physics
	virtual void SetCuts();   
};

#endif



