#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

// geant4
#include "G4VUserDetectorConstruction.hh"

namespace elastic {

class MagneticField;

class DetectorConstruction : public G4VUserDetectorConstruction {

public:
    DetectorConstruction();

    ~DetectorConstruction() override;

public:
    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

private:

    G4LogicalVolume *sensitive_sphere_logical = nullptr;
};


}

#endif
