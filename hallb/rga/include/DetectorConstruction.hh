#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

// geant4
#include "G4VUserDetectorConstruction.hh"
#include "G4FieldManager.hh"
#include "MagneticField.hh"

namespace rga {

class MagneticField;

class DetectorConstruction : public G4VUserDetectorConstruction {

public:
    DetectorConstruction();

    ~DetectorConstruction() override;

public:
    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

private:
    G4LogicalVolume *fMagneticLogical = nullptr;
    static G4ThreadLocal MagneticField* fMagneticField;
    static G4ThreadLocal G4FieldManager* fFieldMgr;

    G4LogicalVolume *sensitive_sphere_logical = nullptr;
};


}

#endif
