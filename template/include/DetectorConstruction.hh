#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

// geant4
#include "G4VUserDetectorConstruction.hh"
#include "G4FieldManager.hh"
#include "MagneticField.hh"

namespace template_project_name {

    class DetectorConstruction : public G4VUserDetectorConstruction {

    public:
        DetectorConstruction();

        virtual ~DetectorConstruction() override;

    public:
        virtual G4VPhysicalVolume *Construct() override;
        virtual void ConstructSDandField() override;

    private:
        G4LogicalVolume* fMagneticLogical = nullptr;
        static G4ThreadLocal MagneticField* fMagneticField;
        static G4ThreadLocal G4FieldManager* fFieldMgr;

    };


}

#endif
