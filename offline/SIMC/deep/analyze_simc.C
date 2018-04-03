#include "TROOT.h"
#include <TChain.h>
#include "deep.C"
#include <fstream>
#include "../../header_files/useful_functions.h" 


// run an analysis based on SNT.C the analyysis script for the simc n-tuple
// this script is setup for the proposed commissioning runs. the steps in pm are 0.15 GeV/c

void analyze_simc(int runNUM, int evtNUM, TString Pmiss)
{

  gROOT->Reset();

  //Create a TChain
  TChain chain("SNT");

  //Create an instance of the heep class
  deep* simc = new deep(&chain);

  
  TString electron_arm;

  Double_t Ib;       //beam current in uA
  Double_t time;     //TIME in hrs

  Double_t charge;
  Double_t Q1, Q2;

  Double_t h_trkEff;   //hadron tracking eff
  Double_t e_trkEff;   //electron tracking eff

  Double_t c_LT;    //computer Live Time
  Double_t elec_LT;   //electronic Live Time
  

  
  
  //Chain each file

  TString simc_file;
  TString data_file;
  TString report_file;
  

  //-------------NON-REALISTIC Estimation of Full Weigtht----------------

  //The actual charge of the run is not used, so we
  //dont use the accumulated charge from data, and set 
  //efficiencies to unity when determining the full weight
  
  /*
  //--------D(e,e'p)n---PWIA---Pmiss = 80 MeV-----------------
  Ib = 40;     //beam current [uA]
  time = 1.;   //beam time [hrs]
  simc_file = "d2_pm80_lagetpwia_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, Ib, time, 1.);
  chain.Reset();

  //----------------------------------------------------
  
  
  //--------D(e,e'p)n---FSI---Pmiss = 80 MeV-----------------
  Ib = 40;     //beam current [uA]
  time = 1.;   //beam time [hrs]
  simc_file = "d2_pm80_lagetfsi_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, Ib, time, 1.);
  chain.Reset();

  //----------------------------------------------------
  

 //--------D(e,e'p)n---PWIA---Pmiss = 580 MeV-----------------
  Ib = 40;     //beam current [uA]
  time = 20.;   //beam time [hrs]
  simc_file = "d2_pm580_lagetpwia_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, Ib, time, 1.);
  chain.Reset();

  //----------------------------------------------------
  
  
  //--------D(e,e'p)n---FSI---Pmiss = 580 MeV-----------------
  Ib = 40;     //beam current [uA]
  time = 20.;   //beam time [hrs]
  simc_file = "d2_pm580_lagetfsi_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, Ib, time, 1.);
  chain.Reset();

  //----------------------------------------------------
  

 //--------D(e,e'p)n---PWIA---Pmiss = 750 MeV-----------------
  Ib = 40;     //beam current [uA]
  time = 42.;   //beam time [hrs]
  simc_file = "d2_pm750_lagetpwia_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, Ib, time, 1.);
  chain.Reset();

  //----------------------------------------------------
  
  
  //--------D(e,e'p)n---FSI---Pmiss = 750 MeV-----------------
  Ib = 40;     //beam current [uA]
  time = 42.;   //beam time [hrs]
  simc_file = "d2_pm750_lagetfsi_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, Ib, time, 1.);
  chain.Reset();

  //----------------------------------------------------
  */


    //-------------------REALISTIC Estimation of Full Weight-----------------------


  data_file = Form("../../../../ROOTfiles/coin_replay_production_%d_%d.root", runNUM, evtNUM );
  report_file = Form("../../../online/CHARGE_REPORTS/deep_report_%d.report", runNUM);

  //Get the accumulated charge from data_file
  Q1 = getCharge("SHMS", "BCM4A", data_file); 
  Q2 = getCharge("SHMS", "BCM4B", data_file);
  charge = (Q1 + Q2)/2.;

  //Get tracking efficinecies and cpu livetime from report file
  e_trkEff = getVal(report_file, "SHMS E SING FID TRACK EFFIC", "val");
  h_trkEff = getVal(report_file, "HMS HADRON SING FID TRACK EFFIC", "val");
  c_LT = getVal(report_file, "ROC2 Pre-Scaled Ps6 ROC2 Computer Live Time", "val");
 
  c_LT = c_LT/100.;  //convert from percern to fraction

  cout << "*****************************************" << endl;
  cout << "" << endl;
  cout << "SIMC: Setting the following for simulation . . ." << endl;
  cout << "Q1 (BCM4A) = " << Q1 << " uC" << endl;
  cout << "Q2 (BCM4A) = " << Q2 << " uC" << endl;
  cout << "Avg. Charge = " << charge << " uC" << endl;
  cout << "e- trkEff = " << e_trkEff <<  endl;
  cout << "hadron trkEff = " << h_trkEff <<  endl;
  cout << "CPU Live Time = " << c_LT <<  endl;
  cout << "*****************************************" << endl;




  if (Pmiss=="80")
    {
  
  //--------D(e,e'p)n---PWIA---Pmiss = 80 MeV-----------------
  
  simc_file = "d2_pm80_lagetpwia_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, charge, e_trkEff, h_trkEff, c_LT);
  chain.Reset();
  
  //--------D(e,e'p)n---FSI---Pmiss = 80 MeV-----------------

  simc_file = "d2_pm80_lagetfsi_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, charge, e_trkEff, h_trkEff, c_LT);
  chain.Reset();

  //-----------------------------------------------------------

    }

  if (Pmiss=="580")
    {
  //--------D(e,e'p)n---PWIA---Pmiss = 580 MeV-----------------
  
  simc_file = "d2_pm580_lagetpwia_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, charge, e_trkEff, h_trkEff, c_LT);
  chain.Reset();

  //--------D(e,e'p)n---FSI---Pmiss = 580 MeV-----------------
  
  simc_file = "d2_pm580_lagetfsi_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, charge, e_trkEff, h_trkEff, c_LT);
  chain.Reset();

  //-----------------------------------------------------------
    }

  if(Pmiss=="750")
    {

    //--------D(e,e'p)n---PWIA---Pmiss = 750 MeV-----------------
  
  simc_file = "d2_pm750_lagetpwia_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, charge, e_trkEff, h_trkEff, c_LT);
  chain.Reset();

  //--------D(e,e'p)n---FSI---Pmiss = 750 MeV-----------------
  
  simc_file = "d2_pm750_lagetfsi_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, charge, e_trkEff, h_trkEff, c_LT);
  chain.Reset();

  //-----------------------------------------------------------

    }



  
}


