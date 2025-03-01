#include "PrimaryGeneratorAction.hh"
#include "g4globals.hh"

// geant4
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

namespace rga {

PrimaryGeneratorAction::PrimaryGeneratorAction()
        : G4VUserPrimaryGeneratorAction(),
          fParticleGun(0) {

    G4int n_particle = 1;

    fParticleGun = new G4ParticleGun(n_particle);

    // default particle kinematic
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName = "e-");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.)); // beam along z axis
    fParticleGun->SetParticleEnergy(g4_globals::beam_energy*GeV);

}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {

    G4int numberOfBeamElectrons = 1000;

    G4double beam_spot_size_x = 0.15 * mm;
    G4double beam_spot_size_y = 0.15 * mm;
    G4double z0 = -5. * cm;

    for (G4int i = 0; i < numberOfBeamElectrons; i++) {

        double tmp_sqrt_rho = sqrt(G4UniformRand());  // Square root gives uniform spread over circle.
        double tmp_phi = 2 * CLHEP::pi * G4UniformRand();

        double x0 = beam_spot_size_x * tmp_sqrt_rho * cos(tmp_phi);
        double y0 = beam_spot_size_y * tmp_sqrt_rho * sin(tmp_phi);

        fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, z0));

        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
}

}
