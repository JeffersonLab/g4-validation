{
    cout << endl << " Root logon by Maurizio Ungaro" << endl;

    TStyle *mystyle = new TStyle("mystyle", "Plain Style");
    mystyle->SetPalette(1);

    mystyle->SetOptTitle(0);
    mystyle->SetOptStat(0);
    mystyle->SetOptFit(0);
    mystyle->SetCanvasColor(kWhite);
    mystyle->SetFillStyle(0);
    mystyle->SetNumberContours(80);
    mystyle->SetErrorX(0);
    mystyle->SetFrameFillColor(kWhite);
    mystyle->SetPadColor(kWhite);
    mystyle->SetNdivisions(505);
    mystyle->SetPaperSize(TStyle::kUSLetter);

    mystyle->SetCanvasBorderMode(0);
    mystyle->SetFrameBorderMode(0);
    mystyle->SetPadBorderMode(0);

    // palette
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.31 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    mystyle->SetNumberContours(NCont);

    gROOT->SetStyle("mystyle");

}
