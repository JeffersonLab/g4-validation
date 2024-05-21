#ifndef MAGNETIC_FIELD
#define MAGNETIC_FIELD 1

#include "G4MagneticField.hh"
#include <CLHEP/Units/SystemOfUnits.h>

// derived from B5, but w/o the messenger
namespace rga {

    class MagneticField : public G4MagneticField {
    public:

        MagneticField();
        ~MagneticField() override;

        void GetFieldValue(const G4double point[4], double *bField) const override;

    private:
        void DefineCommands();
        G4double z_value = 5.0 * CLHEP::tesla;
    };

}

#endif
