#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

// geant4
#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;

class G4Event;

namespace rga {

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {

public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    // method from the base class
    void GeneratePrimaries(G4Event*) override;

    // method to access particle gun
    const G4ParticleGun *GetParticleGun() const { return fParticleGun; }

private:
    G4ParticleGun *fParticleGun; // pointer a to G4 gun class
};

}

#endif
