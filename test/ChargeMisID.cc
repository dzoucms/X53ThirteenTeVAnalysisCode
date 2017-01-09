#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TDirectory.h"
#include "TH1.h"
#include <vector>
#include "TLorentzVector.h"
#include "TChain.h"
#include "../interface/TreeReader.h"
#include <stdio.h>
#include <assert.h>
#include <map>
#include <string>
#include <sstream> 
#include "../plugins/Macros.cc"

//helper functions
std::vector<TLepton*> makeLeptons(std::vector<TElectron*> electrons, bool mc, bool FiftyNs, std::string ID);

//A script to get the prompt rate for electrons and muons. Usage is ./ChargeMisID.o <Data,MC> <El,Mu> 

int main(int argc, char* argv[]){

  if(argc!=4){
    std::cout<<"Need to specify whether running on Data or MC and whether 25 or 50ns as well as the ID. The four possible ways of running are\n"
	     <<"./ChargeMisID.o Data 50ns ID \n"
	     <<"./ChargeMisID.o Data 25ns ID \n"
	     <<"./ChargeMisID.o MC 50ns ID \n"
	     <<"./ChargeMisID.o MC 25ns ID \n";
    return 0;
  }

  std::string argv1 = argv[1];
  std::string argv2 = argv[2];
  std::string ID = argv[3];

  bool correctusage=false;
  if(argc==4 && (argv1.find("Data")!=std::string::npos || argv1.find("MC")!=std::string::npos || true )  && (argv2.find("25ns")!=std::string::npos || argv2.find("2016")!=std::string::npos) ) correctusage=true; //add or true to argv1 to skip argv1 check for using now - dzou
  if(!correctusage){
    std::cout<<"Need to specify whether running on Data or MC and 25 or 50ns. The four possible ways of running are\n"
	     <<"./ChargeMisID.o Data 50ns ID \n"
	     <<"./ChargeMisID.o Data 25ns ID \n"
	     <<"./ChargeMisID.o MC 50ns ID \n"
	     <<"./ChargeMisID.o MC 25ns ID \n";
    return 0;
  }

  //get filename based on Data/MC
  std::string filename;
  bool data;
  bool FiftyNS;

  std::string eosarea="root://cmseos.fnal.gov//store/user/clint/Spring16/25ns/Dec14/ljmet_trees/";

  if(argv1=="Data" && argv2=="50ns") {filename="root://cmseos.fnal.gov//store/user/clint/Run2015B/ljmet_trees/ljmet_Data_ElEl.root"; data=true; FiftyNS=true;}
  else  if(argv1=="Data"){
     data=true; FiftyNS=false;
    if(argv2=="2016B") filename="root://cmseos.fnal.gov//store/user/clint/Run2016/Nov16/ljmet_trees/ljmet_Data_DoubleEG-Run2016B-23Sep2016-v3.root";
    else if(argv2=="2016C") filename="root://cmseos.fnal.gov//store/user/clint/Run2016/Nov16/ljmet_trees/ljmet_Data_DoubleEG-Run2016C-23Sep2016-v1.root";
    else if(argv2=="2016D") filename="root://cmseos.fnal.gov//store/user/clint/Run2016/Nov16/ljmet_trees/ljmet_Data_DoubleEG-Run2016D-23Sep2016-v1.root";
    else if(argv2=="2016E") filename="root://cmseos.fnal.gov//store/user/clint/Run2016/Nov16/ljmet_trees/ljmet_Data_DoubleEG-Run2016E-23Sep2016-v1.root";
    else if(argv2=="2016F") filename="root://cmseos.fnal.gov//store/user/clint/Run2016/Nov16/ljmet_trees/ljmet_Data_DoubleEG-Run2016F-23Sep2016-v1.root";
    else if(argv2=="2016G") filename="root://cmseos.fnal.gov//store/user/clint/Run2016/Nov16/ljmet_trees/ljmet_Data_DoubleEG-Run2016G-23Sep2016-v1.root";
    else if(argv2=="2016H2") filename="root://cmseos.fnal.gov//store/user/clint/Run2016/Nov16/ljmet_trees/ljmet_Data_DoubleEG-Run2016H-PromptReco-v2.root";
    else if(argv2=="2016H3") filename="root://cmseos.fnal.gov//store/user/clint/Run2016/Nov16/ljmet_trees/ljmet_Data_DoubleEG-Run2016H-PromptReco-v3.root";
  }
  else if(argv1=="MC" && argv2=="50ns") {filename="root://cmseos.fnal.gov//store/user/clint/PHYS14/50ns/ljmet_trees/ljmet_DYJets.root"; data=false; FiftyNS=true;}
  else if(argv1=="MC" && argv2=="25ns") {filename="root://cmseos.fnal.gov//store/user/clint/Spring15/25ns/Nov16/ljmet_trees/ljmet_DYJets.root"; data=false; FiftyNS=false;}
  else if(argv1=="TTH" && argv2=="25ns") {filename=eosarea+"/ljmet_TTH.root"; data=false; FiftyNS=false;}
  else if(argv1=="TTTT" && argv2=="25ns") {filename=eosarea+"/ljmet_TTTT.root"; data=false; FiftyNS=false;}
  else if(argv1=="TTZ" && argv2=="25ns") {filename=eosarea+"/ljmet_TTZ.root"; data=false; FiftyNS=false;}
  else if(argv1=="WpWp" && argv2=="25ns") {filename=eosarea+"/ljmet_WpWp.root"; data=false; FiftyNS=false;}
  else if(argv1=="WWZ" && argv2=="25ns") {filename=eosarea+"/ljmet_WWZ.root"; data=false; FiftyNS=false;}
  else if(argv1=="WZ" && argv2=="25ns") {filename=eosarea+"/ljmet_WZ.root"; data=false; FiftyNS=false;}
  else if(argv1=="WZZ" && argv2=="25ns") {filename=eosarea+"/ljmet_WZZ.root"; data=false; FiftyNS=false;}
  else if(argv1=="ZZ" && argv2=="25ns") {filename=eosarea+"/ljmet_ZZ.root"; data=false; FiftyNS=false;}
  else if(argv1=="ZZZ" && argv2=="25ns") {filename=eosarea+"/ljmet_ZZZ.root"; data=false; FiftyNS=false;}
  else{
    std::cout<<"Need to specify whether running on Data or MC and 25 or 50ns. The four possible ways of running are\n"
	     <<"./ChargeMisID.o Data 50ns \n"
	     <<"./ChargeMisID.o Data 25ns \n"
	     <<"./ChargeMisID.o MC 50ns \n"
	     <<"./ChargeMisID.o MC 25ns \n";
  }

  //make filename for output root file
  std::string outname;
  if(data)outname="ChargeMisID_Data_"+argv2+"_Electrons_"+ID+".root"; 
  else outname="ChargeMisID_MC_Electrons_"+ID+"_"+argv1+".root"; 
  //open output file
  TFile* fout= new TFile(outname.c_str(),"RECREATE");

  //get tree reader to read in data
  TreeReader* tr= new TreeReader(filename.c_str(),!data);
  TTree* t=tr->tree;

  //now change back to output file
  fout->cd();
  gDirectory->pwd();

  //initialize needed histograms
  TH1F* ptNumHist_all = new TH1F("ptNumHist_all","p_{T} of Same Sign Leptons",20,0,600);
  TH1F* ptDenHist_all = new TH1F("ptDenHist_all","p_{T} of All Leptons",20,0,600);

  TH1F* ptNumHist_lpt = new TH1F("ptNumHist_lpt","p_{T} of Same Sign Leptons",20,0,100);
  TH1F* ptDenHist_lpt = new TH1F("ptDenHist_lpt","p_{T} of All Leptons",20,0,100);

  TH1F* ptNumHist_hpt = new TH1F("ptNumHist_hpt","p_{T} of Same Sign Leptons",20,0,600);
  TH1F* ptDenHist_hpt = new TH1F("ptDenHist_hpt","p_{T} of All Leptons",20,0,600);

  TH1F* ptNumHist_hhpt = new TH1F("ptNumHist_hhpt","p_{T} of Same Sign Leptons",20,0,600);
  TH1F* ptDenHist_hhpt = new TH1F("ptDenHist_hhpt","p_{T} of All Leptons",20,0,600);

  TH1F* etaAllHist = new TH1F("etaAllHist","#eta of All Leptons",15,-3,3);
  TH1F* etaNumHist = new TH1F("etaNumHist","#eta of Same Sign Leptons",15,-3,3);
  TH1F* etaDenHist = new TH1F("etaDenHist","#eta of All Leptons",15,-3,3);

  TH1F* etaNumHist_lpt = new TH1F("etaNumHist_lpt","#eta of low pT Same Sign Leptons",15,-3,3);
  TH1F* etaDenHist_lpt = new TH1F("etaDenHist_lpt","#eta of low pT Leptons",15,-3,3);

  TH1F* etaNumHist_hpt = new TH1F("etaNumHist_hpt","#eta of High pT Same Sign Leptons",15,-3,3);
  TH1F* etaDenHist_hpt = new TH1F("etaDenHist_hpt","#eta of High pT Leptons",15,-3,3);

  TH1F* etaNumHist_hhpt = new TH1F("etaNumHist_hhpt","#eta of High pT Same Sign Leptons",15,-3,3);
  TH1F* etaDenHist_hhpt = new TH1F("etaDenHist_hhpt","#eta of High pT Leptons",15,-3,3);

  TH1F* massNumHist = new TH1F("massNumHist","M_{ll} of Same Sign Leptons",50,0,150);
  TH1F* massDenHist = new TH1F("massDenHist","M_ll} of All Leptons",50,0,150);

  //output tree
  TTree* outTree = new TTree("ChargeMisID","ChargeMisID");
  float Lep1Pt_,Lep1Eta_,Lep1Phi_,Lep1E_,Lep2Pt_,Lep2Eta_,Lep2Phi_,Lep2E_;
  int Lep1Charge_,Lep2Charge_;
  outTree->Branch("Lep1Pt",&Lep1Pt_);
  outTree->Branch("Lep1Eta",&Lep1Eta_);
  outTree->Branch("Lep1Phi",&Lep1Phi_);
  outTree->Branch("Lep1E",&Lep1E_);
  outTree->Branch("Lep1Charge",&Lep1Charge_);
  outTree->Branch("Lep2Pt",&Lep2Pt_);
  outTree->Branch("Lep2Eta",&Lep2Eta_);
  outTree->Branch("Lep2Phi",&Lep2Phi_);
  outTree->Branch("Lep2E",&Lep2E_);
  outTree->Branch("Lep2Charge",&Lep2Charge_);


  //get number of entries and start event loop
  int nEntries = t->GetEntries();
  for(int ient=0; ient<nEntries; ient++){

    tr->GetEntry(ient);
    float weight;
    if(data) weight =1.0;
    else weight = tr->MCWeight >=0 ? 1.0 : -1.0;
    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;

    for(std::vector<TElectron*>::size_type iel=0; iel<tr->goodElectrons.size();iel++){
      etaAllHist->Fill( (tr->goodElectrons).at(iel)->eta,weight);
    }

    //make vector of leptons
    std::vector<TLepton*> leptons = makeLeptons(tr->allElectrons,!data,FiftyNS,ID);

    //skip if didn't find at least two tight leptons
    if(leptons.size()<2) continue;

    //get pair of leptons closest to z mass;
    float zmass = 91.1;
    float massDiff=9999;
    TLepton* lep1=0;
    TLepton* lep2=0;
    float pairmass=-9999;
    for(std::vector<TLepton*>::size_type ilep=0; ilep<leptons.size(); ilep++){
      //loop over remaining leptons
      for(std::vector<TLepton*>::size_type jlep=ilep+1; jlep<leptons.size(); jlep++){
	pairmass = (leptons.at(ilep)->lv + leptons.at(jlep)->lv).M();
	if(fabs(zmass-pairmass)<massDiff){
	  massDiff = zmass-pairmass;
	  lep1=leptons.at(ilep);
	  lep2=leptons.at(jlep);
	}
      }//end second loop over leptons
    }//end loop over leptons

    //check that leptons are in Zpeak
    bool zpeak= fabs(massDiff)<10 ? true : false;

    //fill denominator
    massDenHist->Fill(zmass+massDiff,weight);

    if(!zpeak) continue;

    //fill tree
    Lep1Pt_=lep1->pt;
    Lep1Eta_=lep1->eta;
    Lep1Phi_=lep1->phi;
    Lep1E_=lep1->energy;
    Lep1Charge_=lep1->charge;
    Lep2Pt_=lep2->pt;
    Lep2Eta_=lep2->eta;
    Lep2Phi_=lep2->phi;
    Lep2E_=lep2->energy;
    Lep2Charge_=lep2->charge;

    outTree->Fill();

    //now fill histograms
    if(lep1->charge == lep2->charge){
      massNumHist->Fill(zmass+massDiff,weight);
      //all pt
      ptNumHist_all->Fill(lep1->pt,weight);
      ptNumHist_all->Fill(lep2->pt,weight);
      //low pt
      if(lep1->pt < 100 && lep2->pt <100){
	ptNumHist_lpt->Fill(lep1->pt,weight);
	ptNumHist_lpt->Fill(lep2->pt,weight);      
      }
      //high high pt
      else if(lep1->pt > 100 && lep2->pt >100){
	ptNumHist_hhpt->Fill(lep1->pt,weight);
	ptNumHist_hhpt->Fill(lep2->pt,weight);      
      }
      //one high one low
      else {
	ptNumHist_hpt->Fill(lep1->pt,weight);
	ptNumHist_hpt->Fill(lep2->pt,weight);      
      }
      //all eta
      etaNumHist->Fill(lep1->eta,weight);
      etaNumHist->Fill(lep2->eta,weight);
      if(lep1->pt>100 && lep2->pt>100){
	etaNumHist_hhpt->Fill(lep1->eta,weight);
	etaNumHist_hhpt->Fill(lep2->eta,weight);
      }	     
      else if(lep1->pt>100 || lep2->pt>100){
	etaNumHist_hpt->Fill(lep1->eta,weight);
	etaNumHist_hpt->Fill(lep2->eta,weight);
      }
      else{
	etaNumHist_lpt->Fill(lep1->eta,weight);
	etaNumHist_lpt->Fill(lep2->eta,weight);
      }
    }

    //fill denominator
    //all pt
    ptDenHist_all->Fill(lep1->pt,weight);
    ptDenHist_all->Fill(lep2->pt,weight);
    //low pt
    if(lep1->pt < 100 && lep2->pt <100){
      ptDenHist_lpt->Fill(lep1->pt,weight);
      ptDenHist_lpt->Fill(lep2->pt,weight);      
    }
    //high high pt
    else if(lep1->pt > 100 && lep2->pt >100){
      ptDenHist_hhpt->Fill(lep1->pt,weight);
      ptDenHist_hhpt->Fill(lep2->pt,weight);      
    }
    //one high one low
    else {
      ptDenHist_hpt->Fill(lep1->pt,weight);
      ptDenHist_hpt->Fill(lep2->pt,weight);      
    }

    //all eta
    etaDenHist->Fill(lep1->eta,weight);
    etaDenHist->Fill(lep2->eta,weight);
    if(lep1->pt>100 && lep2->pt>100){
      etaDenHist_hhpt->Fill(lep1->eta,weight);
      etaDenHist_hhpt->Fill(lep2->eta,weight);
    }
    else if(lep1->pt>100 || lep2->pt>100){
      etaDenHist_hpt->Fill(lep1->eta,weight);
      etaDenHist_hpt->Fill(lep2->eta,weight);
    }
    else{
      etaDenHist_lpt->Fill(lep1->eta,weight);
      etaDenHist_lpt->Fill(lep2->eta,weight);
    }
  }//end event loop

  //save weights 
  etaNumHist->Sumw2();
  etaDenHist->Sumw2();
  etaNumHist_hpt->Sumw2();
  etaDenHist_hpt->Sumw2();
  etaNumHist_lpt->Sumw2();
  etaDenHist_lpt->Sumw2();
  ptNumHist_all->Sumw2();
  ptNumHist_lpt->Sumw2();
  ptNumHist_hpt->Sumw2();
  ptNumHist_hhpt->Sumw2();
  ptDenHist_all->Sumw2();
  ptDenHist_lpt->Sumw2();
  ptDenHist_hpt->Sumw2();
  ptDenHist_hhpt->Sumw2();
  massNumHist->Sumw2();
  massDenHist->Sumw2();

  //scale num hists by 1/2 (except mass)
  etaNumHist->Scale(0.5);
  etaNumHist_lpt->Scale(0.5);
  etaNumHist_hpt->Scale(0.5);
  etaNumHist_hhpt->Scale(0.5);
  ptNumHist_all->Scale(0.5);
  ptNumHist_lpt->Scale(0.5);
  ptNumHist_hpt->Scale(0.5);
  ptNumHist_hhpt->Scale(0.5);

  //write file now that histograms have been filled
  fout->Append(ptNumHist_all);
  fout->Append(ptDenHist_all);
  fout->Append(ptNumHist_lpt);
  fout->Append(ptDenHist_lpt);
  fout->Append(ptNumHist_hpt);
  fout->Append(ptDenHist_hpt);
  fout->Append(ptNumHist_hhpt);
  fout->Append(ptDenHist_hhpt);
  fout->Append(etaAllHist);
  fout->Append(etaNumHist);
  fout->Append(etaDenHist);
  fout->Append(etaNumHist_hpt);
  fout->Append(etaDenHist_hpt);
  fout->Append(etaNumHist_hhpt);
  fout->Append(etaDenHist_hhpt);
  fout->Append(etaNumHist_lpt);
  fout->Append(etaDenHist_lpt);
  fout->Append(massNumHist);
  fout->Append(massDenHist);
  //make tgraphs for promptrate
  TGraphAsymmErrors* ptGraph = new TGraphAsymmErrors(ptNumHist_all,ptDenHist_all);
  TGraphAsymmErrors* etaGraph = new TGraphAsymmErrors(etaNumHist,etaDenHist);
  //write the tgraphs
  fout->Append(ptGraph);
  fout->Append(etaGraph);

  //make hists of rate
  TH1F* rateEta = (TH1F*) etaNumHist->Clone();
  rateEta->Divide(etaDenHist);
  TH1F* ratePt_all = (TH1F*) ptNumHist_all->Clone();
  ratePt_all->Divide(ptDenHist_all);
  TH1F* ratePt_lpt = (TH1F*) ptNumHist_lpt->Clone();
  ratePt_lpt->Divide(ptDenHist_lpt);
  TH1F* ratePt_hpt = (TH1F*) ptNumHist_hpt->Clone();
  ratePt_hpt->Divide(ptDenHist_hpt);
  TH1F* ratePt_hhpt = (TH1F*) ptNumHist_hhpt->Clone();
  ratePt_hhpt->Divide(ptDenHist_hhpt);
  TH1F* rateEta_lpt = (TH1F*)etaNumHist_lpt->Clone();
  rateEta_lpt->Divide(etaDenHist_lpt);
  TH1F* rateEta_hpt = (TH1F*)etaNumHist_hpt->Clone();
  rateEta_hpt->Divide(etaDenHist_hpt);
  TH1F* rateEta_hhpt = (TH1F*)etaNumHist_hhpt->Clone();
  rateEta_hhpt->Divide(etaDenHist_hhpt);
  fout->Append(rateEta);
  fout->Append(rateEta_lpt);
  fout->Append(rateEta_hpt);
  fout->Append(rateEta_hhpt);
  fout->Append(ratePt_all);
  fout->Append(ratePt_lpt);
  fout->Append(ratePt_hpt);
  fout->Append(ratePt_hhpt);
  fout->WriteTObject(outTree);
  fout->Write();




  return 0;
}


