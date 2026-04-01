## Elastic Scattering Test

The geometry consists of a 20 cm long LH2 target. The beam is 11GeV electron.
A sensitive sphere is collecting all the particles produced in the target satisfying 
the following conditions:

- theta angle greater than 2 degrees

The scoring follows the B5 example: 

- ntuple declaration in RunAction constructor, 
- ntuple filling in EndOfEventAction,
- ntuple writing in RunAction.

## Geometry

The target cell is a 20 cm long cylinder with a 2 cm diameter. 
The target is placed in the center of the world volume. 


![elastic](elastic_description.png)


## Sensitivity


## Compilation

With 4 cores (modify accordingly), using eleastic as the build directory:

- mkdir eleastic
- cd eleastic
- cmake \<path to geant4 eleastic source code\>
- make -j8
- add -DCMAKE_VERBOSE_MAKEFILE=ON to the cmake command for compilation verbosity


## Physics List

The example uses the geant4 extensible physics list, defined in the common source 
code at the root of this repo. 
The default is FTFP_BERT.
The option -p physList can be used to select alternative physics modules and constructors.

For example:

`-p FTFP_BERT_EMX`  would replace the standard e.m. physics with G4EmStandardPhysics_option3

`-p QGSP_BERT+G4OpticalPhysics` would use QGSP_BERT and G4OpticalPhysics

`-p QGSP_FTFP_BERT+G4RadioactiveDecayPhysics+G4OpticalPhysics` would use QGSP_FTFP_BERT, 
G4RadioactiveDecayPhysics and G4OpticalPhysics


To print all the geant4 available physics modules and their constructors, use the `pap` option
 

## Root output

The scoring is done with the sensitive detector volume, following the B5 example.


## Run :

### - Batch mode:





# TODO
