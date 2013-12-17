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
    TH1F *nVtx = new TH1F("nVtx","",35,0,35);
    nVtx->Sumw2();
    TH1F *nVtxD = new TH1F("nVtxD","",35,0,35);
    TH1F *nVtxN = new TH1F("nVtxN","",35,0,35);
    for (int i = 1 ; i <35 ; i++){
        nbBefore = chain->GetEntries(Form("nVtx==%i",i));
        nbAfter = chain->GetEntries(Form("(pt>28)&&nVtx==%i&&",i)+cuts);
        nVtxD->SetBinContent(i+1, nbBefore);
        nVtxN->SetBinContent(i+1, nbAfter);
        nVtx->Divide(nVtxN,nVtxD,1,1);
    }
    nVtx->Write("vtx_"+name);
    delete nVtx;
    delete nVtxD;
    delete nVtxN;
    
}

doAndThePtPlot(TString name, TString cuts){
    
    int nbBefore, nbAfter;
    TH1F *nVtx = new TH1F("nVtx","",20,20,40);
    nVtx->Sumw2();
    TH1F *nVtxD = new TH1F("nVtxD","",20,20,40);
    TH1F *nVtxN = new TH1F("nVtxN","",20,20,40);
    int ite=0;
    for (int i = 20 ; i <40 ; i++){
        nbBefore = chain->GetEntries(Form("pt>%i&&pt<%i",i,i+1));
        nbAfter = chain->GetEntries(Form("pt>%i&&pt<%i&&",i,i+1)+cuts);
        nVtxD->SetBinContent(ite+1, nbBefore);
        nVtxN->SetBinContent(ite+1, nbAfter);
        nVtx->Divide(nVtxN,nVtxD,1,1);
        ite++;
    }
    nVtx->Write("pt_"+name);
    delete nVtx;
    delete nVtxD;
    delete nVtxN;
    
}

