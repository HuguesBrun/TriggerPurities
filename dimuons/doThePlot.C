TFile *myFile = new TFile("outFileTrigger.root","RECREATE");
TChain *chain = new TChain("diLeptonTree");


// bining we want to use ! 
float ptBins[5] = {10,20,30,50,80};
float ptBins2[5] = {10,20,30,50,80};

float etaBins[5] = {0., 0.8, 1.2, 2,2.5};
float etaBins2[5] = {0., 0.8, 1.2, 2,2.5};

doAndSaveThePlot(TString name, TString cuts){
    int nbBefore, nbAfter;
    
    TH2F *h_denom = new TH2F("h_denom","",4,ptBins,4,ptBins2);
    TH2F *h_numerateur = new TH2F("h_numerateur","",4,ptBins,4,ptBins2);
    
    TH2F *h_ratio = new TH2F("h_ratio","",4,ptBins,4,ptBins2);
    h_ratio->Sumw2();
    
    for (int i =1 ; i < 4 ; i++){
        for (int j=0 ; j < 4 ; j++){
            cout << "cuts " << cuts << endl;
            nbBefore = chain->GetEntries(Form("(((pt>other_pt)&&(pt>%f&&pt<%f&&other_pt>%f&&other_pt<%f))||((other_pt>pt)&&(pt>%f&&pt<%f&&other_pt>%f&&other_pt<%f)))",ptBins[i],ptBins[i+1],ptBins[j],ptBins[j+1],ptBins[j],ptBins[j+1],ptBins[i],ptBins[i+1]));
            nbAfter = chain->GetEntries(Form("(((pt>other_pt)&&(pt>%f&&pt<%f&&other_pt>%f&&other_pt<%f))||((other_pt>pt)&&(pt>%f&&pt<%f&&other_pt>%f&&other_pt<%f)))&&",ptBins[i],ptBins[i+1],ptBins[j],ptBins[j+1],ptBins[j],ptBins[j+1],ptBins[i],ptBins[i+1])+cuts);
            cout << "i j " << i << " " << j << " nbBefore=" << nbAfter << endl;
            h_denom->SetBinContent(i+1,j+1, nbBefore);
            h_numerateur->SetBinContent(i+1,j+1, nbAfter);
            h_ratio->Divide(h_numerateur,h_denom,1,1);
        }
    }
    h_ratio->Write(name);
    delete h_denom;
    delete h_numerateur;
    delete h_ratio;
    
}
doAndSaveThePlotEta(TString name, TString cuts){
    int nbBefore, nbAfter;
    
    TH2F *h_denom = new TH2F("h_denom","",4,etaBins,4,etaBins2);
    TH2F *h_numerateur = new TH2F("h_numerateur","",4,etaBins,4,etaBins2);
    
    TH2F *h_ratio = new TH2F("h_ratio","",4,etaBins,4,etaBins2);
    h_ratio->Sumw2();
    
    for (int i =0 ; i < 4 ; i++){
        for (int j=0 ; j < 4 ; j++){
            cout << "cuts " << cuts << endl;
            nbBefore = chain->GetEntries(Form("(((pt>other_pt)&&(absEta>%f&&absEta<%f&&other_absEta>%f&&other_absEta<%f))||((other_pt>pt)&&(absEta>%f&&absEta<%f&&other_absEta>%f&&other_absEta<%f)))",etaBins[i],etaBins[i+1],etaBins[j],etaBins[j+1],etaBins[j],ptBins[j+1],etaBins[i],etaBins[i+1]));
            nbAfter = chain->GetEntries(Form("(((pt>other_pt)&&(absEta>%f&&absEta<%f&&other_absEta>%f&&other_absEta<%f))||((other_pt>pt)&&(absEta>%f&&absEta<%f&&other_absEta>%f&&other_absEta<%f)))&&",etaBins[i],etaBins[i+1],etaBins[j],etaBins[j+1],etaBins[j],ptBins[j+1],etaBins[i],etaBins[i+1])+cuts);
            cout << "i j " << i << " " << j << " nbBefore=" << nbAfter << endl;
            h_denom->SetBinContent(i+1,j+1, nbBefore);
            h_numerateur->SetBinContent(i+1,j+1, nbAfter);
            h_ratio->Divide(h_numerateur,h_denom,1,1);
        }
    }
    h_ratio->Write("eta_"+name);
    delete h_denom;
    delete h_numerateur;
    delete h_ratio;
    
}

