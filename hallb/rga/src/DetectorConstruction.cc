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

namespace rga {

// @formatter:off
G4ThreadLocal MagneticField* DetectorConstruction::fMagneticField = nullptr;
G4ThreadLocal G4FieldManager* DetectorConstruction::fFieldMgr = nullptr;
// @formatter:on


DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume *DetectorConstruction::Construct() {
	// Get nist material manager
	G4NistManager *nist = G4NistManager::Instance();

	// World Envelope parameters
	G4double env_sizeXY = 40 * cm, env_sizeZ = 40 * cm;
	G4Material *vacuumMaterial = nist->FindOrBuildMaterial("G4_Galactic");

	G4Box *solidWorld = new G4Box("World",                       // name
								  0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ);    // size

	G4LogicalVolume *logicWorld =
			new G4LogicalVolume(solidWorld,          // solid
								vacuumMaterial,      // material
								"World");            // name

	// keeping log volume for magnetic field
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

	// aluminum windows
	G4Material *aluminumMaterial = nist->FindOrBuildMaterial("G4_Al");

	G4Tubs *aluminumWindow =
			new G4Tubs("aluminumWindow",                                    // name
					   0 * mm, 4.9 * mm, 0.015 * mm, 0 * deg, 360 * deg);   // size

	G4LogicalVolume *aluminumWindowLogical =
			new G4LogicalVolume(aluminumWindow,           // solid
								aluminumMaterial,      // material
								"aluminumWindowLogical"); // name

	G4VisAttributes *aluminumAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0));
	aluminumWindowLogical->SetVisAttributes(aluminumAtt);
	aluminumAtt->SetForceSolid(true);


	new G4PVPlacement(0,                               // no rotation
					  G4ThreeVector(0, 0, -25 * mm),   // at -2.5 mm
					  aluminumWindowLogical,           // logical volume
					  "aluminumWindow",                // name
					  logicWorld,                      // mother volume
					  false,                           // no boolean operation
					  0,                               // copy number
					  true);                           // overlaps checking

	new G4PVPlacement(0,                               // no rotation
					  G4ThreeVector(0, 0, 25 * mm),    // at -2.5 mm
					  aluminumWindowLogical,           // logical volume
					  "aluminumWindow",                // name
					  logicWorld,                      // mother volume
					  false,                           // no boolean operation
					  0,                               // copy number
					  true);                           // overlaps checking

	// target cell
	G4Material *lh2_material = nist->FindOrBuildMaterial("G4_lH2");
	const int n_planes = 5;
	G4double inner_radius[n_planes] = {0.0 * mm, 0.0 * mm, 0.0 * mm, 0.0 * mm, 0.0 * mm};
	G4double outer_radius[n_planes] = {2.5 * mm, 10.3 * mm, 7.3 * mm, 5 * mm, 2.5 * mm};
	G4double z_pos[n_planes] = {-24.2 * mm, -21.2 * mm, 22.5 * mm, 23.5 * mm, 24.5 * mm};

	G4Polycone *target_cell =
			new G4Polycone("target_cell",              // name
						   0.0 * deg, 360 * deg, 5,    // phi and number of planes
						   z_pos,                      // z pos
						   inner_radius,               // inner radius
						   outer_radius);              // outer radius


	G4LogicalVolume *target_cell_logical =
			new G4LogicalVolume(target_cell,             // solid
								lh2_material,            // material
								"target_cell_logical");  // name

	G4VisAttributes *target_cell_att = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
	target_cell_logical->SetVisAttributes(target_cell_att);
	target_cell_att->SetForceSolid(true);

	// refine matrix of rotation, 180 degrees around y axis
	G4RotationMatrix *rot = new G4RotationMatrix();
	rot->rotateY(180 * deg);

	new G4PVPlacement(0,                           // no rotation
					  G4ThreeVector(),             // at (0,0,0)
					  target_cell_logical,         // logical volume
					  "target_cell",               // name
					  logicWorld,                  // mother volume
					  false,                       // no boolean operation
					  0,                           // copy number
					  true);                       // overlaps checking

	// CADMesh *mesh = new CADMesh("target_torlon_base.stl");
	auto target_torlon_base_mesh = CADMesh::TessellatedMesh::FromSTL("target_torlon_base.stl");
	target_torlon_base_mesh->SetScale(mm);
	target_torlon_base_mesh->SetReverse(false);

	auto target_kapton_wall_mesh = CADMesh::TessellatedMesh::FromSTL("target_kapton_wall.stl");
	target_kapton_wall_mesh->SetScale(mm);
	target_kapton_wall_mesh->SetReverse(false);

	G4LogicalVolume *target_torlon_base_logical =
			new G4LogicalVolume(target_torlon_base_mesh->GetSolid(),  // solid
								lh2_material,                         // material
								"target_torlon_base_logical");        // name

	G4LogicalVolume *target_kapton_wall_logical =
			new G4LogicalVolume(target_kapton_wall_mesh->GetSolid(),  // solid
								lh2_material,                         // material
								"target_kapton_wall_logical");        // name

	G4VisAttributes *torlon_att = new G4VisAttributes(G4Colour(0.4, 0.4, 0.4));
	torlon_att->SetForceSolid(true);

	target_torlon_base_logical->SetVisAttributes(torlon_att);
	target_kapton_wall_logical->SetVisAttributes(torlon_att);


	// add a solid sphere surrounding the target
	G4Sphere *sensitive_sphere_solid = new G4Sphere("target_sphere", 10 * cm, 10.01 * cm, 0, 360 * deg, 0, 360 * deg);

	sensitive_sphere_logical =
			new G4LogicalVolume(sensitive_sphere_solid,      // solid
								vacuumMaterial,              // material
								"sensitive_sphere_logical"); // name

	G4VisAttributes *sensitive_sphere_att = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
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

	new G4PVPlacement(rot,                                  // no rotation
					  G4ThreeVector(0, 0, 1273.27 * mm), //mesh coordinates
					  target_torlon_base_logical,         // logical volume
					  "target_torlon_base",               // name
					  logicWorld,                         // mother volume
					  false,                              // no boolean operation
					  0,                                  // copy number
					  true);                              // overlaps checking

	new G4PVPlacement(rot,                                  // no rotation
					  G4ThreeVector(0, 0, 1273.27 * mm), //mesh coordinates
					  target_kapton_wall_logical,         // logical volume
					  "target_kapton_wall",               // name
					  logicWorld,                         // mother volume
					  false,                              // no boolean operation
					  0,                                  // copy number
					  true);                              // overlaps checking
	return physWorld;
}

void DetectorConstruction::ConstructSDandField() {

	// sensitive detectors

	auto sdManager = G4SDManager::GetSDMpointer();
	auto fluxSD = new Flux_SD("fluxSD");
	sdManager->AddNewDetector(fluxSD);
	sensitive_sphere_logical->SetSensitiveDetector(fluxSD);

	// magnetic field ----------------------------------------------------------
	fMagneticField = new MagneticField();
	fFieldMgr = new G4FieldManager();
	fFieldMgr->SetDetectorField(fMagneticField);
	fFieldMgr->CreateChordFinder(fMagneticField);
	G4bool forceToAllDaughters = true;
	fMagneticLogical->SetFieldManager(fFieldMgr, forceToAllDaughters);
}

}
