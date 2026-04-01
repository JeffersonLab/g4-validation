#include "histos/histos.h"

// root
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TF1.h"
#include "TLegend.h"

using namespace std;

void GHistos::show_W() {

	// general label
TLatex glab;
	glab.SetTextColor(kBlue + 3);
	glab.SetNDC(1);

	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.12);
	gStyle->SetPadRightMargin(0.1);
	gStyle->SetPadLeftMargin(0.1);

	auto rcanvas = mcanvas("W Distribution", canvas_size_w, canvas_size);
	auto center_pad = new TPad("center_pad", "center_pad", 0.00, 0.00, 0.98, 0.94);
	center_pad->Draw();

	rcanvas->cd();
	glab.SetTextFont(42);
	glab.SetTextSize(0.03);
	glab.DrawLatex(0.08, 0.94, Form("W Distribution"));

	center_pad->cd();
	wh[0]->Draw("EH");

	for (int m = 1; m < NCONFS; m++) {
		wh[m]->Draw("EHsame");
	}

	for (int m = 0; m < NCONFS; m++) {
		glab.SetTextColor(models_color[m]);
		glab.DrawLatex(0.65, 0.85 - m * 0.05, Form("Model %s ", configurations[m].c_str()));
	}

	if (PRINT != "none") {
		//	rcanvas->Print(Form("img/occ-avg_conf-%s%s", confs[CONF].c_str(), PRINT.c_str()));
	}
}