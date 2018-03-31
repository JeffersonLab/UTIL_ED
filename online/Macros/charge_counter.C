#include "../../offline/header_files/set_heep_histos.h"
#include "../../offline/header_files/useful_functions.h"

//------------------------------MAIN CODE--------------------------------------

void charge_counter(string exp, int run_num, int evtNUM)
{

  using namespace std;
  
  TString hadron_arm;
  TString electron_arm;

  hadron_arm = "HMS";
  electron_arm = "SHMS";

  gROOT->SetBatch(kTRUE);  //prevent root from showing graphicaloutput
  
  //Open data ROOTfile and call TTree
  TString file_path;
  file_path = Form("./ROOTfiles/coin_replay_production_%d_%d.root", run_num, evtNUM);
  TFile *data_file = new TFile(file_path, "READ");

  TTree *T = (TTree*)data_file->Get("T");

  //Open root file where new histograms will be stored
  // TFile *outfile = new TFile(Form("ep_coin_data_%d.root", run_num), "recreate");


  //These histograms binning MUST be exactly the same as those used in SIMC heep.C analysis

  //********* Create 1D Histograms **************
   Int_t bins = 100;

   //Kinematics Quantities
   TH1F *data_Emiss = new TH1F("data_Emiss","missing energy", Em_nbins, Em_xmin, Em_xmax);  //binwidth = 0.0025
   TH1F *data_pm = new TH1F("data_pm","missing momentum", Pm_nbins, Pm_xmin, Pm_xmax);
   TH1F *data_W = new TH1F("data_W", "Invariant Mass, W", W_nbins, W_xmin, W_xmax);

   //Kinematics Quantities with cuts
   TH1F *cut_data_Emiss = new TH1F("cut_data_Emiss","missing energy Cut", Em_nbins, Em_xmin, Em_xmax);  //binwidth = 0.0025
   TH1F *cut_data_pm = new TH1F("cut_data_pm","missing momentum w/ Emiss Cut", Pm_nbins, Pm_xmin, Pm_xmax);
   TH1F *cut_data_W = new TH1F("cut_data_W", "Invariant Mass w/ Emiss Cut, W", W_nbins, W_xmin, W_xmax);

   //Cross-Check correlations
   TH2F *data_emiss_vs_pmiss = new TH2F("data_emiss_vs_pmiss", " E_{miss} vs. P_{miss}", 100, -0.1, 1.5, 100, -0.1, 0.5);
   TH2F *data_edelta_vs_eyptar = new TH2F("data_edelta_vs_eyptar", electron_arm + " #delta vs. Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, edelta_nbins, edelta_xmin, edelta_xmax);


    //DEFINE PID CUTS
   TCut pcal = "P.cal.etot>0.1";
   TCut pcer = "P.ngcer.npeSum>1.0";
   
   TCut hcal = "H.cal.etot>0.1";
   TCut hcer = "H.cer.npeSum<1.0";

   //DEFINE KINEMATIC CUTS
   TCut W_cut = "P.kin.primary.W<1.05";   //select events below pion threshold
   TCut em_cut = "H.kin.secondary.emiss>-0.060&&H.kin.secondary.emiss<0.08";    //Emiss (-60, 80) MeV
   TCut xbj_cut = "P.kin.primary.x_bj>0.7&&P.kin.primary.x_bj<1.3"; 

   TCanvas *c1 =  new TCanvas("c1", "", 800,1000);
   c1->Divide(2,3);

   gStyle->SetOptStat("rmnie");
     
   //Draw the Histograms from the TTree
   c1->cd(1);
   data_Emiss->SetLineColor(kRed);
   data_Emiss->SetLineWidth(3);
   cut_data_Emiss->SetLineColor(kBlue);
   cut_data_Emiss->SetLineWidth(3);
 
   T->Draw("H.kin.secondary.emiss>>data_Emiss");
   T->Draw("H.kin.secondary.emiss>>cut_data_Emiss", em_cut, "sames");



   c1->cd(2);
   data_pm->SetLineColor(kRed);
   data_pm->SetLineWidth(3);
   cut_data_pm->SetLineColor(kBlue);
   cut_data_pm->SetLineWidth(3);

   T->Draw("H.kin.secondary.pmiss>>data_pm");
   T->Draw("H.kin.secondary.pmiss>>cut_data_pm", em_cut, "sames");

   c1->cd(3);
   data_W->SetLineColor(kRed);
   data_W->SetLineWidth(3);
   cut_data_W->SetLineColor(kBlue);
   cut_data_W->SetLineWidth(3);
 
   T->Draw("P.kin.primary.W>>data_W");
   T->Draw("P.kin.primary.W>>cut_data_W", em_cut, "sames");

   // Cross-Check correlations
   c1->cd(4);
   T->Draw("H.kin.secondary.emiss:H.kin.secondary.pmiss>>data_emiss_vs_pmiss", em_cut, "colz");
   c1->cd(5);
   T->Draw("P.gtr.dp:P.gtr.ph>>data_edelta_vs_eyptar", em_cut, "colz");

   c1->Update();
   c1->SaveAs("./UTIL_ED/temp.pdf");
   //Determine the W integral
   Double_t Yield;
   Double_t cut_Yield;
   
   if (exp=="heep")
     {
       Yield = data_W->Integral();
       cut_Yield = cut_data_W->Integral();
     }
   else if (exp=="deep")
     {
       Yield = data_pm->Integral();
       cut_Yield = cut_data_pm->Integral();
     }
   
   //Get the total charge(if beam > 5uA) from the run
   Double_t Q1,Q2;
   Double_t charge;

   Q1 = getCharge("SHMS", "BCM4A", file_path);
   Q2 = getCharge("SHMS", "BCM4B", file_path);

   charge = (Q1 + Q2)/2.;
   //Get the total counts/charge
   Double_t Ratio;
   Double_t cut_Ratio;

   Ratio = Yield / charge;
   cut_Ratio = cut_Yield / charge;

   //Append the counts / charge to the report
   string report_path = Form("./UTIL_ED/online/CHARGE_REPORTS/%s_report_%d.report",exp.c_str(), run_num);
        
   ofstream outreport;
   outreport.open(report_path.c_str(), std::ios_base::app);
   // outreport << "    " << endl;                                                
   //outreport << "****************" << endl;
   //outreport << "Yield / Charge :  " << Yield <<" / " << charge << " = " << Ratio << " Counts/uC" << endl;
   outreport << "Yield / Charge (w/ Em cut) :  " << cut_Yield << " / "<< charge << " = "<< cut_Ratio << " Counts/uC" << endl;;
   outreport << " " << endl;
   outreport << Form("***********************Doing %s***************************", exp.c_str()) << endl;
   
   
   outreport.close();

   gSystem->Exit(1); //exit root session
     
   // outfile->Write();
   //outfile->Close();

}