doThePlot(){
    gStyle->SetOptStat(0);
    chain->Add("TnP_singleElectron.root");
  
    //pt plot or trigger
    //doAndSaveThePlot("FO","passFO==1&&other_passFO==1");
   /* doAndSaveThePlot("FO_ID","passLooseID==1&&tag_passLooseID==1");
    doAndSaveThePlot("FO_ID_IP","passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1");
    doAndSaveThePlot("FO_ID_IP_ISO","passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1&&passLooseISO==1&&tag_passLooseISO==1");
   
    
    //pt plots for path with global muon 
    doAndSaveThePlot("FOglob","(HLT_Mu17_Mu8_DZCut==1||tag_HLT_Mu17_Mu8_DZCut==1)&&passLoose==1&&tag_passLoose==1");
    doAndSaveThePlot("FOglob_ID","(HLT_Mu17_Mu8_DZCut==1||tag_HLT_Mu17_Mu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1");
    doAndSaveThePlot("FOglob_ID_IP","(HLT_Mu17_Mu8_DZCut==1||tag_HLT_Mu17_Mu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1");
    doAndSaveThePlot("FOglob_ID_IP_ISO","(HLT_Mu17_Mu8_DZCut==1||tag_HLT_Mu17_Mu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1&&passLooseISO==1&&tag_passLooseISO==1");
    
     pt plots for path with tracker muon
    doAndSaveThePlot("FOtk","(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&passLoose==1&&tag_passLoose==1");
    doAndSaveThePlot("FOtk_ID","(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1");
    doAndSaveThePlot("FOtk_ID_IP","(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1");
    doAndSaveThePlot("FOtk_ID_IP_ISO","(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1&&passLooseISO==1&&tag_passLooseISO==1");
    */
    

    //eta plot or trigger
    //doAndSaveThePlotEta("FO","passFO==1&&other_passFO==1");
    //doAndSaveThePlotEta("FO","globalOrTrackerMuon==1&&other_globalOrTrackerMuon==1");
    /*doAndSaveThePlotEta("FO_ID","passLooseID==1&&tag_passLooseID==1");
    doAndSaveThePlotEta("FO_ID_IP","passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1");
    doAndSaveThePlotEta("FO_ID_IP_ISO","passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1&&passLooseISO==1&&tag_passLooseISO==1");
    
    
    //eta plots for path with global muon
    doAndSaveThePlotEta("FOglob","(HLT_Mu17_Mu8_DZCut==1||tag_HLT_Mu17_Mu8_DZCut==1)&&passLoose==1&&tag_passLoose==1");
    doAndSaveThePlotEta("FOglob_ID","(HLT_Mu17_Mu8_DZCut==1||tag_HLT_Mu17_Mu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1");
    doAndSaveThePlotEta("FOglob_ID_IP","(HLT_Mu17_Mu8_DZCut==1||tag_HLT_Mu17_Mu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1");
    doAndSaveThePlotEta("FOglob_ID_IP_ISO","(HLT_Mu17_Mu8_DZCut==1||tag_HLT_Mu17_Mu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1&&passLooseISO==1&&tag_passLooseISO==1");
    
    //eta plots for path with tracker muon
    doAndSaveThePlotEta("FOtk","(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&passLoose==1&&tag_passLoose==1");
    doAndSaveThePlotEta("FOtk_ID","(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1");
    doAndSaveThePlotEta("FOtk_ID_IP","(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1");
    doAndSaveThePlotEta("FOtk_ID_IP_ISO","(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1&&passLooseISO==1&&tag_passLooseISO==1");
    */
    
    


    
    // function of vertex
    doAndTheVertexPlot("kine","1");
    doAndTheVertexPlot("ID","passPre==1");
    doAndTheVertexPlot("IP","passPre==1&&passIP==1");
    doAndTheVertexPlot("Convs","passPre==1&&passIP==1&&passConvs==1");
  
    // function of pt
    doAndThePtPlot("kine","1");
    doAndThePtPlot("ID","passPre==1");
    doAndThePtPlot("IP","passPre==1&&passIP==1");
    doAndThePtPlot("Convs","passPre==1&&passIP==1&&passConvs==1");
    
    
    //  doAndTheVertexPlot("FO_ID_IP","passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1");
  //  doAndTheVertexPlot("FO_ID_IP_ISO","passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1&&passLooseISO==1&&tag_passLooseISO==1");
  
    
   /* doAndTheVertexPlot("FOglob","(HLT_Mu17_Mu8_DZCut==1||tag_HLT_Mu17_Mu8_DZCut==1)&&passLoose==1&&tag_passLoose==1");
    doAndTheVertexPlot("FOglob_ID","(HLT_Mu17_Mu8_DZCut==1||tag_HLT_Mu17_Mu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1");
    doAndTheVertexPlot("FOglob_ID_IP","(HLT_Mu17_Mu8_DZCut==1||tag_HLT_Mu17_Mu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1");
    doAndTheVertexPlot("FOglob_ID_IP_ISO","(HLT_Mu17_Mu8_DZCut==1||tag_HLT_Mu17_Mu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1&&passLooseISO==1&&tag_passLooseISO==1");
    
    doAndTheVertexPlot("FOtk","(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&passLoose==1&&tag_passLoose==1");
    doAndTheVertexPlot("FOtk_ID","(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1");
    doAndTheVertexPlot("FOtk_ID_IP","(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1");
    doAndTheVertexPlot("FOtk_ID_IP_ISO","(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&(HLT_Mu17_TkMu8_DZCut==1||tag_HLT_Mu17_TkMu8_DZCut==1)&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1&&passLooseISO==1&&tag_passLooseISO==1");
    
    
    //different for leg
    doAndTheVertexPlot("legGlob_ID","HLT_Mu17_Mu8_Mu17Leg==1&&tag_HLT_Mu17_Mu8_Mu8Leg==1&&passLooseID==1");
    doAndTheVertexPlot("legGlob_IDtag","HLT_Mu17_Mu8_Mu17Leg==1&&tag_HLT_Mu17_Mu8_Mu8Leg==1&&passLooseID==1&&tag_passLooseID==1");
    doAndTheVertexPlot("legGlob_ID_IP","HLT_Mu17_Mu8_Mu17Leg==1&&tag_HLT_Mu17_Mu8_Mu8Leg==1&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1");
    doAndTheVertexPlot("legGlob_ID_IPtag","HLT_Mu17_Mu8_Mu17Leg==1&&tag_HLT_Mu17_Mu8_Mu8Leg==1&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1");
    doAndTheVertexPlot("legGlob_ID_IP_ISO","HLT_Mu17_Mu8_Mu17Leg==1&&tag_HLT_Mu17_Mu8_Mu8Leg==1&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1&&passLooseISO==1");
    doAndTheVertexPlot("legGlob_ID_IP_ISOtag","HLT_Mu17_Mu8_Mu17Leg==1&&tag_HLT_Mu17_Mu8_Mu8Leg==1&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1&&passLooseISO==1&&tag_passLooseISO==1");

    doAndTheVertexPlot("legtk_ID","HLT_Mu17_TkMu8_Mu17Leg==1&&tag_HLT_Mu17_TkMu8_Mu8Leg==1&&passLooseID==1");
    doAndTheVertexPlot("legtk_IDtag","HLT_Mu17_TkMu8_Mu17Leg==1&&tag_HLT_Mu17_TkMu8_Mu8Leg==1&&passLooseID==1&&tag_passLooseID==1");
    doAndTheVertexPlot("legtk_ID_IP","HLT_Mu17_TkMu8_Mu17Leg==1&&tag_HLT_Mu17_TkMu8_Mu8Leg==1&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1");
    doAndTheVertexPlot("legtk_ID_IPtag","HLT_Mu17_TkMu8_Mu17Leg==1&&tag_HLT_Mu17_TkMu8_Mu8Leg==1&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1");
    doAndTheVertexPlot("legtk_ID_IP_ISO","HLT_Mu17_TkMu8_Mu17Leg==1&&tag_HLT_Mu17_TkMu8_Mu8Leg==1&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1&&passLooseISO==1");
    doAndTheVertexPlot("legtk_ID_IP_ISOtag","HLT_Mu17_TkMu8_Mu17Leg==1&&tag_HLT_Mu17_TkMu8_Mu8Leg==1&&passLooseID==1&&tag_passLooseID==1&&passLooseIP==1&&tag_passLooseIP==1&&passLooseISO==1&&tag_passLooseISO==1");
    */


    myFile->Close();
    
}