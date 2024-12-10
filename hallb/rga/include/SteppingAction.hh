#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class G4LogicalVolume;

namespace rga {


class SteppingAction : public G4UserSteppingAction {
public:
    SteppingAction() = default;

    ~SteppingAction() override = default;

    void UserSteppingAction(const G4Step *step) override;

private:

    double max_x_pos = 110;
    double max_y_pos = 110;
    double max_z_pos = 110;

};

}
#endif
