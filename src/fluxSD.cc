#include "fluxSD.hh"
#include "G4SDManager.hh"



Flux_SD::Flux_SD(G4String name) : G4VSensitiveDetector(name) {
    collectionName.insert("fluxColl");
}

void Flux_SD::Initialize(G4HCofThisEvent *hce) {
    fHitsCollection = new FluxHitsCollection(SensitiveDetectorName, collectionName[0]);

    if (fHCID < 0) {
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    hce->AddHitsCollection(fHCID, fHitsCollection);
}

G4bool Flux_SD::ProcessHits(G4Step *step, G4TouchableHistory *) {

    auto preStepPoint = step->GetPreStepPoint();

    auto worldPos = preStepPoint->GetPosition();
    auto time = preStepPoint->GetGlobalTime();
    auto pid = step->GetTrack()->GetDefinition()->GetPDGEncoding();
    auto momentum = preStepPoint->GetMomentum();

    auto hit = new FluxHit();
    hit->setWorldPos(worldPos);
    hit->setTime(time);
    hit->setParticleID(pid);
    hit->setMomentum(momentum);

    fHitsCollection->insert(hit);

    return true;
}
