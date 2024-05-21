#include "DetectorConstruction.hh"

// geant4
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"

// cadmesh
#include "CadMesh.hh"

namespace template_project_name {

    G4ThreadLocal MagneticField* DetectorConstruction::fMagneticField = nullptr;
    G4ThreadLocal G4FieldManager* DetectorConstruction::fFieldMgr = nullptr;

    DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}

    DetectorConstruction::~DetectorConstruction() {}

    G4VPhysicalVolume *DetectorConstruction::Construct() {
        // Get nist material manager
        G4NistManager *nist = G4NistManager::Instance();

        // World Envelope parameters
        G4double env_sizeXY = 500 * cm, env_sizeZ = 500 * cm;
        G4Material *vacuumMaterial = nist->FindOrBuildMaterial("G4_Galactic");

        G4Box *solidWorld = new G4Box("World",                       // name
                                      0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ);    // size

        G4LogicalVolume *logicWorld =
                new G4LogicalVolume(solidWorld,          // solid
                                    vacuumMaterial,      // material
                                    "World");            // name

        fMagneticLogical = logicWorld;

        G4VPhysicalVolume *physWorld =
                new G4PVPlacement(0,                     // no rotation
                                  G4ThreeVector(),       // at (0,0,0)
                                  logicWorld,            // logical volume
                                  "World",               // name
                                  0,                     // mother  volume
                                  false,                 // no boolean operation
                                  0,                     // copy number
                                  true);                 // overlaps checking

        // aluminum target
        G4Material *aluminumMaterial = nist->FindOrBuildMaterial("G4_Al");

        G4Tubs *aluminumTarget =
                new G4Tubs("aluminumTarget",                                 // name
                           0 * mm, 100 * mm, 20 * cm, 0 * deg, 360 * deg);   // size

        G4LogicalVolume *aluminumTargetLogical =
                new G4LogicalVolume(aluminumTarget,           // solid
                                    aluminumMaterial,         // material
                                    "aluminumTargetLogical"); // name

        G4VisAttributes *aluminumAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0));
        aluminumTargetLogical->SetVisAttributes(aluminumAtt);
        aluminumAtt->SetForceSolid(true);

        new G4PVPlacement(0,                               // no rotation
                          G4ThreeVector(0, 0, 0),          // centered
                          aluminumTargetLogical,           // logical volume
                          "aluminumTarget",                // name
                          logicWorld,                      // mother volume
                          false,                           // no boolean operation
                          0,                               // copy number
                          true);                           // overlaps checking
        return physWorld;
    }


    void DetectorConstruction::ConstructSDandField()
    {
        // sensitive detectors


        // magnetic field ----------------------------------------------------------
        fMagneticField = new MagneticField();
        fFieldMgr = new G4FieldManager();
        fFieldMgr->SetDetectorField(fMagneticField);
        fFieldMgr->CreateChordFinder(fMagneticField);
        G4bool forceToAllDaughters = true;
        fMagneticLogical->SetFieldManager(fFieldMgr, forceToAllDaughters);
    }

}
