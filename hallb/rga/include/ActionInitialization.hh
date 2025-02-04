#ifndef ActionInitialization_h
#define ActionInitialization_h 1

// geant4
#include "G4VUserActionInitialization.hh"
#include "G4String.hh"

namespace rga {

class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization(G4String of) : output_file(of) {}

    ~ActionInitialization() override = default;  // fDetConstruction is not owned by this class

    void BuildForMaster() const override;

    void Build() const override;

private:
	G4String output_file;


};

}
#endif
