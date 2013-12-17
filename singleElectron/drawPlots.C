TFile *myFile = new TFile("outFileTrigger.root");


doThe2DPlot(TString nom, TString theAxis){
    UInt_t Number = 2;
	Double_t Red[2]    = { 1.00, 0.00};
	Double_t Green[2]  = { 1.00, 0.00};
	Double_t Blue[2]   = { 1.00, 1.00};
	Double_t Length[2] = { 0.00, 1.0};
	Int_t nb=50;
	TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
    
    TH2F *h2 = (TH2F*) myFile->Get(nom);
    
    
    TCanvas *c0 = new TCanvas("c0","coucou",600,600);
    c0->SetFillColor(0);
	h2->GetXaxis()->SetTitle("leading electron "+theAxis);
	h2->GetYaxis()->SetTitle("trailing electron "+theAxis);
	h2->GetZaxis()->SetLabelSize(0.02);
	h2->SetAxisRange(0.,1.,"Z");
    h2->Draw("COLZ:texte");
    
    c0->Print("plots/"+nom+".png");
    c0->Print("plots/"+nom+".eps");
    
    
}

doThe1DPlot(TString nom, TString theAxis){
    TH1F *kine = (TH1F*) myFile->Get(nom+"_kine");
    TH1F *GT= (TH1F*) myFile->Get(nom+"_ID");
    TH1F *PF = (TH1F*) myFile->Get(nom+"_IP");
    TH1F *TK = (TH1F*) myFile->Get(nom+"_Convs");

    TCanvas *c0 = new TCanvas("c0","coucou",600,600);
    c0->SetFillColor(0);
    kine->SetLineWidth(2);
    kine->GetXaxis()->SetTitle(theAxis);
    kine->SetMaximum(1.5);
    kine->SetMinimum(0.);
    kine->GetYaxis()->SetTitle("#epsilon");
    kine->Draw("E1");
    
    GT->SetLineColor(kGreen-2);
    GT->SetLineWidth(2);
    GT->Draw("E1:same");
    
    
    PF->SetLineColor(kRed-2);
    PF->SetLineWidth(2);
    PF->Draw("E1:same");
    
    TK->SetLineColor(kCyan-2);
    TK->SetLineWidth(2);
    TK->Draw("E1:same");

    
    TLegend *t = new TLegend(0.23,0.66,0.88,0.85);
    t->SetFillColor(0);
    t->SetLineColor(0);
    t->AddEntry(kine,"P_{T} cuts");
    t->AddEntry(GT,"+ preselection");
    t->AddEntry(PF,"+ IP cuts");
    t->AddEntry(TK,"+ conversion rejection");
    t->Draw();
    c0->Print("plots/"+nom+".png");
    c0->Print("plots/"+nom+".eps");
    
}

doThe1DPlotAllLeg(TString nom, TString theAxis){
    TH1F *FO = (TH1F*) myFile->Get(nom);
    TH1F *FOtag = (TH1F*) myFile->Get(nom+"tag");
    TH1F *IP= (TH1F*) myFile->Get(nom+"_IP");
    TH1F *IPtag= (TH1F*) myFile->Get(nom+"_IPtag");
    TH1F *conv = (TH1F*) myFile->Get(nom+"_IP_CONVR");
    TH1F *convtag = (TH1F*) myFile->Get(nom+"_IP_CONVRtag");
    
    TCanvas *c0 = new TCanvas("c0","coucou",600,600);
    c0->SetFillColor(0);
    FO->SetLineWidth(2);
    FO->SetMaximum(1);
    FO->SetMinimum(0.);
    FO->GetXaxis()->SetTitle(theAxis);
    FO->GetYaxis()->SetTitle("#epsilon");
    FO->Draw("E1");
    
    FOtag->SetLineColor(kBlue-9);
    FOtag->SetLineWidth(2);
    FOtag->Draw("E1:same");
    
    IP->SetLineColor(kGreen-2);
    IP->SetLineWidth(2);
    IP->Draw("E1:same");
    
    IPtag->SetLineColor(kGreen-9);
    IPtag->SetLineWidth(2);
    IPtag->Draw("E1:same");

    
    
    conv->SetLineColor(kRed-2);
    conv->SetLineWidth(2);
    conv->Draw("E1:same");
    
    convtag->SetLineColor(kRed-9);
    convtag->SetLineWidth(2);
    convtag->Draw("E1:same");
    
    TLegend *t = new TLegend(0.21,0.15,0.86,0.34);
    t->SetFillColor(0);
    t->SetLineColor(0);
    t->AddEntry(FO,"ID on leading leg");
    t->AddEntry(FOtag,"ID on trailing leg");
    t->AddEntry(IP,"+ IP on leading leg");
    t->AddEntry(IPtag,"+ ID on trailing leg");
    t->AddEntry(conv,"+ conv rejection on leading leg");
    t->AddEntry(convtag,"+ conv rejection on trailing leg");
    t->Draw();
    c0->Print("plots/"+nom+".png");
    c0->Print("plots/"+nom+".eps");
}


drawPlots(){
   /*  doThe2DPlot("FO","P_{T} (GeV/c)");
     doThe2DPlot("eta_FO","|#eta|");*/
    doThe1DPlot("vtx","nb of reconstructed vtx");
    doThe1DPlot("pt","electron P_{T}");
    // doThe1DPlotAllLeg("vtx_leg_FO","nb of reconstructed vtx");

    
}