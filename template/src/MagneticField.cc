
#include "MagneticField.hh"
//#include "G4SystemOfUnits.hh"
//#include "globals.hh"

// derived from B5, but w/o the messenger
namespace template_project_name {


    MagneticField::MagneticField() {}
    MagneticField::~MagneticField() {}

    void MagneticField::GetFieldValue(const G4double [4], double *bField) const {
        bField[0] = 0.;
        bField[1] = z_value;
        bField[2] = 0.;
    }

}