std::vector<TLepton*> makeLeptons(std::vector<TElectron*> electrons, bool mc, bool FiftyNs, std::string ID){

  std::vector<TLepton*> Leptons;

  //fill with  electrons
  for(unsigned int uiel=0; uiel<electrons.size(); uiel++){
    TElectron* iel = electrons.at(uiel);
    TLepton* iLep = new TLepton(iel->pt,iel->eta,iel->phi,iel->energy,iel->charge,iel->relIso,iel->miniIso,iel->susyIso);

    if(ID=="CBTight"){
      iLep->Tight=iel->cutBasedTight25nsSpring15MC();
      iLep->Loose=iel->cutBasedLoose25nsSpring15MC();
    }
    else if(ID=="CBLoose"){
      iLep->Tight=iel->cutBasedLoose25nsSpring15MC();
      iLep->Loose=true;
    }
    if(ID=="CBTightRC"){
      iLep->Tight=iel->cutBasedTight25nsSpring15MCRC();
      iLep->Loose=iel->cutBasedLoose25nsSpring15MCRC();
    }
    else if(ID=="CBLooseRC"){
      iLep->Tight=iel->cutBasedLoose25nsSpring15MCRC();
      iLep->Loose=true;
    }
    else if(ID=="MVATightNew"){
      iLep->Tight=iel->mvaTightNew();
      iLep->Loose=iel->mvaLooseNew();
    }
    else if(ID=="MVATightNewRC"){
      iLep->Tight=iel->mvaTightNewRC();
      iLep->Loose=iel->mvaLooseNewRC();
    }
    else if(ID=="MVATight"){
      iLep->Tight=iel->mvaTightIso();
      iLep->Loose=iel->mvaLooseIso();
    }
    else if(ID=="MVATightNoIso"){
      iLep->Tight=iel->mvaTight();
      iLep->Loose=iel->mvaLoose();
    }
    else if(ID=="MVALoose"){
      iLep->Tight=iel->mvaLooseIso();
      iLep->Loose=true;
    }
    else if(ID=="MVALooseNoIso"){
      iLep->Tight=iel->mvaLoose();
      iLep->Loose=true;
    }
    else if(ID=="MVATightCC"){
      iLep->Tight=iel->mvaTightCCIso();
      iLep->Loose=iel->mvaLooseCCIso();
    }
    else if(ID=="MVATightCCNoIso"){
      iLep->Tight=iel->mvaTightCC();
      iLep->Loose=iel->mvaLooseCC();
    }
    else if(ID=="MVALooseCC"){
      iLep->Tight=iel->mvaLooseCCIso();
      iLep->Loose=true;
    }
    else if(ID=="MVALooseNoIso"){
      iLep->Tight=iel->mvaLoose();
      iLep->Loose=true;
    }  
    else if(ID=="MVATightRC"){
      iLep->Tight=iel->mvaTightRCIso();
      iLep->Loose=iel->mvaLooseRCIso();
    }
    else if(ID=="MVATightLC"){
      iLep->Tight=iel->mvaTightLCIso();
      iLep->Loose=iel->mvaLooseLCIso();
    }
    else if(ID=="MVALooseRC"){
      iLep->Tight=iel->mvaLooseRCIso();
      iLep->Loose=true;
    }
    else if(ID=="SUSYTight"){
      iLep->Tight=iel->susyTight();
      iLep->Loose=iel->susyLoose();
    }
    else if(ID=="SUSYLoose"){
	iLep->Tight=iel->susyLoose();
	iLep->Loose=true;
    }
    else if(ID=="SUSYTightRC"){
      iLep->Tight=iel->susyTightRC();
      iLep->Loose=iel->susyLooseRC();
    }      
    iLep->isMu = false;
    iLep->isEl = true;
    //only save if tight
    if(iLep->Tight){
      //apply pt cut
      if(iLep->pt>30) Leptons.push_back(iLep);
    }
  }


  return Leptons;
 
}
