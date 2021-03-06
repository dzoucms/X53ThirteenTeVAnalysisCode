#ifndef TreeMaker_h
#define TreeMaker_h

#include "TTree.h"
#include "TreeReader.h"
#include "TLepton.h"
#include "TJet.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

class TreeMaker {

 public:

  //constructor and destructor
  TreeMaker();
  virtual ~TreeMaker();

  //TTree
  TTree* tree;

  //weight
  float weight_;
  int MCWeight_;
  //non prompt weight from tight/loos method;
  float NPWeight_;
  int nTL_;
  //scale factors for mc
  float trigSF_;
  float IDSF_;
  float IsoSF_;

  float puweight_;

  //variables for tree
  float Lep1Pt_;
  float Lep1Eta_;
  float Lep1Phi_;
  float Lep1Energy_;
  int Lep1Flavor_;
  int Lep1Charge_;
  int Lep1Loose_;
  int Lep1Tight_;

  float Lep2Pt_;
  float Lep2Eta_;
  float Lep2Phi_;
  float Lep2Energy_;
  int Lep2Flavor_;
  int Lep2Charge_;
  int Lep2Loose_;
  int Lep2Tight_;

  int nConst_;
  int nAK4Jets_;

  float AK4HT_;
  float MET_;
  float DilepMass_;
  float AssocMass_;
  float AK4Jet1Pt_;
  float AK4Jet1Eta_;
  float AK4Jet1Phi_;
  float AK4Jet1Energy_;

  float AK4Jet2Pt_;
  float AK4Jet2Eta_;
  float AK4Jet2Phi_;
  float AK4Jet2Energy_;

  //collections for cleaned jets
  float cleanAK4Jet1Pt_;
  float cleanAK4Jet1Eta_;
  float cleanAK4Jet1Phi_;
  float cleanAK4Jet1Energy_;

  float cleanAK4Jet2Pt_;
  float cleanAK4Jet2Eta_;
  float cleanAK4Jet2Phi_;
  float cleanAK4Jet2Energy_;

  int nCleanAK4Jets_;
  float cleanAK4HT_;

  //collections for simple cleaned jets
  float simpleCleanAK4Jet1Pt_;
  float simpleCleanAK4Jet1Eta_;
  float simpleCleanAK4Jet1Phi_;
  float simpleCleanAK4Jet1Energy_;

  float simpleCleanAK4Jet2Pt_;
  float simpleCleanAK4Jet2Eta_;
  float simpleCleanAK4Jet2Phi_;
  float simpleCleanAK4Jet2Energy_;

  int nSimpleCleanAK4Jets_;
  float simpleCleanAK4HT_;


  int nMu_; //the number of same-sign dileptons which are muons acts as standin for channel


  //functions
  //WriteHists(TreeReader* tr, TTree* t, std::vector<TLepton*> vSSLep);
  void InitTree(std::string treename);
  void FillTree(std::vector<TLepton*> vSSLep, std::vector<TJet*> AK4jets, std::vector<TJet*> cleanAK4jets, std::vector<TJet*> simpleCleanAK4Jets, float HTtemp, float METtemp, float DilepMasstemp, int nMu, float weight,std::vector<TLepton*> vNonSSLep,float mcweight, float NpWeighttemp, int nTLtemp,float trSF, float idSF, float isoSF,float puwtemp,float amasst);

};


#endif
