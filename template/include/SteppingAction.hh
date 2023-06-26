#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class G4LogicalVolume;

namespace pim_absorption {

class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(const DetectorConstruction* detectorConstruction,
						EventAction* eventAction);
	virtual ~SteppingAction() override;

	virtual void UserSteppingAction(const G4Step* step) override;

private:
	const DetectorConstruction* fDetConstruction = nullptr;
	EventAction*  fEventAction;

};

}
#endif
