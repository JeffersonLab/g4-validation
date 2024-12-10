#ifndef FLUX_HIT_H
#define FLUX_HIT_H 1

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"


class FluxHit : public G4VHit {
public:
    FluxHit() { ; }

    ~FluxHit() override = default;

    FluxHit &operator=(const FluxHit &right) = default;

    G4bool operator==(const FluxHit &right) const;

    inline void *operator new(size_t);

    inline void operator delete(void *aHit);

    void Draw() override;

    void Print() override;

    void setWorldPos(G4ThreeVector xyz) { fWorldPos = xyz; }

    G4ThreeVector getWorldPos() const { return fWorldPos; }

    void setTime(double t) { time = t; }

    double getTime() const { return time; }

    void setParticleID(int id) { pid = id; }

    int getParticleID() const { return pid; }

    void setMomentum(G4ThreeVector p) { momentum = p; }

    G4ThreeVector getMomentum() const { return momentum; }

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
