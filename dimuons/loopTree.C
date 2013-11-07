TChain *diLeptonTree = new TChain("diLeptonTree");


TFile *myFile = new TFile("theOutFile.root","RECREATE");

float pt;
float eta;
float absEta;

int globalOrTrackerMuon;
int globalOrTrackerMuonTight;
int PFmuon;
int trackCleaning;
int passMuonIPcuts;
int passMuonMVA;

int global;
int tracker;
int trackChi2;
int nbOfMatches;
int nbValidMuonHits;
int TMlastStation;

int trackKink;
int nbTkLayer;
int nbValidPixHits;
int trackError;


float other_pt;
float other_eta;
float other_absEta;
int other_globalOrTrackerMuon;
int other_globalOrTrackerMuonTight;
int other_PFmuon;
int other_trackCleaning;
int other_passMuonIPcuts;
int other_passMuonMVA;

int other_global;
int other_tracker;
int other_trackChi2;
int other_nbOfMatches;
int other_nbValidMuonHits;
int other_TMlastStation;

int other_trackKink;
int other_nbTkLayer;
int other_nbValidPixHits;
int other_trackError;


fillThe2DHisto(int inte, TH2F* theHisto){
    if (PFmuon&&other_PFmuon) theHisto->Fill(inte,0);
    if (trackChi2&&other_trackChi2) theHisto->Fill(inte,1);
    if (nbOfMatches&&other_nbOfMatches) theHisto->Fill(inte,2);
    if (nbValidMuonHits&&other_nbValidMuonHits) theHisto->Fill(inte,3);
    if (TMlastStation&&other_TMlastStation) theHisto->Fill(inte,4);
    if (trackKink&&other_trackKink) theHisto->Fill(inte,5);
    if (nbTkLayer&&other_nbTkLayer) theHisto->Fill(inte,6);
    if (nbValidPixHits&&other_nbValidPixHits) theHisto->Fill(inte,7);
    if (trackError&&other_trackError) theHisto->Fill(inte,8);


}


