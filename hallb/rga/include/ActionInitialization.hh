#ifndef ActionInitialization_h
#define ActionInitialization_h 1

// geant4
#include "G4VUserActionInitialization.hh"

namespace pim_absorption {

    class DetectorConstruction;

    class ActionInitialization : public G4VUserActionInitialization {
    public:
        ActionInitialization(DetectorConstruction *);

        virtual ~ActionInitialization();

        virtual void BuildForMaster() const;

        virtual void Build() const;

    private:
        DetectorConstruction *fDetConstruction;
    };

}
#endif


