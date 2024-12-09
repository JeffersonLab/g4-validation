#include "fluxHit.hh"

#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"

G4ThreadLocal G4Allocator<FluxHit>* FluxHitHitAllocator;

G4bool FluxHit::operator==(const FluxHit &right) const {
    return time == right.time &&
           fWorldPos == right.fWorldPos &&
           pid == right.pid &&
           momentum == right.momentum;
}


void FluxHit::Draw() {
    auto visManager = G4VVisManager::GetConcreteInstance();

    G4cout << "Drawing hit at " << fWorldPos << G4endl;

    if (!visManager) return;

    G4Circle circle(fWorldPos);
    circle.SetFillStyle(G4Circle::filled);
    circle.SetScreenSize(12);
    G4VisAttributes attribs(G4Colour::Yellow());
    circle.SetVisAttributes(attribs);
    visManager->Draw(circle);

    Print();
}

void FluxHit::Print() {
    G4cout << "  time: " << G4BestUnit(time, "Time")
           << "  position: " << G4BestUnit(fWorldPos, "Length")
           << "  particle ID: " << pid
           << "  momentum: " << G4BestUnit(momentum, "Energy")
           << G4endl;
}
