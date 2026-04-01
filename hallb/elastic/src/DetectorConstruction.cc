#include "DetectorConstruction.hh"
#include "fluxSD.hh"
// geant4
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Polycone.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"

// cadmesh
#include "CadMesh.hh"

namespace elastic {

	DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {
	}

	DetectorConstruction::~DetectorConstruction() {
	}

	G4VPhysicalVolume* DetectorConstruction::Construct() {
		// Get nist material manager
		G4NistManager* nist = G4NistManager::Instance();

		// World Envelope parameters
		G4double    env_sizeXY     = 40 * cm, env_sizeZ = 40 * cm;
		G4Material* vacuumMaterial = nist->FindOrBuildMaterial("G4_Galactic");

		G4Box* solidWorld = new G4Box("World",                       // name
									  0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ);    // size

		G4LogicalVolume* logicWorld =
			new G4LogicalVolume(solidWorld,          // solid
								vacuumMaterial,      // material
								"World");            // name


		G4VPhysicalVolume* physWorld =
			new G4PVPlacement(0,                     // no rotation
							  G4ThreeVector(),       // at (0,0,0)
							  logicWorld,            // logical volume
							  "World",               // name
							  0,                     // mother  volume
							  false,                 // no boolean operation
							  0,                     // copy number
							  true);                 // overlaps checking

		double target_semi_length    = 10 * cm;
		double target_radius         = 2 * cm;
		double flux_sphere_radius    = target_semi_length + 5 * cm;
		double flux_sphere_thickness = 1 * mm;


		// target cell
		G4Material* lh2_material = nist->FindOrBuildMaterial("G4_lH2");

		auto* target_cell =
			new G4Tubs("target_cell", 0 * mm, target_radius, target_semi_length, 0, 360 * deg);


		auto* target_cell_logical =
			new G4LogicalVolume(target_cell,             // solid
								lh2_material,            // material
								"target_cell_logical");  // name

		auto* target_cell_att = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
		target_cell_logical->SetVisAttributes(target_cell_att);
		target_cell_att->SetForceSolid(true);


		new G4PVPlacement(0,                           // no rotation
						  G4ThreeVector(),             // at (0,0,0)
						  target_cell_logical,         // logical volume
						  "target_cell",               // name
						  logicWorld,                  // mother volume
						  false,                       // no boolean operation
						  0,                           // copy number
						  true);                       // overlaps checking


		// add a solid sphere surrounding the target
		auto* sensitive_sphere_solid = new G4Sphere("target_sphere", flux_sphere_radius,
													flux_sphere_radius + flux_sphere_thickness, 0, 360 * deg, 0,
													360 * deg);

		sensitive_sphere_logical =
			new G4LogicalVolume(sensitive_sphere_solid,      // solid
								vacuumMaterial,              // material
								"sensitive_sphere_logical"); // name

		auto* sensitive_sphere_att = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
		sensitive_sphere_att->SetForceSolid(true);
		sensitive_sphere_logical->SetVisAttributes(sensitive_sphere_att);

		new G4PVPlacement(0,                           // no rotation
						  G4ThreeVector(),             // at (0,0,0)
						  sensitive_sphere_logical,     // logical volume
						  "sensitive_sphere",           // name
						  logicWorld,                   // mother volume
						  false,                        // no boolean operation
						  0,                            // copy number
						  true);                        // overlaps checking
		// overlaps checking
		return physWorld;
	}

	void DetectorConstruction::ConstructSDandField() {
		// sensitive detectors

		auto sdManager = G4SDManager::GetSDMpointer();
		auto fluxSD    = new Flux_SD("fluxSD");
		sdManager->AddNewDetector(fluxSD);
		sensitive_sphere_logical->SetSensitiveDetector(fluxSD);
	}
}
