#include "TROOT.h"
#include <TChain.h>
#include "heep.C"
#include <fstream>
#include "../../header_files/useful_functions.h" 

// run an analysis based on SNT.C the analyysis script for the simc n-tuple
// this script is setup for the proposed commissioning runs. the steps in pm are 0.15 GeV/c

void analyze_simc()
{

  gROOT->Reset();

  //Create a TChain
  TChain chain("SNT");

  //Create an instance of the heep class
  heep* simc = new heep(&chain);

  
  TString electron_arm;

  Double_t Ib;       //beam current in uA
  Double_t time;     //TIME in hrs

  Double_t charge;
  Double_t Q1, Q2;

  Double_t h_trkEff;   //hadron tracking eff
  Double_t e_trkEff;   //electron tracking eff

  Double_t c_LT;    //computer Live Time
  Double_t elec_LT;   //electronic Live Time
  
  Int_t runNUM;
  Int_t evtNUM;

  
  
  //Chain each file

  TString simc_file;
  TString data_file;
  TString report_file;
  

 
  /*
  //----Practice HEEP check using coin run 1854---
  runNUM = 1854;
  evtNUM = -1;

  simc_file = Form("ep_coin_simc_%d.root", runNUM);
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 40, 1, 1);
  chain.Reset();
  //--------------------------------------------
  */


  //------NON-REALISTIC Estimation of Full Weigth--------

  //The actual charge of the run is not used, so we
  //dont use the accumulated charge from data, and set 
  //efficiencies to unity when determining the full weight
  /*
  //E12-10-003 H(e,e'p) Check SIMC
  Ib = 40;     //Assume 40 uA
  time = 1.0;  //beam time 1hr
  simc_file = "heep_simc_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, Ib, time, 1);
  chain.Reset();
  */
  //--------------------------------------------



  //------REALISTIC Estimation of Full Weight---------
  runNUM = 1854;
  evtNUM = -1;

  data_file = Form("../../../../ROOTfiles/coin_replay_production_%d_%d.root", runNUM, evtNUM );
  report_file = Form("../../../online/CHARGE_REPORTS/heep_report_%d.report", runNUM);

  //Get the accumulated charge from data_file
  Q1 = getCharge("SHMS", "BCM4A", data_file); 
  Q2 = getCharge("SHMS", "BCM4B", data_file);
  charge = (Q1 + Q2)/2.;

  //Get tracking efficinecies and cpu livetime from report file
  e_trkEff = getVal(report_file, "SHMS E SING FID TRACK EFFIC", "val");
  h_trkEff = getVal(report_file, "HMS HADRON SING FID TRACK EFFIC", "val");
  c_LT = getVal(report_file, "ROC2 Pre-Scaled Ps1 ROC2 Computer Live Time", "val");
  c_LT = c_LT/100.;  //convert from percern to fraction
  if (c_LT<=0 || c_LT >= 1) {c_LT = 1.0;}  //
  //E12-10-003 H(e,e'p) Check SIMC
  simc_file = "heep_simc_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, charge, e_trkEff, h_trkEff, c_LT);
  chain.Reset();





}


