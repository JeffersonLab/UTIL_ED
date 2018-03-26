Double_t getCharge(string spec, string bcm, TString filename)
{
   /*Brief: Get the accumulated charge if beam current was above threhsold (typically > 5 uA)
   */

  /*PARAMETERS: 
    spec --> "HMS" or "SHMS"
    bcm --> "BCM1", "BCM2", "BCM4A", "BCM4B", "BCM17"
    filename --> "/path/to/ROOTfile/file.root"
  */
  
  TFile *data_file = new TFile(filename, "READ");
  Double_t charge;    //in uC

  if (spec=="HMS")
    {

      TTree *TSH = (TTree*)data_file->Get("TSH");		
      
      if (bcm=="BCM1") { charge = TSH->GetMaximum("H.BCM1.scalerChargeCut"); }
      else if (bcm=="BCM2") { charge = TSH->GetMaximum("H.BCM2.scalerChargeCut"); }                                     
      else if (bcm=="BCM4A") { charge = TSH->GetMaximum("H.BCM4A.scalerChargeCut"); }                                       
      else if (bcm=="BCM4B") { charge = TSH->GetMaximum("H.BCM4B.scalerChargeCut"); }    
      else if (bcm=="BCM17") { charge = TSH->GetMaximum("H.BCM17.scalerChargeCut"); }                        
      return charge;
      
    }
	  
  else if (spec=="SHMS")
    {
      
      TTree *TSP = (TTree*)data_file->Get("TSP");		
      
      if (bcm=="BCM1") { charge = TSP->GetMaximum("P.BCM1.scalerChargeCut"); }
      else if (bcm=="BCM2") { charge = TSP->GetMaximum("P.BCM2.scalerChargeCut"); }                                     
      else if (bcm=="BCM4A") { charge = TSP->GetMaximum("P.BCM4A.scalerChargeCut"); }                                       
      else if (bcm=="BCM4B") { charge = TSP->GetMaximum("P.BCM4B.scalerChargeCut"); }    
      else if (bcm=="BCM17") { charge = TSP->GetMaximum("P.BCM17.scalerChargeCut"); }                        
      return charge;
      
    }
}

Double_t get_runtime(string spec, TString filename)
{

  /*Brief: Get the run time (in sec.) if beam current was above threhsold (typically > 5 uA)
   */

  /*PARAMETERS: 
    spec --> "HMS" or "SHMS"
    filename --> "/path/to/ROOTfile/file.root"
  */
  
  TFile *data_file = new TFile(filename, "READ");
  Double_t time;    //in uC

  if (spec=="HMS")
    {
      TTree *TSH = (TTree*)data_file->Get("TSH");		
      time = TSH->GetMaximum("H.1Mhz.scalerTimeCut");                         
      return time;
    }
	  
  else if (spec=="SHMS")
    {
      TTree *TSP = (TTree*)data_file->Get("TSP");		
      time = TSP->GetMaximum("P.1Mhz.scalerTimeCut");
      return time;
    }
}


//------------------------------MAIN CODE--------------------------------------

void charge_counter(string exp, int run_num, int evtNUM)
{

  using namespace std;
  
  TString hadron_arm;
  TString electron_arm;

  hadron_arm = "HMS";
  electron_arm = "SHMS";
    
  
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
   TH1F *data_Emiss = new TH1F("data_Emiss","missing energy", 50, -0.5, 0.8);  //binwidth = 0.0025
   TH1F *data_pm = new TH1F("data_pm","missing momentum", bins, -0.05, 1.7);
   TH1F *data_W = new TH1F("data_W", "Invariant Mass, W", bins, 0.4, 2.0);

   //Kinematics Quantities with cuts
   TH1F *cut_data_Emiss = new TH1F("cut_data_Emiss","missing energy Cut", 50, -0.5, 0.8);  //binwidth = 0.0025
   TH1F *cut_data_pm = new TH1F("cut_data_pm","missing momentum w/ Emiss Cut", bins, -0.05, 1.7);
   TH1F *cut_data_W = new TH1F("cut_data_W", "Invariant Mass w/ Emiss Cut, W", bins, 0.4, 2.0);

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
   c1->Divide(1,3);

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


   c1->Update();
   c1->SaveAs("./UTIL_ED/temp.pdf");
   //Determine the W integral
   Double_t Yield;
   Double_t cut_Yield;

   Yield = data_W->Integral();
   cut_Yield = cut_data_W->Integral();

   //Get the total charge(if beam > 5uA) from the run
   Double_t Q1,Q2;
   Double_t charge;

   Q1 = getCharge("SHMS", "BCM4A", file_path);
   Q2 = getCharge("SHMS", "BCM4B", file_path);
   cout << "Q1 = " << Q1 << endl;
   cout << "Q2 = " << Q2 << endl;
   charge = (Q1 + Q2)/2.;
   cout << "charge = " << charge << endl;
   //Get the total counts/charge
   Double_t Ratio;
   Double_t cut_Ratio;

   Ratio = Yield / charge;
   cut_Ratio = cut_Yield / charge;

   //Append the counts / charge to the report
   string report_path = Form("./UTIL_ED/CHARGE_REPORTS/%s_report_%d.report",exp.c_str(), run_num);
        
   ofstream outreport;
   outreport.open(report_path.c_str(), std::ios_base::app);
   outreport << "    " << endl;                                                
   outreport << "****************" << endl;
   outreport << "Yield / Charge :  " << Yield <<" / " << charge << " = " << Ratio << " Counts/uC" << endl;
   outreport << "Yield / Charge (w/ Em cut) :  " << cut_Yield << " / "<< charge << " = "<< cut_Ratio << " Counts/uC" << endl;;
   outreport << "****************" << endl;
   
   
   outreport.close();

   
     
   // outfile->Write();
   //outfile->Close();

}
