///////////////////////////////////////////////////////////////
//   Analyzer for the Fake Rate Studies within HWW group               
//
//         AUTHOR:    Santiago Folgueras             
//////////////////////////////////////////////////////////////
//
#include "TriggerSingleElectron.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
//#include "GlobalVariables.h"
//#include "MuonEffectiveArea.h"

#if !defined(__CINT__)
ClassImp(TriggerSingleElectron);
#endif

#define DEBUG
using namespace std;

TriggerSingleElectron::TriggerSingleElectron(TTree* tree):
  CMSAnalysisSelectorMiniTrees(tree)  {} 


void TriggerSingleElectron::Initialise() {
	cout << "initialisation ...  " << endl;
    
    GetInputParameters()->TheNamedBool("isMC", isMC);
    GetInputParameters()->TheNamedBool("doDiElectron", doDiElectron);
    GetInputParameters()->TheNamedBool("doDiMuons", doDiMuons);
    GetInputParameters()->TheNamedBool("doEgMu", doEgMu);
    GetInputParameters()->TheNamedBool("doSingleElectron", doSingleElectron);
    GetInputParameters()->TheNamedBool("doSingleMuon", doSingleMuon);
    signal = GetInputParameters()->TheNamedString("Signal");
    GetInputParameters()->TheNamedBool("doMuons", doMuons);
    cout << "le MC est a " << isMC << endl;
    
    nbEvent = 0;
    nbEventPassing = 0;
    nbEventQuiPassent = 0;
    nbEventQuiPassentTrig = 0;
    
    hPt = CreateH1F("hPt", "", 100,0,100);
    
    diLeptonTree = CreateTree("diLeptonTree","the dilepton tree");
    diLeptonTree->Branch("nVtx",          &nVtx,          "nVtx/I");
    diLeptonTree->Branch("isRECO",          &isRECO,          "isRECO/I");
    
    diLeptonTree->Branch("pt",          &pt,          "pt/F");
    diLeptonTree->Branch("absEta",          &absEta,          "absEta/F");
    diLeptonTree->Branch("passFO",          &passFO,          "passFO/I");
    diLeptonTree->Branch("passPre",          &passPre,          "passPre/I");
    diLeptonTree->Branch("passIP",          &passIP,          "passIP/I");
    diLeptonTree->Branch("passConvs",          &passConvs,          "passConvs/I");
    diLeptonTree->Branch("passTrig0",          &passTrig0,          "passTrig0/I");
    diLeptonTree->Branch("passTrig1",          &passTrig1,         "passTrig1/I");
    diLeptonTree->Branch("passTrig0bis",          &passTrig0bis,          "passTrig0bis/I");
    diLeptonTree->Branch("passTrig1bis",          &passTrig1bis,         "passTrig1bis/I");
    diLeptonTree->Branch("passDiMuonGlob",          &passDiMuonGlob,         "passDiMuonGlob/I");
    diLeptonTree->Branch("passEtCut",          &passEtCut,         "passEtCut/I");
    diLeptonTree->Branch("passJetPt",          &passJetPt,         "passJetPt/I");
    diLeptonTree->Branch("passDeltaPhi",          &passDeltaPhi,         "passDeltaPhi/I");
    diLeptonTree->Branch("passDiMuonTk",          &passDiMuonTk,         "passDiMuonTk/I");
    diLeptonTree->Branch("passTrackerIso",          &passTrackerIso,         "passTrackerIso/I");
    diLeptonTree->Branch("passECALIso",          &passECALIso,         "passECALIso/I");
    diLeptonTree->Branch("passHCALIso",          &passHCALIso,         "passHCALIso/I");
    diLeptonTree->Branch("passSigIeta",          &passSigIeta,         "passSigIeta/I");
    diLeptonTree->Branch("passDeltaEtaSC",          &passDeltaEtaSC,         "passDeltaEtaSC/I");
    diLeptonTree->Branch("passdeltaPhiSC",          &passdeltaPhiSC,         "passdeltaPhiSC/I");
    diLeptonTree->Branch("passHoE",          &passHoE,         "passHoE/I");
    diLeptonTree->Branch("passConversionVtxFit",          &passConversionVtxFit,         "passConversionVtxFit/I");
    diLeptonTree->Branch("passMissHit",          &passMissHit,         "passMissHit/I");
    diLeptonTree->Branch("passd0",          &passd0,         "passd0/I");
    diLeptonTree->Branch("passdZ",          &passdZ,         "passdZ/I");
    
    diLeptonTree->Branch("other_passTrackerIso",          &other_passTrackerIso,         "other_passTrackerIso/I");
    diLeptonTree->Branch("other_passECALIso",          &other_passECALIso,         "other_passECALIso/I");
    diLeptonTree->Branch("other_passHCALIso",          &other_passHCALIso,         "other_passHCALIso/I");
    diLeptonTree->Branch("other_passSigIeta",          &other_passSigIeta,         "other_passSigIeta/I");
    diLeptonTree->Branch("other_passDeltaEtaSC",          &other_passDeltaEtaSC,         "other_passDeltaEtaSC/I");
    diLeptonTree->Branch("other_passdeltaPhiSC",          &other_passdeltaPhiSC,         "other_passdeltaPhiSC/I");
    diLeptonTree->Branch("other_passHoE",          &other_passHoE,         "other_passHoE/I");
    diLeptonTree->Branch("other_passConversionVtxFit",          &other_passConversionVtxFit,         "other_passConversionVtxFit/I");
    diLeptonTree->Branch("other_passMissHit",          &other_passMissHit,         "other_passMissHit/I");
    diLeptonTree->Branch("other_passd0",          &other_passd0,         "other_passd0/I");
    diLeptonTree->Branch("other_passdZ",          &other_passdZ,         "other_passdZ/I");
    
    
    
    diLeptonTree->Branch("other_pt",          &other_pt,          "other_pt/F");
    diLeptonTree->Branch("other_absEta",          &other_absEta,          "other_absEta/F");
    diLeptonTree->Branch("other_passFO",          &other_passFO,          "other_passFO/I");
    diLeptonTree->Branch("other_passPre",          &other_passPre,          "other_passPre/I");
    diLeptonTree->Branch("other_passIP",          &other_passIP,          "other_passIP/I");
    diLeptonTree->Branch("other_passConvs",          &other_passConvs,          "other_passConvs/I");
    diLeptonTree->Branch("other_passTrig0bis",          &other_passTrig0bis,          "other_passTrig0bis/I");
    diLeptonTree->Branch("other_passTrig1bis",          &other_passTrig1bis,         "other_passTrig1bis/I");
    diLeptonTree->Branch("globalOrTrackerMuon",          &globalOrTrackerMuon,          "globalOrTrackerMuon/I");
    diLeptonTree->Branch("globalOrTrackerMuonTight",          &globalOrTrackerMuonTight,          "globalOrTrackerMuonTight/I");
    diLeptonTree->Branch("PFmuon",          &PFmuon,          "PFmuon/I");
    diLeptonTree->Branch("trackCleaning",          &trackCleaning,          "trackCleaning/I");
    diLeptonTree->Branch("passMuonIPcuts",          &passMuonIPcuts,          "passMuonIPcuts/I");
    diLeptonTree->Branch("passMuonMVA",          &passMuonMVA,          "passMuonMVA/I");
    diLeptonTree->Branch("other_globalOrTrackerMuon",          &other_globalOrTrackerMuon,          "other_globalOrTrackerMuon/I");
    diLeptonTree->Branch("other_globalOrTrackerMuonTight",          &other_globalOrTrackerMuonTight,          "other_globalOrTrackerMuonTight/I");
    diLeptonTree->Branch("other_PFmuon",          &other_PFmuon,          "other_PFmuon/I");
    diLeptonTree->Branch("other_trackCleaning",          &other_trackCleaning,          "other_trackCleaning/I");
    diLeptonTree->Branch("other_passMuonIPcuts",          &other_passMuonIPcuts,          "other_passMuonIPcuts/I");
    diLeptonTree->Branch("other_passMuonMVA",          &other_passMuonMVA,          "other_passMuonMVA/I");
    diLeptonTree->Branch("passMu8Ele17",          &passMu8Ele17,          "passMu8Ele17/I");
    diLeptonTree->Branch("passEle8Mu17",          &passEle8Mu17,          "passEle8Mu17/I");
    

    triggerTree = CreateTree("triggerTree","the trigger tree");
    triggerTree->Branch("pt",          &pt,          "pt/F");
    triggerTree->Branch("absEta",          &absEta,          "absEta/F");
    triggerTree->Branch("trg_relatTrkIso",          &trg_relatTrkIso,          "trg_relatTrkIso/F");
    triggerTree->Branch("trg_relatEcalIso",          &trg_relatEcalIso,          "trg_relatEcalIso/F");
    triggerTree->Branch("trg_relatHcalIso",          &trg_relatHcalIso,          "trg_relatHcalIso/F");
    triggerTree->Branch("trg_SigIeta",          &trg_SigIeta,          "trg_SigIeta/F");
    triggerTree->Branch("trg_deltaEtaSC",          &trg_deltaEtaSC,          "trg_deltaEtaSC/F");
    triggerTree->Branch("trg_deltaPhiSC",          &trg_deltaPhiSC,          "trg_deltaPhiSC/F");
    triggerTree->Branch("trg_HOE",          &trg_HOE,          "trg_HOE/F");
    triggerTree->Branch("trg_passEle27",          &trg_passEle27,          "trg_passEle27/I");
    triggerTree->Branch("trg_ele17Leg",          &trg_ele17Leg,          "trg_ele17Leg/I");
    triggerTree->Branch("trg_ele8Leg",          &trg_ele8Leg,          "trg_ele8Leg/I");
    triggerTree->Branch("trg_passTrig",          &trg_passTrig,          "trg_passTrig/I");
    triggerTree->Branch("trg_mass",          &trg_mass,          "trg_mass/F");
    

}

