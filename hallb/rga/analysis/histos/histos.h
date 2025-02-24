#ifndef INFO_H
#define INFO_H

// ROOT includes
#include "TH1.h"
#include "TH2.h"
#include "Rtypes.h" // EColor
#include "TCanvas.h"

#include <vector>
#include <string>


// Common Classes with ROOT analysis macro
class GHistos {
public:
	GHistos(std::vector <std::string> confs, int READ = 0);


private:

	std::vector <TH2F * > wh;
	int NCONFS = -1; // to be passed in the constructor

	std::vector <std::string> confs;
	std::string PRINT = "none";
	std::string root_output_filename;
};


#endif
