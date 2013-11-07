///////////////////////////////////////////////////////////////
//   Analyzer for the Fake Rate Studies within HWW group               
//
//         AUTHOR:    Santiago Folgueras             
//////////////////////////////////////////////////////////////
//
#include "TriggerMuons.h"
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
ClassImp(TriggerMuons);
#endif

#define DEBUG
using namespace std;

TriggerMuons::TriggerMuons(TTree* tree):
  CMSAnalysisSelectorMiniTrees(tree)  {} 


void TriggerMuons::Initialise() {
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
    diLeptonTree->Branch("global",          &global,          "global/I");
    diLeptonTree->Branch("tracker",          &tracker,          "tracker/I");
    diLeptonTree->Branch("trackChi2",          &trackChi2,          "trackChi2/I");
    diLeptonTree->Branch("nbOfMatches",          &nbOfMatches,          "nbOfMatches/I");
    diLeptonTree->Branch("nbValidMuonHits",          &nbValidMuonHits,          "nbValidMuonHits/I");
    diLeptonTree->Branch("TMlastStation",          &TMlastStation,          "TMlastStation/I");
    diLeptonTree->Branch("trackKink",          &trackKink,          "trackKink/I");
    diLeptonTree->Branch("nbTkLayer",          &nbTkLayer,          "nbTkLayer/I");
    diLeptonTree->Branch("nbValidPixHits",          &nbValidPixHits,          "nbValidPixHits/I");
    diLeptonTree->Branch("trackError",          &trackError,          "trackError/I");
    
    
    
    
    diLeptonTree->Branch("other_globalOrTrackerMuon",          &other_globalOrTrackerMuon,          "other_globalOrTrackerMuon/I");
    diLeptonTree->Branch("other_globalOrTrackerMuonTight",          &other_globalOrTrackerMuonTight,          "other_globalOrTrackerMuonTight/I");
    diLeptonTree->Branch("other_PFmuon",          &other_PFmuon,          "other_PFmuon/I");
    diLeptonTree->Branch("other_trackCleaning",          &other_trackCleaning,          "other_trackCleaning/I");
    diLeptonTree->Branch("other_passMuonIPcuts",          &other_passMuonIPcuts,          "other_passMuonIPcuts/I");
    diLeptonTree->Branch("other_global",          &other_global,          "other_global/I");
    diLeptonTree->Branch("other_tracker",          &other_tracker,          "other_tracker/I");
    diLeptonTree->Branch("other_trackChi2",          &other_trackChi2,          "other_trackChi2/I");
    diLeptonTree->Branch("other_nbOfMatches",          &other_nbOfMatches,          "other_nbOfMatches/I");
    diLeptonTree->Branch("other_nbValidMuonHits",          &other_nbValidMuonHits,          "other_nbValidMuonHits/I");
    diLeptonTree->Branch("other_TMlastStation",          &other_TMlastStation,          "other_TMlastStation/I");
    diLeptonTree->Branch("other_trackKink",          &other_trackKink,          "other_trackKink/I");
    diLeptonTree->Branch("other_nbTkLayer",          &other_nbTkLayer,          "other_nbTkLayer/I");
    diLeptonTree->Branch("other_nbValidPixHits",          &other_nbValidPixHits,          "other_nbValidPixHits/I");
    diLeptonTree->Branch("other_trackError",          &other_trackError,          "other_trackError/I");
    
    
    
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

void TriggerMuons::InsideLoop() {

    float mass;
    
    if (doDiMuons){
        int nbMuons = T_Muon_Pt->size();
        if (!(T_Event_HLT_Mu17_Mu8==1||T_Event_HLT_Mu17_TkMu8==1)) return;
        bool eventFound=false;
        int passingPaire = 0;
        nbEvent++;
         
        for (int i = 0 ; i < nbMuons ; i++){
            for (int j= i+1 ; j < nbMuons ; j++){
                if (!((T_Muon_HLT_Mu17_Mu8_Mu17Leg->at(i)==1&&T_Muon_HLT_Mu17_Mu8_Mu8Leg->at(j)==1)||(T_Muon_HLT_Mu17_Mu8_Mu17Leg->at(j)==1&&T_Muon_HLT_Mu17_Mu8_Mu8Leg->at(i)==1)||(T_Muon_HLT_Mu17_TkMu8_Mu17Leg->at(i)==1&&T_Muon_HLT_Mu17_TkMu8_Mu8Leg->at(j)==1)||(T_Muon_HLT_Mu17_TkMu8_Mu17Leg->at(j)==1&&T_Muon_HLT_Mu17_TkMu8_Mu8Leg->at(i)==1))) continue;
                passingPaire=1;
                fillTheDiLeptonTreeMuon(i,j,1);
                bool mu1pass =  (T_Muon_IsGlobalMuon->at(i)&&(T_Muon_globalTrackChi2->at(i)<10)&&(T_Muon_numberOfMatches->at(i)>1)&&(T_Muon_validMuonHits->at(i)>0)) || (T_Muon_IsTrackerMuon->at(i)&&T_Muon_TMLastStationTight->at(i));
                bool mu2pass =  (T_Muon_IsGlobalMuon->at(j)&&(T_Muon_globalTrackChi2->at(j)<10)&&(T_Muon_numberOfMatches->at(j)>1)&&(T_Muon_validMuonHits->at(j)>0)) || (T_Muon_IsTrackerMuon->at(j)&&T_Muon_TMLastStationTight->at(j));
                if (mu1pass&&mu2pass) eventFound= true;
            }
        }
        if (eventFound) nbEventPassing++;
        if (passingPaire==0) fillTheDiLeptonTreeMuon(0,0,0);
    }

}



void TriggerMuons::fillTheDiLeptonTreeMuon(int ite, int ite2, int localType){
    //cout << "coucou on est dans la loop ! " << endl;
    nVtx = T_Vertex_z->size();
    isRECO = 0;
    if (localType==1){
        isRECO = 1;
        pt = T_Muon_Pt->at(ite);
        eta = T_Muon_Eta->at(ite);
        absEta = fabs(eta);
        passDiMuonGlob = T_Event_HLT_Mu17_Mu8;
        passDiMuonTk = T_Event_HLT_Mu17_TkMu8;
     
     
        globalOrTrackerMuon = T_Muon_IsGlobalMuon->at(ite) || T_Muon_IsTrackerMuon->at(ite);
        globalOrTrackerMuonTight = (T_Muon_IsGlobalMuon->at(ite)&&(T_Muon_globalTrackChi2->at(ite)<10)&&(T_Muon_numberOfMatches->at(ite)>1)&&(T_Muon_validMuonHits->at(ite)>0)) || (T_Muon_IsTrackerMuon->at(ite)&&T_Muon_TMLastStationTight->at(ite));
        PFmuon = T_Muon_IsPFMuon->at(ite);
        trackCleaning = (T_Muon_trkKink->at(ite)<20)&&(T_Muon_trkNbOfTrackerLayers->at(ite)>5)&&(T_Muon_trkValidPixelHits->at(ite)>0)&&(fabs(T_Muon_trkError->at(ite)/pt)<0.1);
        passMuonIPcuts = (fabs(T_Muon_dB->at(ite))<0.2&&fabs(T_Muon_dzPV->at(ite))<0.1);
        //float isolationMVA1=computedMVAisolation(ite);
        passMuonMVA=(T_Muon_isoRingsMVA->at(ite)>-0.6);
        
        global = T_Muon_IsGlobalMuon->at(ite);
        tracker = T_Muon_IsTrackerMuon->at(ite);
        trackChi2 = (T_Muon_globalTrackChi2->at(ite)<10);
        nbOfMatches = (T_Muon_numberOfMatches->at(ite)>1);
        nbValidMuonHits = (T_Muon_validMuonHits->at(ite)>0);
        TMlastStation = (T_Muon_TMLastStationTight->at(ite));
        trackKink =(T_Muon_trkKink->at(ite)<20);
        nbTkLayer =(T_Muon_trkNbOfTrackerLayers->at(ite)>5);
        nbValidPixHits =(T_Muon_trkValidPixelHits->at(ite)>0);
        trackError = (fabs(T_Muon_trkError->at(ite)/pt)<0.1);
        
        
        
        
     
        passTrig0 = T_Muon_HLT_Mu17_Mu8_Mu17Leg->at(ite);
        passTrig1 = T_Muon_HLT_Mu17_Mu8_Mu8Leg->at(ite);
        passTrig0bis = T_Muon_HLT_Mu17_TkMu8_Mu17Leg->at(ite);
        passTrig1bis = T_Muon_HLT_Mu17_TkMu8_Mu8Leg->at(ite);
    
        passEtCut = (T_METPF_ET<20);
        passJetPt = 0;
        float maxJetPt = 0;
        int leadJet=0;
        for (int k = 0 ; k < T_Jet_Eta->size() ; k++){
            float theJetPt = sqrt(pow(T_Jet_Px->at(k),2)+pow(T_Jet_Py->at(k),2));
            if (theJetPt>maxJetPt) {
                maxJetPt = theJetPt;
                leadJet = k;
            }
        }
        float leadJetPt = sqrt(pow(T_Jet_Px->at(leadJet),2)+pow(T_Jet_Py->at(leadJet),2));
        if (leadJetPt>35) passJetPt =1;
        else passJetPt = 0;
        float deltaPhi = acos(cos(T_Jet_Phi->at(leadJet)-T_Muon_Phi->at(ite)));
        passDeltaPhi = (deltaPhi>1);
    
        other_pt = T_Muon_Pt->at(ite2);
        other_eta = T_Muon_Eta->at(ite2);
        other_absEta = fabs(other_eta);
        other_globalOrTrackerMuon = T_Muon_IsGlobalMuon->at(ite2) || T_Muon_IsTrackerMuon->at(ite2);
        other_globalOrTrackerMuonTight = (T_Muon_IsGlobalMuon->at(ite2)&&(T_Muon_globalTrackChi2->at(ite2)<10)&&(T_Muon_numberOfMatches->at(ite2)>1)&&(T_Muon_validMuonHits->at(ite2)>0)) || (T_Muon_IsTrackerMuon->at(ite2)&&T_Muon_TMLastStationTight->at(ite2));
        other_PFmuon = T_Muon_IsPFMuon->at(ite2);
        other_trackCleaning = (T_Muon_trkKink->at(ite2)<20)&&(T_Muon_trkNbOfTrackerLayers->at(ite2)>5)&&(T_Muon_trkValidPixelHits->at(ite2)>0)&&(fabs(T_Muon_trkError->at(ite2)/other_pt)<0.1);
        other_passMuonIPcuts = (fabs(T_Muon_dB->at(ite2))<0.2&&fabs(T_Muon_dzPV->at(ite2))<0.1);
   //  float isolationMVA2= computedMVAisolation(ite2);
        other_passMuonMVA=(T_Muon_isoRingsMVA->at(ite2)>-0.6);
        
        
        other_global = T_Muon_IsGlobalMuon->at(ite2);
        other_tracker = T_Muon_IsTrackerMuon->at(ite2);
        other_trackChi2 = (T_Muon_globalTrackChi2->at(ite2)<10);
        other_nbOfMatches = (T_Muon_numberOfMatches->at(ite2)>1);
        other_nbValidMuonHits = (T_Muon_validMuonHits->at(ite2)>0);
        other_TMlastStation = (T_Muon_TMLastStationTight->at(ite2));
        other_trackKink =(T_Muon_trkKink->at(ite2)<20);
        other_nbTkLayer =(T_Muon_trkNbOfTrackerLayers->at(ite2)>5);
        other_nbValidPixHits =(T_Muon_trkValidPixelHits->at(ite2)>0);
        other_trackError = (fabs(T_Muon_trkError->at(ite2)/other_pt)<0.1);
        
        other_passTrig0 = T_Muon_HLT_Mu17_Mu8_Mu17Leg->at(ite2);
        other_passTrig1 = T_Muon_HLT_Mu17_Mu8_Mu8Leg->at(ite2);
        other_passTrig0bis = T_Muon_HLT_Mu17_TkMu8_Mu17Leg->at(ite2);
        other_passTrig1bis = T_Muon_HLT_Mu17_TkMu8_Mu8Leg->at(ite2);
    /*  cout << "pt=" << pt << " autre pt=" << other_pt << endl;
     cout << "leg17=" << passTrig0 << " leg8=" << passTrig1 << endl;
     cout << "autre leg17=" << other_passTrig0 << " autre leg8=" << other_passTrig1 << endl;
     
     cout << "leg17=" << passTrig0bis << "tk  leg8=" << passTrig1bis << endl;
     cout << "autre leg17=" << other_passTrig0bis << " autre tk leg8=" << other_passTrig1bis << endl;*/
    
    }
    
    diLeptonTree->Fill();
}



bool TriggerMuons::passPreCuts(float myPt, int isEB, float theSigIeta, float deltaEtaSC, float deltaPhiSC,float HOE, float ecalIso, float hcalIso, float trackerIso)
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



bool TriggerMuons::passIPcuts(float d0, float dz)
{
    if (d0 > 0.02)                                  return false;
    if (dz > 0.1)                                   return false;
    return true;
}

bool TriggerMuons::passMissItCons(bool conversion, int nMissHit)
{
    if (nMissHit > 0)      return false;
    if (conversion)           return false;
    return true;
}


void TriggerMuons::Summary() {
  cout << " ---------------------------------------------------" << endl;
  InitialiseParameters();
    cout << "====================================================================================" << endl;
cout << endl;
    cout << "on a " << nbEventPassing << " sur " << nbEvent << endl;
    cout << "le nb total d'event qui passent = " << nbEventQuiPassent << " " << nbEventQuiPassentTrig << " passent le trigger" << endl;
}




