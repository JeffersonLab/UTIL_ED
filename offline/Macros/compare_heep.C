//Script to make comparison between SIMC and Commissioning Data from HallC Spring 2018
//Compare Target Reconstruction/FOCAL PLANE/ Kinematics Variables

void compare_heep(int runNUM, int evtNUM)
{
  

  //TString simc_filename =  "weighted_ep_coin_simc_1854.root"; //"ep_coin_simc_1929.root";
  
  //Pre-defined SIMC/data root file names containing histogram object to comapare
  TString simc_filename =  Form("weighted_run%d_heep_simc_rad.root", runNUM);
  TString data_filename =  Form("heep_data_%d_%dnewdelta.root", runNUM, evtNUM); 

  TString simc_path;
  TString data_path;
  
  simc_path = "../SIMC/heep/SIMC_ROOTfiles/"+simc_filename;
  data_path = "../DATA/DATA_ROOTfiles/"+data_filename;
  
  //Open SIMC/data ROOT files;
  TFile *simc_file = new TFile(simc_path);
  TFile *data_file = new TFile(data_path);


  //---------------Target Reconstruction Variables----------------
  //Define SIMC histos ('h'-->hadron arm,  'e'-->electron arm)
  TH1F *simc_hytar =  0;
  TH1F *simc_hxptar =  0;
  TH1F *simc_hyptar =  0;
  TH1F *simc_hdelta =  0;

  TH1F *simc_eytar =  0;
  TH1F *simc_exptar =  0;
  TH1F *simc_eyptar =  0;
  TH1F *simc_edelta =  0;
  
  //Define data histos
  TH1F *data_hytar = 0;
  TH1F *data_hxptar =  0;
  TH1F *data_hyptar =  0;
  TH1F *data_hdelta =  0;

  TH1F *data_eytar = 0;
  TH1F *data_exptar =  0;
  TH1F *data_eyptar =  0;
  TH1F *data_edelta =  0;

  //-----------------------------------------------------------
 
  //--------------FOCAL PLANE VARIABLES------------------------

 //Define SIMC histos ('h'-->hadron arm,  'e'-->electron arm)
  TH1F *simc_hxfp =  0;
  TH1F *simc_hyfp =  0;
  TH1F *simc_hxpfp =  0;
  TH1F *simc_hypfp =  0;

  TH1F *simc_exfp =  0;
  TH1F *simc_eyfp =  0;
  TH1F *simc_expfp =  0;
  TH1F *simc_eypfp =  0;

  
  //Define data histos
  TH1F *data_hxfp =  0;
  TH1F *data_hyfp =  0;
  TH1F *data_hxpfp =  0;
  TH1F *data_hypfp =  0;

  TH1F *data_exfp =  0;
  TH1F *data_eyfp =  0;
  TH1F *data_expfp =  0;
  TH1F *data_eypfp =  0;

  //--------------------------------------------------------------

  //-------------------------KINEMATICS---------------------------

  TH1F *simc_emiss =  0;
  TH1F *simc_pmiss =  0;
  TH1F *simc_Q2 =  0;
  TH1F *simc_omega =  0;
  TH1F *simc_W =  0;
  TH1F *simc_thq = 0;

  TH1F *simc_xbj = 0;
  TH1F *simc_th_elec = 0;                                  
  TH1F *simc_th_prot = 0;                                              
  TH1F *simc_Pf = 0;                                                   
  TH1F *simc_kf = 0;  

  //Define data histos
  TH1F *data_emiss = 0;
  TH1F *data_pmiss =  0;
  TH1F *data_Q2 =  0;
  TH1F *data_omega =  0;
  TH1F *data_W =  0;
  TH1F *data_thq = 0;

  TH1F *data_xbj = 0;
  TH1F *data_th_elec = 0;
  TH1F *data_th_prot = 0;
  TH1F *data_Pf = 0;
  TH1F *data_kf = 0;
  

  //---------------------------------------------------------------

 //change to simc_file
  simc_file->cd();

  //----------Get Target Reconstructed Histograms------------------
  //Get Histogram objects from SIMC rootfile
  simc_file->GetObject("cut_hytar", simc_hytar);
  simc_file->GetObject("cut_hxptar", simc_hxptar);
  simc_file->GetObject("cut_hyptar", simc_hyptar);
  simc_file->GetObject("cut_hdelta", simc_hdelta);

  simc_file->GetObject("cut_eytar", simc_eytar);
  simc_file->GetObject("cut_exptar", simc_exptar);
  simc_file->GetObject("cut_eyptar", simc_eyptar);
  simc_file->GetObject("cut_edelta", simc_edelta);


  //Set SIMC Histo Aesthetics
  simc_hytar->SetLineColor(kRed);
  simc_hytar->SetLineWidth(3);
  simc_hxptar->SetLineColor(kRed);
  simc_hxptar->SetLineWidth(3);
  simc_hyptar->SetLineColor(kRed);
  simc_hyptar->SetLineWidth(3);
  simc_hdelta->SetLineColor(kRed);
  simc_hdelta->SetLineWidth(3);
  simc_eytar->SetLineColor(kRed);
  simc_eytar->SetLineWidth(3);
  simc_exptar->SetLineColor(kRed);
  simc_exptar->SetLineWidth(3);
  simc_eyptar->SetLineColor(kRed);
  simc_eyptar->SetLineWidth(3);
  simc_edelta->SetLineColor(kRed);
  simc_edelta->SetLineWidth(3);
  
  
  //change to data_file
  data_file->cd();

  //Get Histogram objects from data rootfile
  data_file->GetObject("data_hytar", data_hytar);
  data_file->GetObject("data_hxptar", data_hxptar);
  data_file->GetObject("data_hyptar", data_hyptar);
  data_file->GetObject("data_hdelta", data_hdelta);

  data_file->GetObject("data_eytar", data_eytar);
  data_file->GetObject("data_exptar", data_exptar);
  data_file->GetObject("data_eyptar", data_eyptar);
  data_file->GetObject("data_edelta", data_edelta);
  
  
  //Set data Histo Aesthetics
  data_hytar->SetFillColorAlpha(kBlue, 0.35);
  data_hytar->SetFillStyle(3004);
  data_hxptar->SetFillColorAlpha(kBlue, 0.35);
  data_hxptar->SetFillStyle(3004);
  data_hyptar->SetFillColorAlpha(kBlue, 0.35);
  data_hyptar->SetFillStyle(3004);
  data_hdelta->SetFillColorAlpha(kBlue, 0.35);
  data_hdelta->SetFillStyle(3004);
  data_eytar->SetFillColorAlpha(kBlue, 0.35);
  data_eytar->SetFillStyle(3004);
  data_exptar->SetFillColorAlpha(kBlue, 0.35);
  data_exptar->SetFillStyle(3004);
  data_eyptar->SetFillColorAlpha(kBlue, 0.35);
  data_eyptar->SetFillStyle(3004);
  data_edelta->SetFillColorAlpha(kBlue, 0.35);
  data_edelta->SetFillStyle(3004);
  
  //-----------------------------------------------------------------

  //---------------Get FOCAL PLANE Histograms------------------------

   //change to simc_file
  simc_file->cd();

  //Get Histogram objects from SIMC rootfile
  simc_file->GetObject("cut_hxfp", simc_hxfp);
  simc_file->GetObject("cut_hyfp", simc_hyfp);
  simc_file->GetObject("cut_hxpfp", simc_hxpfp);
  simc_file->GetObject("cut_hypfp", simc_hypfp);

  simc_file->GetObject("cut_exfp", simc_exfp);
  simc_file->GetObject("cut_eyfp", simc_eyfp);
  simc_file->GetObject("cut_expfp", simc_expfp);
  simc_file->GetObject("cut_eypfp", simc_eypfp);


  //Set SIMC Histo Aesthetics
  simc_hxfp->SetLineColor(kRed);
  simc_hxfp->SetLineWidth(3);
  simc_hyfp->SetLineColor(kRed);
  simc_hyfp->SetLineWidth(3);
  simc_hxpfp->SetLineColor(kRed);
  simc_hxpfp->SetLineWidth(3);
  simc_hypfp->SetLineColor(kRed);
  simc_hypfp->SetLineWidth(3);
  simc_exfp->SetLineColor(kRed);
  simc_exfp->SetLineWidth(3);
  simc_eyfp->SetLineColor(kRed);
  simc_eyfp->SetLineWidth(3);
  simc_expfp->SetLineColor(kRed);
  simc_expfp->SetLineWidth(3);
  simc_eypfp->SetLineColor(kRed);
  simc_eypfp->SetLineWidth(3);
  
  
  //change to data_file
  data_file->cd();

  //Get Histogram objects from data rootfile
  data_file->GetObject("data_hxfp", data_hxfp);
  data_file->GetObject("data_hyfp", data_hyfp);
  data_file->GetObject("data_hxpfp", data_hxpfp);
  data_file->GetObject("data_hypfp", data_hypfp);

  data_file->GetObject("data_exfp", data_exfp);
  data_file->GetObject("data_eyfp", data_eyfp);
  data_file->GetObject("data_expfp", data_expfp);
  data_file->GetObject("data_eypfp", data_eypfp);

  
  //Set data Histo Aesthetics
  data_hxfp->SetFillColorAlpha(kBlue, 0.35);
  data_hxfp->SetFillStyle(3004);
  data_hyfp->SetFillColorAlpha(kBlue, 0.35);
  data_hyfp->SetFillStyle(3004);
  data_hxpfp->SetFillColorAlpha(kBlue, 0.35);
  data_hxpfp->SetFillStyle(3004);
  data_hypfp->SetFillColorAlpha(kBlue, 0.35);
  data_hypfp->SetFillStyle(3004);
  data_exfp->SetFillColorAlpha(kBlue, 0.35);
  data_exfp->SetFillStyle(3004);
  data_eyfp->SetFillColorAlpha(kBlue, 0.35);
  data_eyfp->SetFillStyle(3004);
  data_expfp->SetFillColorAlpha(kBlue, 0.35);
  data_expfp->SetFillStyle(3004);
  data_eypfp->SetFillColorAlpha(kBlue, 0.35);
  data_eypfp->SetFillStyle(3004);

  //--------------------------------------------------------------

  //------------------Get KINEMATICS VARIABLES--------------------

   //change to simc_file
  simc_file->cd();

  //Get Histogram objects from SIMC rootfile
  simc_file->GetObject("Emiss", simc_emiss);
  simc_file->GetObject("cut_pm", simc_pmiss);
  simc_file->GetObject("cut_Q_2", simc_Q2);
  simc_file->GetObject("cut_omega", simc_omega);
  simc_file->GetObject("cut_W_inv", simc_W);
  simc_file->GetObject("cut_theta_q", simc_thq);

  simc_file->GetObject("cut_xbj", simc_xbj);
  simc_file->GetObject("cut_theta_elec", simc_th_elec);
  simc_file->GetObject("cut_theta_prot", simc_th_prot);
  simc_file->GetObject("cut_P_f", simc_Pf);
  simc_file->GetObject("cut_kf", simc_kf);

  

  //Set SIMC Histo Aesthetics
  simc_emiss->SetLineColor(kRed);
  simc_emiss->SetLineWidth(3);
  simc_pmiss->SetLineColor(kRed);
  simc_pmiss->SetLineWidth(3);
  simc_Q2->SetLineColor(kRed);
  simc_Q2->SetLineWidth(3);
  simc_omega->SetLineColor(kRed);
  simc_omega->SetLineWidth(3);
  simc_W->SetLineColor(kRed);
  simc_W->SetLineWidth(3);
  simc_thq->SetLineColor(kRed);
  simc_thq->SetLineWidth(3);

  simc_xbj->SetLineColor(kRed);
  simc_xbj->SetLineWidth(3);
  simc_th_elec->SetLineColor(kRed);
  simc_th_elec->SetLineWidth(3);
  simc_th_prot->SetLineColor(kRed);
  simc_th_prot->SetLineWidth(3);
  simc_Pf->SetLineColor(kRed);
  simc_Pf->SetLineWidth(3);
  simc_kf->SetLineColor(kRed);
  simc_kf->SetLineWidth(3);
  //change to data_file
  data_file->cd();
  
  //Get Histogram objects from data rootfile
  data_file->GetObject("data_Emiss", data_emiss);
  data_file->GetObject("data_pm", data_pmiss);
  data_file->GetObject("data_Q2", data_Q2);
  data_file->GetObject("data_omega", data_omega);
  data_file->GetObject("data_W_inv", data_W);
  data_file->GetObject("data_theta_q", data_thq);


  data_file->GetObject("data_xbj", data_xbj);
  data_file->GetObject("data_theta_elec", data_th_elec);
  data_file->GetObject("data_theta_prot", data_th_prot);
  data_file->GetObject("data_Pf", data_Pf);
  data_file->GetObject("data_kf", data_kf);

  //Set data Histo Aesthetics
  data_emiss->SetFillColorAlpha(kBlue, 0.35);
  data_emiss->SetFillStyle(3004);
  data_pmiss->SetFillColorAlpha(kBlue, 0.35);
  data_pmiss->SetFillStyle(3004);
  data_Q2->SetFillColorAlpha(kBlue, 0.35);
  data_Q2->SetFillStyle(3004);
  data_omega->SetFillColorAlpha(kBlue, 0.35);
  data_omega->SetFillStyle(3004);
  data_W->SetFillColorAlpha(kBlue, 0.35);
  data_W->SetFillStyle(3004);
  data_thq->SetFillColorAlpha(kBlue, 0.35);
  data_thq->SetFillStyle(3004);

  data_xbj->SetFillColorAlpha(kBlue, 0.35);
  data_xbj->SetFillStyle(3004);
  data_th_elec->SetFillColorAlpha(kBlue, 0.35);
  data_th_elec->SetFillStyle(3004);
  data_th_prot->SetFillColorAlpha(kBlue, 0.35);
  data_th_prot->SetFillStyle(3004);
  data_Pf->SetFillColorAlpha(kBlue, 0.35);
  data_Pf->SetFillStyle(3004);
  data_kf->SetFillColorAlpha(kBlue, 0.35);
  data_kf->SetFillStyle(3004);


  //Overlay SIMC/data plots (*** VERY IMPORTANT ***: Range and #bins must be same)

   //Set Legend
   auto leg1 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg2 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg3 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg4 = new TLegend(0.1,0.8,0.28,0.9);

   //Set Legend
   auto leg5 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg6 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg7 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg8 = new TLegend(0.1,0.8,0.28,0.9);


   //-----------------PLOT Target Reconstructed Variables SIMC/Data comparison-----------------------

   //Create A Canvas to store Target Recon. variable comparisons in HADRON ARM
   
   TCanvas *c1 = new TCanvas("c1", "Hadron/Electron Arm: Target Reconstruction", 2000, 1000);
   c1->Divide(4,2);

   
   c1->cd(1);
   data_hytar->DrawNormalized();
   simc_hytar->DrawNormalized("same");
   leg1->AddEntry(data_hytar,"Data","f");
   leg1->AddEntry(simc_hytar,"SIMC");
   leg1->Draw();

   c1->cd(2);
   data_hxptar->DrawNormalized();
   simc_hxptar->DrawNormalized("same");
   leg2->AddEntry(data_hxptar,"Data", "f");
   leg2->AddEntry(simc_hxptar,"SIMC");
   leg2->Draw();

   c1->cd(3);
   data_hyptar->DrawNormalized();
   simc_hyptar->DrawNormalized("same");
   leg3->AddEntry(data_hyptar,"Data", "f");
   leg3->AddEntry(simc_hyptar,"SIMC");
   leg3->Draw();
     
   c1->cd(4);
   data_hdelta->DrawNormalized();
   simc_hdelta->DrawNormalized("same");
   leg4->AddEntry(data_hdelta,"Data", "f");
   leg4->AddEntry(simc_hdelta,"SIMC");
   leg4->Draw();

   c1->cd(5);
   data_eytar->DrawNormalized();
   simc_eytar->DrawNormalized("same");
   leg5->AddEntry(data_eytar,"Data","f");
   leg5->AddEntry(simc_eytar,"SIMC");
   leg5->Draw();

   c1->cd(6);
   data_exptar->DrawNormalized();
   simc_exptar->DrawNormalized("same");
   leg6->AddEntry(data_exptar,"Data", "f");
   leg6->AddEntry(simc_exptar,"SIMC");
   leg6->Draw();

   c1->cd(7);
   data_eyptar->DrawNormalized();
   simc_eyptar->DrawNormalized("same");
   leg7->AddEntry(data_eyptar,"Data", "f");
   leg7->AddEntry(simc_eyptar,"SIMC");
   leg7->Draw();
     
   c1->cd(8);
   data_edelta->DrawNormalized();
   simc_edelta->DrawNormalized("same");
   leg8->AddEntry(data_edelta,"Data", "f");
   leg8->AddEntry(simc_edelta,"SIMC");
   leg8->Draw();

   //------------------------------------------------------------------------------


   //-----------------PLOT FOCAL PLANE  Variables SIMC/Data comparison-----------------------

  //Set Legend
   auto leg9 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg10 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg11 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg12 = new TLegend(0.1,0.8,0.28,0.9);

      //Set Legend
   auto leg13 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg14 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg15 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg16 = new TLegend(0.1,0.8,0.28,0.9);

   TCanvas *c2 = new TCanvas("c2", "Hadron/Electron Arm: Focal Plane", 2000, 1000);
   c2->Divide(4,2);

   c2->cd(1);
   data_hxfp->DrawNormalized();
   simc_hxfp->DrawNormalized("same");
   leg9->AddEntry(data_hxfp,"Data","f");
   leg9->AddEntry(simc_hxfp,"SIMC");
   leg9->Draw();

   c2->cd(2);
   data_hyfp->DrawNormalized();
   simc_hyfp->DrawNormalized("same");
   leg10->AddEntry(data_hyfp,"Data", "f");
   leg10->AddEntry(simc_hyfp,"SIMC");
   leg10->Draw();

   c2->cd(3);
   data_hxpfp->DrawNormalized();
   simc_hxpfp->DrawNormalized("same");
   leg11->AddEntry(data_hxpfp,"Data", "f");
   leg11->AddEntry(simc_hxpfp,"SIMC");
   leg11->Draw();
     
   c2->cd(4);
   data_hypfp->DrawNormalized();
   simc_hypfp->DrawNormalized("same");
   leg12->AddEntry(data_hypfp,"Data", "f");
   leg12->AddEntry(simc_hypfp,"SIMC");
   leg12->Draw();

   c2->cd(5);
   data_exfp->DrawNormalized();
   simc_exfp->DrawNormalized("same");
   leg13->AddEntry(data_exfp,"Data","f");
   leg13->AddEntry(simc_exfp,"SIMC");
   leg13->Draw();
   
   c2->cd(6);
   data_eyfp->DrawNormalized();
   simc_eyfp->DrawNormalized("same");
   leg14->AddEntry(data_eyfp,"Data", "f");
   leg14->AddEntry(simc_eyfp,"SIMC");
   leg14->Draw();

   c2->cd(7);
   data_expfp->DrawNormalized();
   simc_expfp->DrawNormalized("same");
   leg15->AddEntry(data_expfp,"Data", "f");
   leg15->AddEntry(simc_expfp,"SIMC");
   leg15->Draw();
     
   c2->cd(8);
   data_eypfp->DrawNormalized();
   simc_eypfp->DrawNormalized("same");
   leg16->AddEntry(data_eypfp,"Data", "f");
   leg16->AddEntry(simc_eypfp,"SIMC");
   leg16->Draw();

   //----------------------------------------------------------- 
 
   //-----------------PLOT KINEMATICS SIMC/Data comparison---------------

//Set Legend
   auto leg17 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg18 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg19 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg20 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg21 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg22 = new TLegend(0.1,0.8,0.28,0.9);
   
   //Create A Canvas to store kinematic variable comparisons
   TCanvas *c3 = new TCanvas("c3", "Kinematics", 2000, 1000);
   c3->Divide(3,2);
   
   c3->cd(1);
   data_emiss->GetXaxis()->SetTitle("Missing Energy [GeV]");
   data_emiss->GetXaxis()->CenterTitle();

   data_emiss->DrawNormalized();
   simc_emiss->DrawNormalized("same");
   leg17->AddEntry(data_emiss,"Data","f");
   leg17->AddEntry(simc_emiss,"SIMC");
   leg17->Draw();

   c3->cd(2);
   data_pmiss->GetXaxis()->SetTitle("Missing Momentum [GeV/c]");
   data_pmiss->GetXaxis()->CenterTitle();

   data_pmiss->DrawNormalized();
   simc_pmiss->DrawNormalized("same");
   leg18->AddEntry(data_pmiss,"Data", "f");
   leg18->AddEntry(simc_pmiss,"SIMC");
   leg18->Draw();

   c3->cd(3);
   data_Q2->GetXaxis()->SetTitle("Q^{2} [GeV^{2}]");
   data_Q2->GetXaxis()->CenterTitle();

   data_Q2->DrawNormalized();
   simc_Q2->DrawNormalized("same");
   leg19->AddEntry(data_Q2,"Data", "f");
   leg19->AddEntry(simc_Q2,"SIMC");
   leg19->Draw();
     
   c3->cd(4);
   data_omega->GetXaxis()->SetTitle("Energy Transfer, #omega [GeV]");
   data_omega->GetXaxis()->CenterTitle();
   
   data_omega->DrawNormalized();
   simc_omega->DrawNormalized("same");
   leg20->AddEntry(data_omega,"Data", "f");
   leg20->AddEntry(simc_omega,"SIMC");
   leg20->Draw();

   c3->cd(5);
   data_W->GetXaxis()->SetTitle("Invariant Mass, W [GeV]");
   data_W->GetXaxis()->CenterTitle();
  
   data_W->DrawNormalized();
   simc_W->DrawNormalized("same");
   leg21->AddEntry(data_W,"Data", "f");
   leg21->AddEntry(simc_W,"SIMC");
   leg21->Draw();

   c3->cd(6);
   data_thq->GetXaxis()->SetTitle("q-vector Angle, #theta_{q} [deg]");
   data_thq->GetXaxis()->CenterTitle();

   data_thq->DrawNormalized();
   simc_thq->DrawNormalized("same");
   leg22->AddEntry(data_thq,"Data", "f");
   leg22->AddEntry(simc_thq,"SIMC");
   leg22->Draw();



   //Second set of KINEMATIC VARIABLES

   //Set Legend
   auto leg23 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg24 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg25 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg26 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg27 = new TLegend(0.1,0.8,0.28,0.9);
   
   //Create A Canvas to store kinematic variable comparisons
   TCanvas *c4 = new TCanvas("c4", "Kinematics", 2000, 1000);
   c4->Divide(3,2);

   c4->cd(1);
   simc_xbj->DrawNormalized();
   data_xbj->DrawNormalized("same");
   leg23->AddEntry(data_xbj,"Data","f");
   leg23->AddEntry(simc_xbj,"SIMC");
   leg23->Draw();

   c4->cd(2);
   data_th_elec->GetXaxis()->SetTitle("Electron Scatt. Angle, #theta_{e} [deg]");
   data_th_elec->GetXaxis()->CenterTitle();

   data_th_elec->DrawNormalized();
   simc_th_elec->DrawNormalized("same");
   leg24->AddEntry(data_th_elec,"Data","f");
   leg24->AddEntry(simc_th_elec,"SIMC");
   leg24->Draw();

   c4->cd(3);
   data_th_prot->GetXaxis()->SetTitle("Proton Scatt. Angle, #theta_{p} [deg]");
   data_th_prot->GetXaxis()->CenterTitle();

   data_th_prot->DrawNormalized();
   simc_th_prot->DrawNormalized("same");
   leg25->AddEntry(data_th_prot,"Data","f");
   leg25->AddEntry(simc_th_prot,"SIMC");
   leg25->Draw();

   c4->cd(4);
   data_Pf->GetXaxis()->SetTitle("Proton Final Momentum, P_{f} [GeV/c] ");
   data_Pf->GetXaxis()->CenterTitle();

   data_Pf->DrawNormalized();
   simc_Pf->DrawNormalized("same");
   leg26->AddEntry(data_Pf,"Data","f");
   leg26->AddEntry(simc_Pf,"SIMC");
   leg26->Draw();

   c4->cd(5);
   data_kf->GetXaxis()->SetTitle("Electron Final Momentum, k_{f} [GeV/c] ");
   data_kf->GetXaxis()->CenterTitle();
   
   data_kf->DrawNormalized();
   simc_kf->DrawNormalized("same");
   leg27->AddEntry(data_kf,"Data","f");
   leg27->AddEntry(simc_kf,"SIMC");
   leg27->Draw();


}
