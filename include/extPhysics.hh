#ifndef  GPHYSICS_H
#define  GPHYSICS_H  1


// geant4
#include "G4VModularPhysicsList.hh"

// GPhysics Builds and provide a new G4VModularPhysicsList
// rather than being a class derived from G4VModularPhysicsList
class  GPhysics
{
public:
	
	GPhysics(bool printAll, std::string physListString);
	~GPhysics();
	
	G4VModularPhysicsList* getPhysList() { return physList ;}
	
private:
	// logs physics modules and constructors
	void printAvailable();
	G4VModularPhysicsList* physList;
};


#endif

