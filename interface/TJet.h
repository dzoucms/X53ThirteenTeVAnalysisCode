#ifndef TJet_h
#define TJet_h

#include <TLorentzVector.h>
#include <cmath>
#include <iostream>

class TJet{
 public:
  TJet(double pttemp, double etatemp, double phitemp, double energytemp);
  //kinematics
  double pt;
  double eta;
  double phi;
  double energy;

  TJet(const TJet& jet);
  ~TJet();
  TLorentzVector lv;

  void setLV(){
    lv.SetPxPyPzE(pt*cos(phi), pt*sin(phi), pt*TMath::SinH(eta), energy);
  }
};
#endif
