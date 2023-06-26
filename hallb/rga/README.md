## RGA Test

The RGA experiment is 

## Geometry

A G4_Galactic tube encompass a beam dump made of aluminum.
In the stepping action, calls to the event action fill the ntuple when the step is in the scoring tube.


## Compilation

With 4 cores (modify accordingly):

 - cmake .
 - make -j4


## Physics List

The example uses the geant4 extensible physics list. The default is FTFP_BERT.
The option -p physList can be used to select alternative physics modules and constructors.

For example:


`-p FTFP_BERT_EMX`  would replace the standard e.m. physics with G4EmStandardPhysics_option3

`-p QGSP_BERT+G4OpticalPhysics` would use QGSP_BERT and G4OpticalPhysics

`-p QGSP_FTFP_BERT+G4RadioactiveDecayPhysics+G4OpticalPhysics` would use QGSP_FTFP_BERT, G4RadioactiveDecayPhysics and G4OpticalPhysics


To print all geant4 available physics modules and constructors use the -pap option
 
## Run :

### - Batch mode:

`./pim_absorption -m run.mac`

## ROOT Analysis:

The following root macro counts the number of neutrinos:

root neutrinos_histo.C
