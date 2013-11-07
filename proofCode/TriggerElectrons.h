#ifndef TRIGGERELECTRONS_H
#define TRIGGERELECTRONS_H 1

#include "packages/TCounterUI/TCounterUI.h"
#include "packages/CMSAnalysisSelectorMiniTrees/CMSAnalysisSelectorMiniTrees.h"
//#include "packages/MuonMVA/MuonMVAEstimator.h"
//#include "packages/MuonMVA/MuonMVAEstimator.cc"


#include "TH1F.h"
#include "TH2F.h"
#include <vector>
#include "TString.h"
#include "TLorentzVector.h"
#include "TVector3.h"
//#include "GlobalVariables.h"

class TLorentzVector;

class TriggerElectrons: public CMSAnalysisSelectorMiniTrees {
 public:
  TriggerElectrons(TTree *tree=0);
  virtual ~TriggerElectrons() {}
  
  public:

  protected:
    // inside functions
    virtual void Initialise();
    virtual void InsideLoop();
    virtual void Summary();
    
    virtual void fillTheDiLeptonTree(int, int, int);
    virtual bool  passIPcuts(float, float);
    virtual  bool passMissItCons(bool , int );
    virtual bool passPreCuts(float , int , float , float , float ,float , float , float , float );

    
    

    
    // parameters
    bool isMC;
    bool doMuons;
    bool doDiElectron;
    bool doDiMuons;
    bool doEgMu;
    bool doSingleElectron;
    bool doSingleMuon;
    
    int nbEvent;
    int nbEventPassing;
    int nbEventQuiPassent;
    int nbEventQuiPassentTrig;
    TString signal;
    
    
    TTree *diLeptonTree;
    //tree vars
    /*int runNumber;
    int lumiSec;
    float mass;*/
    float pt;
    float eta;
    float absEta;
    int nVtx;
    int isRECO;
    int passEtCut;
    int passJetPt;
    int passDeltaPhi;
    int passTight;
    int passLoose;
    int passFO;
    int passPre;
    int passIP;
    int passConvs;
    int passTrig0;
    int passTrig1;
    int passTrig0bis;
    int passTrig1bis;
    
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
    int other_passFO;
    int other_passPre;
    int other_passIP;
    int other_passConvs;
    int other_passTrig0;
    int other_passTrig1;
    int other_passTrig0bis;
    int other_passTrig1bis;
    
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
    
    // muon cuts
    int passDiMuonGlob;
    int passDiMuonTk;
    
    
    int globalOrTrackerMuon;
    int globalOrTrackerMuonTight;
    int PFmuon;
    int trackCleaning;
    int passMuonIPcuts;
    int passMuonMVA;
    
    int other_globalOrTrackerMuon;
    int other_globalOrTrackerMuonTight;
    int other_PFmuon;
    int other_trackCleaning;
    int other_passMuonIPcuts;
    int other_passMuonMVA;
    
    
    int passMu8Ele17;
    int passEle8Mu17;
    
    
    //tree for trigger studies
    TTree *triggerTree;
    float trg_relatTrkIso;
    float trg_relatEcalIso;
    float trg_relatHcalIso;
    float trg_SigIeta;
    float trg_deltaEtaSC;
    float trg_deltaPhiSC;
    float trg_HOE;
    int trg_passTrig;
    int trg_passEle27;
    int trg_ele17Leg;
    int trg_ele8Leg;
    float trg_mass;
    

    
    //histos
    TH1F *hPt;

  ClassDef(TriggerElectrons,0);
};
#endif

