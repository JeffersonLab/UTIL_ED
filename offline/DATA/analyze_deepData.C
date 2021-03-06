//Macro to analyze D(e,e'p)n E12-10-003 data from Hall C: HMS (Hadron arm), SHMS (electron arm)

//#include "../header_files/set_lowdeep_histos.h"
#include "../header_files/set_highdeep_histos.h"
#include "../header_files/useful_functions.h"

//HMS Momentum correction: P0 = P0*0.9968
//SHMS Momentum correction: P0 = P0*0.985

void analyze_deepData(/*int runNUM, int evtNUM*/)
{

  
  //prevent root from displaying graphs while executing
  gROOT->SetBatch(1);

  TString hadron_arm;
  TString electron_arm;

  string primary = "P";   //electrons
  string secondary = "H";   //hadrons

  TFile *outfile;

  hadron_arm = "HMS";
  electron_arm = "SHMS";
  
  //Open data ROOTfile and call TTree                                                                                                
  TString file_path;                                                                                                                     
  
  //file_path = "~/cyero/hallc_replay/ROOTfiles/Pm580_comb_q1q3corr.root";    
  //file_path = "~/cyero/hallc_replay/ROOTfiles/Pm580_comb.root";    
  //  file_path = "~/cyero/hallc_replay/ROOTfiles/Pm750.root";    
  //  file_path = "../../../ROOTfiles/coin_replay_production_3267nopcorr_-1.root";   
//  file_path = "../../../ROOTfiles/coin_replay_production_3289_-1newdelta.root";   
 file_path = "../../../ROOTfiles/Pm750set2.root";

  TFile *data_file = new TFile(file_path, "READ");                                                                        
  
  TTree *T = (TTree*)data_file->Get("T");                                                                                 
  



  //Open root file where new histograms will be stored                                                                 
  // outfile = new TFile("./DATA_ROOTfiles/deep_Pm750.root", "recreate");                        
  outfile = new TFile("./DATA_ROOTfiles/deep_data_750set2.root", "recreate");  

  //These histograms binning MUST be exactly the same as those used in SIMC heep.C analysis

  //Kinematics Quantities
   TH1F *data_Emiss = new TH1F("data_Emiss","missing energy", Em_nbins, Em_xmin, Em_xmax);      
   TH1F *data_pm = new TH1F("data_pm","missing momentum", Pm_nbins, Pm_xmin, Pm_xmax); 
   TH1F *data_Q2 = new TH1F("data_Q2","Q2", Q2_nbins, Q2_xmin, Q2_xmax);
   TH1F *data_omega = new TH1F("data_omega","Energy Transfer, #omega", om_nbins, om_xmin, om_xmax);
   TH1F *data_W_inv = new TH1F("data_W_inv", "Invariant Mass, W", W_nbins, W_xmin, W_xmax);     
   TH1F *data_theta_elec = new TH1F("data_theta_elec", "Electron Scatt. Angle", the_nbins, the_xmin, the_xmax);
   TH1F *data_theta_prot = new TH1F("data_theta_prot", "Proton Scatt. Angle", thp_nbins, thp_xmin, thp_xmax);

   //Additional Kinematics Variables
   TH1F *data_W2 = new TH1F("data_W2", "Invariant Mass W2", W2_nbins, W2_xmin, W2_xmax);
   TH1F *data_xbj = new TH1F("data_xbj", "x-Bjorken", xbj_nbins, xbj_xmin, xbj_xmax);
   TH1F *data_Pf = new TH1F("data_Pf", "Final Proton Momentum", Pf_nbins, Pf_xmin, Pf_xmax);
   TH1F *data_kf = new TH1F("data_kf", "Final e^{-} Momentum", kf_nbins, kf_xmin, kf_xmax);
   TH1F *data_q = new TH1F("data_q", "|q|, 3-vector Magnitude ", q_nbins, q_xmin, q_xmax);
   TH1F *data_theta_nq = new TH1F("data_theta_nq", "Neutron Angle, #theta_{nq}", thnq_nbins, thnq_xmin, thnq_xmax);
   TH1F *data_theta_q = new TH1F("data_theta_q", "q-vector Angle, #theta_{q}", thq_nbins, thq_xmin, thq_xmax);
   TH1F *data_theta_pq = new TH1F("data_theta_pq", "Proton Angle, #theta_{pq}", thpq_nbins, thpq_xmin, thpq_xmax);

   //theta_nq debug
   TH1F *data_pm2 = new TH1F("data_pm2","missing momentum2", Pm_nbins, Pm_xmin, Pm_xmax); 
   TH1F *data_Pf2 = new TH1F("data_Pf2", "Final Proton Momentum2", Pf_nbins, Pf_xmin, Pf_xmax);
   TH1F *data_q2 = new TH1F("data_q2", "|q|, 3-vector Magnitude2 ", q_nbins, q_xmin, q_xmax);

   
   //Target Reconstruction Variables
   TH1F *data_x_tar = new TH1F("data_x_tar", "x_Target", xtar_nbins, xtar_xmin, xtar_xmax);
   TH1F *data_y_tar = new TH1F("data_y_tar", "y_Target", ytar_nbins, ytar_xmin, ytar_xmax);
   TH1F *data_z_tar = new TH1F("data_z_tar", "z_Target", ztar_nbins, ztar_xmin, ztar_xmax);
   
   //Target_Recon, 2D
   //TH2F *data_reactz_vs_yptar = new TH2F("data_reactz_vs_yptar", electron_arm + "React Z vs. Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, ztar_nbins, ztar_xmin, ztar_xmax);
   
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
   
   TH2F *data_emiss_vs_exptar = new TH2F("data_emiss_vs_exptar", " E_{miss} vs. X'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax, Em_nbins, Em_xmin, Em_xmax);
   TH2F *data_emiss_vs_eyptar = new TH2F("data_emiss_vs_eyptar", " E_{miss} vs. Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, Em_nbins, Em_xmin, Em_xmax);


   //Create 2D Histograms at the Focal Plane Quantities
   TH2F *data_hxfp_vs_hyfp = new TH2F("data_hxfp_vs_hyfp", "X_{fp} vs Y_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, hxfp_nbins, hxfp_xmin, hxfp_xmax);
   TH2F *data_exfp_vs_eyfp = new TH2F("data_exfp_vs_eyfp", "X_{fp} vs Y_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, exfp_nbins, exfp_xmin, exfp_xmax);

   //2D HMS v. SHMS Acceptance Correlations
   TH2F *data_hxptar_vs_exptar = new TH2F("data_hxptar_vs_exptar", "HMS vs. SHMS, X'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);
   TH2F *data_hyptar_vs_eyptar = new TH2F("data_hyptar_vs_eyptar", "HMS vs. SHMS, Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, hyptar_nbins, hyptar_xmin, hyptar_xmax);
   TH2F *data_hdelta_vs_edelta = new TH2F("data_hdelta_vs_edelta", "HMS vs. SHMS, #delta", edelta_nbins, edelta_xmin, edelta_xmax, hdelta_nbins, hdelta_xmin, hdelta_xmax);
   
   
   /*********************************************/
   
   //DEFINE PID CUTS
   TCut pcal = "P.cal.etracknorm>0.85";
   TCut pelec = "P.ngcer.npeSum>1.0";

   TCut hprot = "H.cer.npeSum<1.0";
   TCut hcal = "H.cal.etot>0.1";

   TCut pid = pcal;

   //DEFINE KINEMATIC CUTS
   TCut W_cut = Form("%s.kin.primary.W<1.05", primary.c_str());   //select events below pion thresshold
   TCut em_cut = Form("%s.kin.secondary.emiss_nuc>=-0.08&&%s.kin.secondary.emiss_nuc<=0.05", secondary.c_str(), secondary.c_str());  
   TCut Q2_cut = Form("%s.kin.primary.Q2>3&&%s.kin.primary.Q2<5.0", primary.c_str(), primary.c_str());
   TCut xbj_cut = Form("%s.kin.primary.x_bj>0.7&&%s.kin.primary.x_bj<1.3", primary.c_str(), primary.c_str()); 


   //Draw the Histograms from the TTree

   //Kinematics Quantities, P.* ->SHMS,  H.* -->HMS
   T->Draw(Form("%s.kin.secondary.emiss_nuc>>data_Emiss", secondary.c_str()), pid);
   //T->Draw("(P.kin.primary.nu - H.kin.secondary.tx - H.kin.secondary.tb)>>data_Emiss");


   T->Draw(Form("%s.kin.secondary.pmiss>>data_pm", secondary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.kin.primary.Q2>>data_Q2", primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.kin.primary.nu>>data_omega", primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.kin.primary.W>>data_W_inv", primary.c_str()), em_cut&&pid);
   T->Draw(Form("(%s.kin.primary.scat_ang_deg)>>data_theta_elec", primary.c_str()), em_cut&&pid);
   T->Draw(Form("(%s.kin.secondary.xangle-%s.kin.primary.scat_ang_rad)*180./3.14>>data_theta_prot", secondary.c_str(), primary.c_str()),  em_cut&&pid); 
   
   //Additional Kinematic Variables
   T->Draw(Form("%s.kin.primary.W2>>data_W2", primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.kin.primary.x_bj>>data_xbj", primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.gtr.p>>data_Pf", secondary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.gtr.p>>data_kf", primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.kin.primary.q3m>>data_q", primary.c_str()), em_cut&&pid);
   
   T->Draw(Form("(%s.kin.secondary.th_bq*(180./3.14))>>data_theta_nq", secondary.c_str()), em_cut&&pid);   //theta_nq
 


   T->Draw(Form("%s.kin.primary.th_q*(180./3.14)>>data_theta_q", primary.c_str()), em_cut&&pid ); //theta_q
   T->Draw(Form("%s.kin.secondary.th_xq*(180./3.14)>>data_theta_pq", secondary.c_str()),em_cut&&pid ); //theta_pq

   //Target Reconstruction Variables ????? What are these in data????
   T->Draw(Form("%s.react.x>>data_x_tar", primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.react.y>>data_y_tar", primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.react.z>>data_z_tar", primary.c_str()), em_cut&&pid);
		   
		   //Target Recon, 2d
   //T->Draw(Form("%s.react.z:%s.gtr.ph>>data_reactz_vs_yptar", primary.c_str(), primary.c_str()), em_cut&&pid);
   
   //Secondary arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta), theta: xptar, phi:yptar
   T->Draw(Form("%s.gtr.y>>data_hytar", secondary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.gtr.th>>data_hxptar", secondary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.gtr.ph>>data_hyptar", secondary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.gtr.dp>>data_hdelta", secondary.c_str()), em_cut&&pid);

   //Secondary arm Focal Plane Quantities
   T->Draw(Form("%s.dc.x_fp>>data_hxfp", secondary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.dc.y_fp>>data_hyfp", secondary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.dc.xp_fp>>data_hxpfp", secondary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.dc.yp_fp>>data_hypfp", secondary.c_str()), em_cut&&pid);
   
   //Primary arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta), theta: xptar, phi:yptar
   T->Draw(Form("%s.gtr.y>>data_eytar", primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.gtr.th>>data_exptar", primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.gtr.ph>>data_eyptar", primary.c_str()), em_cut&&pid); 
   T->Draw(Form("%s.gtr.dp>>data_edelta", primary.c_str()), em_cut&&pid);

   //Primary arm Focal Plane Quantities
   T->Draw(Form("%s.dc.x_fp>>data_exfp", primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.dc.y_fp>>data_eyfp", primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.dc.xp_fp>>data_expfp", primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.dc.yp_fp>>data_eypfp", primary.c_str()), em_cut&&pid);

   
   // TH2F General TTree::Draw Format:  T->Draw(Form("y:x>>(xbins, xmin, xmax, ybins, ymin, ymax)")   
   
   // Cross-Check correlations
   T->Draw(Form("%s.kin.secondary.emiss_nuc:%s.kin.secondary.pmiss>>data_emiss_vs_pmiss", secondary.c_str(), secondary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.gtr.dp:%s.gtr.ph>>data_edelta_vs_eyptar", primary.c_str(), primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.kin.secondary.emiss_nuc:%s.gtr.th>>data_emiss_vs_exptar", secondary.c_str(), primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.kin.secondary.emiss_nuc:%s.gtr.ph>>data_emiss_vs_eyptar", secondary.c_str(), primary.c_str()), em_cut&&pid);
   
   //2D Focal Plane Correlations
   T->Draw(Form("%s.dc.x_fp:%s.dc.y_fp>>data_hxfp_vs_hyfp", secondary.c_str(), secondary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.dc.x_fp:%s.dc.y_fp>>data_exfp_vs_eyfp", primary.c_str(), primary.c_str()), em_cut&&pid);
   
   //2D HMS v. SHMS Acceptance Correlations
   T->Draw(Form("%s.gtr.th:%s.gtr.th>>data_hxptar_vs_exptar", secondary.c_str(), primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.gtr.ph:%s.gtr.ph>>data_hyptar_vs_eyptar", secondary.c_str(), primary.c_str()), em_cut&&pid);
   T->Draw(Form("%s.gtr.dp:%s.gtr.dp>>data_hdelta_vs_edelta", secondary.c_str(), primary.c_str()), em_cut&&pid);
   
   outfile->Write();
   outfile->Close();
   

   


}
