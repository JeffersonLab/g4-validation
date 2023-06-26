#include "PrimaryGeneratorAction.hh"

// geant4
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

namespace pim_absorption {

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
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
        fParticleGun->SetParticleEnergy(11. * GeV);

    }

    PrimaryGeneratorAction::~PrimaryGeneratorAction() {
        delete fParticleGun;
    }


    void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
        G4double x0 = 0 * mm / 2.;
        G4double y0 = 0 * mm / 2.;
        G4double z0 = -201. * cm;

        fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, z0));

        fParticleGun->GeneratePrimaryVertex(anEvent);
    }

}

