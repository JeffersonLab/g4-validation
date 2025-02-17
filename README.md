# Validation suite for physics at JLab's regime

The idea is to collect target / beam conditions of our experiments and check particle 
rates / cross sections of what comes out.

The various setups are meant to be Geant4 standalone tests, to be added later in geant4-validation 


## Compilation

### Notice for 11.3.0, affecting MacOs but not Linux:

The file Geant4PackageCache.cmake is missing in the 11.3.0 installation, 
but is present in the 11.2.2 installation. It is added to repository.  
Copying it in $G4INSTALL/lib/cmake/Geant4/  fixes cmake complications:

```bash
cp Geant4PackageCache.cmake $G4INSTALL/lib/cmake/Geant4/
```


To compile, create a build directory, run cmake then make. For example, for the **rga** experiment:

```bash
mkdir rga
cmake <path to rga source>
make -j8
```


### Common sources for the geant4 extensible physics list

The template use the common sources for the geant4 extensible physics list.
The default is FTFP_BERT.
The option -p physList can be used to select alternative physics modules and constructors.

For example:

`-p FTFP_BERT_EMX`  would replace the standard e.m. physics with G4EmStandardPhysics_option3

`-p QGSP_BERT+G4OpticalPhysics` would use QGSP_BERT and G4OpticalPhysics

`-p QGSP_FTFP_BERT+G4RadioactiveDecayPhysics+G4OpticalPhysics` would use QGSP_FTFP_BERT, G4RadioactiveDecayPhysics and G4OpticalPhysics


To print all geant4 available physics modules and constructors use the -pap option

Common Sources are in the root include and src directories.

