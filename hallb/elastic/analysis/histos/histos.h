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
	GHistos(std::string path, int READ = 0);

	void show_W();
	void change_configuration();


private:

	int CONF = 0;
	static constexpr double canvas_size = 1200;
	static constexpr double canvas_size_w = 1400;

	std::string PRINT = "none";
	std::string root_output_filename;

	std::vector <std::string> configurations;
	int NCONFS = -1; // to be passed in the constructor

	// warning: duplicated function. Perhaps can have a superclass
	// that includes common colls
	TCanvas *mcanvas(std::string title, double xsize, double ysize);
	std::vector <TH2F * > wh;
	std::vector <EColor> models_color = {kBlack, kRed, kBlue, kGreen, kOrange, kMagenta, kGray};


	void write();


};


#endif
