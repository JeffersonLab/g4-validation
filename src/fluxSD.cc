#include "fluxSD.hh"
#include "G4SDManager.hh"



Flux_SD::Flux_SD(G4String name) : G4VSensitiveDetector(name) {
    collectionName.insert("fluxColl");
}

void Flux_SD::Initialize(G4HCofThisEvent *HCE) {
    fHitsCollection = new FluxHitsCollection(SensitiveDetectorName, collectionName[0]);

    if (fHCID < 0) {
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    HCE->AddHitsCollection(fHCID, fHitsCollection);
}

G4bool Flux_SD::ProcessHits(G4Step *step, G4TouchableHistory *) {

    auto preStepPoint = step->GetPreStepPoint();

    auto worldPos = preStepPoint->GetPosition();
    auto time = preStepPoint->GetGlobalTime();
    auto pid = step->GetTrack()->GetDefinition()->GetPDGEncoding();
    auto momentum = preStepPoint->GetMomentum();

    auto hit = new FluxHit();
    hit->SetWorldPos(worldPos);
    hit->SetTime(time);
    hit->SetParticleID(pid);
    hit->SetMomentum(momentum);

    fHitsCollection->insert(hit);

    return true;
}
