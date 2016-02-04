#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <map>
#include <string>
#include <sstream> 
#include <algorithm>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TChain.h"

#include "../interface/TreeReader.h"
#include "JetAnalyzer.cc"
#include "GenAnalyzer.cc"
#include "../interface/TreeMaker.h"
#include "../plugins/Macros.cc"
#include "../plugins/EventFilterFromFile_MuonEG.cc"
#include "../plugins/EventFilterFromFile_DoubleMu.cc"
#include "../plugins/EventFilterFromFile_DoubleEG.cc"
//#include "../plugins/EventFilterFromFile_CSC.cc"
#include "../plugins/EventFilterFromFile_ECALSC.cc"
#include "../plugins/EventFilterFromVector.cc"
#include "../plugins/ReadEventFilterFromFile.cc"

std::vector<TLepton*> makeLeptons(std::vector<TMuon*>, std::vector<TElectron*>, float, std::string, std::string, bool);
std::vector<TLepton*> makeSSLeptons(std::vector<TLepton*>);
std::vector<TLepton*> makeOSLeptonsForDY(std::vector<TLepton*>);
bool checkSameSignLeptons(std::vector<TLepton*>);
bool checkOppositeSignLeptonsForDY(std::vector<TLepton*>);
int getNSSDLGen(std::vector<TGenParticle*>, int);
void printParticle(TGenParticle*);
void printParticle(TLepton*);
std::pair<bool,float> checkSecondaryZVeto(std::vector<TLepton*> leps, std::vector<TMuon*> muons, std::vector<TElectron*> electrons);
std::vector<TLepton*> pruneSSLep(std::vector<TLepton*> allLeps, std::vector<TLepton*> ssLeps);
bool sortByPt(TLepton* lep1, TLepton* lep2){return lep1->pt > lep2->pt;};

