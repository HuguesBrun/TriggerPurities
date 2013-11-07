TChain *diLeptonTree = new TChain("diLeptonTree");


TFile *myFile = new TFile("theOutFile.root","RECREATE");

float pt;
float eta;
float absEta;
int passTrackerIso;
int passECALIso;
int passHCALIso;
int passSigIeta;
int passDeltaEtaSC;
int passdeltaPhiSC;
int passHoE;
int passConversionVtxFit;
int passMissHit;
int passd0;
int passdZ;


float other_pt;
float other_eta;
float other_absEta;
int other_passTrackerIso;
int other_passECALIso;
int other_passHCALIso;
int other_passSigIeta;
int other_passDeltaEtaSC;
int other_passdeltaPhiSC;
int other_passHoE;
int other_passConversionVtxFit;
int other_passMissHit;
int other_passd0;
int other_passdZ;




fillThe2DHisto(int inte, TH2F* theHisto){
    if (passTrackerIso&&other_passTrackerIso) theHisto->Fill(inte,0);
    if (passECALIso&&other_passECALIso) theHisto->Fill(inte,1);
    if (passHCALIso&&other_passHCALIso) theHisto->Fill(inte,2);
    if (passSigIeta&&other_passSigIeta) theHisto->Fill(inte,3);
    if (passDeltaEtaSC&&other_passDeltaEtaSC) theHisto->Fill(inte,4);
    if (passdeltaPhiSC&&other_passdeltaPhiSC) theHisto->Fill(inte,5);
    if (passHoE&&other_passHoE) theHisto->Fill(inte,6);
    if (passConversionVtxFit&&other_passConversionVtxFit) theHisto->Fill(inte,7);
    if (passMissHit&&other_passMissHit) theHisto->Fill(inte,8);
    if (passd0&&other_passd0) theHisto->Fill(inte,9);
    if (passdZ&&other_passdZ)  theHisto->Fill(inte,10);
        


}


