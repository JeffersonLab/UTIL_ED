#include "TROOT.h"
#include <TChain.h>
#include "deep.C"
#include <fstream>
#include "../../header_files/useful_functions.h" 


// run an analysis based on SNT.C the analyysis script for the simc n-tuple
// this script is setup for the proposed commissioning runs. the steps in pm are 0.15 GeV/c

void analyze_simc(TString Pmiss, int runNUM=1, int evtNUM=-1)
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
  
  int run_min;
  int run_max;
  int runTOT;

    if(Pmiss=="80")
      {
	run_min = runNUM;
	run_max = runNUM;
	runTOT = run_max - run_min + 1;

      }

    else if (Pmiss=="580")
      {
	run_min = 3290;
	run_max = 3305;
	runTOT = 1;
      }


    else if (Pmiss=="750")
      {
       	run_min = 3306;
        run_max = 3340;
        runTOT = 1;
      }

	cout << "Everything OK before loop . . . " << endl;
 
    //-------------------REALISTIC Estimation of Full Weight-----------------------

  //Loop over all runs

  for (int run = run_min; run <=run_max; run++)
    {
	cout << "InLOOP: run " << run << endl;
      if (run==3290 || run==3303 || run==3304 || run==3326) {continue;}
      runTOT = runTOT+1;
      data_file =Form("../../../../ROOTfiles/coin_replay_production_%d_%d.root", run, evtNUM);
      // coin_replay_production_3267_-1olddelta.root

      report_file = Form("../../../online/CHARGE_REPORTS/deep_report_%d.report", run);
      
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
  
  h_trkEff_AVG = h_trkEff_SUM / runTOT;
  e_trkEff_AVG = e_trkEff_SUM / runTOT;
  c_LT_AVG = c_LT_SUM / runTOT;

  cout << "*****************************************" << endl;
  cout << "" << endl;
  cout << "SIMC: Setting the following for simulation . . ." << endl;
  cout << "Avg. TOTAL Charge = " << chargeTOTAL << " uC" << endl;
  cout << "Avg. e- trkEff = " << e_trkEff_AVG <<  endl;
  cout << "Avg hadron trkEff = " << h_trkEff_AVG <<  endl;
  cout << "Avg CPU Live Time = " << c_LT_AVG <<  endl;
  cout << "*****************************************" << endl;




  if (Pmiss=="80")
    {

      cout << "Doing 80 MeV setting " << endl;	

  //--------D(e,e'p)n---PWIA---Pmiss = 80 MeV-----------------
  
  simc_file = "d2_pm80_lagetpwia_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, chargeTOTAL, 1, 1, 1);
  chain.Reset();
  
  
  //--------D(e,e'p)n---FSI---Pmiss = 80 MeV-----------------

  simc_file = "d2_pm80_lagetfsi_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, chargeTOTAL, 1, 1, 1);
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
  simc->Loop(simc_file, 1, 1, chargeTOTAL, 1, 1, 1);
  chain.Reset();

  //--------D(e,e'p)n---FSI---Pmiss = 580 MeV-----------------
  
  simc_file = "d2_pm580_lagetfsi_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, chargeTOTAL, 1, 1, 1);
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
  simc->Loop(simc_file, 1, 1, chargeTOTAL, 1, 1, 1);
  chain.Reset();
     
  
  //--------D(e,e'p)n---FSI---Pmiss = 750 MeV-----------------
  
  simc_file = "d2_pm750_lagetfsi_rad.root";
  cout << "Analyzing: " << simc_file << endl;
  chain.Add("./worksim_voli/"+simc_file);
  simc->Init(&chain);
  simc->Loop(simc_file, 1, 1, chargeTOTAL, 1, 1, 1);
  chain.Reset();

  //-----------------------------------------------------------
  
    }



  
}