int main(int argc, char* argv[]){


  if(argc!=4) return 0;
  std::string argv1=argv[1];
  std::string elID = argv[2];
  std::string muID = argv[3];

  typedef std::map<std::string,std::string> StringMap;
  
  StringMap bg_samples, sig_samples,data_samples;
  bg_samples["TTJets"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_TTJets.root";
  bg_samples["TTbar"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_TTbar.root";
  bg_samples["TTbar_ext1"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_TTbar_ext1.root";
  bg_samples["TTbar_ext2"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_TTbar_ext2.root";
  bg_samples["TTW"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_TTW.root";
  bg_samples["TTZ"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_TTZ.root";
  bg_samples["TTH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_TTH.root";
  bg_samples["TTTT"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_TTTT.root";
  bg_samples["TTWW"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_TTWW.root";
  bg_samples["WW"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_WW.root";
  bg_samples["WWW"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_WWW.root";
  bg_samples["WWZ"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_WWZ.root";
  bg_samples["WZZ"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_WZZ.root";
  bg_samples["ZZZ"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_ZZZ.root";
  bg_samples["WZ"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_WZ.root";
  bg_samples["WZ_MiniAODv1"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_WZ_MiniAODv1.root";
  bg_samples["ZZ"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_ZZ.root";
  bg_samples["VH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_VH.root";
  bg_samples["WJets"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_WJets.root";
  bg_samples["DYJets"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_DYJets.root";
  bg_samples["WpWp"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_WpWp.root";
  bg_samples["WW-mpi"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_WW-mpi.root";

  //nonoPrompt versions
  bg_samples["NonPromptTTJets"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_TTJets.root";
  bg_samples["NonPromptWJets"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_WJets.root";
  bg_samples["NonPromptTTbar"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_TTbar.root";
  bg_samples["NonPromptTTbar_ext1"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_TTbar_ext1.root";
  bg_samples["NonPromptTTbar_ext2"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_TTbar_ext2.root";

  
  sig_samples["X53X53m700RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m700RH.root";
  sig_samples["X53X53m800RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m800RH.root";
  sig_samples["X53X53m900RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m900RH.root";
  //sig_samples["X53X53m1000RH"]="ljmet_X53X53m1000RH.root";
  sig_samples["X53X53m1000RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1000RH.root";
  sig_samples["X53X53m1100RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1100RH.root";
  sig_samples["X53X53m1200RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1200RH.root";
  sig_samples["X53X53m1300RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1300RH.root";
  sig_samples["X53X53m1400RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1400RH.root";
  sig_samples["X53X53m1500RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1500RH.root";
  sig_samples["X53X53m1600RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1600RH.root";
  sig_samples["X53X53m700LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m700LH.root";
  sig_samples["X53X53m800LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m800LH.root";
  sig_samples["X53X53m900LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m900LH.root";
  sig_samples["X53X53m1000LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1000LH.root";
  sig_samples["X53X53m1100LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1100LH.root";
  sig_samples["X53X53m1200LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1200LH.root";
  sig_samples["X53X53m1300LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1300LH.root";
  sig_samples["X53X53m1400LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1400LH.root";
  sig_samples["X53X53m1500LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1500LH.root";
  sig_samples["X53X53m1600LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1600LH.root";

  sig_samples["X53X53m700RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m700RH_Inc.root";
  sig_samples["X53X53m800RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m800RH_Inc.root";
  sig_samples["X53X53m900RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m900RH_Inc.root";
  sig_samples["X53X53m1000RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1000RH_Inc.root";
  sig_samples["X53X53m1100RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1100RH_Inc.root";
  sig_samples["X53X53m1200RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1200RH_Inc.root";
  sig_samples["X53X53m1300RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1300RH_Inc.root";
  sig_samples["X53X53m1400RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1400RH_Inc.root";
  sig_samples["X53X53m1500RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1500RH_Inc.root";
  sig_samples["X53X53m1600RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1600RH_Inc.root";
  sig_samples["X53X53m700LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m700LH_Inc.root";
  sig_samples["X53X53m800LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m800LH_Inc.root";
  sig_samples["X53X53m900LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m900LH_Inc.root";
  sig_samples["X53X53m1000LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1000LH_Inc.root";
  sig_samples["X53X53m1100LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1100LH_Inc.root";
  sig_samples["X53X53m1200LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1200LH_Inc.root";
  sig_samples["X53X53m1300LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1300LH_Inc.root";
  sig_samples["X53X53m1400LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1400LH_Inc.root";
  sig_samples["X53X53m1500LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1500LH_Inc.root";
  sig_samples["X53X53m1600LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53X53m1600LH_Inc.root";

  // Dave ljmet trees PHYS14
  sig_samples["X53Tm700RH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-700_right_Tune4C_13TeV-madgraph-tauola.root";   
  sig_samples["X53Tm800RH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-800_right_Tune4C_13TeV-madgraph-tauola.root";   
  sig_samples["X53Tm900RH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-900_right_Tune4C_13TeV-madgraph-tauola.root";   
  sig_samples["X53Tm1000RH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1000_right_Tune4C_13TeV-madgraph-tauola.root";
  sig_samples["X53Tm1100RH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1100_right_Tune4C_13TeV-madgraph-tauola.root";
  sig_samples["X53Tm1200RH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1200_right_Tune4C_13TeV-madgraph-tauola.root";
  sig_samples["X53Tm1300RH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1300_right_Tune4C_13TeV-madgraph-tauola.root";
  sig_samples["X53Tm1400RH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1400_right_Tune4C_13TeV-madgraph-tauola.root";
  sig_samples["X53Tm1500RH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1500_right_Tune4C_13TeV-madgraph-tauola.root";
  sig_samples["X53Tm1600RH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1600_right_Tune4C_13TeV-madgraph-tauola.root";
  sig_samples["X53Tm700LH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-700_left_Tune4C_13TeV-madgraph-tauola.root";    
  sig_samples["X53Tm800LH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-800_left_Tune4C_13TeV-madgraph-tauola.root";    
  sig_samples["X53Tm900LH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-900_left_Tune4C_13TeV-madgraph-tauola.root";    
  sig_samples["X53Tm1000LH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1000_left_Tune4C_13TeV-madgraph-tauola.root";  
  sig_samples["X53Tm1100LH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1100_left_Tune4C_13TeV-madgraph-tauola.root";  
  sig_samples["X53Tm1200LH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1200_left_Tune4C_13TeV-madgraph-tauola.root";  
  sig_samples["X53Tm1300LH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1300_left_Tune4C_13TeV-madgraph-tauola.root";  
  sig_samples["X53Tm1400LH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1400_left_Tune4C_13TeV-madgraph-tauola.root";  
  sig_samples["X53Tm1500LH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1500_left_Tune4C_13TeV-madgraph-tauola.root";  
  sig_samples["X53Tm1600LH"]="/eos/uscms/store/user/lpctlbsm/dzou/PHYS14/Single_SSDL/PU20/ljmet_trees/ljmet_tree_T53TTo2L2Nu_M-1600_left_Tune4C_13TeV-madgraph-tauola.root";

  /*  
  sig_samples["X53Tm700RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-700_right.root";
  sig_samples["X53Tm800RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-800_right.root";
  sig_samples["X53Tm900RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-900_right.root";
  sig_samples["X53Tm1000RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1000_right.root";
  sig_samples["X53Tm1100RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1100_right.root";
  sig_samples["X53Tm1200RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1200_right.root";
  sig_samples["X53Tm1300RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1300_right.root";
  sig_samples["X53Tm1400RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1400_right.root";
  sig_samples["X53Tm1500RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1500_right.root";
  sig_samples["X53Tm1600RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1600_right.root";
  sig_samples["X53Tm700LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-700_left.root";
  sig_samples["X53Tm800LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-800_left.root";
  sig_samples["X53Tm900LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-900_left.root";
  sig_samples["X53Tm1000LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1000_left.root";
  sig_samples["X53Tm1100LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1100_left.root";
  sig_samples["X53Tm1200LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1200_left.root";
  sig_samples["X53Tm1300LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1300_left.root";
  sig_samples["X53Tm1400LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1400_left.root";
  sig_samples["X53Tm1500LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1500_left.root";
  sig_samples["X53Tm1600LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Approval/ljmet_trees/ljmet_X53TToAll_M-1600_left.root";
  */

  //data samples
  data_samples["Data"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Nov17/ljmet_trees/ljmet_Data_All.root";
  data_samples["DataElEl"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Nov17/ljmet_trees/ljmet_Data_ElEl.root";
  data_samples["DataElMu"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Nov17/ljmet_trees/ljmet_Data_ElMu.root";
  data_samples["DataMuMu"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Nov17/ljmet_trees/ljmet_Data_MuMu.root";
  data_samples["NonPromptData"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Nov17/ljmet_trees/ljmet_Data_All.root";
  data_samples["NonPromptDataElEl"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Nov17/ljmet_trees/ljmet_Data_ElEl.root";
  data_samples["NonPromptDataElMu"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Nov17/ljmet_trees/ljmet_Data_ElMu.root";
  data_samples["NonPromptDataMuMu"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Nov17/ljmet_trees/ljmet_Data_MuMu.root";

  data_samples["ChargeMisID"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Nov17/ljmet_trees/ljmet_Data_All.root";
  data_samples["ChargeMisIDElEl"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Nov17/ljmet_trees/ljmet_Data_ElEl.root";
  data_samples["ChargeMisIDElMu"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Nov17/ljmet_trees/ljmet_Data_ElMu.root";

  bool signal=false;
  bool bg_mc=false;
  bool bg_np = false; //bool to run  using tight loose method to get non prompt background
  //bool bg_dd=false;
  bool data=false;

  //check usage
  bool correctusage=true;
  if(argc!=4 || ( bg_samples.find(argv[1])==bg_samples.end() && sig_samples.find(argv[1])==sig_samples.end() && data_samples.find(argv[1])==data_samples.end() && argv1!="NonPromptMC") ) correctusage=false;
  if(!correctusage){
    std::cout<<"Need to specify electron and muon ID as well as supply argument for sample name of one of the following"<<std::endl;
    std::cout<<std::endl<<"********** Background *********"<<std::endl;
    for(std::map<std::string,std::string>::iterator iter=bg_samples.begin(); iter!= bg_samples.end(); iter++){
      std::cout<<iter->first<<std::endl;
    }
    std::cout<<std::endl<<"********** Signal *********"<<std::endl;
    for(std::map<std::string,std::string>::iterator iter=sig_samples.begin(); iter!= sig_samples.end(); iter++){
      std::cout<<iter->first<<std::endl;
    }  
    std::cout<<"********* OR Specify \'NonPromptMC\' to run over MC using Data-Driven Method"<<std::endl;
    std::cout<<" Examples:\n       ./X53Analyzer.o TTJets CBTight CBMed\n       ./X53Analyzer.o NonPromptMC MVATight CBTight"<<std::endl;
    return 0;
  }

  if(bg_samples.find(argv[1])!=bg_samples.end()) bg_mc=true;
  if(sig_samples.find(argv[1])!=sig_samples.end()) signal=true;
  if(data_samples.find(argv[1])!=data_samples.end()) data=true;
  std::string sample = argv[1];
  if(sample.find("NonPrompt")!=std::string::npos) bg_np = true;
  
  //make TreeReader
  std::string filename;
  if(bg_mc) filename = bg_samples.find(argv[1])->second;
  if(signal) filename = sig_samples.find(argv[1])->second;
  if(data) filename = data_samples.find(argv[1])->second;
  if(bg_np)  std::cout<<"running NonPrompt on  file: "<<filename<<std::endl;
  else  std::cout<<"running RegularMethod  on  file: "<<filename<<std::endl;

  //make output file
  std::stringstream outnamestream;
  if(bg_np){
    outnamestream<<argv[1]<<"_Mu"<<muID<<"_El"<<elID<<".root";
  }
  else{
    outnamestream<<argv[1]<<"_Mu"<<muID<<"_El"<<elID<<".root";
  }
  std::string outname = outnamestream.str();
  TFile* fsig = new TFile(outname.c_str(),"RECREATE");

  TreeMaker* tm_ssdl = new TreeMaker();
  tm_ssdl->InitTree("tEvts_ssdl");
  TreeMaker* tm_sZVeto = new TreeMaker();
  tm_sZVeto->InitTree("tEvts_sZVeto");
  TreeMaker* tm_DilepMassCut = new TreeMaker();
  tm_DilepMassCut->InitTree("tEvts_DilepMassCut");

  TreeReader* tr;
  tr = new TreeReader(filename.c_str(),!data);
  
  TTree* t=tr->tree;

  //histogram for cutflow
  TH1F* h_MuCutFlow = new TH1F("h_MuCutFlow","Cut Flow For Muons",13,0,13);

  //histogram for trigger studies
  TH1F* h_DoubleEle33Num = new TH1F("h_DoubleEle33Num","",60,0,600);
  TH1F* h_DoubleEle33_MWNum = new TH1F("h_DoubleEle33_MWNum","",60,0,600);
  TH1F* h_Ele27WP85Num = new TH1F("h_Ele27WP85Num","",60,0,600);
  TH1F* h_Mu30TkMu11Num = new TH1F("h_Mu30TkMu11Num","",60,0,600);
  TH1F* h_Mu40Num = new TH1F("h_Mu40Num","",60,0,600);
  TH1F* h_IsoTkMu24Num = new TH1F("h_IsoTkMu24Num","",60,0,600);
  TH1F* h_DoubleMu33NoFiltersNoVtxNum = new TH1F("h_DoubleMu33NoFiltersNoVtxNum","",60,0,600);
  TH1F* h_Mu23Ele12Num = new TH1F("h_Mu23Ele12Num","",60,0,600);
  TH1F* h_Mu8Ele23Num = new TH1F("h_Mu8Ele23Num","",60,0,600);
  TH1F* h_PFHT900Num = new TH1F("h_PFHT900Num","",60,0,600);
  TH1F* h_AK8PFJet360TrimMass30Num = new TH1F("h_AK8PFJet360TrimMass30Num","",60,0,600);

  TH1F* h_DoubleEle33Den = new TH1F("h_DoubleEle33Den","",60,0,600);
  TH1F* h_DoubleEle33_MWDen = new TH1F("h_DoubleEle33_MWDen","",60,0,600);
  TH1F* h_Ele27WP85Den = new TH1F("h_Ele27WP85Den","",60,0,600);
  TH1F* h_Mu30TkMu11Den = new TH1F("h_Mu30TkMu11Den","",60,0,600);
  TH1F* h_Mu40Den = new TH1F("h_Mu40Den","",60,0,600);
  TH1F* h_IsoTkMu24Den = new TH1F("h_IsoTkMu24Den","",60,0,600);
  TH1F* h_DoubleMu33NoFiltersNoVtxDen = new TH1F("h_DoubleMu33NoFiltersNoVtxDen","",60,0,600);
  TH1F* h_Mu23Ele12Den = new TH1F("h_Mu23Ele12Den","",60,0,600);
  TH1F* h_Mu8Ele23Den = new TH1F("h_Mu8Ele23Den","",60,0,600);
  TH1F* h_PFHT900Den = new TH1F("h_PFHT900Den","",60,0,600);
  TH1F* h_AK8PFJet360TrimMass30Den = new TH1F("h_AK8PFJet360TrimMass30Den","",60,0,600);

  //get vector of histograms for nonprompt
  std::vector<TH1F*> npHistos_all  = getNPHistos(-1);
  std::vector<TH1F*> npHistos_ee   = getNPHistos(0);
  std::vector<TH1F*> npHistos_emu  = getNPHistos(1);
  std::vector<TH1F*> npHistos_mumu = getNPHistos(2);

  //histogram for pdf uncertainties
  TH2F* hist_pdfHT = new TH2F("hist_pdfHT","PDF Weights",500,0,5,30,0,3000);
  //histogram for scale uncertainties - one for all and then separate ones
  TH2F* hist_scaleHT = new TH2F("hist_scaleHT","MC Scale Uncertainties Combined",500,0,5,30,0,3000);//total
  TH1F* hist_scaleHT_nom = new TH1F("hist_scaleHT_nom","MC Scale Uncertainties ID:Nominal",30,0,3000);//1002
  TH1F* hist_scaleHT_1002 = new TH1F("hist_scaleHT_1002","MC Scale Uncertainties ID:1002",30,0,3000);//1002
  TH1F* hist_scaleHT_1003 = new TH1F("hist_scaleHT_1003","MC Scale Uncertainties ID:1003",30,0,3000);//1003
  TH1F* hist_scaleHT_1004 = new TH1F("hist_scaleHT_1004","MC Scale Uncertainties ID:1004",30,0,3000);//1004
  TH1F* hist_scaleHT_1005 = new TH1F("hist_scaleHT_1005","MC Scale Uncertainties ID:1005",30,0,3000);//1005
  TH1F* hist_scaleHT_1007 = new TH1F("hist_scaleHT_1007","MC Scale Uncertainties ID:1007",30,0,3000);//1007
  TH1F* hist_scaleHT_1009 = new TH1F("hist_scaleHT_1009","MC Scale Uncertainties ID:1009",30,0,3000);//1009

  TH1F* hist_scaleHT_ssdl_nom = new TH1F("hist_scaleHT_ssdl_nom","MC Scale Uncertainties ID:Nominal",30,0,3000);//1002
  TH1F* hist_scaleHT_ssdl_1002 = new TH1F("hist_scaleHT_ssdl_1002","MC Scale Uncertainties ID:1002",30,0,3000);//1002
  TH1F* hist_scaleHT_ssdl_1003 = new TH1F("hist_scaleHT_ssdl_1003","MC Scale Uncertainties ID:1003",30,0,3000);//1003
  TH1F* hist_scaleHT_ssdl_1004 = new TH1F("hist_scaleHT_ssdl_1004","MC Scale Uncertainties ID:1004",30,0,3000);//1004
  TH1F* hist_scaleHT_ssdl_1005 = new TH1F("hist_scaleHT_ssdl_1005","MC Scale Uncertainties ID:1005",30,0,3000);//1005
  TH1F* hist_scaleHT_ssdl_1007 = new TH1F("hist_scaleHT_ssdl_1007","MC Scale Uncertainties ID:1007",30,0,3000);//1007
  TH1F* hist_scaleHT_ssdl_1009 = new TH1F("hist_scaleHT_ssdl_1009","MC Scale Uncertainties ID:1009",30,0,3000);//1009



  //load eta weights in:
  std::string cmidFilename = "ChargeMisID_Data_Run2015D_Electrons_"+elID+".root";
  TFile* eWfile = new TFile(cmidFilename.c_str());
  std::vector<float> etaWeights_lpt = getEtaWeights_lpt(eWfile);
  std::vector<float> etaWeights_hpt = getEtaWeights_hpt(eWfile);

  //load pileup hist
  TFile* fpu = new TFile("PileupWeights.root");
  TH1F* hpu = (TH1F*) fpu->Get("h_weights");
  

  //get fake rate according to ID
  float muPromptRate;
  if(muID=="CBTight") muPromptRate=0.940;
  else if(muID=="CBTightMiniIso") muPromptRate=0.940;
  else{ std::cout<<"Didn't pick a valid muon ID. Exiting..."<<std::endl; return 0;}

  //get electron fake rate
  float elPromptRate;
  if(elID=="CBTight" || elID=="CBTightRC") elPromptRate = 0.7259;
  else if(elID=="MVATightCC" || elID=="MVATightRC") elPromptRate = 0.873;
  else if(elID=="MVATightNew" || elID=="MVATightNewRC") elPromptRate = 0.8618;
  else if(elID=="SUSYTight" || elID=="SUSYTightRC") elPromptRate = 0.7956;
  else{std::cout<<"Didn't pick a valid electron ID. Exiting..."<<std::endl; return 0;}

  //get fake rate according to ID
  float muFakeRate;
  if(muID=="CBTight") muFakeRate=0.371;
  else if(muID=="CBTightMiniIso") muFakeRate=0.371;
  else{ std::cout<<"Didn't pick a valid muon ID. Exiting..."<<std::endl; return 0;}

  //get electron fake rate
  float elFakeRate;
  if(elID=="CBTight" || elID=="CBTightRC") elFakeRate = 0.43;
  else if(elID=="MVATightCC" || elID=="MVATightRC") elFakeRate = 0.298;
  else if(elID=="MVATightNew" || elID=="MVATightNewRC") elFakeRate = 0.28;
  else if(elID=="SUSYTight" || elID=="SUSYTightRC") elFakeRate = 0.20;
  else{std::cout<<"Didn't pick a valid electron ID. Exiting..."<<std::endl; return 0;}

  //doGenPlots(fsig,t,tr);
  //cd back to main directory after making gen plots
  fsig->cd();

  int nEntries = t->GetEntries();

  int nMuMu=0;
  int nElMu=0;
  int nElEl=0;
  int nGenMuMu=0;
  int nGenElMu=0;
   int nGenElEl=0;

  //floats for trigger eff
  float nMu40=0;
  float nIsoTkMu24=0;
  float nMu30TkMu11=0;
  float nMu27TkMu8=0;
  float nEle27=0;
  float nDoubleEle33=0;
  float nEle17Ele12=0;
  float nEle17Ele12ORDoubleEle8HT300=0;
  float nEle17Ele12_highHT=0;
  float nEle17Ele12ORDoubleEle8HT300_highHT=0;
  float nMu30Ele30=0;
  float nMu17Ele12=0;
  float nMu8Ele17=0;
  float nMu23Ele12=0;
  float nMu8Ele23=0;
  float nMu30Ele30ORMu17Ele12ORMu8Ele17=0;

  //get variable vector
  std::vector<Variable*> vVar = getVariableVec();
  //now make histograms for various levels of cuts;
  std::vector<TH1F*> hists_ssdl_all = initHistos(vVar,-1,"ssdl");
  std::vector<TH1F*> hists_ssdl_elel = initHistos(vVar,0,"ssdl");
  std::vector<TH1F*> hists_ssdl_elmu = initHistos(vVar,1,"ssdl");
  std::vector<TH1F*> hists_ssdl_mumu = initHistos(vVar,2,"ssdl");
  //associated z-veto
  std::vector<TH1F*> hists_sZVeto_all = initHistos(vVar,-1,"sZVeto");
  std::vector<TH1F*> hists_sZVeto_elel = initHistos(vVar,0,"sZVeto");
  std::vector<TH1F*> hists_sZVeto_elmu = initHistos(vVar,1,"sZVeto");
  std::vector<TH1F*> hists_sZVeto_mumu = initHistos(vVar,2,"sZVeto");
  //two jets
  std::vector<TH1F*> hists_TwoJets_all = initHistos(vVar,-1,"TwoJets");
  std::vector<TH1F*> hists_TwoJets_elel = initHistos(vVar,0,"TwoJets");
  std::vector<TH1F*> hists_TwoJets_elmu = initHistos(vVar,1,"TwoJets");
  std::vector<TH1F*> hists_TwoJets_mumu = initHistos(vVar,2,"TwoJets");
  //nConst
  std::vector<TH1F*> hists_nConst_all = initHistos(vVar,-1,"nConst");
  std::vector<TH1F*> hists_nConst_elel = initHistos(vVar,0,"nConst");
  std::vector<TH1F*> hists_nConst_elmu = initHistos(vVar,1,"nConst");
  std::vector<TH1F*> hists_nConst_mumu = initHistos(vVar,2,"nConst");



  //load in event lists for filtering
  std::vector<int> runs254227 = getRunListFilterFromFile("csc2015_Dec01.txt");  std::vector<int> lumis254227 = getLumiListFilterFromFile("csc2015_Dec01.txt");  std::vector<unsigned long long> evts254227 = getEventListFilterFromFile("csc2015_Dec01.txt");
  std::vector<int> runs256676 = getRunListFilterFromFile("csc2015_Dec01_run256676.txt");  std::vector<int> lumis256676 = getLumiListFilterFromFile("csc2015_Dec01_run256676.txt");  std::vector<unsigned long long> evts256676 = getEventListFilterFromFile("csc2015_Dec01_run256676.txt");
  std::vector<int> runs256677 = getRunListFilterFromFile("csc2015_Dec01_run256677.txt");  std::vector<int> lumis256677 = getLumiListFilterFromFile("csc2015_Dec01_run256677.txt");  std::vector<unsigned long long> evts256677 = getEventListFilterFromFile("csc2015_Dec01_run256677.txt");
  std::vector<int> runs256734 = getRunListFilterFromFile("csc2015_Dec01_run256734.txt");  std::vector<int> lumis256734 = getLumiListFilterFromFile("csc2015_Dec01_run256734.txt");  std::vector<unsigned long long> evts256734 = getEventListFilterFromFile("csc2015_Dec01_run256734.txt");
  std::vector<int> runs256866 = getRunListFilterFromFile("csc2015_Dec01_run256866.txt");  std::vector<int> lumis256866 = getLumiListFilterFromFile("csc2015_Dec01_run256866.txt");  std::vector<unsigned long long> evts256866 = getEventListFilterFromFile("csc2015_Dec01_run256866.txt");
  std::vector<int> runs257490 = getRunListFilterFromFile("csc2015_Dec01_run257490.txt");  std::vector<int> lumis257490 = getLumiListFilterFromFile("csc2015_Dec01_run257490.txt");  std::vector<unsigned long long> evts257490 = getEventListFilterFromFile("csc2015_Dec01_run257490.txt");
  std::vector<int> runs257751 = getRunListFilterFromFile("csc2015_Dec01_run257751.txt");  std::vector<int> lumis257751 = getLumiListFilterFromFile("csc2015_Dec01_run257751.txt");  std::vector<unsigned long long> evts257751 = getEventListFilterFromFile("csc2015_Dec01_run257751.txt");
  std::vector<int> runs258136 = getRunListFilterFromFile("csc2015_Dec01_run258136.txt");  std::vector<int> lumis258136 = getLumiListFilterFromFile("csc2015_Dec01_run258136.txt");  std::vector<unsigned long long> evts258136 = getEventListFilterFromFile("csc2015_Dec01_run258136.txt");
  std::vector<int> runs258211 = getRunListFilterFromFile("csc2015_Dec01_run258211.txt");  std::vector<int> lumis258211 = getLumiListFilterFromFile("csc2015_Dec01_run258211.txt");  std::vector<unsigned long long> evts258211 = getEventListFilterFromFile("csc2015_Dec01_run258211.txt");
  std::vector<int> runs258244 = getRunListFilterFromFile("csc2015_Dec01_run258244.txt");  std::vector<int> lumis258244 = getLumiListFilterFromFile("csc2015_Dec01_run258244.txt");  std::vector<unsigned long long> evts258244 = getEventListFilterFromFile("csc2015_Dec01_run258244.txt");
  std::vector<int> runs258713 = getRunListFilterFromFile("csc2015_Dec01_run258713.txt");  std::vector<int> lumis258713 = getLumiListFilterFromFile("csc2015_Dec01_run258713.txt");  std::vector<unsigned long long> evts258713 = getEventListFilterFromFile("csc2015_Dec01_run258713.txt");
  std::vector<int> runs259686 = getRunListFilterFromFile("csc2015_Dec01_run259686.txt");  std::vector<int> lumis259686 = getLumiListFilterFromFile("csc2015_Dec01_run259686.txt");  std::vector<unsigned long long> evts259686 = getEventListFilterFromFile("csc2015_Dec01_run259686.txt");
  std::vector<int> runs259891 = getRunListFilterFromFile("csc2015_Dec01_run259891.txt");  std::vector<int> lumis259891 = getLumiListFilterFromFile("csc2015_Dec01_run259891.txt");  std::vector<unsigned long long> evts259891 = getEventListFilterFromFile("csc2015_Dec01_run259891.txt");
  std::vector<int> runs260536 = getRunListFilterFromFile("csc2015_Dec01_run260536.txt");  std::vector<int> lumis260536 = getLumiListFilterFromFile("csc2015_Dec01_run260536.txt");  std::vector<unsigned long long> evts260536 = getEventListFilterFromFile("csc2015_Dec01_run260536.txt");



  for(int ient=0; ient<nEntries; ient++){

    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;
    
    tr->GetEntry(ient);
    
    //weight for non prompt method
    float NPweight=0;
    int TL;
    //make vector of good Leptons change based on data/mc   
    std::vector<TLepton*> goodLeptons;
    if(data) goodLeptons = makeLeptons(tr->allMuons, tr->allElectrons,30.0,elID,muID,bg_np);
    else goodLeptons = makeLeptons(tr->allMuons, tr->allElectrons,30.0,elID,muID,bg_np);

    //reorder the leptons by pt to remove flavor ordering
    std::sort(goodLeptons.begin(),goodLeptons.end(),sortByPt);
    bool samesign;

    //get chargeMisID rate for DY and save DY events outside of Z-peak (71-111 GeV) with weights for chargeMisID
    float weight=0;
    if(outname.find("DYJets")!=std::string::npos || outname.find("ChargeMisID")!=std::string::npos){
      
      samesign = checkOppositeSignLeptonsForDY(goodLeptons); //returns true if find opposite sign leptons not in mu-mu channel
      
    }
    //now that we have good leptons, if it's not DY sample just check for two with same-sign charge and assign weight of 1
    else{
      samesign = checkSameSignLeptons(goodLeptons);
      weight=1;
    }


    if(!samesign) continue;


    //now make vector of same-sign leptons, for DY make vector containing opposite sign leptons closest to Z mass
    std::vector<TLepton*> vSSLep;
    if(outname.find("DYJets")!=std::string::npos || outname.find("ChargeMisID")!=std::string::npos){      
      vSSLep = makeOSLeptonsForDY(goodLeptons);
    }
    else vSSLep = makeSSLeptons(goodLeptons);

    //dummy check to make sure the vector got filled properly
    assert(vSSLep.size() > 1);


    //now prune the goodleptons of the ssleptons
    std::vector<TLepton*> vNonSSLep = pruneSSLep(goodLeptons,vSSLep);
    //with vector now get weight for DY Events
    if(outname.find("DYJets")!=std::string::npos || outname.find("ChargeMisID")!=std::string::npos) {
      if( vSSLep.at(0)->pt >100 || vSSLep.at(1)->pt >100){ //high pt case
	weight = getEtaWeight(etaWeights_hpt,vSSLep);
      }
      else weight = getEtaWeight(etaWeights_lpt,vSSLep); //low pt case
    }

    //now get dilepton mass
    float dilepMass = (vSSLep.at(0)->lv + vSSLep.at(1)->lv).M();


    float HT=0;
    HT+=vSSLep.at(0)->pt+vSSLep.at(1)->pt;
    for(unsigned int uijet=0; uijet<tr->allAK4Jets.size();uijet++){
      HT+=tr->allAK4Jets.at(uijet)->pt;
    }

    //get channel
    int nMu=0;
    if(vSSLep.at(0)->isMu) nMu++;
    if(vSSLep.at(1)->isMu) nMu++;

    //bools for channels
    bool mumu=false;
    bool elmu=false;
    bool elel=false;



    //ok at this point only have events with same-sign leptons, now let's do simple check to see how many of each channel we have:
    if(vSSLep.at(0)->isMu && vSSLep.at(1)->isMu){ nMuMu+=1; mumu=true;}
    else if( ( vSSLep.at(0)->isEl && vSSLep.at(1)->isMu) || (vSSLep.at(0)->isMu && vSSLep.at(1)->isEl)){ nElMu+=1; elmu=true;}
    else {nElEl+=1; elel=true;}


    //require OR of triggers but make each channel consistent
    // dzou - comment out trigger requirements for use with PHYS14 ljmet - trigger menus have changed 
    bool skip = false;
    /*  
    bool skip = true;
    if(mumu && tr->HLT_Mu27TkMu8) skip =false;
    if(elmu && (tr->HLT_Mu8Ele17 || tr->HLT_Mu17Ele12)) skip = false;
    if(elel && tr->HLT_Ele17Ele12) skip = false;
    if(skip) continue;
*/

    //now skip if not the channel from the corresponding dataset
    if((argv1=="DataMuMu" || argv1=="NonPromptDataMuMu") && !mumu) continue;
    if((argv1=="DataElMu" || argv1=="NonPromptDataElMu" || argv1=="ChargeMisIDElMu") && !elmu) continue;
    if((argv1=="DataElEl" || argv1=="NonPromptDataElEl" || argv1=="ChargeMisIDElEl") && !elel) continue;

    //now veto on bad events from met scanners
    bool badEvent = false;
    if(data){

      if(tr->run >= 260536) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs260536,lumis260536,evts260536)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      else if(tr->run >= 259891) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs259891,lumis259891,evts259891)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      else if(tr->run >= 259686) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs259686,lumis259686,evts259686)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      else if(tr->run >= 258713) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs258713,lumis258713,evts258713)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      else if(tr->run >= 258244) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs258244,lumis258244,evts258244)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      else if(tr->run >= 258211) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs258211,lumis258211,evts258211)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      else if(tr->run >= 258136) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs258136,lumis258136,evts258136)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      else if(tr->run >= 257751) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs257751,lumis257751,evts257751)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      else if(tr->run >= 257490) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs257490,lumis257490,evts257490)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      else if(tr->run >= 256866) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs256866,lumis256866,evts256866)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      else if(tr->run >= 256734) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs256734,lumis256734,evts256734)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      else if(tr->run >= 256677) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs256677,lumis256677,evts256677)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      else if(tr->run >= 256676) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs256676,lumis256676,evts256676)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      else if(tr->run >= 254227) badEvent = EventFilterFromVector(tr->run, tr->lumi, tr->event, runs254227,lumis254227,evts254227)|| EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      //std::cout<<"checking at beginning for sample "<<sample<<std::endl;
      //badEvent = EventFilterFromFile_CSC(tr->run,tr->lumi,tr->event) || EventFilterFromFile_ECALSC(tr->run,tr->lumi,tr->event);
      //if(elel) badEvent = EventFilterFromFile_DoubleEG(tr->run,tr->lumi,tr->event);
      ///else if(mumu) badEvent = EventFilterFromFile_DoubleMu(tr->run,tr->lumi,tr->event);
      //else if(elmu) badEvent = EventFilterFromFile_MuonEG(tr->run,tr->lumi,tr->event);
    }
    if(badEvent) {std::cout<<"filtering bad event"<<std::endl;continue;}
    

    //now veto on dielectron events coming from Z bosons
    //if(elel && (dilepMass>71.1 && dilepMass<111.1)) continue;

    //fill muon trigger histograms
    if(mumu){
      //HLTMu40 - check efficiency of leading lepton
      h_Mu40Den->Fill(vSSLep.at(0)->pt);
      if(tr->HLT_Mu40){
	h_Mu40Num->Fill(vSSLep.at(0)->pt);
	nMu40+=1;
      }
      //HLT_IsoTkMu24 - also check for leading lepton
      h_IsoTkMu24Den->Fill(vSSLep.at(0)->pt);
      if(tr->HLT_IsoTkMu24){
	h_IsoTkMu24Num->Fill(vSSLep.at(0)->pt);
	nIsoTkMu24+=1;
      }
      //HLT_Mu30TkMu11 - check for subleading lepton
      h_Mu30TkMu11Den->Fill(vSSLep.at(1)->pt);
      if(tr->HLT_Mu30TkMu11){
	h_Mu30TkMu11Num->Fill(vSSLep.at(1)->pt);
	nMu30TkMu11+=1;
      }
      if(tr->HLT_Mu27TkMu8) nMu27TkMu8+=1;
      //HLT_DoubleMu33NoFiltersNoVtx - check fo subleading lepton
      h_DoubleMu33NoFiltersNoVtxDen->Fill(vSSLep.at(1)->pt);
      if(tr->HLT_DoubleMu33NoFiltersNoVtx) h_DoubleMu33NoFiltersNoVtxNum->Fill(vSSLep.at(1)->pt);
    }
    //now electron trigger
    if(elel){
      //HLt_Ele27 - check vs leading lepton
      h_Ele27WP85Den->Fill(vSSLep.at(0)->pt);
      if(tr->HLT_Ele27WP85){
	h_Ele27WP85Num->Fill(vSSLep.at(0)->pt);
	nEle27+=1;
      }
      //HLT_DoubleEle33 - check vs subleading lepton
      h_DoubleEle33Den->Fill(vSSLep.at(1)->pt);
      if(tr->HLT_DoubleEle33){
	h_DoubleEle33Num->Fill(vSSLep.at(1)->pt);
	nDoubleEle33+=1;
      }
      //HLT_DoubleEle33_MW - check vs subleading lepton
      h_DoubleEle33_MWDen->Fill(vSSLep.at(1)->pt);
      if(tr->HLT_DoubleEle33_MW) h_DoubleEle33_MWNum->Fill(vSSLep.at(1)->pt);
      if(tr->HLT_Ele17Ele12) nEle17Ele12+=1;
      if(tr->HLT_Ele17Ele12 || tr->HLT_DoubleEle8_HT300) nEle17Ele12ORDoubleEle8HT300+=1;
    }
  
    //if cross channel
    if(elmu){
      if(tr->HLT_Mu30Ele30) nMu30Ele30+=1;
      if(tr->HLT_Mu17Ele12) nMu17Ele12+=1;
      if(tr->HLT_Mu8Ele17) nMu8Ele17+=1;
      if(tr->HLT_Mu23Ele12) nMu23Ele12+=1;
      if(tr->HLT_Mu8Ele23) nMu8Ele23+=1;
      //also get OR
      if( (tr->HLT_Mu17Ele12) || (tr->HLT_Mu8Ele17) )nMu30Ele30ORMu17Ele12ORMu8Ele17+=1;
      
    }


    //get trigger scale factors
    float trigSF; 
    if(data) trigSF = 1.0;
    else trigSF = getTrigSF(vSSLep);

    //now get lepton ID Scale Factors
    float lepIDSF;
    if(data) lepIDSF = 1.0;
    else lepIDSF = getLepIDSF(vSSLep);
    float lepIsoSF;
    if(data) lepIsoSF = 1.0;
    else lepIsoSF = getLepIsoSF(vSSLep);

    //now need to calculate nonPropmtWeight
    if(!bg_np) {NPweight=1.0;TL=-1;}
    else{
      if(mumu){//muon channel
	if(vSSLep.at(0)->Tight && vSSLep.at(1)->Tight) {NPweight = WeightSF_T2(muPromptRate,muFakeRate); TL = 3;}//both tight
	else if(vSSLep.at(0)->Tight || vSSLep.at(1)->Tight) {NPweight = WeightSF_T1(muPromptRate,muFakeRate); TL=2;}//one tight
	else {NPweight = WeightSF_T0(muPromptRate,muFakeRate); TL=0;}//both loose
      }
      else if(elel){//electron channel

	if(vSSLep.at(0)->Tight && vSSLep.at(1)->Tight) {NPweight = WeightSF_T2(elPromptRate,elFakeRate); TL=3;}//both tight
	else if(vSSLep.at(0)->Tight || vSSLep.at(1)->Tight) {NPweight = WeightSF_T1(elPromptRate,elFakeRate); TL=1;}//one tight
	else {NPweight = WeightSF_T0(elPromptRate,elFakeRate); TL=0;}//both loose
      }
      else{ //cross channel
	if(vSSLep.at(0)->Tight && vSSLep.at(1)->Tight) {NPweight = WeightOF_T11(elPromptRate,elFakeRate,muPromptRate,muFakeRate); TL=3;} //both tight
	else if ( (vSSLep.at(0)->isEl && vSSLep.at(0)->Tight) || (vSSLep.at(1)->isEl && vSSLep.at(1)->Tight) )  {NPweight = WeightOF_T10(elPromptRate,elFakeRate,muPromptRate,muFakeRate);TL=2;} //if electron is tight, muon must be loose or we would be on line above so just see if either lepton is a tight electron
	else if ( (vSSLep.at(0)->isMu && vSSLep.at(0)->Tight) || (vSSLep.at(1)->isMu && vSSLep.at(1)->Tight) ) {NPweight = WeightOF_T01(elPromptRate,elFakeRate,muPromptRate,muFakeRate); TL=1;}//if muon is tight, el must be loose or we would be on tight-tight line so just check for tight muon
	else {NPweight = WeightOF_T00(elPromptRate,elFakeRate,muPromptRate,muFakeRate); TL=0;}//otherwise both are loose
      }
    }
      
    //get pileup weight;
    float puweight=-11;
    if(data) puweight=1;
    else{
      puweight = getPUWeight(hpu,(int)tr->nPU);
    }

    if(puweight >20) std::cout<<"Pileup weight is: "<<puweight<<std::endl;

    float mcweight;
    if(data) mcweight = 1;
    else{
      if(tr->MCWeight>=0) mcweight=1.0;
      else mcweight=-1.0;
    }

    //make boolean here so we can fill the closets associated mass
    bool secondaryZVeto = (checkSecondaryZVeto(vSSLep,tr->looseMuons,tr->looseElectrons)).first;
    float assocMass =  (checkSecondaryZVeto(vSSLep,tr->looseMuons,tr->looseElectrons)).second;

    //fill tree for post ssdl cut since that is all that we've applied so far
    tm_ssdl->FillTree(vSSLep, tr->allAK4Jets, tr->cleanedAK4Jets, tr->simpleCleanedAK4Jets, HT, tr->MET, dilepMass,nMu,weight,vNonSSLep,tr->MCWeight,NPweight,TL,trigSF,lepIDSF,lepIsoSF,puweight,assocMass);
    //fill histos for same cut level
    float totalweight = weight * NPweight * trigSF * lepIDSF * lepIsoSF* puweight * mcweight;
    fillHistos(hists_ssdl_all, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);
    if(elel) fillHistos(hists_ssdl_elel, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);
    if(elmu) fillHistos(hists_ssdl_elmu, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);
    if(mumu) fillHistos(hists_ssdl_mumu, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);


    float st = vSSLep.at(0)->pt + vSSLep.at(1)->pt;
    for(unsigned int j=0; j < vNonSSLep.size(); j++){
      st = st + vNonSSLep.at(j)->pt;
    }
    for(unsigned int j=0; j <tr->cleanedAK4Jets.size();j++){
      st = st + tr->cleanedAK4Jets.at(j)->pt;
    }

    //now get pdf weights at early stage
    if(!data){
      //now fill ppdf weight histogram
      std::vector<double> pdfweight_ssdl = (*tr->LHEWeights);
      std::vector<int> pdfweightIDs_ssdl = (*tr->LHEWeightIDs);
      hist_scaleHT_ssdl_nom->Fill(st,mcweight);
      for(unsigned int i=0; i< pdfweightIDs_ssdl.size(); i++){
	int ID = pdfweightIDs_ssdl.at(i);
	if(ID==1002 || ID==1003 || ID==1004 || ID==1005 || ID==1007 || ID==1009 || ID==2 || ID==3 || ID==4 || ID==5 || ID==7 || ID==9){
	  //now fill individual
	  if(ID==1002 || (outname.find("X53")!=std::string::npos && ID==2) )hist_scaleHT_ssdl_1002->Fill(st,pdfweight_ssdl.at(i)*mcweight);
	  if(ID==1003 || (outname.find("X53")!=std::string::npos && ID==3) )hist_scaleHT_ssdl_1003->Fill(st,pdfweight_ssdl.at(i)*mcweight);
	  if(ID==1004 || (outname.find("X53")!=std::string::npos && ID==4) )hist_scaleHT_ssdl_1004->Fill(st,pdfweight_ssdl.at(i)*mcweight);
	  if(ID==1005 || (outname.find("X53")!=std::string::npos && ID==5) )hist_scaleHT_ssdl_1005->Fill(st,pdfweight_ssdl.at(i)*mcweight);
	  if(ID==1007|| (outname.find("X53")!=std::string::npos && ID==7) )hist_scaleHT_ssdl_1007->Fill(st,pdfweight_ssdl.at(i)*mcweight);
	  if(ID==1009|| (outname.find("X53")!=std::string::npos && ID==2) )hist_scaleHT_ssdl_1009->Fill(st,pdfweight_ssdl.at(i)*mcweight);
	}
	if(!(ID>2000 && i<2101)) continue;

      }
    }


    //since we have the two same-sign leptons, now make sure neither of them reconstructs with any other tight lepton in the event to form a Z
    if(secondaryZVeto) continue;
    //fill tree for post secondary z veto
    tm_sZVeto->FillTree(vSSLep, tr->allAK4Jets, tr->cleanedAK4Jets, tr->simpleCleanedAK4Jets, HT, tr->MET, dilepMass,nMu,weight,vNonSSLep,tr->MCWeight,NPweight,TL,trigSF,lepIDSF,lepIsoSF,puweight,assocMass);
    //now fill corresponding histos
    fillHistos(hists_sZVeto_all, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);
    if(elel) fillHistos(hists_sZVeto_elel, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);
    if(elmu) fillHistos(hists_sZVeto_elmu, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);
    if(mumu) fillHistos(hists_sZVeto_mumu, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);

    //skip events in dielectron which reconstruct to z
    if(elel){
      if(dilepMass < 106 && dilepMass>76) continue;
    }

    //quarkonia veto
    if(!(dilepMass>20)) continue;

    //if(data && sample=="ChargeMisIDElEl"){     //do charge misID after vetoing on primary Z
    //if(elel) badEvent = EventFilterFromFile_DoubleEG(tr->run,tr->lumi,tr->event);
    //else if(mumu) badEvent = EventFilterFromFile_DoubleMu(tr->run,tr->lumi,tr->event);
    //else if(elmu) badEvent = EventFilterFromFile_MuonEG(tr->run,tr->lumi,tr->event);
    //}
    if(badEvent) {std::cout<<"filtering bad event"<<std::endl;continue;}
    tm_DilepMassCut->FillTree(vSSLep, tr->allAK4Jets, tr->cleanedAK4Jets, tr->simpleCleanedAK4Jets, HT, tr->MET, dilepMass,nMu,weight,vNonSSLep,tr->MCWeight,NPweight,TL,trigSF,lepIDSF,lepIsoSF,puweight,assocMass);

    if(tr->cleanedAK4Jets.size()>1){
      //now fill corresponding histos
      fillHistos(hists_TwoJets_all, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);
      if(elel) fillHistos(hists_TwoJets_elel, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);
      if(elmu) fillHistos(hists_TwoJets_elmu, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);
      if(mumu) fillHistos(hists_TwoJets_mumu, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);
    }

    if(vSSLep.at(0)->pt<40) continue; //skip events with leading lepton pt less than 40
    
    int nconst = tr->cleanedAK4Jets.size() + vNonSSLep.size();
    if(nconst<5) continue; //nconst cutl

    //now fill corresponding histos
    fillHistos(hists_nConst_all, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);
    if(elel) fillHistos(hists_nConst_elel, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);
    if(elmu) fillHistos(hists_nConst_elmu, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);
    if(mumu) fillHistos(hists_nConst_mumu, vSSLep, vNonSSLep, tr->cleanedAK4Jets, tr->MET, dilepMass, totalweight);

    if(elel && st>1000){
      if(tr->HLT_Ele17Ele12) nEle17Ele12_highHT+=1;
      if(tr->HLT_Ele17Ele12 || tr->HLT_DoubleEle8_HT300) nEle17Ele12ORDoubleEle8HT300_highHT+=1;
    }

    if(!data){
      //now fill ppdf weight histogram
      std::vector<double> pdfweights = (*tr->LHEWeights);
      std::vector<int> pdfweightIDs = (*tr->LHEWeightIDs);
      //now fill ppdf weight histogram
      hist_scaleHT_nom->Fill(st,mcweight);
      for(unsigned int i=0; i< pdfweightIDs.size(); i++){
	int ID = pdfweightIDs.at(i);
	if(ID==1002 || ID==1003 || ID==1004 || ID==1005 || ID==1007 || ID==1009 || ID==2 || ID==3 || ID==4 || ID==5 || ID==7 || ID==9){
	  hist_scaleHT->Fill(pdfweights.at(i),st);//fill combined
	  //now fill individual
	  if(ID==1002 || (outname.find("X53")!=std::string::npos && ID==2) )hist_scaleHT_1002->Fill(st,pdfweights.at(i)*mcweight);
	  if(ID==1003 || (outname.find("X53")!=std::string::npos && ID==3) )hist_scaleHT_1003->Fill(st,pdfweights.at(i)*mcweight);
	  if(ID==1004 || (outname.find("X53")!=std::string::npos && ID==4) )hist_scaleHT_1004->Fill(st,pdfweights.at(i)*mcweight);
	  if(ID==1005 || (outname.find("X53")!=std::string::npos && ID==5) )hist_scaleHT_1005->Fill(st,pdfweights.at(i)*mcweight);
	  if(ID==1007 || (outname.find("X53")!=std::string::npos && ID==7) )hist_scaleHT_1007->Fill(st,pdfweights.at(i)*mcweight);
	  if(ID==1009 || (outname.find("X53")!=std::string::npos && ID==9) )hist_scaleHT_1009->Fill(st,pdfweights.at(i)*mcweight);
	}
	if(!( (ID>2000 && i<2101 && outname.find("X53")==std::string::npos ) || (outname.find("X53")!=std::string::npos && ( ID> 111 && ID <212)) ) ) continue;
	hist_pdfHT->Fill(pdfweights.at(i),st);
      }
    }

    //now fill nonprompt histos for later use
    if(bg_np){

	if(TL==0) npHistos_all.at(0)->Fill(st,mcweight);
	if(TL==1) npHistos_all.at(1)->Fill(st,mcweight);
	if(TL==2) npHistos_all.at(2)->Fill(st,mcweight);
	if(TL==3) npHistos_all.at(3)->Fill(st,mcweight);
      
      if(elel){
	if(TL==0) npHistos_ee.at(0)->Fill(st,mcweight);
	if(TL==1) npHistos_ee.at(1)->Fill(st,mcweight);
	if(TL==2) npHistos_ee.at(2)->Fill(st,mcweight);
	if(TL==3) npHistos_ee.at(3)->Fill(st,mcweight);
      }
      if(elmu){
	if(TL==0) npHistos_emu.at(0)->Fill(st,mcweight);
	if(TL==1) npHistos_emu.at(1)->Fill(st,mcweight);
	if(TL==2) npHistos_emu.at(2)->Fill(st,mcweight);
	if(TL==3) npHistos_emu.at(3)->Fill(st,mcweight);
      }
      if(mumu){
	if(TL==0) npHistos_mumu.at(0)->Fill(st,mcweight);
	if(TL==1) npHistos_mumu.at(1)->Fill(st,mcweight);
	if(TL==2) npHistos_mumu.at(2)->Fill(st,mcweight);
	if(TL==3) npHistos_mumu.at(3)->Fill(st,mcweight);
      }
    }//end filling of nphistos

  }//end event loop

  //write the trees
  tm_ssdl->tree->Write();
  tm_sZVeto->tree->Write();
  tm_DilepMassCut->tree->Write();

  //write the nonprompt histograms
  for(unsigned int j=0; j<4; j++){
    fsig->WriteTObject(npHistos_all.at(j));
    fsig->WriteTObject(npHistos_ee.at(j));
    fsig->WriteTObject(npHistos_emu.at(j));
    fsig->WriteTObject(npHistos_mumu.at(j));
  }

  //write histograms
  writeHistos(fsig, hists_ssdl_all);
  writeHistos(fsig, hists_ssdl_elel);
  writeHistos(fsig, hists_ssdl_elmu);
  writeHistos(fsig, hists_ssdl_mumu);

  writeHistos(fsig, hists_sZVeto_all);
  writeHistos(fsig, hists_sZVeto_elel);
  writeHistos(fsig, hists_sZVeto_elmu);
  writeHistos(fsig, hists_sZVeto_mumu);

  writeHistos(fsig, hists_TwoJets_all);
  writeHistos(fsig, hists_TwoJets_elel);
  writeHistos(fsig, hists_TwoJets_elmu);
  writeHistos(fsig, hists_TwoJets_mumu);

  writeHistos(fsig, hists_nConst_all);
  writeHistos(fsig, hists_nConst_elel);
  writeHistos(fsig, hists_nConst_elmu);
  writeHistos(fsig, hists_nConst_mumu);

  fsig->WriteTObject(h_DoubleEle33Num); 
  fsig->WriteTObject(h_DoubleEle33_MWNum);
  fsig->WriteTObject(h_Ele27WP85Num); 
  fsig->WriteTObject(h_Mu30TkMu11Num); 
  fsig->WriteTObject(h_Mu40Num); 
  fsig->WriteTObject(h_IsoTkMu24Num); 
  fsig->WriteTObject(h_DoubleMu33NoFiltersNoVtxNum);
  //fsig->WriteTObject(h_Mu23Ele12Num);
  //fsig->WriteTObject(h_Mu8Ele23Num);
  //fsig->WriteTObject(h_PFHT900Num);
  //fsig->WriteTObject(h_AK8PFJet360TrimMass30Num);

  fsig->WriteTObject(h_DoubleEle33Den); 
  fsig->WriteTObject(h_DoubleEle33_MWDen);
  fsig->WriteTObject(h_Ele27WP85Den);
  fsig->WriteTObject(h_Mu30TkMu11Den);
  fsig->WriteTObject(h_Mu40Den);
  fsig->WriteTObject(h_IsoTkMu24Den);
  fsig->WriteTObject(h_DoubleMu33NoFiltersNoVtxDen);
  //fsig->WriteTObject(h_Mu23Ele12Den);
  //fsig->WriteTObject(h_Mu8Ele23Den);
  //fsig->WriteTObject(h_PFHT900Den);
  //fsig->WriteTObject(h_AK8PFJet360TrimMass30Den);
  
  fsig->WriteTObject(hist_pdfHT);
  fsig->WriteTObject(hist_scaleHT);
  fsig->WriteTObject(hist_scaleHT_nom);
  fsig->WriteTObject(hist_scaleHT_1002);
  fsig->WriteTObject(hist_scaleHT_1003);
  fsig->WriteTObject(hist_scaleHT_1004);
  fsig->WriteTObject(hist_scaleHT_1005);
  fsig->WriteTObject(hist_scaleHT_1007);
  fsig->WriteTObject(hist_scaleHT_1009);

  fsig->WriteTObject(hist_scaleHT_ssdl_nom);
  fsig->WriteTObject(hist_scaleHT_ssdl_1002);
  fsig->WriteTObject(hist_scaleHT_ssdl_1003);
  fsig->WriteTObject(hist_scaleHT_ssdl_1004);
  fsig->WriteTObject(hist_scaleHT_ssdl_1005);
  fsig->WriteTObject(hist_scaleHT_ssdl_1007);
  fsig->WriteTObject(hist_scaleHT_ssdl_1009);

  fsig->Write();
  fsig->Close();

  std::cout<<"Number of Gen MuMu: "<<nGenMuMu<<std::endl;
  std::cout<<"Number of MuMu: "<<nMuMu<<std::endl;
  std::cout<<"Number of ElMu: "<<nElMu<<std::endl;
  std::cout<<"Number of ElEl: "<<nElEl<<std::endl;


  std::cout<<"Efficiency of Mu40 for MuMu: "<<nMu40/(nMuMu)<<std::endl;
  std::cout<<"Efficiency of Mu40 for MuMu+ElMu: "<<nMu40/(nMuMu + nElMu)<<std::endl;
  std::cout<<"Efficiency of IsoTkmu24 for MuMu: "<<nIsoTkMu24/(nMuMu)<<std::endl;
  std::cout<<"Efficiency of IsoTkmu24 for MuMu+ElMu: "<<nIsoTkMu24/(nMuMu+nElMu)<<std::endl;

  TH1F* hNMu30TkMu11Num = new TH1F("hNMu30TkMu11Num","",1,0,10000);
  TH1F* hNMu30TkMu11Den = new TH1F("hNMu30TkMu11Den","",1,0,10000);
  for(int j =0; j<nMu30TkMu11;j++) hNMu30TkMu11Num->Fill(j);
  for(int j =0; j<nMuMu;j++) hNMu30TkMu11Den->Fill(j);
  TGraphAsymmErrors* Mu30TkMu11Graph = new TGraphAsymmErrors(hNMu30TkMu11Num,hNMu30TkMu11Den);
  std::cout<<"Efficiency of Mu30TkMu11: "<<nMu30TkMu11/nMuMu<<" +"<<Mu30TkMu11Graph->GetErrorYhigh(0)<<" -"<<Mu30TkMu11Graph->GetErrorYlow(0)<<std::endl<<"\n";
  std::cout<<"Efficiency of Ele27 for ElEl: "<<nEle27/nElEl<<std::endl;
  std::cout<<"Efficiency of Ele27 for ElEl + ElMu: "<<nEle27/(nElMu +nElEl)<<std::endl;

  TH1F* hNMu27TkMu8Num = new TH1F("hNMu27TkMu8Num","",1,0,10000);
  TH1F* hNMu27TkMu8Den = new TH1F("hNMu27TkMu8Den","",1,0,10000);
  for(int j =0; j<nMu27TkMu8;j++) hNMu27TkMu8Num->Fill(j);
  for(int j =0; j<nMuMu;j++) hNMu27TkMu8Den->Fill(j);
  TGraphAsymmErrors* Mu27TkMu8Graph = new TGraphAsymmErrors(hNMu27TkMu8Num,hNMu27TkMu8Den);
  std::cout<<"Efficiency of Mu27TkMu8: "<<nMu27TkMu8/nMuMu<<" +"<<Mu27TkMu8Graph->GetErrorYhigh(0)<<" -"<<Mu27TkMu8Graph->GetErrorYlow(0)<<std::endl<<"\n";

  TH1F* hNDoubleEle33Num = new TH1F("hNDoubleEle33Num","",1,0,10000);
  TH1F* hNDoubleEle33Den = new TH1F("hNDoubleEle33Den","",1,0,10000);
  for(int j =0; j<nDoubleEle33;j++) hNDoubleEle33Num->Fill(j);
  for(int j =0; j<nElEl;j++) hNDoubleEle33Den->Fill(j);
  TGraphAsymmErrors* DoubleEle33Graph = new TGraphAsymmErrors(hNDoubleEle33Num,hNDoubleEle33Den);
  std::cout<<"Efficiency of DoubleEle33: "<<nDoubleEle33/nElEl<<" +"<<DoubleEle33Graph->GetErrorYhigh(0)<<" -"<<DoubleEle33Graph->GetErrorYlow(0)<<std::endl<<"\n";

  TH1F* hNEle17Ele12Num = new TH1F("hNEle17Ele12Num","",1,0,10000);
  TH1F* hNEle17Ele12Den = new TH1F("hNEle17Ele12Den","",1,0,10000);
  for(int j =0; j<nEle17Ele12;j++) hNEle17Ele12Num->Fill(j);
  for(int j =0; j<nElEl;j++) hNEle17Ele12Den->Fill(j);
  TGraphAsymmErrors* Ele17Ele12Graph = new TGraphAsymmErrors(hNEle17Ele12Num,hNEle17Ele12Den);
  std::cout<<"Efficiency of Ele17Ele12: "<<nEle17Ele12/nElEl<<" +"<<Ele17Ele12Graph->GetErrorYhigh(0)<<" -"<<Ele17Ele12Graph->GetErrorYlow(0)<<std::endl;
  std::cout<<"Efficiency of Ele17Ele12 OR DoubleEle8HT300: "<<nEle17Ele12ORDoubleEle8HT300/nElEl<<"\n";
  std::cout<<"Efficiency of Ele17Ele12 at HT > 1000: "<<nEle17Ele12_highHT/nElEl<<"\n\n";
  std::cout<<"Efficiency of Ele17Ele12 OR DoubleEle8HT300 at HT >1000: "<<nEle17Ele12ORDoubleEle8HT300_highHT/nElEl<<"\n\n";
 
  TH1F* hNMu30Ele30Num = new TH1F("hNMu30Ele30Num","",1,0,10000);
  TH1F* hNMu30Ele30Den = new TH1F("hNMu30Ele30Den","",1,0,10000);
  for(int j =0; j<nMu30Ele30;j++) hNMu30Ele30Num->Fill(j);
  for(int j =0; j<nElMu;j++) hNMu30Ele30Den->Fill(j);
  TGraphAsymmErrors* Mu30Ele30Graph = new TGraphAsymmErrors(hNMu30Ele30Num,hNMu30Ele30Den);
  std::cout<<"Efficiency of Mu30Ele30: "<<nMu30Ele30/nElMu<<" +"<<Mu30Ele30Graph->GetErrorYhigh(0)<<" -"<<Mu30Ele30Graph->GetErrorYlow(0)<<std::endl<<"\n";

  TH1F* hNMu8Ele17Num = new TH1F("hNMu8Ele17Num","",1,0,10000);
  TH1F* hNMu8Ele17Den = new TH1F("hNMu8Ele17Den","",1,0,10000);
  for(int j =0; j<nMu8Ele17;j++) hNMu8Ele17Num->Fill(j);
  for(int j =0; j<nElMu;j++) hNMu8Ele17Den->Fill(j);
  TGraphAsymmErrors* Mu8Ele17Graph = new TGraphAsymmErrors(hNMu8Ele17Num,hNMu8Ele17Den);
  std::cout<<"Efficiency of Mu8Ele17: "<<nMu8Ele17/nElMu<<" +"<<Mu8Ele17Graph->GetErrorYhigh(0)<<" -"<<Mu8Ele17Graph->GetErrorYlow(0)<<std::endl<<"\n";

  TH1F* hNMu8Ele23Num = new TH1F("hNMu8Ele23Num","",1,0,10000);
  TH1F* hNMu8Ele23Den = new TH1F("hNMu8Ele23Den","",1,0,10000);
  for(int j =0; j<nMu8Ele23;j++) hNMu8Ele23Num->Fill(j);
  for(int j =0; j<nElMu;j++) hNMu8Ele23Den->Fill(j);
  TGraphAsymmErrors* Mu8Ele23Graph = new TGraphAsymmErrors(hNMu8Ele23Num,hNMu8Ele23Den);
  std::cout<<"Efficiency of Mu8Ele23: "<<nMu8Ele23/nElMu<<" +"<<Mu8Ele23Graph->GetErrorYhigh(0)<<" -"<<Mu8Ele23Graph->GetErrorYlow(0)<<std::endl<<"\n";

  TH1F* hNMu17Ele12Num = new TH1F("hNMu17Ele12Num","",1,0,10000);
  TH1F* hNMu17Ele12Den = new TH1F("hNMu17Ele12Den","",1,0,10000);
  for(int j =0; j<nMu17Ele12;j++) hNMu17Ele12Num->Fill(j);
  for(int j =0; j<nElMu;j++) hNMu17Ele12Den->Fill(j);
  TGraphAsymmErrors* Mu17Ele12Graph = new TGraphAsymmErrors(hNMu17Ele12Num,hNMu17Ele12Den);
  std::cout<<"Efficiency of Mu17Ele12: "<<nMu17Ele12/nElMu<<" +"<<Mu17Ele12Graph->GetErrorYhigh(0)<<" -"<<Mu17Ele12Graph->GetErrorYlow(0)<<std::endl<<"\n";

  TH1F* hNMu23Ele12Num = new TH1F("hNMu23Ele12Num","",1,0,10000);
  TH1F* hNMu23Ele12Den = new TH1F("hNMu23Ele12Den","",1,0,10000);
  for(int j =0; j<nMu23Ele12;j++) hNMu23Ele12Num->Fill(j);
  for(int j =0; j<nElMu;j++) hNMu23Ele12Den->Fill(j);
  TGraphAsymmErrors* Mu23Ele12Graph = new TGraphAsymmErrors(hNMu23Ele12Num,hNMu23Ele12Den);
  std::cout<<"Efficiency of Mu23Ele12: "<<nMu23Ele12/nElMu<<" +"<<Mu23Ele12Graph->GetErrorYhigh(0)<<" -"<<Mu23Ele12Graph->GetErrorYlow(0)<<std::endl<<"\n";

  std::cout<<"Efficiency of Mu17Ele12 OR Mu8Ele17: "<<nMu30Ele30ORMu17Ele12ORMu8Ele17/nElMu<<std::endl;
}


std::vector<TLepton*> makeLeptons(std::vector<TMuon*> muons, std::vector<TElectron*> electrons, float ptCut, std::string elID, std::string muID, bool doFakes){

  std::vector<TLepton*> Leptons;

  //fill with  muons
  for(unsigned int uimu=0; uimu<muons.size(); uimu++){
    TMuon* imu = muons.at(uimu);
    TLepton* iLep = new TLepton(imu->pt,imu->eta,imu->phi,imu->energy,imu->charge);

    if(muID=="CBTight"){
      iLep->Tight=imu->cutBasedTight();
      iLep->Loose=imu->cutBasedLoose();
    }
    else if(muID=="CBTightMiniIso"){
      iLep->Tight=imu->cutBasedTightMiniIso();
      iLep->Loose=imu->cutBasedLoose();
    }
    else if(muID=="CBLoose"){
      iLep->Tight=imu->cutBasedLoose();
      iLep->Loose=true; //in case 'loose ID' is specified as 'tight', take any muon as loose ID
    }
    iLep->isMu = true;
    iLep->isEl = false;
    //skip for smaller than pT cut
    if(iLep->pt<ptCut) continue;
    //now save based on ID requirments if 'normal' running then require tight, else save if loose
    if(!doFakes){
      if(iLep->Tight) Leptons.push_back(iLep);
    } 
    else{ //if doing fake estimate save if loose
      if(iLep->Loose) Leptons.push_back(iLep);
    }
  }
  
  
  //fill with  electrons
  for(unsigned int uiel=0; uiel<electrons.size(); uiel++){
    TElectron* iel = electrons.at(uiel);
    TLepton* iLep = new TLepton(iel->pt,iel->eta,iel->phi,iel->energy,iel->charge);
    iLep->isMu = false;
    iLep->isEl = true;
    if(elID=="CBTight"){
      iLep->Tight=iel->cutBasedTight25nsSpring15MC();
      iLep->Loose=iel->cutBasedLoose25nsSpring15MC();
    }
    else if(elID=="CBLoose"){
      iLep->Tight=iel->cutBasedLoose25nsSpring15MC();
      iLep->Loose=true;
    }
    if(elID=="CBTightRC"){
      iLep->Tight=iel->cutBasedTight25nsSpring15MCRC();
      iLep->Loose=iel->cutBasedLoose25nsSpring15MCRC();
    }
    else if(elID=="CBLooseRC"){
      iLep->Tight=iel->cutBasedLoose25nsSpring15MCRC();
      iLep->Loose=true;
    }
    else if(elID=="MVATight"){
      iLep->Tight=iel->mvaTightIso();
      iLep->Loose=iel->mvaLooseIso();
    }
    else if(elID=="MVATightNew"){
      iLep->Tight=iel->mvaTightNew();
      iLep->Loose=iel->mvaLooseNew();
    }
    else if(elID=="MVATightNewRC"){
      iLep->Tight=iel->mvaTightNewRC();
      iLep->Loose=iel->mvaLooseNewRC();
    }
    else if(elID=="MVATightNoIso"){
      iLep->Tight=iel->mvaTight();
      iLep->Loose=iel->mvaLoose();
    }
    else if(elID=="MVALoose"){
      iLep->Tight=iel->mvaLooseIso();
      iLep->Loose=true;
    }
    else if(elID=="MVALooseNoIso"){
      iLep->Tight=iel->mvaLoose();
      iLep->Loose=true;
    }
    else if(elID=="MVATightCC"){
      iLep->Tight=iel->mvaTightCCIso();
      iLep->Loose=iel->mvaLooseCCIso();
    }
    else if(elID=="MVATightCCNoIso"){
      iLep->Tight=iel->mvaTightCC();
      iLep->Loose=iel->mvaLooseCC();
    }
    else if(elID=="MVALooseCC"){
      iLep->Tight=iel->mvaLooseCCIso();
      iLep->Loose=true;
    }
    else if(elID=="MVALooseNoIso"){
      iLep->Tight=iel->mvaLoose();
      iLep->Loose=true;
    }  
    else if(elID=="MVATightRC"){
      iLep->Tight=iel->mvaTightRCIso();
      iLep->Loose=iel->mvaLooseRCIso();
    }
    else if(elID=="MVALooseRC"){
      iLep->Tight=iel->mvaLooseRCIso();
      iLep->Loose=true;
    }
    else if(elID=="SUSYTight"){
      iLep->Tight=iel->susyTight();
      iLep->Loose=iel->susyLoose();
    }
    else if(elID=="SUSYLoose"){
	iLep->Tight=iel->susyLoose();
	iLep->Loose=true;
    }
    else if(elID=="SUSYTightRC"){
      iLep->Tight=iel->susyTightRC();
      iLep->Loose=iel->susyLooseRC();
    }      
    if(iLep->pt<ptCut) continue;
    //now save based on elID requirments if 'normal' running then require tight, else save if loose
    if(!doFakes){
      if(iLep->Tight) Leptons.push_back(iLep);
    } 
    else{ //if doing fake estimate save if loose
      if(iLep->Loose) Leptons.push_back(iLep);
    }

 
  }
  
  return Leptons;

}

bool checkSameSignLeptons(std::vector<TLepton*> leptons){

  bool samesign=false;

  for(unsigned int uilep=0; uilep<leptons.size(); uilep++){
    for(unsigned int ujlep=uilep+1; ujlep<leptons.size(); ujlep++){
      if(leptons.at(uilep)->charge == leptons.at(ujlep)->charge){
	samesign=true;
      }
    }
  }

  return samesign;
  
}

bool checkOppositeSignLeptonsForDY(std::vector<TLepton*> leptons){


  bool oppositeSign=false;
  bool sameSign=false;
  float pairMass=-999;
  float minDiff=99999;

  TLepton* Lep1 =0;
  TLepton* Lep2 =0;

  for(unsigned int uilep=0; uilep<leptons.size(); uilep++){
    TLepton* lep1 = leptons.at(uilep);
    for(unsigned int ujlep=uilep+1; ujlep<leptons.size(); ujlep++){
      TLepton* lep2 = leptons.at(ujlep);
      //check for hardest
      if(lep1->charge==lep2->charge) sameSign=true;
      if(lep1->charge!=lep2->charge) {
	oppositeSign=true;
	Lep1=lep1;
	Lep2=lep2;
      }
    }
  
  }
  std::string os = oppositeSign ? "true" : "false";


  //now don't allow any events with samesign dileptons to pass
  if(sameSign) return false;
  //else return whether or not there were indeed opposite sign leptons
  else{
    if(oppositeSign){
      if(Lep1->isMu && Lep2->isMu) return false; //skipp mumu events
      else return true;
    }
    else return false;
  }
}


std::vector<TLepton*> makeSSLeptons(std::vector<TLepton*> leptons){

  std::vector<TLepton*> vSSLep;

  for(unsigned int uilep=0; uilep<leptons.size(); uilep++){
    for(unsigned int ujlep=uilep+1; ujlep<leptons.size(); ujlep++){
      if(leptons.at(uilep)->charge == leptons.at(ujlep)->charge){
	
	vSSLep.push_back(leptons.at(uilep));
	vSSLep.push_back(leptons.at(ujlep));

      }
    }
  }

  return vSSLep;
  
}

std::vector<TLepton*> makeOSLeptonsForDY(std::vector<TLepton*> leptons){

  std::vector<TLepton*> vSSLep;
  

  for(unsigned int uilep=0; uilep<leptons.size(); uilep++){
    TLepton* lep1 = leptons.at(uilep);
    for(unsigned int ujlep=uilep+1; ujlep<leptons.size(); ujlep++){
      TLepton* lep2 = leptons.at(ujlep);
      //if both are muons don't save pair
      if(lep1->isMu && lep2->isMu) continue;
      if(lep1->charge != lep2->charge){
	vSSLep.push_back(lep1);
	vSSLep.push_back(lep2);
      }
    }
  }



  return vSSLep;

}

int getNSSDLGen(std::vector<TGenParticle*> genParticles, int nMu){

  bool samesign;
 
  int flav1=-999;
  int flav2=-999;

  for(unsigned int uigen=0; uigen < genParticles.size(); uigen++){
    //only check particles from the hard scattering
    //if( genParticles.at(uigen)->status!=23) continue;
    //only check electrons and muons
    if( !( abs(genParticles.at(uigen)->id)==11 || abs(genParticles.at(uigen)->id)==13) ) continue;
    for(unsigned int ujgen=0;  ujgen < genParticles.size(); ujgen++){
      //only check particles from the hard scattering
    if( genParticles.at(ujgen)->status!=23) continue;
      if(ujgen==uigen) continue;
      //std::cout<<"flavor 1: "<<genParticles.at(uigen)->id<<" w/ charge: "<<genParticles.at(uigen)->charge<<" flavor 2: "<<genParticles.at(ujgen)->id<<" w/ charge: "<<genParticles.at(ujgen)->charge<<std::endl;
      //only check electrons and muons
      if( !( abs(genParticles.at(ujgen)->id)==11 || abs(genParticles.at(ujgen)->id)==13) ) continue;
      if( genParticles.at(uigen)->charge == genParticles.at(ujgen)->charge){
	samesign = true;
	flav1 = abs(genParticles.at(uigen)->id);
	flav2 = abs(genParticles.at(ujgen)->id);
      }
    }

  }

  //std::cout<<"\n *** End Event *** \n"<<std::endl;

  if(!samesign) return 0;

  if(nMu==2){
    if( flav1 ==13 && flav2==13) return 1;
    else return 0;
  }

  if(nMu==1){
    if( (flav1==11 && flav2==13) || (flav1==13 || flav2==11) ) return 1;
    else return 0;
  }


  if(nMu==0){
    if( flav1==11 && flav2==11) return 1;
    else return 0;
  }

  //in case none above 
  return 0;

}


void printParticle(TGenParticle* p){
	std::cout<<"genP id: "<<p->id<<" charge "<<p->charge<<" status: "<<p->status<<" pt: "<<p->pt<<" eta: "<<p->eta<<" phi: "<<p->phi<<std::endl;
}

void printParticle(TLepton* l){
	std::cout<<"charge "<<l->charge<<" pt: "<<l->pt<<" eta: "<<l->eta<<" phi: "<<l->phi<<std::endl;
}

std::pair<bool,float> checkSecondaryZVeto(std::vector<TLepton*> leps, std::vector<TMuon*> muons, std::vector<TElectron*> electrons){

  bool veto=false;
  float assocMass=-999;
  float zmass=91.1;

  for(std::vector<TLepton*>::size_type ilep=0; ilep < leps.size(); ilep++){
    // get lepton
    TLepton* lep = leps.at(ilep);

    //if muon check to find mass w/ other muons
    if(lep->isMu){
      for(std::vector<TMuon*>::size_type imu=0; imu< muons.size(); imu++){
	//skip if loose lepton has pt <= 15 GeV
	if(muons.at(imu)->pt<=15) continue;

	//skip if looking at any of the SS leptons:
	bool skip=false;
	for(std::vector<TLepton*>::size_type jlep =0; jlep<leps.size(); jlep++){
	  if(leps.at(jlep)->pt==muons.at(imu)->pt && leps.at(jlep)->phi==muons.at(imu)->phi){skip=true; break;}
	}
	if(skip) continue; 

	float diff =  getPairMass(lep,muons.at(imu)) - zmass;
	if(fabs(diff) < 15){ veto=true; assocMass = zmass+diff; break;}
      }
    }
    //else check mass w/ other electrons
    else{
      for(std::vector<TElectron*>::size_type iel=0; iel< electrons.size(); iel++){
	//skip if loose electron pt <= 15 GeV
	if(electrons.at(iel)->pt <= 15) continue;

	//skip if looking at any of the SS leptons:
	bool skip=false;
	for(std::vector<TLepton*>::size_type jlep =0; jlep<leps.size(); jlep++){
	  if(leps.at(jlep)->pt==electrons.at(iel)->pt && leps.at(jlep)->phi==electrons.at(iel)->phi){skip=true; break;}
	}
	if(skip) continue; 

	float diff =  getPairMass(lep,electrons.at(iel)) - zmass;
	if(fabs(diff) < 15){ veto=true; assocMass = zmass+diff; break;}
      }
    }
  }

  std::pair<bool,float> checkAndMass(veto,assocMass);
  return checkAndMass;

}


std::vector<TLepton*> pruneSSLep(std::vector<TLepton*> allLeps, std::vector<TLepton*> ssLeps){

  std::vector<TLepton*> nonSSLeps;


  for(std::vector<TLepton*>::size_type ilep=0; ilep<allLeps.size();ilep++){
    //std::cout<<"SSLep 1 pt, eta, phi: "<<ssLeps.at(0)->pt<<", "<<ssLeps.at(0)->eta<<", "<<ssLeps.at(0)->phi<<" SSLep 2 pt, eta, phi: "<<ssLeps.at(1)->pt<<", "<<ssLeps.at(1)->eta<<", "<<ssLeps.at(1)->phi<<" current lep pt, eta, phi: "<<allLeps.at(ilep)->pt<<", "<<allLeps.at(ilep)->eta<<", "<<allLeps.at(ilep)->phi<<std::endl;
    if( (allLeps.at(ilep)->pt==ssLeps.at(0)->pt && allLeps.at(ilep)->eta==ssLeps.at(0)->eta && allLeps.at(ilep)->phi==ssLeps.at(0)->phi) || (allLeps.at(ilep)->pt==ssLeps.at(1)->pt && allLeps.at(ilep)->eta==ssLeps.at(1)->eta && allLeps.at(ilep)->phi==ssLeps.at(1)->phi) || (!allLeps.at(ilep)->Tight) ){ //skip non tight since loose leptons can make it here from np background
    }
    else(nonSSLeps.push_back(allLeps.at(ilep)) );

  }
  //std::cout<<" done pruning for this event and found "<<nonSSLeps.size()<<" nonSSleptons \n \n";
  return nonSSLeps;
}
