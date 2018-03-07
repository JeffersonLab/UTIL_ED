//Macro to analyze H(e,e'p) data from Hall C: HMS (electron arm), SHMS (hadron arm)

//HMS Momentum correction: P0 = P0*0.9968
//SHMS Momentum correction: P0 = P0*0.985

void analyze_heep(int run_num, int evtNUM)
{

  
  //prevent root from displaying graphs while executing
  gROOT->SetBatch(1);

  TString hadron_arm;
  TString electron_arm;

  hadron_arm = "HMS";
  electron_arm = "SHMS";
    
  
  //Open data ROOTfile and call TTree
  TString file_path;
  file_path = Form("../../ROOTfiles/coin_replay_production_%d_%d.root", run_num, evtNUM);
  TFile *data_file = new TFile(file_path, "READ");

  TTree *T = (TTree*)data_file->Get("T");

  //Open root file where new histograms will be stored
  TFile *outfile = new TFile(Form("ep_coin_data_%d.root", run_num), "recreate");


  //These histograms binning MUST be exactly the same as those used in SIMC heep.C analysis

  //********* Create 1D Histograms **************
   Int_t bins = 100;

   //Kinematics Quantities
   TH1F *data_Emiss = new TH1F("data_Emiss","missing energy", 50, -0.5, 0.8);  //binwidth = 0.0025
   TH1F *data_pm = new TH1F("data_pm","missing momentum", bins, -0.05, 1.7);
   TH1F *data_Q2 = new TH1F("data_Q2","Q2", 100, 4., 6.);
   TH1F *data_omega = new TH1F("data_omega","Energy Transfer, #omega", bins, 1.8, 3.4);
   TH1F *data_W_inv = new TH1F("data_W_inv", "Invariant Mass, W", bins, 0.2, 1.7);
   TH1F *data_theta_elec = new TH1F("data_theta_elec", "Electron Scatt. Angle", bins, 20, 40);
   TH1F *data_theta_prot = new TH1F("data_theta_prot", "Proton Scatt. Angle", bins, 20, 40);

      //Additional Kinematics Variables
   TH1F *data_W2 = new TH1F("data_W2", "Invariant Mass W2", bins, 0.4, 2.0);
   TH1F *data_xbj = new TH1F("data_xbj", "x-Bjorken", bins, 0.6, 1.3);
   TH1F *data_Pf = new TH1F("data_Pf", "Final Proton Momentum", bins, 2.5, 4.5);
   TH1F *data_kf = new TH1F("data_kf", "Final e^{-} Momentum", bins, 0., 5.0);
   
   /*
   //Target Reconstruction Variables
   TH1F *data_x_tar = new TH1F("data_x_tar", "x_Target", bins, -0.25, 0.25);
   TH1F *data_y_tar = new TH1F("data_y_tar", "y_Target", bins, -0.25, 0.25);
   TH1F *data_z_tar = new TH1F("data_z_tar", "z_Target", bins, -5.5, 5.5);
   */
   //Hadron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
   TH1F *data_hytar = new TH1F("data_hytar", hadron_arm + "  Y_{tar}", bins, -6., 6.);
   TH1F *data_hxptar = new TH1F("data_hxptar", hadron_arm + "  X'_{tar}", bins, -0.08, 0.08 );
   TH1F *data_hyptar = new TH1F("data_hyptar", hadron_arm + "  Y'_{tar}", bins, -0.04, 0.04 );
   TH1F *data_hdelta = new TH1F("data_hdelta", hadron_arm + "  Momentum Acceptance, #delta", bins, -15., 15. );

   //Hadron arm Focal Plane Quantities
   TH1F *data_hxfp = new TH1F("data_hxfp", hadron_arm + "  X_{fp}", bins, -30., 20.);
   TH1F *data_hyfp = new TH1F("data_hyfp", hadron_arm + "  Y_{fp}", bins, -15., 15.);
   TH1F *data_hxpfp = new TH1F("data_hxpfp", hadron_arm + "  X'_{fp}", bins, -0.2, 0.06 );
   TH1F *data_hypfp = new TH1F("data_hypfp", hadron_arm + "  Y'_{fp}", bins, -0.08, 0.8);

      
   //Electron Arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
   TH1F *data_eytar = new TH1F("data_eytar", electron_arm + "  Y_{tar}", bins, -5., 5.);
   TH1F *data_exptar = new TH1F("data_exptar", electron_arm + "  X'_{tar}", bins, -0.1, 0.1);
   TH1F *data_eyptar = new TH1F("data_eyptar", electron_arm + "  Y'_{tar}", bins, -0.5, 0.5);
   TH1F *data_edelta = new TH1F("data_edelta", electron_arm + "  Momentum Acceptance, #delta", bins, -15., 15. );

   //Electron Arm Focal Plane Quantities
   TH1F *data_exfp = new TH1F("data_exfp", electron_arm + "  X_{fp}", bins, -60., 60.);
   TH1F *data_eyfp = new TH1F("data_eyfp", electron_arm + "  Y_{fp}", bins, -30., 30.);
   TH1F *data_expfp = new TH1F("data_expfp", electron_arm + "  X'_{fp}", bins, -0.1, 0.06);
   TH1F *data_eypfp = new TH1F("data_eypfp", electron_arm + "  Y'_{fp}", bins, -0.04, 0.04);


   //Cross-Check correlations
   TH2F *data_em_vs_pm = new TH2F("data_em_vs_pm", " E_{miss} vs. P_{miss}", 104, 0.0, 1.0, 100, -0.1, 0.5);
   TH2F *data_edelta_vs_eyptar = new TH2F("data_edelta_vs_eyptar", electron_arm + " #delta vs. Y'_{tar}", bins, -0.03, 0.025, bins, -15., 25.);


   //2D Focal Plane Correlations 
   TH2F *data_hxfp_vs_hyfp = new TH2F("data_hxfp_vs_hyfp", hadron_arm + " X_{fp} vs Y_{fp}", bins, -50., 50., bins, -60., 60.);
   TH2F *data_exfp_vs_eyfp = new TH2F("data_exfp_vs_eyfp", electron_arm + " X_{fp} vs Y_{fp}", bins, -50., 50., bins, -60., 60.);

   //2D HMS v. SHMS Acceptance Correlations
   TH2F *data_hxptar_vs_exptar = new TH2F("data_hxptar_vs_exptar", "HMS vs. SHMS, X'_{tar}", bins, -0.08, 0.08, bins, -0.1, 0.1);
   TH2F *data_hyptar_vs_eyptar = new TH2F("data_hyptar_vs_eyptar", "HMS vs. SHMS, Y'_{tar}", bins, -0.05, 0.025, bins, -0.05, 0.04);
   TH2F *data_hdelta_vs_edelta = new TH2F("data_hdelta_vs_edelta", "HMS vs. SHMS, #delta", bins, -16., 16, bins, -12., 10.);

  
   
   /*********************************************/
   
   //DEFINE PID CUTS
   TCut pcal = "P.cal.etracknorm>0.7";
   TCut pelec = "P.ngcer.npeSum>1.0";
   TCut hprot = "H.cer.npeSum<1.0";


   //DEFINE KINEMATIC CUTS
   TCut W_cut = "P.kin.primary.W<1.05";   //select events below pion thresshold
   TCut em_cut = "H.kin.secondary.emiss>0.060";
   //Draw the Histograms from the TTree

   //Kinematics Quantities, P.* ->SHMS,  H.* -->HMS
   T->Draw("H.kin.secondary.emiss>>data_Emiss");
   T->Draw("H.kin.secondary.pmiss>>data_pm");
   T->Draw("P.kin.primary.Q2>>data_Q2");
   T->Draw("P.kin.primary.nu>>data_omega");
   T->Draw("P.kin.primary.W>>data_W_inv");
   T->Draw("(P.kin.primary.scat_ang_rad*180./3.14)>>data_theta_elec");
   T->Draw("(H.kin.secondary.scat_ang_rad*180./3.14)>>data_theta_prot"); 

   //Additional Kinematic Variables
   T->Draw("P.kin.primary.W2>>data_W2");
   T->Draw("P.kin.primary.x_bj>>data_xbj");
   T->Draw("H.gtr.p>>data_Pf");
   T->Draw("P.gtr.p>>(data_kf)");

   //Target Reconstruction Variables ????? What are these in data????
   //T->Draw("");
   //T->Draw("");
   //T->Draw("");

   //Hadron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta), theta: xptar, phi:yptar
   T->Draw("P.gtr.y>>data_hytar");
   T->Draw("P.gtr.th>>data_hxptar");
   T->Draw("P.gtr.ph>>data_hyptar");
   T->Draw("P.gtr.dp>>data_hdelta");

   //Hadron arm Focal Plane Quantities
   T->Draw("P.dc.x_fp>>data_hxfp");
   T->Draw("P.dc.y_fp>>data_hyfp");
   T->Draw("P.dc.xp_fp>>data_hxpfp");
   T->Draw("P.dc.yp_fp>>data_hypfp");
   
   //Electron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta), theta: xptar, phi:yptar
   T->Draw("H.gtr.y>>data_eytar");
   T->Draw("H.gtr.th>>data_exptar");
   T->Draw("H.gtr.ph>>data_eyptar"); 
   T->Draw("H.gtr.dp>>data_edelta");

   //Electron arm Focal Plane Quantities
   T->Draw("H.dc.x_fp>>data_exfp");
   T->Draw("H.dc.y_fp>>data_eyfp");
   T->Draw("H.dc.xp_fp>>data_expfp");
   T->Draw("H.dc.yp_fp>>data_eypfp");


   // TH2F General TTree::Draw Format:  T->Draw("y:x>>(xbins, xmin, xmax, ybins, ymin, ymax)")   

   // Cross-Check correlations
   T->Draw("H.kin.secondary.emiss:H.kin.secondary.pmiss>>data_em_vs_pm");
   T->Draw("P.gtr.dp:P.gtr.ph>>data_edelta_vs_eyptar");

   //2D Focal Plane Correlations
   T->Draw("H.dc.x_fp:H.dc.y_fp>>data_hxfp_vs_hyfp");
   T->Draw("P.dc.x_fp:P.dc.y_fp>>data_exfp_vs_eyfp");
   
   //2D HMS v. SHMS Acceptance Correlations
   T->Draw("H.gtr.th:P.gtr.th>>data_hxptar_vs_exptar");
   T->Draw("H.gtr.ph:P.gtr.ph>>data_hyptar_vs_eyptar");
   T->Draw("H.gtr.dp:P.gtr.dp>>data_hdelta_vs_edelta");

   outfile->Write();

   //Yield Estimates, Counts/charge, 
   


}
