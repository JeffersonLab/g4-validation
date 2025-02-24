#include "TControlBar.h"
#include "TApplication.h"

#include "histos/histos.h"

GHistos *histos = nullptr;

void rga_analysis(string path, bool printa = false) {

	cout << "\n > Processing Directory: " << path << endl;
	vector<string> rfiles = getListOfFilesInDirectory(path, {"root"});


	TControlBar *bar = new TControlBar("vertical", "Mauri Background Analysis", 1800, 30);
	bar->AddButton("RGA Inclusive Analysis", "");
	bar->AddButton("", "");
	bar->Show();

}