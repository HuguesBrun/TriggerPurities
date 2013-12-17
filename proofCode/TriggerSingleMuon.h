#ifndef TRIGGERSINGLEMUON_H
#define TRIGGERSINGLEMUON_H 1

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

class TriggerSingleMuon: public CMSAnalysisSelectorMiniTrees {
 public:
  TriggerSingleMuon(TTree *tree=0);
  virtual ~TriggerSingleMuon() {}
  
  public:

  protected:
    // inside functions
    virtual void Initialise();
    virtual void InsideLoop();
    virtual void Summary();
    
    virtual void fillTheDiLeptonTreeMuon(int , int , int );
    virtual bool  passPreCuts(float, int, float, float, float,float, float, float,float);
    virtual bool  passIPcuts(float, float);
    virtual  bool passMissItCons(bool , int );

    
    

    
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
    
    // muon cuts
    int passDiMuonGlob;
    int passDiMuonTk;
    
    
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

  ClassDef(TriggerSingleMuon,0);
};
#endif

