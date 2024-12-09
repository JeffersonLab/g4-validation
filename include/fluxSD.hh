#ifndef FLUX_SD_H
#define FLUX_SD_H 1

#include "fluxHit.hh"
#include "G4VSensitiveDetector.hh"

class Flux_SD : public G4VSensitiveDetector {
public:
    Flux_SD(G4String name);

    ~Flux_SD() override = default;

    void Initialize(G4HCofThisEvent *HCE) override;

    G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override;

private:
    FluxHitsCollection* fHitsCollection = nullptr;
    G4int fHCID = -1;

};

#endif