void TriggerSingleElectron::InsideLoop() {
  /*  int nbMuons = T_Muon_Pt->size();
    for (int i = 0 ; i < nbMuons ; i++){
        //cout << "muons Pt=" << T_Muon_Pt->at(i) << endl;
        hPt->Fill(T_Muon_Pt->at(i));
        pt = T_Muon_Pt->at(i);
        diLeptonTree->Fill();
    }*/
    
    TLorentzVector* elecTag;
    TLorentzVector*  elecProb;
    TLorentzVector sumElec;
    float mass;
    
    
    if (doDiElectron){
        if (!(T_Event_HLT_Ele27_WP80==1)) return;
        int nbElec = T_Elec_Pt->size();
        for (int i = 0 ; i < nbElec ; i++){
                if (!(T_Elec_HLT_Elec27_WP80->at(i))) continue;
                fillTheDiLeptonTree(i,0,0);
     
        }
     }
    
}

void TriggerSingleElectron::fillTheDiLeptonTree(int ite, int ite2, int localType){
    nVtx = T_Vertex_z->size();

    pt = T_Elec_Pt->at(ite);
    eta = T_Elec_Eta->at(ite);
    absEta = fabs(eta);
    passFO = T_Elec_isFO->at(ite);
    passPre = passPreCuts(pt, T_Elec_isEB->at(ite), T_Elec_sigmaIetaIeta->at(ite), T_Elec_deltaEtaIn->at(ite), T_Elec_deltaPhiIn->at(ite) ,T_Elec_HtoE->at(ite), T_Elec_dr03EcalSumEt->at(ite), T_Elec_dr03TkSumPt->at(ite), T_Elec_dr03EcalSumEt->at(ite));
    passIP = passIPcuts(T_Elec_d0->at(ite), T_Elec_dZ->at(ite));
    passConvs  = passMissItCons(T_Elec_passConversionVeto->at(ite), T_Elec_nHits->at(ite));
    passTrig0 = T_Elec_HLT_Ele17_Ele8_Ele17Leg->at(ite);
    passTrig1 = T_Elec_HLT_Ele17_Ele8_Ele8Leg->at(ite);
    
    passTrackerIso = (T_Elec_dr03TkSumPt->at(ite)/pt < 0.2);
    passHCALIso = (T_Elec_dr03HcalSumEt->at(ite)/pt < 0.2);
    passECALIso = (T_Elec_isEB->at(ite) ? ((T_Elec_dr03EcalSumEt->at(ite)-1)/pt < 0.2) : (T_Elec_dr03EcalSumEt->at(ite)/pt < 0.2));
    passSigIeta = (T_Elec_isEB->at(ite) ? (T_Elec_sigmaIetaIeta->at(ite)                               < 0.01) : (T_Elec_sigmaIetaIeta->at(ite)                               < 0.03));
    passDeltaEtaSC = (T_Elec_isEB->at(ite) ? (fabs(T_Elec_deltaEtaIn->at(ite))        < 0.007) : (fabs(T_Elec_deltaEtaIn->at(ite))        < 0.009));
    passdeltaPhiSC = (T_Elec_isEB->at(ite) ? (fabs(T_Elec_deltaPhiIn->at(ite))        < 0.15) : (fabs(T_Elec_deltaPhiIn->at(ite))        < 0.10));
    passHoE = (T_Elec_isEB->at(ite) ? (T_Elec_HtoE->at(ite)                            <0.12) : (T_Elec_HtoE->at(ite)                              < 0.10));
    passConversionVtxFit = (T_Elec_passConversionVeto->at(ite) <= 0);
    passMissHit = (T_Elec_nHits->at(ite) == false);
    passd0 =(T_Elec_d0->at(ite) < 0.02);
    passdZ =(T_Elec_dZ->at(ite) < 0.1);
    

    
    diLeptonTree->Fill();
}







