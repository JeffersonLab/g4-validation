#include "TControlBar.h"
#include "TApplication.h"

#include "histos/histos.h"

GHistos *histos = nullptr;

void elastic_analysis(string path, bool printa = false) {

histos = new GHistos(path);

	TControlBar *bar = new TControlBar("vertical", "Mauri Analysis", 1800, 30);
	bar->AddButton("Elastic Scattering Analysis", "");
	bar->AddButton("", "");
	bar->AddButton("Change Configuration", "histos->change_configuration()");
	bar->AddButton("", "");
	bar->AddButton("Show W", "histos->show_W()");
	bar->AddButton("", "");
	bar->Show();

}