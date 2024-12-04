#ifndef ActionInitialization_h
#define ActionInitialization_h 1

// geant4
#include "G4VUserActionInitialization.hh"

namespace rga {

class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization(DetectorConstruction *detConstruction);

    ~ActionInitialization() override = default;  // fDetConstruction is not owned by this class

    void BuildForMaster() const override;

    void Build() const override;

private:
    DetectorConstruction *fDetConstruction;
};

}
#endif