doAndTheVertexPlot(TString name, TString cuts){
    
    int nbBefore, nbAfter;
    TH1F *nVtx = new TH1F("nVtx","",35,0,40);
    nVtx->Sumw2();
    TH1F *nVtxD = new TH1F("nVtxD","",35,0,40);
    TH1F *nVtxN = new TH1F("nVtxN","",35,0,40);
    for (int i = 1 ; i <40 ; i++){
        nbBefore = chain->GetEntries(Form("nVtx==%i",i));
        nbAfter = chain->GetEntries(Form("nVtx==%i&&",i)+cuts);
        nVtxD->SetBinContent(i+1, nbBefore);
        nVtxN->SetBinContent(i+1, nbAfter);
        nVtx->Divide(nVtxN,nVtxD,1,1);
    }
    nVtx->Write("vtx_"+name);
    delete nVtx;
    delete nVtxD;
    delete nVtxN;
    
}

doThePlot(){
    gStyle->SetOptStat(0);
    chain->Add("TnP_doubleMuons.root");
  
    
    // function of vertex
    doAndTheVertexPlot("GTK","globalOrTrackerMuon==1&&other_globalOrTrackerMuon==1");
    doAndTheVertexPlot("kine","globalOrTrackerMuon==1&&other_globalOrTrackerMuon==1&&(((pt>other_pt)&&(pt>20&&other_pt>10))||((other_pt>pt)&&(pt>10&&other_pt>20)))");
    doAndTheVertexPlot("GT","(((pt>other_pt)&&(pt>20&&other_pt>10))||((other_pt>pt)&&(pt>10&&other_pt>20)))&&globalOrTrackerMuonTight==1&&other_globalOrTrackerMuonTight==1");
    doAndTheVertexPlot("PF","(((pt>other_pt)&&(pt>20&&other_pt>10))||((other_pt>pt)&&(pt>10&&other_pt>20)))&&globalOrTrackerMuonTight==1&&PFmuon==1&&other_globalOrTrackerMuonTight==1&&other_PFmuon==1");
    doAndTheVertexPlot("TK","(((pt>other_pt)&&(pt>20&&other_pt>10))||((other_pt>pt)&&(pt>10&&other_pt>20)))&&globalOrTrackerMuonTight==1&&PFmuon==1&&trackCleaning==1&&other_globalOrTrackerMuonTight==1&&other_PFmuon==1&&other_trackCleaning==1");
    doAndTheVertexPlot("IP","(((pt>other_pt)&&(pt>20&&other_pt>10))||((other_pt>pt)&&(pt>10&&other_pt>20)))&&globalOrTrackerMuonTight==1&&PFmuon==1&&trackCleaning==1&&passMuonIPcuts==1&&other_globalOrTrackerMuonTight==1&&other_PFmuon==1&&other_trackCleaning==1&&other_passMuonIPcuts==1");
    doAndTheVertexPlot("ISO","(((pt>other_pt)&&(pt>20&&other_pt>10))||((other_pt>pt)&&(pt>10&&other_pt>20)))&&globalOrTrackerMuonTight==1&&PFmuon==1&&trackCleaning==1&&passMuonIPcuts==1&&passMuonMVA==1&&other_globalOrTrackerMuonTight==1&&other_PFmuon==1&&other_trackCleaning==1&&other_passMuonIPcuts==1&&other_passMuonMVA==1");
  
    
    
 
    myFile->Close();
    
}