//Macro to analyze H(e,e'p) E12-10-003 data from Hall C: HMS (Hadron arm), SHMS (electron arm)

#include "set_heep_histos.h"


//HMS Momentum correction: P0 = P0*0.9968
//SHMS Momentum correction: P0 = P0*0.985

void analyze_heep(int runNUM, int evtNUM)
{

  
  //prevent root from displaying graphs while executing
  gROOT->SetBatch(1);

  TString hadron_arm;
  TString electron_arm;

  hadron_arm = "HMS";
  electron_arm = "SHMS";
    
  
  //Open data ROOTfile and call TTree
  TString file_path;
  file_path = Form("../../../ROOTfiles/coin_replay_production_%d_%d.root", runNUM, evtNUM);
  TFile *data_file = new TFile(file_path, "READ");

  TTree *T = (TTree*)data_file->Get("T");

  //Open root file where new histograms will be stored
  TFile *outfile = new TFile(Form("heep_data_%d_%d.root", runNUM, evtNUM), "recreate");


  //These histograms binning MUST be exactly the same as those used in SIMC heep.C analysis

  //Kinematics Quantities
   TH1F *data_Emiss = new TH1F("data_Emiss","missing energy", Em_nbins, Em_xmin, Em_xmax);       //min width = 21.6 (0.0216)MeV,  DATA_OUNTS/25 MeV
   TH1F *data_pm = new TH1F("data_pm","missing momentum", Pm_nbins, Pm_xmin, Pm_xmax);  //min width = 32 MeV (0.032)
   TH1F *data_Q2 = new TH1F("data_Q2","Q2", Q2_nbins, Q2_xmin, Q2_xmax);
   TH1F *data_omega = new TH1F("data_omega","Energy Transfer, #omega", om_nbins, om_xmin, om_xmax);
   TH1F *data_W_inv = new TH1F("data_W_inv", "Invariant Mass, W", W_nbins, W_xmin, W_xmax);     //min width = 19.9 MeV (0.0199) (bin width = 25 MeV)
   TH1F *data_theta_elec = new TH1F("data_theta_elec", "Electron Scatt. Angle", the_nbins, the_xmin, the_xmax);
   TH1F *data_theta_prot = new TH1F("data_theta_prot", "Proton Scatt. Angle", thp_nbins, thp_xmin, thp_xmax);

   //Additional Kinematics Variables
   TH1F *data_W2 = new TH1F("data_W2", "Invariant Mass W2", W2_nbins, W2_xmin, W2_xmax);
   TH1F *data_xbj = new TH1F("data_xbj", "x-Bjorken", xbj_nbins, xbj_xmin, xbj_xmax);
   TH1F *data_Pf = new TH1F("data_Pf", "Final Proton Momentum", Pf_nbins, Pf_xmin, Pf_xmax);
   TH1F *data_kf = new TH1F("data_kf", "Final e^{-} Momentum", kf_nbins, kf_xmin, kf_xmax);

   /*
   //Target Reconstruction Variables
   TH1F *data_x_tar = new TH1F("data_x_tar", "x_Target", xtar_nbins, xtar_xmin, xtar_xmax);
   TH1F *data_y_tar = new TH1F("data_y_tar", "y_Target", ytar_nbins, ytar_xmin, ytar_xmax);
   TH1F *data_z_tar = new TH1F("data_z_tar", "z_Target", ztar_nbins, ztar_xmin, ztar_xmax);
   */
   
   //Hadron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
   TH1F *data_hytar = new TH1F("data_hytar", hadron_arm + " Y_{tar}", hytar_nbins, hytar_xmin, hytar_xmax);
   TH1F *data_hxptar = new TH1F("data_hxptar", hadron_arm + " X'_{tar}", hxptar_nbins, hxptar_xmin, hxptar_xmax);
   TH1F *data_hyptar = new TH1F("data_hyptar", hadron_arm + " Y'_{tar}", hyptar_nbins, hyptar_xmin, hyptar_xmax );
   TH1F *data_hdelta = new TH1F("data_hdelta", hadron_arm + " Momentum Acceptance, #delta", hdelta_nbins, hdelta_xmin, hdelta_xmax);

   //Hadron arm Focal Plane Quantities
   TH1F *data_hxfp = new TH1F("data_hxfp", hadron_arm + " X_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax);
   TH1F *data_hyfp = new TH1F("data_hyfp", hadron_arm + " Y_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax);
   TH1F *data_hxpfp = new TH1F("data_hxpfp", hadron_arm + " X'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax );
   TH1F *data_hypfp = new TH1F("data_hypfp", hadron_arm + " Y'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax);

      
   //Electron Arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
   TH1F *data_eytar = new TH1F("data_eytar", electron_arm + " Y_{tar}", eytar_nbins, eytar_xmin, eytar_xmax);
   TH1F *data_exptar = new TH1F("data_exptar", electron_arm + " X'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax);
   TH1F *data_eyptar = new TH1F("data_eyptar", electron_arm + " Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax);
   TH1F *data_edelta = new TH1F("data_edelta", electron_arm + " Momentum Acceptance, #delta", edelta_nbins, edelta_xmin, edelta_xmax);

   //Electron Arm Focal Plane Quantities
   TH1F *data_exfp = new TH1F("data_exfp", electron_arm + " X_{fp}", exfp_nbins, exfp_xmin, exfp_xmax);
   TH1F *data_eyfp = new TH1F("data_eyfp", electron_arm + " Y_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax);
   TH1F *data_expfp = new TH1F("data_expfp", electron_arm + " X'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax);
   TH1F *data_eypfp = new TH1F("data_eypfp", electron_arm + " Y'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax);

   //Cross-Check correlations
   TH2F *data_emiss_vs_pmiss = new TH2F("data_emiss_vs_pmiss", " E_{miss} vs. P_{miss}", Pm_nbins, Pm_xmin, Pm_xmax, Em_nbins, Em_xmin, Em_xmax);
   TH2F *data_edelta_vs_eyptar = new TH2F("data_edelta_vs_eyptar", electron_arm + " #delta vs. Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, edelta_nbins, edelta_xmin, edelta_xmax);


   //Create 2D Histograms at the Focal Plane Quantities
   TH2F *data_hxfp_vs_hyfp = new TH2F("data_hxfp_vs_hyfp", "X_{fp} vs Y_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, hxfp_nbins, hxfp_xmin, hxfp_xmax);
   TH2F *data_exfp_vs_eyfp = new TH2F("data_exfp_vs_eyfp", "X_{fp} vs Y_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, exfp_nbins, exfp_xmin, exfp_xmax);

   //2D HMS v. SHMS Acceptance Correlations
   TH2F *data_hxptar_vs_exptar = new TH2F("data_hxptar_vs_exptar", "HMS vs. SHMS, X'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);
   TH2F *data_hyptar_vs_eyptar = new TH2F("data_hyptar_vs_eyptar", "HMS vs. SHMS, Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, hyptar_nbins, hyptar_xmin, hyptar_xmax);
   TH2F *data_hdelta_vs_edelta = new TH2F("data_hdelta_vs_edelta", "HMS vs. SHMS, #delta", edelta_nbins, edelta_xmin, edelta_xmax, hdelta_nbins, hdelta_xmin, hdelta_xmax);
  
   
   /*********************************************/
   
   //DEFINE PID CUTS
   TCut pcal = "P.cal.etot>0.1";
   TCut pelec = "P.ngcer.npeSum>1.0";
   
   TCut hprot = "H.cer.npeSum<1.0";
   TCut hcal = "H.cal.etot>0.1";

   //DEFINE KINEMATIC CUTS
   TCut W_cut = "P.kin.primary.W<1.05";   //select events below pion thresshold
   TCut em_cut = "H.kin.secondary.emiss>-0.060&&H.kin.secondary.emiss<0.08";
   TCut Q2_cut = "P.kin.primary.Q2>3&&P.kin.primary.Q2<5.0";
   TCut xbj_cut = "P.kin.primary.x_bj>0.7&&P.kin.primary.x_bj<1.3"; 


   //Draw the Histograms from the TTree

   //Kinematics Quantities, P.* ->SHMS,  H.* -->HMS
   T->Draw("H.kin.secondary.emiss>>data_Emiss", em_cut);
   T->Draw("H.kin.secondary.pmiss>>data_pm", em_cut);
   T->Draw("P.kin.primary.Q2>>data_Q2", em_cut);
   T->Draw("P.kin.primary.nu>>data_omega", em_cut);
   T->Draw("P.kin.primary.W>>data_W_inv", em_cut);
   T->Draw("(P.kin.primary.scat_ang_rad*180./3.14)>>data_theta_elec", em_cut);
   T->Draw("(H.kin.secondary.xangle*180./3.14)>>data_theta_prot", em_cut); 

   //Additional Kinematic Variables
   T->Draw("P.kin.primary.W2>>data_W2", em_cut);
   T->Draw("P.kin.primary.x_bj>>data_xbj", em_cut);
   T->Draw("H.gtr.p>>data_Pf", em_cut);
   T->Draw("P.gtr.p>>(data_kf)", em_cut);

   //Target Reconstruction Variables ????? What are these in data????
   //T->Draw("");
   //T->Draw("");
   //T->Draw("");

   //Hadron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta), theta: xptar, phi:yptar
   T->Draw("H.gtr.y>>data_hytar", em_cut);
   T->Draw("H.gtr.th>>data_hxptar", em_cut);
   T->Draw("H.gtr.ph>>data_hyptar", em_cut);
   T->Draw("H.gtr.dp>>data_hdelta", em_cut);

   //Hadron arm Focal Plane Quantities
   T->Draw("H.dc.x_fp>>data_hxfp", em_cut);
   T->Draw("H.dc.y_fp>>data_hyfp", em_cut);
   T->Draw("H.dc.xp_fp>>data_hxpfp", em_cut);
   T->Draw("H.dc.yp_fp>>data_hypfp", em_cut);
   
   //Electron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta), theta: xptar, phi:yptar
   T->Draw("P.gtr.y>>data_eytar", em_cut);
   T->Draw("P.gtr.th>>data_exptar", em_cut);
   T->Draw("P.gtr.ph>>data_eyptar", em_cut); 
   T->Draw("P.gtr.dp>>data_edelta", em_cut);

   //Electron arm Focal Plane Quantities
   T->Draw("P.dc.x_fp>>data_exfp", em_cut);
   T->Draw("P.dc.y_fp>>data_eyfp", em_cut);
   T->Draw("P.dc.xp_fp>>data_expfp", em_cut);
   T->Draw("P.dc.yp_fp>>data_eypfp", em_cut);


   // TH2F General TTree::Draw Format:  T->Draw("y:x>>(xbins, xmin, xmax, ybins, ymin, ymax)")   

   // Cross-Check correlations
   T->Draw("H.kin.secondary.emiss:H.kin.secondary.pmiss>>data_emiss_vs_pmiss", em_cut);
   T->Draw("P.gtr.dp:P.gtr.ph>>data_edelta_vs_eyptar", em_cut);

   //2D Focal Plane Correlations
   T->Draw("H.dc.x_fp:H.dc.y_fp>>data_hxfp_vs_hyfp", em_cut);
   T->Draw("P.dc.x_fp:P.dc.y_fp>>data_exfp_vs_eyfp", em_cut);
   
   //2D HMS v. SHMS Acceptance Correlations
   T->Draw("H.gtr.th:P.gtr.th>>data_hxptar_vs_exptar", em_cut);
   T->Draw("H.gtr.ph:P.gtr.ph>>data_hyptar_vs_eyptar", em_cut);
   T->Draw("H.gtr.dp:P.gtr.dp>>data_hdelta_vs_edelta", em_cut);

   outfile->Write();
   outfile->Close();


   


}