loopTree(){
    diLeptonTree->Add("TnP_doubleElectrons.root");
    diLeptonTree->SetBranchAddress("other_pt",          &other_pt);
   // diLeptonTree->SetBranchAddress("other_eta",          &other_eta);
    diLeptonTree->SetBranchAddress("other_absEta",          &other_absEta);
    diLeptonTree->SetBranchAddress("other_passTrackerIso",          &other_passTrackerIso);
    diLeptonTree->SetBranchAddress("other_passECALIso",          &other_passECALIso);
    diLeptonTree->SetBranchAddress("other_passHCALIso",          &other_passHCALIso);
    diLeptonTree->SetBranchAddress("other_passSigIeta",          &other_passSigIeta);
    diLeptonTree->SetBranchAddress("other_passDeltaEtaSC",          &other_passDeltaEtaSC);
    diLeptonTree->SetBranchAddress("other_passdeltaPhiSC",          &other_passdeltaPhiSC);
    diLeptonTree->SetBranchAddress("other_passHoE",          &other_passHoE);
    diLeptonTree->SetBranchAddress("other_passConversionVtxFit",          &other_passConversionVtxFit);
    diLeptonTree->SetBranchAddress("other_passMissHit",          &other_passMissHit);
    diLeptonTree->SetBranchAddress("other_passd0",          &other_passd0);
    diLeptonTree->SetBranchAddress("other_passdZ",          &other_passdZ);
    
    diLeptonTree->SetBranchAddress("pt",          &pt);
   // diLeptonTree->SetBranchAddress("eta",          &eta);
    diLeptonTree->SetBranchAddress("absEta",          &absEta);
    diLeptonTree->SetBranchAddress("passTrackerIso",          &passTrackerIso);
    diLeptonTree->SetBranchAddress("passECALIso",          &passECALIso);
    diLeptonTree->SetBranchAddress("passHCALIso",          &passHCALIso);
    diLeptonTree->SetBranchAddress("passSigIeta",          &passSigIeta);
    diLeptonTree->SetBranchAddress("passDeltaEtaSC",          &passDeltaEtaSC);
    diLeptonTree->SetBranchAddress("passdeltaPhiSC",          &passdeltaPhiSC);
    diLeptonTree->SetBranchAddress("passHoE",          &passHoE);
    diLeptonTree->SetBranchAddress("passConversionVtxFit",          &passConversionVtxFit);
    diLeptonTree->SetBranchAddress("passMissHit",          &passMissHit);
    diLeptonTree->SetBranchAddress("passd0",          &passd0);
    diLeptonTree->SetBranchAddress("passdZ",          &passdZ);

    

    TH1F *hMinus1Num = new TH1F("hMinus1Num","",11,0,11);
    hMinus1Num->Sumw2();
    TH1F *hMinus1Den = new TH1F("hMinus1Den","",11,0,11);
    hMinus1Den->Sumw2();
 
    TH2F *correCuts = new TH2F("correCuts","",11,0,11,11,0,11);

    int nbEvents = diLeptonTree->GetEntries();
    
   for (int i = 0 ; i < nbEvents ; i++){
        if ((i%1000)==0) cout << "i=" << i << endl;
        diLeptonTree->GetEntry(i);
      //  cout << "pt=" << pt << " ptOther=" << other_pt << endl;
       if (!(((pt>other_pt)&&(pt>20&&other_pt>10))||((other_pt>pt)&&(pt>10&&other_pt>20)))) continue;
       if (!(absEta<2.5&&other_absEta<2.5)) continue;
        for (int j = 0 ; j < 11 ; j++) hMinus1Den->Fill(j);
        if (passTrackerIso&&other_passTrackerIso) {hMinus1Num->Fill(0); fillThe2DHisto(0,correCuts);}
        if (passECALIso&&other_passECALIso) {hMinus1Num->Fill(1); fillThe2DHisto(1,correCuts);}
        if (passHCALIso&&other_passHCALIso) {hMinus1Num->Fill(2); fillThe2DHisto(2,correCuts);}
        if (passSigIeta&&other_passSigIeta) {hMinus1Num->Fill(3); fillThe2DHisto(3,correCuts);}
        if (passDeltaEtaSC&&other_passDeltaEtaSC) {hMinus1Num->Fill(4); fillThe2DHisto(4,correCuts);}
        if (passdeltaPhiSC&&other_passdeltaPhiSC) {hMinus1Num->Fill(5); fillThe2DHisto(5,correCuts);}
        if (passHoE&&other_passHoE) {hMinus1Num->Fill(6); fillThe2DHisto(6,correCuts);}
       if (passConversionVtxFit&&other_passConversionVtxFit) {hMinus1Num->Fill(7); fillThe2DHisto(7,correCuts);}
       if (passMissHit&&other_passMissHit) {hMinus1Num->Fill(8); fillThe2DHisto(8,correCuts);}
        if (passd0&&other_passd0) {hMinus1Num->Fill(9); fillThe2DHisto(9,correCuts);}
        if (passdZ&&other_passdZ) {hMinus1Num->Fill(10); fillThe2DHisto(10,correCuts);}
        
        
    }
    
    TH1F *hMinus1Eff = (TH1F*) hMinus1Num->Clone("hMinus1Eff");
    
    
   // hMinus1Eff->Sumw2();
    hMinus1Eff->Divide(hMinus1Num,hMinus1Den, 1,1);
    hMinus1Eff->GetXaxis()->SetBinLabel(1,"trackerIso");
    hMinus1Eff->GetXaxis()->SetBinLabel(2,"ECALiso");
    hMinus1Eff->GetXaxis()->SetBinLabel(3,"HCALiso");
    hMinus1Eff->GetXaxis()->SetBinLabel(4,"#sigma_{i #eta i #eta}");
    hMinus1Eff->GetXaxis()->SetBinLabel(5,"#Delta #eta_{SC}");
    hMinus1Eff->GetXaxis()->SetBinLabel(6,"#Delta #phi_{SC}");
    hMinus1Eff->GetXaxis()->SetBinLabel(7,"H/E");
    hMinus1Eff->GetXaxis()->SetBinLabel(8,"conv vtx fit");
    hMinus1Eff->GetXaxis()->SetBinLabel(9,"no missing hit");
    hMinus1Eff->GetXaxis()->SetBinLabel(10,"dO");
    hMinus1Eff->GetXaxis()->SetBinLabel(11,"dZ");
    
    TH2F *h2Norm = (TH2F*) correCuts->Clone("h2Norm");
    for (int i = 0 ; i < 11 ; i++){
        for (int j = 0 ; j < 11 ; j++){
            h2Norm->SetBinContent(i+1, j+1,1.0*correCuts->GetBinContent(i+1,j+1)/correCuts->GetBinContent(i+1,i+1));
            
        }
    }
            h2Norm->GetXaxis()->SetBinLabel(1,"trackerIso");
            h2Norm->GetXaxis()->SetBinLabel(2,"ECALiso");
            h2Norm->GetXaxis()->SetBinLabel(3,"HCALiso");
            h2Norm->GetXaxis()->SetBinLabel(4,"#sigma_{i #eta i #eta}");
            h2Norm->GetXaxis()->SetBinLabel(5,"#Delta #eta_{SC}");
            h2Norm->GetXaxis()->SetBinLabel(6,"#Delta #phi_{SC}");
            h2Norm->GetXaxis()->SetBinLabel(7,"H/E");
            h2Norm->GetXaxis()->SetBinLabel(8,"conv vtx fit");
            h2Norm->GetXaxis()->SetBinLabel(9,"no missing hit");
            h2Norm->GetXaxis()->SetBinLabel(10,"dO");
            h2Norm->GetXaxis()->SetBinLabel(11,"dZ");
    
            h2Norm->GetYaxis()->SetBinLabel(1,"trackerIso");
            h2Norm->GetYaxis()->SetBinLabel(2,"ECALiso");
            h2Norm->GetYaxis()->SetBinLabel(3,"HCALiso");
            h2Norm->GetYaxis()->SetBinLabel(4,"#sigma_{i #eta i #eta}");
            h2Norm->GetYaxis()->SetBinLabel(5,"#Delta #eta_{SC}");
            h2Norm->GetYaxis()->SetBinLabel(6,"#Delta #phi_{SC}");
            h2Norm->GetYaxis()->SetBinLabel(7,"H/E");
            h2Norm->GetYaxis()->SetBinLabel(8,"conv vtx fit");
            h2Norm->GetYaxis()->SetBinLabel(9,"no missing hit");
            h2Norm->GetYaxis()->SetBinLabel(10,"dO");
            h2Norm->GetYaxis()->SetBinLabel(11,"dZ");
    
    
    myFile->cd();
    hMinus1Num->Write();
    hMinus1Den->Write();
    hMinus1Eff->Write();
    h2Norm->Write();
    correCuts->Write();
    
    
    
    myFile->Close();


}