bool TriggerSingleElectron::passIPcuts(float d0, float dz)
{
    if (d0 > 0.02)                                  return false;
    if (dz > 0.1)                                   return false;
    return true;
}

bool TriggerSingleElectron::passMissItCons(bool conversion, int nMissHit)
{
    if (nMissHit > 0)      return false;
    if (conversion)           return false;
    return true;
}


bool TriggerSingleElectron::passPreCuts(float myPt, int isEB, float theSigIeta, float deltaEtaSC, float deltaPhiSC,float HOE, float ecalIso, float hcalIso, float trackerIso)
{
    if (trackerIso/myPt > 0.2) return false;
    if (hcalIso/myPt > 0.2) return false;
    
    if (isEB) {
        if (theSigIeta                               > 0.01)  return false;
        if (fabs(deltaEtaSC)        > 0.007) return false;
        if (fabs(deltaPhiSC)        > 0.15)  return false;
        if (HOE                              > 0.12)  return false;
        if ((ecalIso-1)/myPt > 0.2) return false;
        
    } else {
        if (theSigIeta                               > 0.03)  return false;
        if (fabs(deltaEtaSC)        > 0.009) return false;
        if (fabs(deltaPhiSC)        > 0.10)  return false;
        if (HOE                              > 0.10)  return false;
        if (ecalIso/myPt > 0.2) return false;
        
    }
    
    return true;
    
}

void TriggerSingleElectron::Summary() {
  cout << " ---------------------------------------------------" << endl;
  InitialiseParameters();
    cout << "====================================================================================" << endl;
cout << endl;
    cout << "on a " << nbEventPassing << " sur " << nbEvent << endl;
    cout << "le nb total d'event qui passent = " << nbEventQuiPassent << " " << nbEventQuiPassentTrig << " passent le trigger" << endl;
}