loopTree(){
    diLeptonTree->Add("TnP_doubleMuons.root");
    
    diLeptonTree->SetBranchAddress("pt",          &pt);
    diLeptonTree->SetBranchAddress("absEta",          &absEta);
    
    diLeptonTree->SetBranchAddress("other_pt",          &other_pt);
    diLeptonTree->SetBranchAddress("other_absEta",          &other_absEta);

    diLeptonTree->SetBranchAddress("globalOrTrackerMuon",          &globalOrTrackerMuon);
    diLeptonTree->SetBranchAddress("globalOrTrackerMuonTight",          &globalOrTrackerMuonTight);
    diLeptonTree->SetBranchAddress("PFmuon",          &PFmuon);
    diLeptonTree->SetBranchAddress("trackCleaning",          &trackCleaning);
    diLeptonTree->SetBranchAddress("passMuonIPcuts",          &passMuonIPcuts);
    diLeptonTree->SetBranchAddress("passMuonMVA",          &passMuonMVA);
    diLeptonTree->SetBranchAddress("global",          &global);
    diLeptonTree->SetBranchAddress("tracker",          &tracker);
    diLeptonTree->SetBranchAddress("trackChi2",          &trackChi2);
    diLeptonTree->SetBranchAddress("nbOfMatches",          &nbOfMatches);
    diLeptonTree->SetBranchAddress("nbValidMuonHits",          &nbValidMuonHits);
    diLeptonTree->SetBranchAddress("TMlastStation",          &TMlastStation);
    diLeptonTree->SetBranchAddress("trackKink",          &trackKink);
    diLeptonTree->SetBranchAddress("nbTkLayer",          &nbTkLayer);
    diLeptonTree->SetBranchAddress("nbValidPixHits",          &nbValidPixHits);
    diLeptonTree->SetBranchAddress("trackError",          &trackError);
    
    
    
    
    diLeptonTree->SetBranchAddress("other_globalOrTrackerMuon",          &other_globalOrTrackerMuon);
    diLeptonTree->SetBranchAddress("other_globalOrTrackerMuonTight",          &other_globalOrTrackerMuonTight);
    diLeptonTree->SetBranchAddress("other_PFmuon",          &other_PFmuon);
    diLeptonTree->SetBranchAddress("other_trackCleaning",          &other_trackCleaning);
    diLeptonTree->SetBranchAddress("other_passMuonIPcuts",          &other_passMuonIPcuts);
    diLeptonTree->SetBranchAddress("other_global",          &other_global);
    diLeptonTree->SetBranchAddress("other_tracker",          &other_tracker);
    diLeptonTree->SetBranchAddress("other_trackChi2",          &other_trackChi2);
    diLeptonTree->SetBranchAddress("other_nbOfMatches",          &other_nbOfMatches);
    diLeptonTree->SetBranchAddress("other_nbValidMuonHits",          &other_nbValidMuonHits);
    diLeptonTree->SetBranchAddress("other_TMlastStation",          &other_TMlastStation);
    diLeptonTree->SetBranchAddress("other_trackKink",          &other_trackKink);
    diLeptonTree->SetBranchAddress("other_nbTkLayer",          &other_nbTkLayer);
    diLeptonTree->SetBranchAddress("other_nbValidPixHits",          &other_nbValidPixHits);
    diLeptonTree->SetBranchAddress("other_trackError",          &other_trackError);

    
    

    TH1F *hMinus1Num = new TH1F("hMinus1Num","",9,0,9);
    hMinus1Num->Sumw2();
    TH1F *hMinus1Den = new TH1F("hMinus1Den","",9,0,9);
    hMinus1Den->Sumw2();
 
    TH2F *correCuts = new TH2F("correCuts","",9,0,9,9,0,9);

    int nbEvents = diLeptonTree->GetEntries();
    
    for (int i = 0 ; i < nbEvents ; i++){
        if ((i%1000)==0) cout << "i=" << i << endl;
        diLeptonTree->GetEntry(i);
      //  cout << "pt=" << pt << " ptOther=" << other_pt << endl;
        if (!(((pt>other_pt)&&(pt>20&&other_pt>10))||((other_pt>pt)&&(pt>10&&other_pt>20)))) continue;
        if (!(absEta<2.4&&other_absEta<2.4)) continue;
      //  cout << "kine" << endl;
        if (!(globalOrTrackerMuon&&other_globalOrTrackerMuon)) continue;
      //  cout << "c koi ce muon" << endl;
        for (int j = 0 ; j < 9 ; j++) hMinus1Den->Fill(j);
        if (PFmuon&&other_PFmuon) {hMinus1Num->Fill(0); fillThe2DHisto(0,correCuts);}
        if (trackChi2&&other_trackChi2) {hMinus1Num->Fill(1); fillThe2DHisto(1,correCuts);}
        if (nbOfMatches&&other_nbOfMatches) {hMinus1Num->Fill(2); fillThe2DHisto(2,correCuts);}
        if (nbValidMuonHits&&other_nbValidMuonHits) {hMinus1Num->Fill(3); fillThe2DHisto(3,correCuts);}
        if (TMlastStation&&other_TMlastStation) {hMinus1Num->Fill(4); fillThe2DHisto(4,correCuts);}
        if (trackKink&&other_trackKink) {hMinus1Num->Fill(5); fillThe2DHisto(5,correCuts);}
        if (nbTkLayer&&other_nbTkLayer) {hMinus1Num->Fill(6); fillThe2DHisto(6,correCuts);}
        if (nbValidPixHits&&other_nbValidPixHits) {hMinus1Num->Fill(7); fillThe2DHisto(7,correCuts);}
        if (trackError&&other_trackError) {hMinus1Num->Fill(8); fillThe2DHisto(8,correCuts);}
    
        
        
    }
    
    TH1F *hMinus1Eff = (TH1F*) hMinus1Num->Clone("hMinus1Eff");
    
    
   // hMinus1Eff->Sumw2();
    hMinus1Eff->Divide(hMinus1Num,hMinus1Den, 1,1);
    hMinus1Eff->GetXaxis()->SetBinLabel(1,"PF");
    hMinus1Eff->GetXaxis()->SetBinLabel(2,"trackChi2");
    hMinus1Eff->GetXaxis()->SetBinLabel(3,"nbOfMatches");
    hMinus1Eff->GetXaxis()->SetBinLabel(4,"nbValidMuonHits");
    hMinus1Eff->GetXaxis()->SetBinLabel(5,"TMlastStation");
    hMinus1Eff->GetXaxis()->SetBinLabel(6,"trackKink");
    hMinus1Eff->GetXaxis()->SetBinLabel(7,"nbTkLayer");
    hMinus1Eff->GetXaxis()->SetBinLabel(8,"nbValidPixHits");
    hMinus1Eff->GetXaxis()->SetBinLabel(9,"trackError");
    
    TH2F *h2Norm = (TH2F*) correCuts->Clone("h2Norm");
    for (int i = 0 ; i < 9 ; i++){
        for (int j = 0 ; j < 9 ; j++){
            h2Norm->SetBinContent(i+1, j+1,1.0*correCuts->GetBinContent(i+1,j+1)/correCuts->GetBinContent(i+1,i+1));
            
        }
    }
    h2Norm->GetXaxis()->SetBinLabel(1,"PF");
    h2Norm->GetXaxis()->SetBinLabel(2,"trackChi2");
    h2Norm->GetXaxis()->SetBinLabel(3,"nbOfMatches");
    h2Norm->GetXaxis()->SetBinLabel(4,"nbValidMuonHits");
    h2Norm->GetXaxis()->SetBinLabel(5,"TMlastStation");
    h2Norm->GetXaxis()->SetBinLabel(6,"trackKink");
    h2Norm->GetXaxis()->SetBinLabel(7,"nbTkLayer");
    h2Norm->GetXaxis()->SetBinLabel(8,"nbValidPixHits");
    h2Norm->GetXaxis()->SetBinLabel(9,"trackError");
    
    h2Norm->GetYaxis()->SetBinLabel(1,"PF");
    h2Norm->GetYaxis()->SetBinLabel(2,"trackChi2");
    h2Norm->GetYaxis()->SetBinLabel(3,"nbOfMatches");
    h2Norm->GetYaxis()->SetBinLabel(4,"nbValidMuonHits");
    h2Norm->GetYaxis()->SetBinLabel(5,"TMlastStation");
    h2Norm->GetYaxis()->SetBinLabel(6,"trackKink");
    h2Norm->GetYaxis()->SetBinLabel(7,"nbTkLayer");
    h2Norm->GetYaxis()->SetBinLabel(8,"nbValidPixHits");
    h2Norm->GetYaxis()->SetBinLabel(9,"trackError");
    
    
    myFile->cd();
    hMinus1Num->Write();
    hMinus1Den->Write();
    hMinus1Eff->Write();
    h2Norm->Write();
    correCuts->Write();
    
    
    
    myFile->Close();


}
