#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
/*
#include "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/plugins/Sample.cc"
#include "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/plugins/CutClass.cc"
#include "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/interface/TreeReader.h"
#include "TGraphAsymmErrors.h"
*/
#include "Sample.cc"
#include "CutClass.cc"
#include "../interface/TreeReader.h"
#include "TGraphAsymmErrors.h"

std::string testDir = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_10_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/";
std::string bgTestDir = testDir;
std::string x53String = "X53X53";
/*
std::string testDir = "/uscms/home/dzou/CMSSW_7_3_0/src/X53ThirteenTeVAnalysisCode/test/"; //global variable for test directory used for samples, etc.
std::string testDir = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_10_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/";
std::string x53String = "X53";
*/

std::vector<Variable*> getVariableVec(){

  std::vector<Variable*> vVar;

  Variable* lep1pt = new Variable("Lep1Pt",6,0,600,"Leading Lepton p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(lep1pt);
  Variable* lep1eta = new Variable("Lep1Eta",25,-5,5,"Leading Lepton #eta","N_{Events}");
  vVar.push_back(lep1eta);
  Variable* lep1phi = new Variable("Lep1Phi",20,-3.5,3.5,"Leading Lepton #phi","N_{Events}");
  vVar.push_back(lep1phi);

  Variable* lep2pt = new Variable("Lep2Pt",6,0,600,"subLeading Lepton p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(lep2pt);
  Variable* lep2eta = new Variable("Lep2Eta",25,-5,5,"subLeading Lepton #eta","N_{Events}");
  vVar.push_back(lep2eta);
  Variable* lep2phi = new Variable("Lep2Phi",20,-3.5,3.5,"subLeading Lepton #phi","N_{Events}");
  vVar.push_back(lep2phi);

  /*Variable* ak4jet1pt = new Variable("AK4Jet1Pt",15,0,600,"Leading Jet p_{T} (GeV)","N_{Events}");
  vVar.push_back(ak4jet1pt);
  Variable* ak4jet1eta = new Variable("AK4Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
  vVar.push_back(ak4jet1eta);
  Variable* ak4jet1phi = new Variable("AK4Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
  vVar.push_back(ak4jet1phi);

<  Variable* ak4jet2pt = new Variable("AK4Jet2Pt",15,0,600,"subLeading Jet p_{T} (GeV)","N_{Events}");
  vVar.push_back(ak4jet2pt);
  Variable* ak4jet2eta = new Variable("AK4Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
  vVar.push_back(ak4jet2eta);
  Variable* ak4jet2phi = new Variable("AK4Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
  vVar.push_back(ak4jet2phi);


  Variable* ak4ht = new Variable("AK4HT",20,0,3000,"AK4 H_{T} (GeV)","N_{Events}");
  vVar.push_back(ak4ht);
  Variable* nak4jets = new Variable("nAK4Jets",17,0,17,"N_{AK4 Jets}","N_{Events}");
  vVar.push_back(nak4jets);*/

  //cleaned jet variables
  Variable* cleanak4jet1pt = new Variable("cleanAK4Jet1Pt",6,0,600,"Leading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(cleanak4jet1pt);
  Variable* cleanak4jet1eta = new Variable("cleanAK4Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
  vVar.push_back(cleanak4jet1eta);
  Variable* cleanak4jet1phi = new Variable("cleanAK4Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
  vVar.push_back(cleanak4jet1phi);

  Variable* cleanak4jet2pt = new Variable("cleanAK4Jet2Pt",6,0,600,"subLeading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(cleanak4jet2pt);
  Variable* cleanak4jet2eta = new Variable("cleanAK4Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
  vVar.push_back(cleanak4jet2eta);
  Variable* cleanak4jet2phi = new Variable("cleanAK4Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
  vVar.push_back(cleanak4jet2phi);


  Variable* cleanak4ht = new Variable("cleanAK4HT",25,0,3000,"H_{T}^{lep} (GeV)","N_{Events} / 150 GeV");
  vVar.push_back(cleanak4ht);
  Variable* ncleanak4jets = new Variable("nCleanAK4Jets",17,0,17,"N_{AK4 Jets}","N_{Events}");
  vVar.push_back(ncleanak4jets);

  Variable* nnonssleps = new Variable("nNonSSLeps",17,0,17,"N_{Non-SS Leps}","N_{Events}");
  vVar.push_back(nnonssleps);

  //simple cleaned jet variables
  /*Variable* simpleCleanak4jet1pt = new Variable("simpleCleanAK4Jet1Pt",6,0,600,"Leading Jet p_{T} (GeV)","N_{Events}");
  vVar.push_back(simpleCleanak4jet1pt);
  Variable* simpleCleanak4jet1eta = new Variable("simpleCleanAK4Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
  vVar.push_back(simpleCleanak4jet1eta);
  Variable* simpleCleanak4jet1phi = new Variable("simpleCleanAK4Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
  vVar.push_back(simpleCleanak4jet1phi);

  Variable* simpleCleanak4jet2pt = new Variable("simpleCleanAK4Jet2Pt",6,0,600,"subLeading Jet p_{T} (GeV)","N_{Events}");
  vVar.push_back(simpleCleanak4jet2pt);
  Variable* simpleCleanak4jet2eta = new Variable("simpleCleanAK4Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
  vVar.push_back(simpleCleanak4jet2eta);
  Variable* simpleCleanak4jet2phi = new Variable("simpleCleanAK4Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
  vVar.push_back(simpleCleanak4jet2phi);


  Variable* simpleCleanak4ht = new Variable("simpleCleanAK4HT",20,0,3000,"simpleCleanAK4 H_{T} (GeV)","N_{Events}");
  vVar.push_back(simpleCleanak4ht);
  Variable* nsimpleCleanak4jets = new Variable("nSimpleCleanAK4Jets",17,0,17,"N_{simpleCleanAK4 Jets}","N_{Events}");
  vVar.push_back(nsimpleCleanak4jets);*/

  Variable* nConst = new Variable("nConst",17,0,17,"N_{Const}","N_{Events}");
  vVar.push_back(nConst);


  Variable* met = new Variable("MET",60,0,600,"MET (GeV)", "N_{Events}");
  vVar.push_back(met);
  Variable* dilepMass = new Variable("DilepMass",20,0,600,"Dilepton Mass (GeV)", "N_{Events} / 30 GeV");
  vVar.push_back(dilepMass);
  return vVar;

}

std::vector<Variable*> getVariablesForClosureTest(){

  std::vector<Variable*> vVar;

  Variable* lep1pt = new Variable("Lep1Pt",6,0,600,"Leading Lepton p_{T} (GeV)","N_{Events}");
  vVar.push_back(lep1pt);
  /*Variable* lep1eta = new Variable("Lep1Eta",25,-5,5,"Leading Lepton #eta","N_{Events}");
  vVar.push_back(lep1eta);
  Variable* lep1phi = new Variable("Lep1Phi",20,-3.5,3.5,"Leading Lepton #phi","N_{Events}");
  vVar.push_back(lep1phi);*/

  Variable* lep2pt = new Variable("Lep2Pt",6,0,600,"subLeading Lepton p_{T} (GeV)","N_{Events}");
  vVar.push_back(lep2pt);
  /*Variable* lep2eta = new Variable("Lep2Eta",25,-5,5,"subLeading Lepton #eta","N_{Events}");
  vVar.push_back(lep2eta);
  Variable* lep2phi = new Variable("Lep2Phi",20,-3.5,3.5,"subLeading Lepton #phi","N_{Events}");
  vVar.push_back(lep2phi);*/

  //cleaned jet variables
  Variable* cleanak4jet1pt = new Variable("cleanAK4Jet1Pt",6,0,600,"Leading Jet p_{T} (GeV)","N_{Events}");
  vVar.push_back(cleanak4jet1pt);
  /*Variable* cleanak4jet1eta = new Variable("cleanAK4Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
  vVar.push_back(cleanak4jet1eta);
  Variable* cleanak4jet1phi = new Variable("cleanAK4Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
  vVar.push_back(cleanak4jet1phi);*/

  Variable* cleanak4jet2pt = new Variable("cleanAK4Jet2Pt",6,0,600,"subLeading Jet p_{T} (GeV)","N_{Events}");
  vVar.push_back(cleanak4jet2pt);
  /*Variable* cleanak4jet2eta = new Variable("cleanAK4Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
  vVar.push_back(cleanak4jet2eta);
  Variable* cleanak4jet2phi = new Variable("cleanAK4Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
  vVar.push_back(cleanak4jet2phi);*/


  Variable* cleanak4ht = new Variable("cleanAK4HT",20,0,3000,"H_{T} (GeV)","N_{Events}");
  vVar.push_back(cleanak4ht);
  Variable* ncleanak4jets = new Variable("nCleanAK4Jets",17,0,17,"N_{AK4 Jets}","N_{Events}");
  vVar.push_back(ncleanak4jets);

  //Variable* nConst = new Variable("nConst",17,0,17,"N_{Const}","N_{Events}");
  //vVar.push_back(nConst);

  //Variable* met = new Variable("MET",60,0,600,"MET (GeV)", "N_{Events}");
  //vVar.push_back(met);
  Variable* dilepMass = new Variable("DilepMass",60,0,600,"Dilepton Mass (GeV)", "N_{Events}");
  vVar.push_back(dilepMass);
  return vVar;

}


std::vector<TH1F*> getNPHistos(int nMu){

  std::vector<TH1F*> hists;
  std::string channel;
  if(nMu==-1) channel="All";
  if(nMu==0) channel="ElEl";
  if(nMu==1) channel="ElMu";
  if(nMu==2) channel="MuMu";

  std::string nt00 = channel+"_HT_nConstCut_NT00";
  std::string nt01 = channel+"_HT_nConstCut_NT01";
  std::string nt10 = channel+"_HT_nConstCut_NT10";
  std::string nt11 = channel+"_HT_nConstCut_NT11";

  //10 gev bins sot hat later I can use bin number ask cut
  hists.push_back(new TH1F(nt00.c_str(),nt00.c_str(),1000,0,10000) );
  hists.push_back(new TH1F(nt01.c_str(),nt01.c_str(),1000,0,10000) );
  hists.push_back(new TH1F(nt10.c_str(),nt10.c_str(),1000,0,10000) );
  hists.push_back(new TH1F(nt11.c_str(),nt11.c_str(),1000,0,10000) );

  return hists;
}


Sample* getDataSample(std::string cut,std::string elID, std::string muID){
  std::string filename = testDir.c_str()+muID+"_El"+elID+".root";
  TFile* tfile = new TFile(filename.c_str());
  Sample* dataSample = new Sample("Data",tfile,1,1,cut,kBlack,1);
  return dataSample;
}

std::vector<Sample*> getSigSampleVecForPlots(std::string cut, float lumi, std::string elID, std::string muID){

  //br is OR of either side decaying to ssdl. BR(ssdl) for one side = BR(W->enu) OR BR(W->munu) OR BR(W->taunu) **2 where the square comes from AND requiring both to decay leptonically
  float BRssdl= 2*( pow((.1063 + .1071 + .1138),2));
  //make names vector
  //make x-sec vector - NEED TO FIX THESE VALUES************************************************
  //make vector for number of events ran to get weight
  std::vector<float> vNEvts;
  std::vector<std::string> vSigNames;  std::vector<float> vXsec;
  vSigNames.push_back("LH_X53X53_M-700");   vXsec.push_back(0.442*BRssdl);  vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-700"); vXsec.push_back(0.442*BRssdl);vNEvts.push_back(20000.);
  //vSigNames.push_back("LH_X53X53_M-1000"); vXsec.push_back(0.0427*BRssdl);vNEvts.push_back(20000.);
  //vSigNames.push_back("RH_X53X53_M-1000"); vXsec.push_back(0.0427*BRssdl);vNEvts.push_back(19400.);

  //FOR RUNNING ON INCLUSIVE DON'T APPLY BR TO SSDL!!
  //vXsec.push_back(0.442);vXsec.push_back(0.442);vXsec.push_back(0.0427);vXsec.push_back(0.0427);vXsec.push_back(0.00618);vXsec.push_back(0.00618);


  

  //vector to hold weights
  std::vector<float> vWeights;
  for(std::vector<float>::size_type i=0; i<vXsec.size();i++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(i) / vNEvts.at(i) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  std::vector<Sample*> vSigSamples;
  
  std::string lh700name =testDir.c_str()+"X53X53m700LH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53700Lfile = new TFile(lh700name.c_str());
  Sample* x53x53m700L = new Sample(vSigNames.at(0),x53x53700Lfile,vWeights.at(0),vXsec.at(0),cut,kGreen,2);
  vSigSamples.push_back(x53x53m700L);

  std::string rh700name = testDir.c_str()+"X53X53m700RH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53700Rfile = new TFile(rh700name.c_str());
  Sample* x53x53m700R = new Sample(vSigNames.at(1),x53x53700Rfile,vWeights.at(1),vXsec.at(1),cut,kGreen,1);
  vSigSamples.push_back(x53x53m700R);
  
  /* std::string lh1000name = testDir.c_str()+"X53X53m1000LH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531000Lfile = new TFile(lh1000name.c_str());
  Sample* x53x53m1000L = new Sample(vSigNames.at(2),x53x531000Lfile,vWeights.at(2),vXsec.at(2),cut,kCyan,2);
  vSigSamples.push_back(x53x53m1000L);
  
  std::string rh1000name = testDir.c_str()+"X53X53m1000RH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531000Rfile = new TFile(rh1000name.c_str());
  Sample* x53x53m1000R = new Sample(vSigNames.at(3),x53x531000Rfile,vWeights.at(3),vXsec.at(3),cut,kCyan,1);
  vSigSamples.push_back(x53x53m1000R);*/

  /*  TFile* x53x531300Lfile = new TFile(testDir.c_str()+"X53X53m1300LH.root");
  Sample* x53x53m1300L = new Sample(vSigNames.at(4),x53x531300Lfile,vWeights.at(4),vXsec.at(4),cut,kBlue,2);
  TFile* x53x531300Rfile = new TFile(testDir.c_str()+"X53X53m1300RH.root");
  Sample* x53x53m1300R = new Sample(vSigNames.at(5),x53x531300Rfile,vWeights.at(5),vXsec.at(5),cut,kBlue,1);
  */
  return vSigSamples;

}

std::vector<Sample*> getSigSampleVecForTable(std::string cut, float lumi, std::string elID, std::string muID){
  //make names vector
  std::vector<std::string> vSigNames;
  std::vector<float> vXsec;
  //br is OR of either side decaying to ssdl. BR(ssdl) for one side = BR(W->enu) OR BR(W->munu) **2 where the square comes from AND requiring both to decay leptonically
  float BRssdl= 2*( pow((.1063 + .1071 + .1138),2));
  std::vector<int> vNEvts;
  vSigNames.push_back("LH_X53X53_M-700"); vXsec.push_back(0.442*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-700"); vXsec.push_back(0.442*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("LH_X53X53_M-800"); vXsec.push_back(.190*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-800"); vXsec.push_back(.190*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("LH_X53X53_M-900"); vXsec.push_back(.0877*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-900"); vXsec.push_back(.0877*BRssdl); vNEvts.push_back(19800.);
  vSigNames.push_back("LH_X53X53_M-1000"); vXsec.push_back(0.0427*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-1000"); vXsec.push_back(0.0427*BRssdl); vNEvts.push_back(19400.);
  vSigNames.push_back("LH_X53X53_M-1100"); vXsec.push_back(0.0217*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-1100"); vXsec.push_back(0.0217*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("LH_X53X53_M-1300"); vXsec.push_back(0.00618*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-1300"); vXsec.push_back(0.00618*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("LH_X53X53_M-1400"); vXsec.push_back(0.00342*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-1400"); vXsec.push_back(0.00342*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("LH_X53X53_M-1500"); vXsec.push_back(0.00193*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-1500"); vXsec.push_back(0.00193*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("LH_X53X53_M-1600"); vXsec.push_back(0.00111*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-1600"); vXsec.push_back(0.00111*BRssdl); vNEvts.push_back(20000.);

 

  //vector to hold weights
  std::vector<float> vWeights;
  for(std::vector<float>::size_type i=0; i<vXsec.size();i++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(i) / vNEvts.at(i) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  std::vector<Sample*> vSigSamples;
  std::string lh700 = testDir.c_str()+"X53X53m700LH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53700Lfile = new TFile(lh700.c_str());
  Sample* x53x53m700L = new Sample(vSigNames.at(0),x53x53700Lfile,vWeights.at(0),vXsec.at(0),cut,kGreen,2);
  vSigSamples.push_back(x53x53m700L);
  std::string rh700 = testDir.c_str()+"X53X53m700RH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53700Rfile = new TFile(rh700.c_str());
  Sample* x53x53m700R = new Sample(vSigNames.at(1),x53x53700Rfile,vWeights.at(1),vXsec.at(1),cut,kGreen,1);
  vSigSamples.push_back(x53x53m700R);

  std::string lh800 = testDir.c_str()+"X53X53m800LH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53800Lfile = new TFile(lh800.c_str());
  Sample* x53x53m800L = new Sample(vSigNames.at(2),x53x53800Lfile,vWeights.at(2),vXsec.at(2),cut,kBlue,2);
  vSigSamples.push_back(x53x53m800L);
  std::string rh800 = testDir.c_str()+"X53X53m800RH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53800Rfile = new TFile(rh800.c_str());
  Sample* x53x53m800R = new Sample(vSigNames.at(3),x53x53800Rfile,vWeights.at(3),vXsec.at(3),cut,kBlue,1);
  vSigSamples.push_back(x53x53m800R);

  std::string lh900 = testDir.c_str()+"X53X53m900LH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53900Lfile = new TFile(lh900.c_str());
  Sample* x53x53m900L = new Sample(vSigNames.at(4),x53x53900Lfile,vWeights.at(4),vXsec.at(4),cut,kGreen,2);
  //vSigSamples.push_back(x53x53m900L);
  std::string rh900 = testDir.c_str()+"X53X53m900RH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53900Rfile = new TFile(rh900.c_str());
  Sample* x53x53m900R = new Sample(vSigNames.at(5),x53x53900Rfile,vWeights.at(5),vXsec.at(5),cut,kGreen,1);
  vSigSamples.push_back(x53x53m900R);

  std::string lh1000 = testDir.c_str()+"X53X53m1000LH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531000Lfile = new TFile(lh1000.c_str());
  Sample* x53x53m1000L = new Sample(vSigNames.at(6),x53x531000Lfile,vWeights.at(6),vXsec.at(6),cut,kCyan,2);
  //vSigSamples.push_back(x53x53m1000L);
  std::string rh1000 = testDir.c_str()+"X53X53m1000RH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531000Rfile = new TFile(rh1000.c_str());
  Sample* x53x53m1000R = new Sample(vSigNames.at(7),x53x531000Rfile,vWeights.at(7),vXsec.at(7),cut,kCyan,1);
  vSigSamples.push_back(x53x53m1000R);

  std::string lh1100 = testDir.c_str()+"X53X53m1100LH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531100Lfile = new TFile(lh1100.c_str());
  Sample* x53x53m1100L = new Sample(vSigNames.at(8),x53x531100Lfile,vWeights.at(8),vXsec.at(8),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1100L);
  std::string rh1100 = testDir.c_str()+"X53X53m1100RH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531100Rfile = new TFile(rh1100.c_str());
  Sample* x53x53m1100R = new Sample(vSigNames.at(9),x53x531100Rfile,vWeights.at(9),vXsec.at(9),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1100R);

  std::string lh1300 = testDir.c_str()+"X53X53m1300LH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531300Lfile = new TFile(lh1300.c_str());
  Sample* x53x53m1300L = new Sample(vSigNames.at(10),x53x531300Lfile,vWeights.at(10),vXsec.at(10),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1300L);
  std::string rh1300 = testDir.c_str()+"X53X53m1300RH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531300Rfile = new TFile(rh1300.c_str());
  Sample* x53x53m1300R = new Sample(vSigNames.at(11),x53x531300Rfile,vWeights.at(11),vXsec.at(11),cut,kBlue,1);
  //vSigSamples.push_back(x53x53m1300R);

  std::string lh1400 = testDir.c_str()+"X53X53m1400LH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531400Lfile = new TFile(lh1400.c_str());
  Sample* x53x53m1400L = new Sample(vSigNames.at(12),x53x531400Lfile,vWeights.at(12),vXsec.at(12),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1400L);
  std::string rh1400 = testDir.c_str()+"X53X53m1400RH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531400Rfile = new TFile(rh1400.c_str());
  Sample* x53x53m1400R = new Sample(vSigNames.at(13),x53x531400Rfile,vWeights.at(13),vXsec.at(13),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1400R);

  std::string lh1500 = testDir.c_str()+"X53X53m1500LH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531500Lfile = new TFile(lh1500.c_str());
  Sample* x53x53m1500L = new Sample(vSigNames.at(14),x53x531500Lfile,vWeights.at(14),vXsec.at(14),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1500L);
  std::string rh1500 = testDir.c_str()+"X53X53m1500RH_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531500Rfile = new TFile(rh1500.c_str());
  Sample* x53x53m1500R = new Sample(vSigNames.at(15),x53x531500Rfile,vWeights.at(15),vXsec.at(15),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1500R);

  /*  TFile* x53x531600Lfile = new TFile(testDir.c_str()+"X53X53m1600LH_Mu"+muID+"_El"+elID+".root");
  Sample* x53x53m1600L = new Sample(vSigNames.at(16),x53x531600Lfile,vWeights.at(16),vXsec.at(16),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1600L);
  TFile* x53x531600Rfile = new TFile(testDir.c_str()+"X53X53m1600RH_Mu"+muID+"_El"+elID+".root");
  Sample* x53x53m1600R = new Sample(vSigNames.at(17),x53x531600Rfile,vWeights.at(17),vXsec.at(17),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1600R);*/


  return vSigSamples;

}


std::vector<Sample*> getInclusiveSigSampleVecForTable(std::string cut, float lumi, std::string elID, std::string muID){
  //make names vector
  std::vector<std::string> vSigNames;
  std::vector<float> vXsec;
  //br is OR of either side decaying to ssdl. BR(ssdl) for one side = BR(W->enu) OR BR(W->munu) **2 where the square comes from AND requiring both to decay leptonically
  //float BRssdl= 2*( pow((.1063 + .1071 + .1138),2)); INCLUSIVE SO NO BRANCHING RATIO
  std::vector<int> vNEvts;
  vSigNames.push_back("LH_X53X53_M-700"); vXsec.push_back(0.442); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-700"); vXsec.push_back(0.442); vNEvts.push_back(297400.);
  vSigNames.push_back("LH_X53X53_M-800"); vXsec.push_back(.190); vNEvts.push_back(295600.);
  vSigNames.push_back("RH_X53X53_M-800"); vXsec.push_back(.190); vNEvts.push_back(299600.);
  vSigNames.push_back("LH_X53X53_M-900"); vXsec.push_back(.0877); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-900"); vXsec.push_back(.0877); vNEvts.push_back(299800.);
  vSigNames.push_back("LH_X53X53_M-1000"); vXsec.push_back(0.0427); vNEvts.push_back(293600.);
  vSigNames.push_back("RH_X53X53_M-1000"); vXsec.push_back(0.0427); vNEvts.push_back(299000.);
  vSigNames.push_back("LH_X53X53_M-1100"); vXsec.push_back(0.0217); vNEvts.push_back(299600.);
  vSigNames.push_back("RH_X53X53_M-1100"); vXsec.push_back(0.0217); vNEvts.push_back(299800.);
  vSigNames.push_back("LH_X53X53_M-1200"); vXsec.push_back(0.0114); vNEvts.push_back(295400.);
  vSigNames.push_back("RH_X53X53_M-1200"); vXsec.push_back(0.0114); vNEvts.push_back(300000.);
  vSigNames.push_back("LH_X53X53_M-1300"); vXsec.push_back(0.00618); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-1300"); vXsec.push_back(0.00618); vNEvts.push_back(293600.);
  vSigNames.push_back("LH_X53X53_M-1400"); vXsec.push_back(0.00342); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-1400"); vXsec.push_back(0.00342); vNEvts.push_back(298400.);
  vSigNames.push_back("LH_X53X53_M-1500"); vXsec.push_back(0.00193); vNEvts.push_back(298400.);
  vSigNames.push_back("RH_X53X53_M-1500"); vXsec.push_back(0.00193); vNEvts.push_back(300000.);
  vSigNames.push_back("LH_X53X53_M-1600"); vXsec.push_back(0.00111); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-1600"); vXsec.push_back(0.00111); vNEvts.push_back(300000.);

 

  //vector to hold weights
  std::vector<float> vWeights;
  for(std::vector<float>::size_type i=0; i<vXsec.size();i++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(i) / vNEvts.at(i) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  std::vector<Sample*> vSigSamples;
  std::string lh700 = testDir.c_str()+"X53X53m700LH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53700Lfile = new TFile(lh700.c_str());
  Sample* x53x53m700L = new Sample(vSigNames.at(0),x53x53700Lfile,vWeights.at(0),vXsec.at(0),cut,kGreen,2);
  vSigSamples.push_back(x53x53m700L);
  std::string rh700 = testDir.c_str()+"X53X53m700RH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53700Rfile = new TFile(rh700.c_str());
  Sample* x53x53m700R = new Sample(vSigNames.at(1),x53x53700Rfile,vWeights.at(1),vXsec.at(1),cut,kGreen,1);
  vSigSamples.push_back(x53x53m700R);

  std::string lh800 = testDir.c_str()+"X53X53m800LH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53800Lfile = new TFile(lh800.c_str());
  Sample* x53x53m800L = new Sample(vSigNames.at(2),x53x53800Lfile,vWeights.at(2),vXsec.at(2),cut,kBlue,2);
  vSigSamples.push_back(x53x53m800L);
  std::string rh800 = testDir.c_str()+"X53X53m800RH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53800Rfile = new TFile(rh800.c_str());
  Sample* x53x53m800R = new Sample(vSigNames.at(3),x53x53800Rfile,vWeights.at(3),vXsec.at(3),cut,kBlue,1);
  vSigSamples.push_back(x53x53m800R);

  std::string lh900 = testDir.c_str()+"X53X53m900LH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53900Lfile = new TFile(lh900.c_str());
  Sample* x53x53m900L = new Sample(vSigNames.at(4),x53x53900Lfile,vWeights.at(4),vXsec.at(4),cut,kGreen,2);
  vSigSamples.push_back(x53x53m900L);
  std::string rh900 = testDir.c_str()+"X53X53m900RH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x53900Rfile = new TFile(rh900.c_str());
  Sample* x53x53m900R = new Sample(vSigNames.at(5),x53x53900Rfile,vWeights.at(5),vXsec.at(5),cut,kGreen,1);
  vSigSamples.push_back(x53x53m900R);

  std::string lh1000 = testDir.c_str()+"X53X53m1000LH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531000Lfile = new TFile(lh1000.c_str());
  Sample* x53x53m1000L = new Sample(vSigNames.at(6),x53x531000Lfile,vWeights.at(6),vXsec.at(6),cut,kCyan,2);
  vSigSamples.push_back(x53x53m1000L);
  std::string rh1000 = testDir.c_str()+"X53X53m1000RH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531000Rfile = new TFile(rh1000.c_str());
  Sample* x53x53m1000R = new Sample(vSigNames.at(7),x53x531000Rfile,vWeights.at(7),vXsec.at(7),cut,kCyan,1);
  vSigSamples.push_back(x53x53m1000R);

  std::string lh1100 = testDir.c_str()+"X53X53m1100LH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531100Lfile = new TFile(lh1100.c_str());
  Sample* x53x53m1100L = new Sample(vSigNames.at(8),x53x531100Lfile,vWeights.at(8),vXsec.at(8),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1100L);
  std::string rh1100 = testDir.c_str()+"X53X53m1100RH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531100Rfile = new TFile(rh1100.c_str());
  Sample* x53x53m1100R = new Sample(vSigNames.at(9),x53x531100Rfile,vWeights.at(9),vXsec.at(9),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1100R);

  std::string lh1200 = testDir.c_str()+"X53X53m1200LH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531200Lfile = new TFile(lh1200.c_str());
  Sample* x53x53m1200L = new Sample(vSigNames.at(10),x53x531200Lfile,vWeights.at(10),vXsec.at(10),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1200L);
  std::string rh1200 = testDir.c_str()+"X53X53m1200RH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531200Rfile = new TFile(rh1200.c_str());
  Sample* x53x53m1200R = new Sample(vSigNames.at(11),x53x531200Rfile,vWeights.at(11),vXsec.at(11),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1200R);

  std::string lh1300 = testDir.c_str()+"X53X53m1300LH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531300Lfile = new TFile(lh1300.c_str());
  Sample* x53x53m1300L = new Sample(vSigNames.at(12),x53x531300Lfile,vWeights.at(12),vXsec.at(12),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1300L);
  std::string rh1300 = testDir.c_str()+"X53X53m1300RH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531300Rfile = new TFile(rh1300.c_str());
  Sample* x53x53m1300R = new Sample(vSigNames.at(13),x53x531300Rfile,vWeights.at(13),vXsec.at(13),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1300R);

  std::string lh1400 = testDir.c_str()+"X53X53m1400LH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531400Lfile = new TFile(lh1400.c_str());
  Sample* x53x53m1400L = new Sample(vSigNames.at(14),x53x531400Lfile,vWeights.at(14),vXsec.at(14),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1400L);
  std::string rh1400 = testDir.c_str()+"X53X53m1400RH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531400Rfile = new TFile(rh1400.c_str());
  Sample* x53x53m1400R = new Sample(vSigNames.at(15),x53x531400Rfile,vWeights.at(15),vXsec.at(15),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1400R);

  std::string lh1500 = testDir.c_str()+"X53X53m1500LH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531500Lfile = new TFile(lh1500.c_str());
  Sample* x53x53m1500L = new Sample(vSigNames.at(16),x53x531500Lfile,vWeights.at(16),vXsec.at(16),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1500L);
  std::string rh1500 = testDir.c_str()+"X53X53m1500RH_Inc_Mu"+muID+"_El"+elID+".root";
  TFile* x53x531500Rfile = new TFile(rh1500.c_str());
  Sample* x53x53m1500R = new Sample(vSigNames.at(17),x53x531500Rfile,vWeights.at(17),vXsec.at(17),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1500R);

  /*  TFile* x53x531600Lfile = new TFile(testDir.c_str()+"X53X53m1600LH_Inc_Mu"+muID+"_El"+elID+".root");
  Sample* x53x53m1600L = new Sample(vSigNames.at(16),x53x531600Lfile,vWeights.at(16),vXsec.at(16),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1600L);
  TFile* x53x531600Rfile = new TFile(testDir.c_str()+"X53X53m1600RH_Inc_Mu"+muID+"_El"+elID+".root");
  Sample* x53x53m1600R = new Sample(vSigNames.at(17),x53x531600Rfile,vWeights.at(17),vXsec.at(17),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1600R);*/


  return vSigSamples;

}




std::vector<Sample*> getSamplesForClosureTest(std::string cut, float lumi, std::string elID, std::string muID){  
  std::vector<std::string> vBkgNames;  std::vector<float> vXsec;  std::vector<float> vNEvts;
  vBkgNames.push_back("TTJets");  vXsec.push_back(831.76);  vNEvts.push_back(42730273 * 0.331582);
  vBkgNames.push_back("NonPromptTTJets");  vXsec.push_back(831.76);  vNEvts.push_back(42730273 * 0.331582);
  vBkgNames.push_back("TTbar");  vXsec.push_back(831.76);  vNEvts.push_back(115091972);
  vBkgNames.push_back("NonPromptTTbar");  vXsec.push_back(831.76);  vNEvts.push_back(115091972);

  //now make vector to hold weights;
  std::vector<float> vWeights;
  for(std::vector<float>::size_type ui=0; ui<vXsec.size(); ui++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(ui) / vNEvts.at(ui) ) ); //factor of 1000 to convert lumi to pb^-1
  }


  std::vector<Sample*> vSample;
  std::string tt = testDir.c_str()+"TTJets_Mu"+muID+"_El"+elID+".root";
  TFile* ttfile = new TFile(tt.c_str());
  Sample* ttSample = new Sample(vBkgNames.at(0),ttfile, vWeights.at(0),vXsec.at(0),cut,kRed+2);
  vSample.push_back(ttSample);


  std::string nptt = testDir.c_str()+"NonPromptTTJets_Mu"+muID+"_El"+elID+".root";
  TFile* npttfile = new TFile(nptt.c_str());
  Sample* npttSample = new Sample(vBkgNames.at(1),npttfile, vWeights.at(1),vXsec.at(1),cut,kBlue+2);
  vSample.push_back(npttSample);

  std::string ttb = testDir.c_str()+"TTbar-powheg_Mu"+muID+"_El"+elID+".root";
  TFile* ttbfile = new TFile(ttb.c_str());
  Sample* ttbSample = new Sample(vBkgNames.at(2),ttbfile, vWeights.at(2),vXsec.at(2),cut,kGreen+2);
  vSample.push_back(ttbSample);

  std::string npttb = testDir.c_str()+"NonPromptTTbar-powheg_Mu"+muID+"_El"+elID+".root";
  TFile* npttbfile = new TFile(npttb.c_str());
  Sample* npttbSample = new Sample(vBkgNames.at(3),npttbfile, vWeights.at(3),vXsec.at(3),cut,kBlack);
  vSample.push_back(npttbSample);

  return vSample;
}

std::vector<Sample*> getBkgSampleVec(std::string cut, float lumi, std::string elID, std::string muID){  

   //setup info for list of samples, xsec and events run  //make vector of actual number of events run MULTIPLIED BY AMCATNLO WEIGHT
  std::vector<std::string> vBkgNames;  std::vector<float> vXsec;  std::vector<float> vNEvts;

  //************** MC *************

 //vBkgNames.push_back("TTbar");  vXsec.push_back(831.76);  vNEvts.push_back(42730273 * 0.331582);
  vBkgNames.push_back("TTZ");    vXsec.push_back(0.2529);  vNEvts.push_back(398000 * 0.464779);
  vBkgNames.push_back("TTW");    vXsec.push_back(0.2043);  vNEvts.push_back(252908 * 0.513428);
  vBkgNames.push_back("TTH");    vXsec.push_back(0.215);  vNEvts.push_back(17882125 *0.296995);
  vBkgNames.push_back("TTTT");    vXsec.push_back(0.009103);  vNEvts.push_back(1238145 *0.4177);
  vBkgNames.push_back("WZ");     vXsec.push_back(4.42965); vNEvts.push_back(1925000 * 1);
  //vBkgNames.push_back("WJets");  vXsec.push_back(61526.7); vNEvts.push_back(24151270 * 0.683948);
  //vBkgNames.push_back("DYJets"); vXsec.push_back(6025.2);  vNEvts.push_back(28825132 * 0.6693);
  vBkgNames.push_back("ZZ");     vXsec.push_back(1.212);  vNEvts.push_back(6652512 * 0.689851);
  vBkgNames.push_back("VH");     vXsec.push_back(0.952);  vNEvts.push_back(993464 * 0.45775);
  vBkgNames.push_back("WpWp");   vXsec.push_back(0.03711); vNEvts.push_back( 140224* 1);
  vBkgNames.push_back("WW-mpi"); vXsec.push_back(1.64);   vNEvts.push_back( 843514* 1);  
  vBkgNames.push_back("WWZ");    vXsec.push_back(0.1651); vNEvts.push_back(250000*0.885872);
  vBkgNames.push_back("WZZ");    vXsec.push_back(0.05565); vNEvts.push_back(250000*0.876672);
  vBkgNames.push_back("ZZZ");    vXsec.push_back(0.01398); vNEvts.push_back(250000*0.8554);

  //******* Non Prompt**********
  //vBkgNames.push_back("NonPromptMC");  vXsec.push_back(831.76);  vNEvts.push_back(42730273 * 0.331582);
  vBkgNames.push_back("NonPrompt"); vXsec.push_back(1); vNEvts.push_back(1);
  vBkgNames.push_back("ChargeMisID"); vXsec.push_back(1); vNEvts.push_back(1);
  //now make vector to hold weights;
  std::vector<float> vWeights;
  for(std::vector<float>::size_type ui=0; ui<vXsec.size(); ui++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(ui) / vNEvts.at(ui) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  //now make samples and add to vector
  std::vector<Sample*> vSample;
  //TFile* ttfile = new TFile(testDir.c_str()+"TTbar.root");
  //Sample* ttSample = new Sample(vBkgNames.at(0),ttfile, vWeights.at(0),vXsec.at(0),cut,kRed+2);
  //vSample.push_back(ttSample);

  std::string ttZfilename = bgTestDir.c_str()+"TTZ_Mu"+muID+"_El"+elID+".root";
  TFile* ttZfile = new TFile(ttZfilename.c_str());
  Sample* ttZSample = new Sample(vBkgNames.at(0),ttZfile, vWeights.at(0),vXsec.at(0),cut,kRed);
  vSample.push_back(ttZSample);

  std::string ttWfilename = bgTestDir.c_str()+"TTW_Mu"+muID+"_El"+elID+".root";
  TFile* ttwfile = new TFile(ttWfilename.c_str());
  Sample* ttwSample = new Sample(vBkgNames.at(1),ttwfile, vWeights.at(1),vXsec.at(1),cut,kYellow-2);
  vSample.push_back(ttwSample);

  std::string tthfilename = bgTestDir.c_str()+"TTH_Mu"+muID+"_El"+elID+".root";
  TFile* tthfile = new TFile(tthfilename.c_str());
  Sample* tthSample = new Sample(vBkgNames.at(2),tthfile, vWeights.at(2),vXsec.at(2),cut,kYellow);
  vSample.push_back(tthSample);

  std::string ttttfilename = bgTestDir.c_str()+"TTTT_Mu"+muID+"_El"+elID+".root";
  TFile* ttttfile = new TFile(ttttfilename.c_str());
  Sample* ttttSample = new Sample(vBkgNames.at(3),ttttfile, vWeights.at(3),vXsec.at(3),cut,kRed+2);
  vSample.push_back(ttttSample);


  std::string wzfilename=bgTestDir.c_str()+"WZ_Mu"+muID+"_El"+elID+".root";
  TFile* wzfile = new TFile(wzfilename.c_str());
  Sample* wzSample = new Sample(vBkgNames.at(4),wzfile, vWeights.at(4),vXsec.at(4),cut,kBlue-3);
  vSample.push_back(wzSample);

  //TFile* wjfile = new TFile(bgTestDir.c_str()+"WJets_Mu"+muID+"_El"+elID+".root");
  //Sample* wjSample = new Sample(vBkgNames.at(4),wjfile, vWeights.at(4),vXsec.at(4),cut,kGreen+2);
  //vSample.push_back(wjSample);

  /*std::string dyfilename =  bgTestDir.c_str()+"DYJets_Mu"+muID+"_El"+elID+".root";
  TFile* dyjfile = new TFile(dyfilename.c_str());
  Sample* dyjSample = new Sample(vBkgNames.at(3),dyjfile, vWeights.at(3),vXsec.at(3),cut,kMagenta+2);
  vSample.push_back(dyjSample);*/
  
  std::string zzfilename = bgTestDir.c_str()+"ZZ_Mu"+muID+"_El"+elID+".root";
  TFile* zzjfile = new TFile(zzfilename.c_str());
  Sample* zzjSample = new Sample(vBkgNames.at(5),zzjfile, vWeights.at(5),vXsec.at(5),cut,kOrange+1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(zzjSample);

  /*std::string vhfilename = bgTestDir.c_str()+"VH_Mu"+muID+"_El"+elID+".root";
  TFile* vhjfile = new TFile(vhfilename.c_str());
  Sample* vhjSample = new Sample(vBkgNames.at(6),vhjfile, vWeights.at(6),vXsec.at(6),cut,kBlue);
  //std::cout<<"weight for VH is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(vhjSample);*/

  std::string wpwpfilename = bgTestDir.c_str()+"WpWp_Mu"+muID+"_El"+elID+".root";
  TFile* wpwpfile = new TFile(wpwpfilename.c_str());
  Sample* wpwpSample = new Sample(vBkgNames.at(7),wpwpfile, vWeights.at(7),vXsec.at(7),cut,kGreen+1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(wpwpSample);

  /*std::string wwmpifilename = bgTestDir.c_str()+"WW-mpi_Mu"+muID+"_El"+elID+".root";
  TFile* wwmpifile = new TFile(wwmpifilename.c_str());
  Sample* wwmpiSample = new Sample(vBkgNames.at(8),wwmpifile, vWeights.at(8),vXsec.at(8),cut,kGreen-1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(wwmpiSample);*/


  std::string wwzfilename = bgTestDir.c_str()+"WWZ_Mu"+muID+"_El"+elID+".root";
  TFile* wwzfile = new TFile(wwzfilename.c_str());
  Sample* wwzSample = new Sample(vBkgNames.at(9),wwzfile, vWeights.at(9),vXsec.at(9),cut,kViolet+1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(wwzSample);

  std::string wzzfilename = bgTestDir.c_str()+"WZZ_Mu"+muID+"_El"+elID+".root";
  TFile* wzzfile = new TFile(wzzfilename.c_str());
  Sample* wzzSample = new Sample(vBkgNames.at(10),wzzfile, vWeights.at(10),vXsec.at(10),cut,kViolet+3);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(wzzSample);

  std::string zzzfilename = bgTestDir.c_str()+"ZZZ_Mu"+muID+"_El"+elID+".root";
  TFile* zzzfile = new TFile(zzzfilename.c_str());
  Sample* zzzSample = new Sample(vBkgNames.at(11),zzzfile, vWeights.at(11),vXsec.at(11),cut,kViolet);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(zzzSample);


  //********** Nonprompt ***************
  /*std::string npTTfilename = bgTestDir.c_str()+"NonPromptTTJets_Mu"+muID+"_El"+elID+".root";
  TFile* npttfile = new TFile(nptTfilename.c_str());
  Sample* npttSample = new Sample(vBkgNames.at(-1),npttfile,vWeights.at(-1),vXsec.at(01),cut,kBlue);
  vSample.push_back(npttSample)*/

  std::string npfilename = bgTestDir.c_str()+"NonPromptData_Mu"+muID+"_El"+elID+".root";
  TFile* npfile = new TFile(npfilename.c_str());
  Sample* npSample = new Sample(vBkgNames.at(12),npfile,vWeights.at(13),vXsec.at(13),cut,kGray);
  vSample.push_back(npSample);

  //********ChargeMisID**********
  std::string cmidfilename = bgTestDir.c_str()+"ChargeMisID_Mu"+muID+"_El"+elID+".root";
  TFile* cmidfile = new TFile(cmidfilename.c_str());
  Sample* cmidSample = new Sample(vBkgNames.at(13),cmidfile,vWeights.at(13),vXsec.at(13),cut,kAzure+6); //force charge misID to start here since only at this point do we filter events
  vSample.push_back(cmidSample);


  return vSample;

}


std::vector<std::string> getCutString(){

  std::vector<std::string> vString;

  //quarkonia-veto
  std::string null = "Lep1Pt>0";
  vString.push_back(null);
  std::string qv = "("+null+" && (DilepMass>20) )";
  vString.push_back(qv);
  //z mass veto for ee channel only
  std::string zv = "("+qv+" && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )";
  vString.push_back(zv);
  //Leading Lep pT
  std::string lep1pt = "("+zv+"&& Lep1Pt > 40)" ;
  vString.push_back(lep1pt);
  //SubLeadingLep pT
  //std::string lep2pt = "("+lep1pt+"&& Lep2Pt > 30)" ;
  //vString.push_back(lep2pt);
  //Leading nJetscut
  std::string nConstCut = "("+lep1pt+"&& nConst >= 5)";
  vString.push_back(nConstCut);
  //SubLeading Jet Pt
  //std::string jet2pt = "("+jet1pt+"&& cleanAK4Jet2Pt > 150)";
  //vString.push_back(jet2pt);
  //HT cut
  std::string htcut = "("+nConstCut+"&& cleanAK4HT > 900)";
  vString.push_back(htcut);
  return vString;
}

std::pair<float,float> getNEvtsAndError(Sample* s, std::string cut, int nMu, bool scale_){
  bool scale = scale_;
  TTree* t = s->tree;
  TH1F* hdummy = new TH1F("hdummy","hdummy",1,0,10000);
  hdummy->Sumw2();
  //make cut string based on channel, should always be outside of parantheses for other cuts so a simply && should work also apply chargeMisIDWeight
  std::stringstream channel;
  if(nMu>=0)  channel<<"&& (Channel =="<<nMu<<")";
  else  channel<<"";

  std::string cutstring= " PUWeight* trigSF * IDSF * IsoSF * MCWeight * ChargeMisIDWeight * NPWeight* ( "+cut+channel.str()+")";

  //draw the last variable to cut on just to be safe though it shouldn't matter
  t->Project("hdummy","AK4HT",cutstring.c_str());
  
  //std::cout<<"Sample: "<<s->name<<" and cut: "<<cutstring<<" unweighted events: "<<nEvts<<" weight: "<<s->weight<<std::endl;
  //now weight properly - for Data don't apply
  if( ( (s->name).find("NonPrompt")!=std::string::npos) && ((s->name).find("TTJets")==std::string::npos) ) { scale=false; }
  else if( ( (s->name).find("ChargeMisID")!=std::string::npos) && ((s->name).find("MC")==std::string::npos) ) { scale=false; }
  if(scale) hdummy->Scale(s->weight);
  float nEvts = hdummy->Integral(1,hdummy->GetNbinsX()+1);
  double_t err;
  hdummy->IntegralAndError(1,hdummy->GetNbinsX()+1,err);
  delete hdummy;
  std::pair<float,float> nEvtsAndError(nEvts,(float)err);
  return nEvtsAndError;
};



std::string getPrettyCutString(std::string cut){

  //find the positions of && in the cut string
  std::vector<size_t> positions; // holds all the positions that sub occurs within str

  size_t pos = cut.find("&&", 0);
  while(pos != std::string::npos)
    {
      positions.push_back(pos);
      pos = cut.find("&&",pos+1);
    }

  //now take the last of them since what we want is the cut applied to the right of the last &&
  if(positions.size()==0) return "SSDL";
  else if(positions.size()==2) return "EE-ZVeto";
  size_t last = positions.at(positions.size()-1);
  size_t length = cut.size() - last; //should give number of characters remaining in string
  length = length -3; //decrement by one to ignor final ')'
  
  std::string prettyString(cut, last+2, length);
  
  return prettyString;

};


CutClass* makeCutClass(Sample* s, std::vector<std::string> vCuts,int nMu)
{


  std::vector<float> vEvts,vErr;
  std::vector<std::string> vCutsPretty;

  for(size_t j=0; j < vCuts.size(); j++){
    
    //get number of events and save to vector - IMPORTANT TO DO THIS WITH THE FULL CUT STRING AND NOT A PRETTY VERSION
    bool scale = true; //helper function will set to false if need be
    std::pair<float,float> evtsAndErr = getNEvtsAndError(s, vCuts.at(j), nMu, scale);
    vEvts.push_back(evtsAndErr.first);
    vErr.push_back(evtsAndErr.second);
    //now trim the cuts string to write prettily
    
    std::string cutPretty = getPrettyCutString(vCuts.at(j));
    vCutsPretty.push_back(cutPretty);
  }

  CutClass* c = new CutClass(s->name,vCutsPretty,vEvts,vErr,s->xsec);
  return c;

};


std::vector<CutClass*> getCutClassVector(std::vector<Sample*> vS, std::vector<std::string> vCuts, int nMu){

  std::vector<CutClass*> vCC;

  for(size_t i =0; i < vS.size(); i++){
    CutClass* c = makeCutClass(vS.at(i),vCuts,nMu);
    vCC.push_back(c);
  }

  return vCC;

};


/*std::vector<float> getEtaWeights(TreeReader* tr, TTree* t, TFile* outfile){

  std::vector<float> etaWeights;

  //float xbins[9] = {-2.5,-2.1,-1.5,-0.9,0,0.9,1.5,2.1,2.5};

  TH1F* h_ss = new TH1F("h_ss","",15,-3,3);
  TH1F* h_all = new TH1F("h_all","",15,-3,3);
  TH1F* h_PairMass = new TH1F("h_PairMass","",50,50,150);
  int nEntries=t->GetEntries();



  for(int ient=0; ient<nEntries; ient++){

    float mindiff=9999;
    float pairmass=-9999;
    TElectron* El1;
    TElectron* El2;

    tr->GetEntry(ient);
    //run over good electrons and find pair closest to Z Mass
    for(size_t i=0; i< tr->goodElectrons.size(); i++){
      TElectron* el1 = tr->goodElectrons.at(i);
      for(size_t j=i+1; j<tr->goodElectrons.size(); j++){
	TElectron* el2 = tr->goodElectrons.at(j);
	float mass = (el1->lv + el2->lv).M();
	
	if( fabs( 91.1 - mass) < mindiff){
	  mindiff=fabs(91.1 - mass);
	  El1=el1;
	  El2=el2;
	  pairmass=mass;	  
	}

      }
      
    }

    bool inPeak=false;
    if(mindiff<20) inPeak=true; //also implies that a pair was found since requires min diff to be reset;
    //std::cout<<"size of goodEls: "<<tr->goodElectrons.size()<<"El 1 eta: "<<El1->eta<<" El2 eta: "<<El2->eta<<" mass: "<<pairmass<<" mindiff: "<<mindiff<<std::endl;
    
    h_PairMass->Fill(pairmass);
    if(!inPeak) continue;

    if(El1->charge == El2->charge){
      h_ss->Fill(El1->eta);
      h_ss->Fill(El2->eta);
    }

    h_all->Fill(El1->eta);
    h_all->Fill(El2->eta);


  }//end event loop

  outfile->WriteTObject(h_PairMass);
  outfile->WriteTObject(h_ss);
  outfile->WriteTObject(h_all);
  //scale by 1/2
  h_all->Sumw2();
  h_ss->Sumw2();
  h_ss->Scale(0.5);


  TGraphAsymmErrors* chargeMisIDgraph = new TGraphAsymmErrors(h_ss,h_all);

  outfile->WriteTObject(chargeMisIDgraph);

  for(size_t i=0; i< chargeMisIDgraph->GetN(); i++){
    etaWeights.push_back(chargeMisIDgraph->GetY()[i]);
    std::cout<<"Weight is: "<<chargeMisIDgraph->GetY()[i]<<std::endl;
  }

  std::cout<<"size of etaWeights: "<<etaWeights.size()<<std::endl;

  return etaWeights;

  }*/

std::vector<float> getEtaWeights_lpt(TFile* weightfile){
  
  //TGraphAsymmErrors* g = (TGraphAsymmErrors*) weightfile->Get("divide_etaNumHist_by_etaDenHist");
  TH1F* h = (TH1F*) weightfile->Get("etaNumHist_lpt");
  //TH1F* den = (TH1F*) weightfile->Get("etaDenHist");
  //h->Divide(den);
  std::vector<float> etaWeights;

  for(int i=1; i<= h->GetNbinsX(); i++){
    etaWeights.push_back(h->GetBinContent(i));
  }
  
  return etaWeights;
  
};

std::vector<float> getEtaWeights_hpt(TFile* weightfile){
  
  //TGraphAsymmErrors* g = (TGraphAsymmErrors*) weightfile->Get("divide_etaNumHist_by_etaDenHist");
  TH1F* h = (TH1F*) weightfile->Get("etaNumHist_hpt");
  //TH1F* den = (TH1F*) weightfile->Get("etaDenHist");
  //h->Divide(den);
  std::vector<float> etaWeights;

  for(int i=1; i<= h->GetNbinsX(); i++){
    etaWeights.push_back(h->GetBinContent(i));
  }
  
  return etaWeights;
  
};

float getEtaWeight(std::vector<float> etaWeights, std::vector<TLepton*> leptons){

  float weight1=1;
  float weight2=1;
  TLepton* Lep1=leptons.at(0);
  TLepton* Lep2=leptons.at(1);

  if(Lep1->isEl){
    if(Lep1->eta<-2.6) weight1 = 0;//no electrons greater than 2.6
    else if(Lep1->eta<-2.2) weight1 = weight1*etaWeights.at(0);
    else if(Lep1->eta<-1.8) weight1 = weight1*etaWeights.at(1);
    else if(Lep1->eta<-1.4) weight1 = weight1*etaWeights.at(2);
    else if(Lep1->eta< -1.0) weight1 = weight1*etaWeights.at(3);
    else if(Lep1->eta< -0.6) weight1 = weight1*etaWeights.at(4);
    else if(Lep1->eta< -0.2) weight1 = weight1*etaWeights.at(5);
    else if(Lep1->eta< 0.2) weight1 = weight1*etaWeights.at(6);
    else if(Lep1->eta< 0.6) weight1 = weight1*etaWeights.at(7);
    else if(Lep1->eta< 1.0) weight1 = weight1*etaWeights.at(8);
    else if(Lep1->eta< 1.4) weight1 = weight1*etaWeights.at(9);
    else if(Lep1->eta< 1.8) weight1 = weight1*etaWeights.at(10);
    else if(Lep1->eta< 2.2) weight1 = weight1*etaWeights.at(11);
    else if(Lep1->eta< 2.6) weight1 = weight1*etaWeights.at(12);
    else if(Lep1->eta< 3.0) weight1 = 0; //no electrons w/ eta greater than 2.6

  }

  if(Lep2->isEl){
    if(Lep2->eta<-2.6) weight2 = 0;//no electrons outside eta 2.6
    else if(Lep2->eta<-2.2) weight2 = weight2*etaWeights.at(0);
    else if(Lep2->eta<-1.8) weight2 = weight2*etaWeights.at(1);
    else if(Lep2->eta<-1.4) weight2 = weight2*etaWeights.at(2);
    else if(Lep2->eta< -1.0) weight2 = weight2*etaWeights.at(3);
    else if(Lep2->eta< -0.6) weight2 = weight2*etaWeights.at(4);
    else if(Lep2->eta< -0.2) weight2 = weight2*etaWeights.at(5);
    else if(Lep2->eta< 0.2) weight2 = weight2*etaWeights.at(6);
    else if(Lep2->eta< 0.6) weight2 = weight2*etaWeights.at(7);
    else if(Lep2->eta< 1.0) weight2 = weight2*etaWeights.at(8);
    else if(Lep2->eta< 1.4) weight2 = weight2*etaWeights.at(9);
    else if(Lep2->eta< 1.8) weight2 = weight2*etaWeights.at(10);
    else if(Lep2->eta< 2.2) weight2 = weight2*etaWeights.at(11);
    else if(Lep2->eta< 2.6) weight2 = weight2*etaWeights.at(12);
    else if(Lep2->eta< 3.0) weight2 = 0; //no electrons outside eta 2.6
  }


  float weight=1;
  if(Lep1->isEl && Lep2->isEl) weight = weight1 + weight2 - weight1*weight2;
  else if( (Lep1->isEl && !Lep2->isEl) || (!Lep1->isEl && Lep2->isEl) ){
    if(Lep1->isEl) weight = weight1;
    else weight = weight2;
  }


  return weight;

};

float getPairMass(TLepton* lep1, TLepton* lep2){

  float mass = (lep1->lv + lep2->lv).M();
  return mass;

}

float getPairMass(TLepton* lep1, TMuon* mu){
  float mass = (lep1->lv + mu->lv).M();
  return mass;
}

float getPairMass(TLepton* lep1, TElectron* el){
  float mass = (lep1->lv + el->lv).M();
  return mass;
}

float getPairMass(TMuon* mu1, TMuon* mu2){
  float mass = (mu1->lv + mu2->lv).M();
  return mass;
}

float getPairMass(TElectron* el1, TElectron* el2){
  float mass = (el1->lv + el2->lv).M();
  return mass;
}


float getPrate(TFile* f){

  TH1F* h1 = (TH1F*) f->Get("ptNumHist");
  TH1F* h2 = (TH1F*) f->Get("ptDenHist");
  
  float rate = (float) h1->GetEntries();
  rate = rate / h2->GetEntries();
  return rate;

}


//functions to get weights for tight/loose method
float getMuFakeRate(std::string ID){

  if(ID=="CBTight") return 0.371;
  else return 0.371;
}

float getMuPromptRate(std::string ID){

  if(ID=="CBTight") return 0.94;
  else return 0.94;
		      
}

float getElFakeRate(std::string ID){

  if(ID=="CBTight") return 0.43;
  else if(ID=="MVATightRC") return 0.298;
  else if(ID=="MVATightCC") return 0.298;
  else if(ID=="CBTightRC") return 0.43;
  else return 0.298;

}

float getElPromptRate(std::string ID){

  if(ID=="CBTight") return 0.7259;
  else if(ID=="MVATightRC") return 0.873;
  else if(ID=="MVATightCC") return 0.873;
  else if(ID=="CBTightRC") return 0.7259;
  else return 0.873;

}  

//method weights
//same flavor
float WeightSF_T0(float pr, float fr){
  float weight = (-1.0)*( pow( fr*pr,2)) / (pow( pr - fr, 2));
  return weight;
}

float WeightSF_T0(std::string elID, std::string muID, int nMu){
  float prate = nMu==2 ? getMuPromptRate(muID) : getElPromptRate(elID);
  float frate = nMu==2 ? getMuFakeRate(muID) : getElFakeRate(elID);
  float weight = WeightSF_T0(prate,frate);
  return weight;
}

float WeightSF_T1(float pr, float fr){
  float weight= (pr*pr * (fr - fr*fr) ) / (pow( (pr -fr),2) );
  return weight;
}

float WeightSF_T1(std::string elID, std::string muID, int nMu){
  float prate = nMu==2 ? getMuPromptRate(muID) : getElPromptRate(elID);
  float frate = nMu==2 ? getMuFakeRate(muID) : getElFakeRate(elID);
  float weight = WeightSF_T1(prate,frate);
  return weight;
}

float WeightSF_T2(float pr, float fr){
  float weight= ( (fr) / (pow( (pr -fr),2)) ) * ( fr*(pow(1.0-pr,2)) - 2.0*pr*(1.0-pr)*(1.0-fr) ) ;
  return weight;
}

float WeightSF_T2(std::string elID, std::string muID, int nMu){
  float prate = nMu==2 ? getMuPromptRate(muID) : getElPromptRate(elID);
  float frate = nMu==2 ? getMuFakeRate(muID) : getElFakeRate(elID);
  float weight = WeightSF_T2(prate,frate);
  return weight;
}


//opposite flavor
float WeightOF_T00(float elpr, float elfr, float mupr, float mufr){
  float weight = (-1.0 * elfr * elpr * mufr * mupr);
  weight = weight * ( 1.0 / ( (elpr - elfr)*(mupr-mufr)) );
  return weight;
}

float WeightOF_T00(std::string elID, std::string muID){

  float elpr = getElPromptRate(elID);
  float elfr = getElFakeRate(elID);
  float mupr = getMuPromptRate(muID);
  float mufr = getMuFakeRate(muID);

  float weight = WeightOF_T00(elpr,elfr,mupr,mufr);
  return weight;

}

float WeightOF_T10(float elpr, float elfr, float mupr, float mufr){
  float weight = elpr * ( 1.0 - elfr) * mupr * mufr;
  weight = weight * ( 1.0 / ( (elpr - elfr)*(mupr-mufr)) );
  return weight;

}

float WeightOF_T10(std::string elID, std::string muID){

  float elpr = getElPromptRate(elID);
  float elfr = getElFakeRate(elID);
  float mupr = getMuPromptRate(muID);
  float mufr = getMuFakeRate(muID);

  float weight = WeightOF_T10(elpr,elfr,mupr,mufr);
  return weight;

}

float WeightOF_T01(float elpr, float elfr, float mupr, float mufr){
  float weight = elpr * elfr * mupr * (1.0 - mufr);
  weight = weight * ( 1.0 / ( (elpr - elfr)*(mupr-mufr)) );
  return weight;
}

float WeightOF_T01(std::string elID, std::string muID){

  float elpr = getElPromptRate(elID);
  float elfr = getElFakeRate(elID);
  float mupr = getMuPromptRate(muID);
  float mufr = getMuFakeRate(muID);

  float weight = WeightOF_T01(elpr,elfr,mupr,mufr);
  return weight;

}


float WeightOF_T11(float elpr, float elfr, float mupr, float mufr){
  float weight = ( elfr*(1.0-elpr)*mufr*(1.0-mupr) ) - ( elfr*(1.0-elpr)*mupr*(1.0-mufr) )  - ( elpr*(1.0-elfr)*mufr*(1.0-mupr) ) ;
  weight = weight * ( 1.0 / ( (elpr - elfr)*(mupr-mufr)) );
  return weight;
}

float WeightOF_T11(std::string elID, std::string muID){

  float elpr = getElPromptRate(elID);
  float elfr = getElFakeRate(elID);
  float mupr = getMuPromptRate(muID);
  float mufr = getMuFakeRate(muID);

  float weight = WeightOF_T11(elpr,elfr,mupr,mufr);
  return weight;

}
float getTrigSF(std::vector<TLepton*> vLep){

  float sf;

  if(vLep.at(0)->isMu && vLep.at(1)->isMu){ //dimuon channel
    
    float eta1 = fabs(vLep.at(0)->eta);
    float eta2 = fabs(vLep.at(1)->eta);
    
    if(eta1 > 2.1){
      if(eta2>2.1) sf=0.955;
      else if(eta2>1.2) sf=0.958;
      else if(eta2>0.9) sf=0.962;
      else if(eta2>0.4) sf=0.979;
      else sf=0.991;
    }
    else if(eta1 > 1.2){
      if(eta2>2.1) sf=0.963;
      else if(eta2>1.2) sf=0.961;
      else if(eta2>0.9) sf=0.969;
      else if(eta2>0.4) sf=0.972;
      else sf=0.974;
    }
    else if(eta1 > 0.9){
      if(eta2>2.1) sf=0.966;
      else if(eta2>1.2) sf=0.969;
      else if(eta2>0.9) sf=0.973;
      else if(eta2>0.4) sf=0.978;
      else sf=0.975;
    }
    else if(eta1 > 0.4){
      if(eta2>2.1) sf=0.991;
      else if(eta2>1.2) sf=0.970;
      else if(eta2>0.9) sf=0.976;
      else if(eta2>0.4) sf=0.975;
      else sf=0.971;
    }
    else{
      if(eta2>2.1) sf=1.003;
      else if(eta2>1.2) sf=0.970;
      else if(eta2>0.9) sf=0.973;
      else if(eta2>0.4) sf=0.970;
      else sf=0.966;
    }
  }

  else if(vLep.at(0)->isEl && vLep.at(1)->isEl){//dielectron channel
    sf = 0.97;
  }
  else{ //cross channel
    sf = 0.999;
  }

  return sf;

}

float getLepIDSF(TLepton* lep){

  float sf;

  if(lep->isMu){
    if(lep->eta > 2.1){
      if(lep->pt>100) sf = 1.0028;
      else if(lep->pt>60) sf = 0.9724;
      else if(lep->pt>40) sf = 0.9851;
      else sf = 0.9818;
    }
    else if(lep->eta > 1.2){
      if(lep->pt>100) sf = 0.9987;
      else if(lep->pt>60) sf = 0.9929;
      else if(lep->pt>40) sf = 0.9947;
      else sf = 0.9929;
    }
    else if(lep->eta > 0.9){
      if(lep->pt>100) sf = 0.9757;
      else if(lep->pt>60) sf = 0.9696;
      else if(lep->pt>40) sf = 0.9746;
      else sf = 0.9724;
    }
    else if(lep->eta > 0.4){
      if(lep->pt>100) sf = 0.9754;
      else if(lep->pt>60) sf = 0.9875;
      else if(lep->pt>40) sf = 0.9898;
      else sf = 0.9869;
    }
    else if(lep->eta > 0.0){
      if(lep->pt>100) sf = 1.0165;
      else if(lep->pt>60) sf = 0.9896;
      else if(lep->pt>40) sf = 0.9877;
      else sf = 0.9847;
    }
    else if(lep->eta > -0.4){
      if(lep->pt>100) sf = 0.9985;
      else if(lep->pt>60) sf = 0.9885;
      else if(lep->pt>40) sf = 0.9874;
      else sf = 0.9878;
    }
    else if(lep->eta > -0.9){
      if(lep->pt>100) sf = 0.9951;
      else if(lep->pt>60) sf = 0.9854;
      else if(lep->pt>40) sf = 0.9920;
      else sf = 0.9909;
    }
    else if(lep->eta > -1.2){
      if(lep->pt>100) sf = 0.9876;
      else if(lep->pt>60) sf = 0.9873;
      else if(lep->pt>40) sf = 0.9886;
      else sf = 0.9828;
    }
    else if(lep->eta > -2.1){
      if(lep->pt>100) sf = 1.0039;
      else if(lep->pt>60) sf = 0.9923;
      else if(lep->pt>40) sf = 0.9922;
      else sf = 0.9910;
    }
    else if(lep->eta > -2.4){
      if(lep->pt>100) sf = 0.9738;
      else if(lep->pt>60) sf = 0.9600;
      else if(lep->pt>40) sf = 0.9793;
      else sf = 0.9812;
    }
  }
  else{//electron
    if(lep->eta>1.566){
      if(lep->pt>250) sf = 1.0271;
      else if(lep->pt>180) sf = 0.9987;
      else if(lep->pt>130) sf = 0.9597;
      else if(lep->pt>90)  sf = 1.0039;
      else if(lep->pt>70)  sf = 0.9843;
      else if(lep->pt>50)  sf = 0.9868;
      else if(lep->pt>40)  sf = 0.9835;
      else if(lep->pt>30)  sf = 0.9746;
    }
    else if(lep->eta > 1.442) sf = 0; //should never happen but this is dummy to prevent electrons in gap
    else if(lep->eta>0.8){
      if(lep->pt>250)      sf = 0.9443;
      else if(lep->pt>180) sf = 0.9824;
      else if(lep->pt>130) sf = 1.0141;
      else if(lep->pt>90)  sf = 0.9545;
      else if(lep->pt>70)  sf = 0.9846;
      else if(lep->pt>50)  sf = 0.9871;
      else if(lep->pt>40)  sf = 0.9814;
      else if(lep->pt>30)  sf = 0.9934;
    }
    else if(lep->eta>0.0){
      if(lep->pt>250)      sf = 0.9334;
      else if(lep->pt>180) sf = 0.9769;
      else if(lep->pt>130) sf = 0.9725;
      else if(lep->pt>90)  sf = 0.9963;
      else if(lep->pt>70)  sf = 0.9963;
      else if(lep->pt>50)  sf = 0.9657;
      else if(lep->pt>40)  sf = 0.9808;
      else if(lep->pt>30)  sf = 0.9990;
    }
    else if(lep->eta>-0.8){
      if(lep->pt>250)      sf = 0.9677;
      else if(lep->pt>180) sf = 0.999;
      else if(lep->pt>130) sf = 1.0176;
      else if(lep->pt>90)  sf = 0.9611;
      else if(lep->pt>70)  sf = 0.9742;
      else if(lep->pt>50)  sf = 0.9887;
      else if(lep->pt>40)  sf = 0.9794;
      else if(lep->pt>30)  sf = 0.9923;
    }
    else if(lep->eta>-1.442){
      if(lep->pt>250)      sf = 0.9274;
      else if(lep->pt>180) sf = 0.9556;
      else if(lep->pt>130) sf = 0.9915;
      else if(lep->pt>90)  sf = 1.0077;
      else if(lep->pt>70)  sf = 1.0008;
      else if(lep->pt>50)  sf = 0.9944;
      else if(lep->pt>40)  sf = 0.9849;
      else if(lep->pt>30)  sf = 0.9945;
    }
    else if(lep->eta > -1.566) sf = 0; //same dummy protection against gap as above
    else if(lep->eta>-2.4){
      if(lep->pt>250)      sf = 0.9205;
      else if(lep->pt>180) sf = 0.9118;
      else if(lep->pt>130) sf = 0.9978;
      else if(lep->pt>90)  sf = 0.9727;
      else if(lep->pt>70)  sf = 0.9762;
      else if(lep->pt>50)  sf = 0.9884;
      else if(lep->pt>40)  sf = 0.9663;
      else if(lep->pt>30)  sf = 0.9880;
    }
  }

  return sf;
}

float getLepIDSF(std::vector<TLepton*> vLep){

  float sf1,sf2;
  sf1 = getLepIDSF(vLep.at(0));
  sf2 = getLepIDSF(vLep.at(1));
  float sf = sf1*sf2;
  return sf;

}

float getLepIsoSF(TLepton* lep){

  float sf;
  if(lep->isMu) sf = 1.0; //no scale factor for muon iso
  else{
    if(fabs(lep->eta) > 1.566){
      if(lep->pt>50) sf = 1.00;
      else if(lep->pt>40) sf = 1.019;
      else if (lep->pt>30) sf = 1.000;
    }
    else{
      if(lep->pt>50) sf = 0.995;
      else if(lep->pt>40) sf = 0.995;
      else if (lep->pt>30) sf = 0.995;
    }
  }

  return sf;

}

float getLepIsoSF(std::vector<TLepton*> leps){

  float sf1 = getLepIsoSF(leps.at(0));
  float sf2 = getLepIsoSF(leps.at(1));
  float sf = sf1* sf2;
  return sf;

}

std::pair<float,float> getFakeRateByFlavor (std::string flavor){

  float mufr;
  float elfr;

  if(flavor=="data"){
    mufr=0.347;
    elfr=0.288;
  }

  if(flavor=="light"){
    mufr = 0.120;
    elfr = 0.209;
  }

  if(flavor=="charm"){
    mufr=0.376;
    elfr=0.215;
  }

  if(flavor=="bottom"){
    mufr=0.283;
    elfr=0.180;
  }
  if(flavor=="fakes"){
    mufr=0.109;
    elfr=0.278;
  }
  if(flavor=="average"){
    mufr=0.281;
    elfr=0.203;
  }
  if(flavor=="light_qcd"){
    mufr=0.193;
    elfr=0.585;
  }
  if(flavor=="charm_qcd"){
    mufr=0.330;
    elfr=0.323;
  }
  if(flavor=="bottom_qcd"){
    mufr=0.390;
    elfr=0.211;
  }
  if(flavor=="fakes_qcd"){
    mufr=0.354;
    elfr=0.374;
  }
  if(flavor=="average_qcd"){
    mufr=0.392;
    elfr=0.371;
  }

  if(flavor=="light_ttb"){
    mufr=0.405;
    elfr=0.249;
  }
  if(flavor=="charm_ttb"){
    mufr=0.376;
    elfr=0.209;
  }
  if(flavor=="bottom_ttb"){
    mufr=0.297;
    elfr=0.185;
  }
  if(flavor=="fakes_ttb"){
    mufr=0.117;
    elfr=0.263;
  }
  if(flavor=="unmatched_ttb"){
    mufr=0.692;
    elfr=0.116;
  }
  if(flavor=="average_ttb"){
    mufr=0.294;
    elfr=0.202;
  }


  std::pair<float,float> fr(mufr,elfr);
  return fr;
}

std::vector<float> weights_elel(std::string flavor){

  std::vector<float> weights;
  float elfr = getFakeRateByFlavor(flavor).second;
  float elpr = getElPromptRate("MVATightRC");
  //dielectron channel so only same flavor weights, order is 0: nt00, 1: nt01, 2: nt10, 3: nt11
  weights.push_back(WeightSF_T0(elpr,elfr));
  weights.push_back(WeightSF_T1(elpr,elfr));
  weights.push_back(WeightSF_T1(elpr,elfr));
  weights.push_back(WeightSF_T2(elpr,elfr));
  return weights;
}

std::vector<float> weights_elmu(std::string flavor){

  std::vector<float> weights;
  float elfr = getFakeRateByFlavor(flavor).second;
  float elpr = getElPromptRate("MVATightRC");
  float mufr = getFakeRateByFlavor(flavor).first;
  float mupr = getMuPromptRate("CBTight");

  //cross channel, but order remains the same
  weights.push_back(WeightOF_T00(elpr,elfr,mupr,mufr));
  weights.push_back(WeightOF_T01(elpr,elfr,mupr,mufr));
  weights.push_back(WeightOF_T10(elpr,elfr,mupr,mufr));
  weights.push_back(WeightOF_T11(elpr,elfr,mupr,mufr));

  return weights;
}

std::vector<float> weights_mumu(std::string flavor){

  std::vector<float> weights;
  float mufr = getFakeRateByFlavor(flavor).first;
  float mupr = getMuPromptRate("MVATightRC");
  //dimuectron channel so only same flavor weights, order is 0: nt00, 1: nt01, 2: nt10, 3: nt11
  weights.push_back(WeightSF_T0(mupr,mufr));
  weights.push_back(WeightSF_T1(mupr,mufr));
  weights.push_back(WeightSF_T1(mupr,mufr));
  weights.push_back(WeightSF_T2(mupr,mufr));
  return weights;
}

float getPUWeight(TH1F* h, int nPU){

  float weight = -1;
  weight = h->GetBinContent(nPU+1); // plus one because 1st bin is 0-0.9999 so pilupe of 1 falls in bin 2
  //std::cout<<"nInteractions: "<<nPU<<" and weight: "<<weight<<std::endl;
  return weight;

};



std::vector<TH1F*> initHistos(std::vector<Variable*> vVar, int nMu, std::string cutname){

  //make vector
  std::vector<TH1F*> hists;
  std::string chan ="";
  if(nMu==-1) chan ="All";
  if(nMu==0) chan ="ElEl";
  if(nMu==1) chan ="ElMu";
  if(nMu==2) chan ="MuMu";  
  
  for(unsigned int i=0; i< vVar.size(); i++){
    Variable* var = vVar.at(i);
    std::string histname = chan+"_"+cutname+"_"+var->name;
    hists.push_back(new TH1F(histname.c_str(),(var->name).c_str(), var->nbins, var->xmin, var->xmax));
  }
  for(unsigned int i=0; i< hists.size();i++){
    //save weights
    hists.at(i)->Sumw2();
  }
  return hists;

};


void fillHistos(std::vector<TH1F*> hists,std::vector<TLepton*> vSSLep, std::vector<TLepton*> vNonSSLep, std::vector<TJet*> jets, float MET, float DilepMass, float weight){
  
  
  //make nConst and HT
  int nConst = vNonSSLep.size() + jets.size();
  float HT = vSSLep.at(0)->pt + vSSLep.at(1)->pt;
  for(unsigned int i=0; i< vNonSSLep.size(); i++){
    HT = HT + vNonSSLep.at(i)->pt;
  }
  for(unsigned int i=0; i< jets.size(); i++){
    HT = HT + jets.at(i)->pt;
  }
  
  //fill histograms
  for(unsigned int i=0; i<hists.size(); i++){
   
    std::string title = hists.at(i)->GetTitle();
    if(title=="Lep1Pt") hists.at(i)->Fill(vSSLep.at(0)->pt,weight);
    if(title=="Lep1Eta") hists.at(i)->Fill(vSSLep.at(0)->eta,weight);
    if(title=="Lep1Phi") hists.at(i)->Fill(vSSLep.at(0)->phi,weight);
    
    if(title=="Lep2Pt") hists.at(i)->Fill(vSSLep.at(1)->pt,weight);
    if(title=="Lep2Eta") hists.at(i)->Fill(vSSLep.at(1)->eta,weight);
    if(title=="Lep2Phi") hists.at(i)->Fill(vSSLep.at(1)->phi,weight);
    
    if(title=="cleanAK4Jet1Pt") {
      if(jets.size() >0) hists.at(i)->Fill(jets.at(0)->pt,weight);
      else hists.at(i)->Fill(-999,weight);
    }
    if(title=="cleanAK4Jet1Eta") {
      if(jets.size() >0) hists.at(i)->Fill(jets.at(0)->eta,weight);
      else hists.at(i)->Fill(-999,weight);
    }
    if(title=="cleanAK4Jet1Phi"){
      if(jets.size() >0) hists.at(i)->Fill(jets.at(0)->phi,weight);
      else hists.at(i)->Fill(-999,weight);
    }
    
    if(title=="cleanAK4Jet2Pt"){
      if(jets.size()>1) hists.at(i)->Fill(jets.at(1)->pt,weight);
      else hists.at(i)->Fill(-999,weight);
    }
    if(title=="cleanAK4Jet2Eta"){
      if(jets.size()>1) hists.at(i)->Fill(jets.at(1)->eta,weight);
      else hists.at(i)->Fill(-999,weight);
    }
    if(title=="cleanAK4Jet2Phi"){
      if(jets.size()>1) hists.at(i)->Fill(jets.at(1)->phi,weight);
      else hists.at(i)->Fill(-999,weight);
    }
    
    if(title=="cleanAK4HT") hists.at(i)->Fill(HT,weight);
    if(title=="nCleanAK4Jets") hists.at(i)->Fill(jets.size(),weight);
    if(title=="nNonSSLeps") hists.at(i)->Fill(vNonSSLep.size(),weight);
    if(title=="MET") hists.at(i)->Fill(MET,weight);
    if(title=="DilepMass") hists.at(i)->Fill(DilepMass,weight);
    if(title=="nConst") hists.at(i)->Fill(nConst,weight);
    
    
  }
  
  
};
		      
void writeHistos(TFile* f, std::vector<TH1F*> hists){

  for(unsigned int i=0; i< hists.size();i++){
    f->WriteTObject(hists.at(i));
  }
};
