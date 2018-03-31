#include "TROOT.h"
#include <TChain.h>
#include "heep.C"
#include <fstream>
#include "../header_files/useful_functions.h"

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

  Double_t cpu_LT;    //computer Live Time
  Double_t elec_LT;   //electronic Live Time
  
  Int_t runNUM;
  Int_t evtNUM;

  
  
  //Chain each file

  TString simc_file;
  TString data_file;
  TString rep_file;
  
  /*
  //--Estimate Spectrometer Resolution
  Ib = 40.;
  time = 1.;
  simc_file = "heep_simc_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("../worksim/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, Ib, time);
  chain.Reset();
  */
  
  /*
  //E12-10-003 H(e,e'p) Check!

  //------Get TRUE accumulated charge from actual data to use in SIMC--------
  runNUM = 1854;
  evtNUM = -1;
  data_file = Form("../ROOTfiles/coin_replay_production_%d_%d.root", runNUM, evtNUM);
  Q1 = getCharge("SHMS", "BCM4A", data_file);
  Q2 = getCharge("SHMS", "BCM4B", data_file);
  charge = (Q1 + Q2)/2.;
  //-------------------------------------------------------------------------
    
  simc_file = Form("heep_simc_rad_%d_%d.root", runNUM, evtNUM);
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("../worksim/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, charge);
  chain.Reset();
  */ 

  //----Practice HEEP check using coin run 1854---
  runNUM = 1854;
  evtNUM = -1;
  data_file = Form("../../../ROOTfiles/coin_replay_production_%d_%d.root", runNUM, evtNUM);
  Q1 = getCharge("SHMS", "BCM4A", data_file);
  Q2 = getCharge("SHMS", "BCM4B", data_file);
  charge = (Q1 + Q2)/2.;

  rep_file = "../CHARGE_REPORTS/";
  

  //-------------------------------------------------------------------------
    
  simc_file = Form("ep_coin_simc_%d.root", runNUM);
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("~/cyero/sims_heep/worksim/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, charge);
  chain.Reset();
  
  /*
  
  //Coin Run 1929
  //electron_arm = "HMS";
  Ib = 40.;
  time = 1.;
  simc_file = "ep_coin_simc_1929.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("../worksim/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, Ib, time);
  chain.Reset();

  
  
  //Coin Run 2279
  electron_arm = "SHMS";
  simc_file = "ep_coin_simc_1929.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("../worksim/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, electron_arm);
  chain.Reset();
  */

}


