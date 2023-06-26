# Template Files

This directory, including this README, is meant to be used as template for new projects.

Each project should be a single directory within its JLab hall's directory, e.g. 
`hallb/rga/

The root directory includes source code for common option and the geant4 
extensible physics list.

## Experiment Description

Summarize the setup

## Geometry

Summarize the geometry

## Compilation

With 4 cores (modify accordingly):

 - cmake .
 - make -j4


## Physics List

The template use the common sources for the geant4 extensible physics list. 
The default is FTFP_BERT.
The option -p physList can be used to select alternative physics modules and constructors.

For example:

`-p FTFP_BERT_EMX`  would replace the standard e.m. physics with G4EmStandardPhysics_option3

`-p QGSP_BERT+G4OpticalPhysics` would use QGSP_BERT and G4OpticalPhysics

`-p QGSP_FTFP_BERT+G4RadioactiveDecayPhysics+G4OpticalPhysics` would use QGSP_FTFP_BERT, G4RadioactiveDecayPhysics and G4OpticalPhysics


To print all geant4 available physics modules and constructors use the -pap option
 
## Run :

### - Batch mode:

`./template_name -m run.mac`

## ROOT Analysis:

Provide instructions to run the analysis
