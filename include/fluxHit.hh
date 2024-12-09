#ifndef FLUX_HIT_H
#define FLUX_HIT_H 1

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"


class FluxHit : public G4VHit {
public:
    FluxHit() = default;

    ~FluxHit() override = default;

    FluxHit &operator=(const FluxHit &right) = default;

    G4bool operator==(const FluxHit &right) const;

    inline void *operator new(size_t);

    inline void operator delete(void *aHit);

    void Draw() override;

    void Print() override;

    void SetWorldPos(G4ThreeVector xyz) { fWorldPos = xyz; }

    G4ThreeVector GetWorldPos() const { return fWorldPos; }

    void SetTime(double t) { time = t; }

    double GetTime() const { return time; }

    void SetParticleID(int id) { pid = id; }

    int GetParticleID() const { return pid; }

    void SetMomentum(G4ThreeVector p) { momentum = p; }

    G4ThreeVector GetMomentum() const { return momentum; }

private:

    double time;
    G4ThreeVector fWorldPos;
    int pid;
    G4ThreeVector momentum;

};


using FluxHitsCollection = G4THitsCollection<FluxHit>;

extern G4ThreadLocal G4Allocator<FluxHit>* FluxHitHitAllocator;


inline void *FluxHit::operator new(size_t) {
    if (!FluxHitHitAllocator) {
        FluxHitHitAllocator = new G4Allocator<FluxHit>;
    }
    return (void *) FluxHitHitAllocator->MallocSingle();
}

inline void FluxHit::operator delete(void *aHit) {
    FluxHitHitAllocator->FreeSingle((FluxHit *) aHit);
}

#endif
