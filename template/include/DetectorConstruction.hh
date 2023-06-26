#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

// geant4
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

namespace pim_absorption {

    class DetectorConstruction : public G4VUserDetectorConstruction {

    public:
        DetectorConstruction();
        virtual ~DetectorConstruction() override;

    public:
        virtual G4VPhysicalVolume *Construct() override;

    public:
        inline const G4VPhysicalVolume* getVacuumDetectorPV() const { return vacuumDetectorPV; }


    private:
        G4VPhysicalVolume* vacuumDetectorPV = nullptr; // the scoring volume




    };


}

#endif

