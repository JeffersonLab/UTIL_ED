#include "TROOT.h"
#include <TChain.h>
#include "deep.C"
#include <fstream>
#include "../../header_files/useful_functions.h" 


// run an analysis based on SNT.C the analyysis script for the simc n-tuple
// this script is setup for the proposed commissioning runs. the steps in pm are 0.15 GeV/c

void analyze_highPmsimc(int evtNUM, TString Pmiss)
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
  
  //Define Average quantities for High Pmiss, since
  //it is likely that we will have to combine multiple 
  //root files due to low statistics.
  Double_t chargeTOTAL = 0.0;
   
  Double_t c_LT_SUM = 0.0;
  Double_t h_trkEff_SUM = 0.0;
  Double_t e_trkEff_SUM = 0.0;
  
  Double_t c_LT_AVG;
  Double_t h_trkEff_AVG;
  Double_t e_trkEff_AVG;
  

  
  
  //Chain each file
  TString simc_file;
  TString data_file;
  TString report_file;
  
  int runNUM;
  int runMAX = 1;
  int run_list[runMAX] = {1851};
 
    //-------------------REALISTIC Estimation of Full Weight-----------------------

  //Loop over all runs

  for (int i = 0; i < runMAX; i++)
    {

      runNUM = run_list[i];

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

      //Calculate Average Quantities
      chargeTOTAL = chargeTOTAL + charge;

      h_trkEff_SUM =  h_trkEff_SUM + h_trkEff;
      e_trkEff_SUM =  e_trkEff_SUM + e_trkEff;
      c_LT_SUM = c_LT_SUM + c_LT;

    }
  
  h_trkEff_AVG = h_trkEff_SUM / runMAX;
  e_trkEff_AVG = e_trkEff_SUM / runMAX;
  c_LT_AVG = c_LT_SUM / runMAX;

  cout << "*****************************************" << endl;
  cout << "" << endl;
  cout << "SIMC: Setting the following for simulation . . ." << endl;
  cout << "Q1 (BCM4A) = " << Q1 << " uC" << endl;
  cout << "Q2 (BCM4B) = " << Q2 << " uC" << endl;
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
  simc->Loop(simc_file, 1, 1, chargeTOTAL, e_trkEff_AVG, h_trkEff_AVG, c_LT_AVG);
  chain.Reset();
  
  //--------D(e,e'p)n---FSI---Pmiss = 80 MeV-----------------

  simc_file = "d2_pm80_lagetfsi_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, chargeTOTAL, e_trkEff_AVG, h_trkEff_AVG, c_LT_AVG);
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
  simc->Loop(simc_file, 1, 1, chargeTOTAL, e_trkEff_AVG, h_trkEff_AVG, c_LT_AVG);
  chain.Reset();

  //--------D(e,e'p)n---FSI---Pmiss = 580 MeV-----------------
  
  simc_file = "d2_pm580_lagetfsi_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, chargeTOTAL, e_trkEff_AVG, h_trkEff_AVG, c_LT_AVG);
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
  simc->Loop(simc_file, 1, 1, chargeTOTAL, e_trkEff_AVG, h_trkEff_AVG, c_LT_AVG);
  chain.Reset();

  //--------D(e,e'p)n---FSI---Pmiss = 750 MeV-----------------
  
  simc_file = "d2_pm750_lagetfsi_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, chargeTOTAL, e_trkEff_AVG, h_trkEff_AVG, c_LT_AVG);
  chain.Reset();

  //-----------------------------------------------------------

    }



  
}


