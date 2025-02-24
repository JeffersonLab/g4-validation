#include "histos.h"
#include "utilities.h"
#include "iostream"

// root includes
#include "TFile.h"
#include "TROOT.h"

using namespace std;
using namespace utilities;

GHistos::GHistos(string path, int READ) {

	vector<string> root_files = getListOfFilesInDirectory(path, {"root"});
	NCONFS = root_files.size();
	root_output_filename = "rga.root";
	wh.resize(NCONFS);

	// log root files
	for (unsigned int i = 0; i < root_files.size(); i++) {
		string filename = getFileFromPath(root_files[i]);
		configurations.push_back(filename.substr(0, filename.find(".root") ) ) ;

		cout << " > Processing root file: " << root_files[i] << " --> " << configurations.back() << endl;

		if (!READ) {
			TFile *f = new TFile(root_files[i].c_str());
			wh[i] = (TH2F *) f->Get("W");
			wh[i]->SetDirectory(0);  // Detach from TFile to avoid deletion
			wh[i]->SetLineColor(models_color[CONF]);
		}

	}

//	if (!READ) {
//		write();
//	}

}


void GHistos::write() {

	TFile *file = new TFile(root_output_filename.c_str(), "RECREATE");
	cout << endl << " > Writing histograms to ROOT file " << root_output_filename << endl << endl;
//
//	for (int i = 0; i < NCONFS; i++) {
//		wh[i]->Write();
//	}
//
	file->Close();
}


void GHistos::change_configuration() {
	CONF++;
	if (CONF == configurations.size()) { CONF = 0; }
	cout << " > Configuration: " << configurations[CONF] << endl << endl;
}


// warning: duplicated codem see header
TCanvas *GHistos::mcanvas(string title, double xsize, double ysize) {

	string label;
	// Remove spaces from the original string
	for (char c: title) {
		if (c != ' ') {
			label += c;
		}
	}

	TCanvas *rcanvas = dynamic_cast<TCanvas *>(gROOT->FindObject(label.c_str()));
	if (rcanvas) {
		rcanvas->Clear(); // Clear the canvas if it exists
	} else {
		rcanvas = new TCanvas(label.c_str(), title.c_str(), xsize, ysize);
	}

	return rcanvas;
}