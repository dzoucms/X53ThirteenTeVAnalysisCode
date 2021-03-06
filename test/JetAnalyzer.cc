#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include <vector>
#include "TLorentzVector.h"
#include "TChain.h"
#include "TDirectory.h"
#include "../interface/TreeReader.h"
#include <stdio.h>
#include "TGraphAsymmErrors.h"

void DrawGenJetHists(TFile* outFile, TTree* t, TreeReader* tr){

  //for safety change to top directory
  outFile->cd();
  TDirectory *genJetDir = outFile->mkdir("GenJets");
  genJetDir->cd();

  TH1F* GenJetPt = new TH1F("GenJetPt","Gen Jet p_{T}",100,0,1000);
  TH1F* GenJetMaxPt = new TH1F("GenJetMaxPt","Leading Gen Jet p_{T}",100,0,1000);
  TH1F* GenJetPenPt = new TH1F("GenJetPenPt","subLeading Gen Jet p_{T}",100,0,1000);

  int nEntries = t->GetEntries();

  //event loop
  for(int ient = 0; ient < nEntries; ient++){
    tr->GetEntry(ient);

    float maxgenjetpt=0;
    for(unsigned int i=0; i <tr->genJets.size(); i ++){
      if(tr->genJets.at(i)->eta>2.5)continue;
      GenJetPt->Fill(tr->genJets.at(i)->pt);
      if(tr->genJets.at(i)->pt > maxgenjetpt){
	maxgenjetpt=tr->genJets.at(i)->pt;
      }
    }

    GenJetMaxPt->Fill(maxgenjetpt);
    float pengenjetpt=0;
    for(unsigned int i=0; i < tr->genJets.size(); i++){
      if(tr->genJets.at(i)->eta > 2.5) continue;
      if(tr->genJets.at(i)->pt > pengenjetpt && tr->genJets.at(i)->pt!=maxgenjetpt) pengenjetpt=tr->genJets.at(i)->pt;
    }

    GenJetPenPt->Fill(pengenjetpt);

  }
  outFile->Write();

}

void DrawAK4JetHists(TFile* outFile, TTree* t, TreeReader* tr){

  //for safety change to top directory
  outFile->cd();
  TDirectory *ak4jetDir = outFile->mkdir("AK4jets");
  ak4jetDir->cd();

  TH1F* AK4JetPt = new TH1F("AK4JetPt","AK4 Jet p_{T}",100,0,1000);
  TH1F* AK4JetMaxPt = new TH1F("AK4JetMaxPt","Leading AK4 Jet p_{T}",100,0,1000);
  TH1F* AK4JetPenPt = new TH1F("AK4JetPenPt","subLeading AK4 Jet p_{T}",100,0,1000);

  int nEntries = t->GetEntries();

  //event loop
  for(int ient = 0; ient < nEntries; ient++){
    tr->GetEntry(ient);

    float maxak4jetpt=0;
    for(unsigned int i=0; i <tr->allAK4Jets.size(); i ++){
      if(tr->allAK4Jets.at(i)->eta > 2.5) continue;
      AK4JetPt->Fill(tr->allAK4Jets.at(i)->pt);
      if(tr->allAK4Jets.at(i)->pt > maxak4jetpt){
	maxak4jetpt=tr->allAK4Jets.at(i)->pt;
      }
    }

    AK4JetMaxPt->Fill(maxak4jetpt);
    float penak4jetpt=0;
    for(unsigned int i=0; i < tr->allAK4Jets.size(); i++){
      if(tr->allAK4Jets.at(i)->eta>2.5)continue;
      if(tr->allAK4Jets.at(i)->pt > penak4jetpt && tr->allAK4Jets.at(i)->pt!=maxak4jetpt) penak4jetpt=tr->allAK4Jets.at(i)->pt;
    }

    AK4JetPenPt->Fill(penak4jetpt);
  }

  outFile->Write();
}

void MakeJetResponseHist(TFile* outFile, TTree* t, TreeReader* tr){

  //for safety change to top directory
  outFile->cd();
  TDirectory *jetResponseDir = outFile->mkdir("jetResponse");
  jetResponseDir->cd();

  TH1F* JetNumHist = new TH1F("JetNumHist","p_{T} of Gen Jets Matched to RECO AK4 Jets",100,0,1000);
  TH1F* JetDenHist = new TH1F("JetDenHist","p_{T} of RECO AK4 Jets Matched to Gen Jets",100,0,1000);

  std::vector<TJet*> matchedGenJets;
  std::vector<TJet*> matchedAK4Jets;
  
  int nEntries = t->GetEntries();
  
  //event loop
  for(int ient = 0; ient < nEntries; ient++){
    if(ient % 1000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;
    //go through reco jets
    for(unsigned int i=0;i<tr->allAK4Jets.size();i++){
      TJet* ijet = tr->allAK4Jets.at(i);

      //go through genjets tofind match
      float dR=100;
      for(unsigned int j=0; j<tr->genJets.size();j++){

	TJet* jjet = tr->genJets.at(j);
	float dRtemp=pow( pow( ijet->eta - jjet->eta, 2) + pow(ijet->phi - jjet->phi,2), 0.5);
	if(dRtemp < dR) dR = dRtemp;
	delete jjet;
      }

      //if find a match, save the jets
      if(dR<0.2){
	matchedAK4Jets.push_back(ijet);
	//now find genjet again to save
	for(unsigned int j=0; j<tr->genJets.size();j++){
	  TJet* jjet = tr->genJets.at(j);
	  float dRtemp=pow( pow( ijet->eta - jjet->eta, 2) + pow(ijet->phi - jjet->phi,2), 0.5);
	  if(dRtemp==dR) matchedGenJets.push_back(jjet);
	  delete jjet;
	}
	std::cout<<"working on jet "<<i<<"out of "<<tr->allAK4Jets.size()<<std::endl;
      }//end if find matched jet    
    }

    //now that we have the jets, loop over them
    for(unsigned int i =0; i <matchedGenJets.size(); i ++){
      JetNumHist->Fill(matchedGenJets.at(i)->pt);
      JetDenHist->Fill(matchedAK4Jets.at(i)->pt);
    }

  }//end event loop


  outFile->Write();
}
