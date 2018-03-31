//Analysis for HMS/SHMS coincidence D(e,e'p)n, High Missing Momentum Setting (580, 750) MeV
#define deep_cxx
#include "deep.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
void deep::Loop(TString simc_file, Double_t Ib, Double_t time)
{
//   In a ROOT session, you can do:
//      root> .L deep.C
//      root> deep t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

      TString hadron_arm = "HMS";
      TString electron_arm = "SHMS";

 // define histograms
   Double_t pi = 3.141592654;
   Double_t dtr = pi/180.;
   Double_t MP = 0.938272; //GeV
   Double_t MD = 1.87561; //GeV
   Double_t MN = 0.939566; //GeV
   Double_t me = 0.000510998; //GeV
   
   TString ofile_name("weighted_XBjwithQ2Cut");
   ofile_name.Append(simc_file);
   
   //create output root file
   TFile *outfile = new TFile(ofile_name.Data(), "recreate");

   //-------spectrometer resolution calculation----------

   /*
   Double_t hP0_580 = 2.2622;       //proton arm central momentum in GeV/c --for pmiss = 580 MeV setting
   Double_t hP0_750 = 2.1557;       //proton arm central momentum in GeV/c --for pmiss = 750 MeV setting
   
   Double_t eP0 = 8.7000;       //electron arm central momentum
   
   
   //define variables to hold standard deviatons 
   Double_t h_sigma;         //h_sigma = (h_deltai - h_delta) 'delta resolution'
   Double_t h_Psigma;         //hadron arm momentum resolution
   Double_t e_sigma;          //e_sigma = (e_deltai - e_delta) 'delta resolution'
   Double_t e_Psigma;         //electron arm momentum resolution
   Double_t Pm_sigma;
   Double_t Em_sigma;
   
   //variables to be filled
   Double_t h_Pf_thrown;   //thrown final hadron momentum
   Double_t e_kf_thrown;   //thrown final electron momentum
   Double_t Pm_thrown;
   Double_t Em_thrown;
   Double_t nu_thrown;      //thrown energy transfer
   Double_t Ep_thrown;      //final proton energy, thrown
   Double_t En_thrown;      //final neutron energy, thrown
   Double_t Kp_thrown;      //thrown proton kinetic energy
   Double_t Kn_thrown;      //thrown neutron kinetic energy
   
   Double_t h_dP;          //hms momentum resolution
   Double_t h_d_delta;    //hms delta resolution


   Double_t dPmiss;        //missing momentum resolution
   Double_t dEmiss;        //missing energy resolution
   
   Double_t e_dP;         //electron arm momentum resolution
   Double_t e_d_delta;    //electron arm delta resolution
   
   //histograms to store filled variables
   TH1F * res_hdelta = new TH1F("res_hdelta", hadron_arm + " #delta_{i} - #delta", 100,  -2., 2.);   //HISTO to store (hdelta_i - hdelta)
   TH1F * res_hP = new TH1F("res_hP", "HMS Momentum Resolution", 200, -0.1, 0.1);
   TH1F * res_pmiss = new TH1F("res_pmiss", "Missing Momentum Resolution", 100,  -0.2, 0.2);
   TH1F * res_emiss = new TH1F("res_Emiss", "Missing Energy Resolution", 100,  -0.2, 0.2);
   
   TH1F * res_edelta = new TH1F("res_edelta", electron_arm + " #delta_{i} - #delta", 100,  -2., 2.);   //HISTO to store (hdelta_i - hdelta)
   TH1F * res_ekf = new TH1F("res_ekf", "SHMS Momentum Resolution", 200, -0.1, 0.1);
   */

   //----------------------------------------------------
   
   
   //********* Create 1D Histograms **************
   Int_t bins = 65;

   //Kinematics Quantities
   TH1F *Emiss = new TH1F("Emiss","missing energy", 30, -0.1, 0.5);  //MIN binwidth = 0.010 GeV  --Set to 20 MeV
   TH1F *Emiss_v2 = new TH1F("Emiss_v2","missing energy", 30, -0.1, 0.5);
   TH1F *pm = new TH1F("pm","missing momentum", 104, 0.0, 2.6);      //MIN binwidth = 0.020 GeV --Set to 25 MeV
   TH1F *Q_2 = new TH1F("Q_2","Q2", bins, 2., 5.5);
   TH1F *omega = new TH1F("omega","Energy Transfer, #omega", bins, 0., 4.);
   TH1F *W_inv = new TH1F("W_inv", "Invariant Mass, W", bins, -1.5, 2.3);
   TH1F *theta_elec = new TH1F("theta_elec", "Electron Scatt. Angle", bins, 8., 15.);
   TH1F *theta_prot = new TH1F("theta_prot", "Proton Scatt. Angle", bins, 35., 65.);

   //Additional Kinematics Variables
   TH1F *W_2 = new TH1F("W2", "Invariant Mass W2", bins, 0, 2.3);
   TH1F *xbj = new TH1F("xbj", "x-Bjorken", bins, 0.0, 2.0);
   TH1F *P_f = new TH1F("P_f", "Final Proton Momentum", bins, 0., 3.);
   TH1F *k_i = new TH1F("ki", "Initial e^{-} Momentum", bins, 8., 12.);
   TH1F *k_f = new TH1F("kf", "Final e^{-} Momentum", bins, 7., 9.5);
   TH1F *E_n = new TH1F("En", "Neutron Final Energy", bins, 0., 2.);
   TH1F *theta_nq = new TH1F("theta_nq", "Neutron Angle, #theta_{nq}", bins, 0., 80.);
   TH1F *theta_q = new TH1F("theta_q", "q-vector Angle, #theta_{q}", bins, 40, 100.);

   //Target Reconstruction Variables
   TH1F *x_tar = new TH1F("x_tar", "x_Target", bins, -0.25, 0.25);
   TH1F *y_tar = new TH1F("y_tar", "y_Target", bins, -0.25, 0.25);
   TH1F *z_tar = new TH1F("z_tar", "z_Target", bins, -5.5, 5.5);
   
   //Hadron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
   TH1F *hytar = new TH1F("hytar", hadron_arm + " Y_{tar}", bins, -5., 5.);
   TH1F *hxptar = new TH1F("hxptar", hadron_arm + " X'_{tar}", bins, -0.1, 0.1 );
   TH1F *hyptar = new TH1F("hyptar", hadron_arm + " Y'_{tar}", bins, -0.05, 0.05 );
   TH1F *hdelta = new TH1F("hdelta", hadron_arm + " Momentum Acceptance, #delta", bins, -15., 15. );

   //Hadron arm Focal Plane Quantities
   TH1F *hxfp = new TH1F("hxfp", hadron_arm + " X_{fp}", bins, -60., 60.);
   TH1F *hyfp = new TH1F("hyfp", hadron_arm + " Y_{fp}", bins, -40., 40.);
   TH1F *hxpfp = new TH1F("hxpfp", hadron_arm + " X'_{fp}", bins, -0.08, 0.08 );
   TH1F *hypfp = new TH1F("hypfp", hadron_arm + " Y'_{fp}", bins, -0.04, 0.04);

      
   //Electron Arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
   TH1F *eytar = new TH1F("eytar", electron_arm + " Y_{tar}", bins, -3., 3.);
   TH1F *exptar = new TH1F("exptar", electron_arm + " X'_{tar}", bins, -0.06, 0.06);
   TH1F *eyptar = new TH1F("eyptar", electron_arm + " Y'_{tar}", bins, -0.04, 0.04);
   TH1F *edelta = new TH1F("edelta", electron_arm + " Momentum Acceptance, #delta", bins, -15., 8. );

   //Electron Arm Focal Plane Quantities
   TH1F *exfp = new TH1F("exfp", electron_arm + " X_{fp}", bins, -40., 20.);
   TH1F *eyfp = new TH1F("eyfp", electron_arm + " Y_{fp}", bins, -20., 30.);
   TH1F *expfp = new TH1F("expfp", electron_arm + " X'_{fp}", bins, -0.1, 0.06);
   TH1F *eypfp = new TH1F("eypfp", electron_arm + " Y'_{fp}", bins, -0.04, 0.06);

   //Cross-Check correlations (emiss v. pmiss should be flat)
   TH2F *emiss_vs_pmiss = new TH2F("emiss_vs_pmiss", " E_{miss} vs. P_{miss}", 104, 0.0, 2.6, 100, -0.1, 0.5);


   //2D Focal Plane Quantities
   TH2F *h_xfp_vs_yfp = new TH2F("h_xfp_vs_yfp", "X_{fp} vs Y_{fp}", bins, -40., 40., bins, -60., 60.);
   TH2F *e_xfp_vs_yfp = new TH2F("e_xfp_vs_yfp", "X_{fp} vs Y_{fp}", bins, -20., 30., bins, -40., 20.);

   //2D theta_nq correlations with other kinematics
   TH2F *Q2_vs_thnq = new TH2F("Q2_vs_thnq", "", bins, 0., 80., bins, 2., 5.5);
   TH2F *xbj_vs_thnq = new TH2F("xbj_vs_thnq", "", bins, 0., 80., bins, 0., 2.0);
   TH2F *pm_vs_thnq = new TH2F("pm_vs_thnq", "", bins, 0., 80., 104, 0., 2.6);
   TH2F *Em_vs_thnq = new TH2F("Em_vs_thnq", "", bins, 0., 80., 60, -0.1, 0.5);

   //2D HMS v. SHMS Acceptance Correlations
   TH2F *hxptar_vs_exptar = new TH2F("hxptar_vs_exptar", "HMS vs. SHMS, X'_{tar}", bins, -0.06, 0.06, bins, -0.1, 0.1);
   TH2F *hyptar_vs_eyptar = new TH2F("hyptar_vs_eyptar", "HMS vs. SHMS, Y'_{tar}", bins, -0.04, 0.04, bins, -0.05, 0.05);
   TH2F *hdelta_vs_edelta = new TH2F("hdelta_vs_edelta", "HMS vs. SHMS, #delta", bins, -15., 12, bins, -15., 15.);

   TH2F *hdelta_vs_thnq = new TH2F("hdelta_vs_thnq", "", bins, 0, 80., bins, -15., 15.);
   TH2F *edelta_vs_thnq = new TH2F("edelta_vs_thnq", "", bins, 0, 80., bins, -15., 8.);
   
   
   /************Define Histos to APPLY CUTS*********************************/
 
     //Kinematics Quantities
   TH1F *cut_Emiss = new TH1F("cut_Emiss","missing energy", 30, -0.1, 0.5);  //binwidth = 0.0020
   TH1F *cut_pm = new TH1F("cut_pm","missing momentum",  104, 0.0, 2.6);
   TH1F *cut_Q_2 = new TH1F("cut_Q_2","Q2", bins, 2., 5.5);
   TH1F *cut_omega = new TH1F("cut_omega","Energy Transfer, #omega", bins, 0., 4.);
   TH1F *cut_W_inv = new TH1F("cut_W_inv", "Invariant Mass, W", bins, -1.5, 2.3);
   TH1F *cut_theta_elec = new TH1F("cut_theta_elec", "Electron Scatt. Angle", bins, 8, 15);
   TH1F *cut_theta_prot = new TH1F("cut_theta_prot", "Proton Scatt. Angle", bins, 35, 65);


   //Additional Kinematics Variables
   TH1F *cut_W_2 = new TH1F("cut_W2", "Invariant Mass W2", bins, 0, 2.3);
   TH1F *cut_xbj = new TH1F("cut_xbj", "x-Bjorken", bins, 0.0, 2.0);
   TH1F *cut_P_f = new TH1F("cut_P_f", "Final Proton Momentum", bins, 0., 3.);
   TH1F *cut_k_i = new TH1F("cut_ki", "Initial e^{-} Momentum", bins, 8., 12.);
   TH1F *cut_k_f = new TH1F("cut_kf", "Final e^{-} Momentum", bins, 7., 9.5);
   TH1F *cut_E_n = new TH1F("cut_En", "Neutron Final Energy", bins, 0., 2.);
   TH1F *cut_theta_nq = new TH1F("cut_theta_nq", "Neutron Angle, #theta_{nq}", bins, 0., 80.);
   TH1F *cut_theta_q = new TH1F("cut_theta_q", "q-vector Angle, #theta_{q}", bins, 40, 100.);
   
   
   //Target Reconstruction Variables
   TH1F *cut_x_tar = new TH1F("cut_x_tar", "x_Target", bins, -0.25, 0.25);
   TH1F *cut_y_tar = new TH1F("cut_y_tar", "y_Target", bins, -0.25, 0.25);
   TH1F *cut_z_tar = new TH1F("cut_z_tar", "z_Target", bins, -5.5, 5.5);
   
   //Hadron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
   TH1F *cut_hytar = new TH1F("cut_hytar", hadron_arm + " Y_{tar}", bins, -5., 5.);
   TH1F *cut_hxptar = new TH1F("cut_hxptar", hadron_arm + " X'_{tar}", bins, -0.1, 0.1 );
   TH1F *cut_hyptar = new TH1F("cut_hyptar", hadron_arm + " Y'_{tar}", bins, -0.05, 0.05 );
   TH1F *cut_hdelta = new TH1F("cut_hdelta", hadron_arm + " Momentum Acceptance, #delta", bins, -15., 15.);

   //Hadron arm Focal Plane Quantities
   TH1F *cut_hxfp = new TH1F("cut_hxfp", hadron_arm + " X_{fp}", bins, -60., 60.);
   TH1F *cut_hyfp = new TH1F("cut_hyfp", hadron_arm + " Y_{fp}", bins, -40., 40.);
   TH1F *cut_hxpfp = new TH1F("cut_hxpfp", hadron_arm + " X'_{fp}", bins, -0.08, 0.08 );
   TH1F *cut_hypfp = new TH1F("cut_hypfp", hadron_arm + " Y'_{fp}", bins, -0.04, 0.04);

      
   //Electron Arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
   TH1F *cut_eytar = new TH1F("cut_eytar", electron_arm + " Y_{tar}", bins, -3., 3.);
   TH1F *cut_exptar = new TH1F("cut_exptar", electron_arm + " X'_{tar}", bins, -0.06, 0.06);
   TH1F *cut_eyptar = new TH1F("cut_eyptar", electron_arm + " Y'_{tar}", bins, -0.04, 0.04);
   TH1F *cut_edelta = new TH1F("cut_edelta", electron_arm + " Momentum Acceptance, #delta", bins, -15., 8.);

   //Electron Arm Focal Plane Quantities
   TH1F *cut_exfp = new TH1F("cut_exfp", electron_arm + " X_{fp}", bins, -40., 20.);
   TH1F *cut_eyfp = new TH1F("cut_eyfp", electron_arm + " Y_{fp}", bins, -20., 30.);
   TH1F *cut_expfp = new TH1F("cut_expfp", electron_arm + " X'_{fp}", bins, -0.1, 0.06);
   TH1F *cut_eypfp = new TH1F("cut_eypfp", electron_arm + " Y'_{fp}", bins, -0.04, 0.06);


   TH2F *cut_h_xfp_vs_yfp = new TH2F("cut_h_xfp_vs_yfp", "X_{fp} vs Y_{fp}", bins, -40., 40., bins, -60., 60.);
   TH2F *cut_e_xfp_vs_yfp = new TH2F("cut_e_xfp_vs_yfp", "X_{fp} vs Y_{fp}", bins, -20., 30., bins, -40., 20.);

   TH2F *cut_emiss_vs_pmiss = new TH2F("cut_emiss_vs_pmiss", " E_{miss} vs. P_{miss}", 104, 0.0, 2.6, 100, -0.1, 0.5);

   //2D theta_nq correlations with other kinematics
   TH2F *cut_Q2_vs_thnq = new TH2F("cut_Q2_vs_thnq", "", bins, 0., 80., bins, 2.0, 5.5);
   TH2F *cut_xbj_vs_thnq = new TH2F("cut_xbj_vs_thnq", "", bins, 0., 80., bins, 0.5, 1.5);
   TH2F *cut_pm_vs_thnq = new TH2F("cut_pm_vs_thnq", "", bins, 0., 80., 104, 0.0, 2.6);
   TH2F *cut_Em_vs_thnq = new TH2F("cut_Em_vs_thnq", "", bins, 0., 80., 60, -0.1, 0.5);

   //2D HMS v. SHMS Acceptance Correlations
   TH2F *cut_hxptar_vs_exptar = new TH2F("cut_hxptar_vs_exptar", "HMS vs. SHMS, X'_{tar}", bins, -0.06, 0.06, bins, -0.1, 0.1);
   TH2F *cut_hyptar_vs_eyptar = new TH2F("cut_hyptar_vs_eyptar", "HMS vs. SHMS, Y'_{tar}", bins, -0.04, 0.04, bins, -0.05, 0.05);
   TH2F *cut_hdelta_vs_edelta = new TH2F("cut_hdelta_vs_edelta", "HMS vs. SHMS, #delta", bins, -15., 12, bins, -15., 15.);

   
   //---------------------------------------------------------


   //Define Additional Kinematic Variables
   Double_t W2;             //Invarianrt Mass Squared
   Double_t X;              //B-jorken X
   Double_t Pf;             //Final Proton Momentum 
   Double_t ki;             //Incident e- momentum
   Double_t kf;             //Final electron momentum
   Double_t Ee;              //Electron final energy
   Double_t En;             //Neutron Energy
   Double_t Ep;             //proton Energy
   Double_t Kp;             //proton kinetic energy
   Double_t Kn;            //neutron kinetic energy
   Double_t th_nq;       //Angle betweenq-vector and neutron
   Double_t th_q;        //Angle between q-vector and beamline (+z axis --lab)
   Double_t Em_v2;      //missing energy v.2
   
   //DEFINE KINEMATICS Limits

   //th_nq = 40 +/- 5 deg (fsi are small)
   Double_t thnq_cent = 40.*dtr;
   Double_t dth = 5.*dtr;
   Double_t thnq_min = thnq_cent - dth;
   Double_t thnq_max = thnq_cent + dth;

   //Q2_cent = 4.25 +/- 0.25 limits
   Double_t Q2_min = 4.0;
   Double_t Q2_max = 5.0; //4.5;

   //x-Bjorken Limits x = 1.35 +/- 0.05
   Double_t xbj_min = 1.30;
   Double_t xbj_max = 1.70; //1.40;

   //Missing Energy, Em = 2.2 MeV (-10 MeV, 25 MeV)
   Double_t Em_min = -0.04;
   Double_t Em_max = 0.08;
   


   


   //Determine the charge factor:
   //definition: total charge deposited on target over a time period
   //SIMC assumes it is #generated_events / 1mC
   
   //Charge factor is the total integrated charge assuming a beam current and run time
   // Double_t Ib = 40;       //beam current in microamps (micro-Coulombs / sec),   1 mC = 1000 uC
   //Double_t time = 1.0;     //estimated time (in hours) a run takes (start - end) of run
   Double_t charge_factor = Ib * time * 3600. / 1000.;


   //----------Use Total Charge (ONLY from data)---------
   //Double_t Q_bcm1;
   //Double_t Q_bcm2;

   //Double_t Q_avg = (Q_bcm1 + Q_bcm2) / 2.;
   //Double_t charge_factor = Q_avg / 1000.;   //in mC
   //-----------------------------------------------------
   
   //Tracking efficiencies and beamON time
   Double_t e_trk_eff;
   Double_t h_trk_eff;
   Double_t beam_time;


   //Set to 1 for SIMC
   e_trk_eff = 1.0;
   h_trk_eff = 1.0;

   Double_t FullWeight;
   

   //************************************************
   

      
   Long64_t nentries  = fChain->GetEntries();


   //Begin Looping over EVENTS
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


      //-----Define Additional Kinematic Variables--------
      Ein = Ein / 1000.;
      W2 = W*W;
      X = Q2 / (2.*MP*nu);
      En = sqrt(MN*MN + Pm*Pm);
      Pf = sqrt(pow(nu+MD-En,2) - MP*MP);
      Ep = sqrt(MP*MP + Pf*Pf);
      ki = sqrt(Ein*Ein - me*me);
      kf = Q2 / (4.*ki*pow(sin(theta_e/2.), 2));
      Ee = sqrt(me*me + kf*kf);
      Kp = Ep - MP;
      Kn = En - MN;
      th_nq = acos((q - Pf*cos(theta_pq))/Pm);
      th_q = theta_pq + theta_p;

      Em_v2 = Kp + Kn - nu;
      
      /*
 //-------Spectrometer resolution variables-----------
      h_d_delta = h_deltai - h_delta;
      e_d_delta = e_deltai - e_delta;

      
      if (time == 20.)
	{
	  h_dP = h_d_delta*hP0_580/100.;         //hadron arm momentum resolution
	  e_dP = e_d_delta*eP0/100.;         //electron arm momentum resolution
	  
	  h_Pf_thrown = h_deltai*hP0_580/100. + hP0_580;             //thrown final hadron momentum
	  e_kf_thrown = e_deltai*eP0/100. + eP0;             //thrown final electron momentum
	}
      else if (time == 42.)
	{
	  h_dP = h_d_delta*hP0_750/100.;         //hadron arm momentum resolution
	  e_dP = e_d_delta*eP0/100.;         //electron arm momentum resolution
	  
	  h_Pf_thrown = h_deltai*hP0_750/100. + hP0_750;             //thrown final hadron momentum
	  e_kf_thrown = e_deltai*eP0/100. + eP0;             //thrown final electron momentum

	}

      nu_thrown = Ein - e_kf_thrown;                     //thown energy transfer
      Ep_thrown = sqrt(MP*MP + h_Pf_thrown*h_Pf_thrown);   //thrown proton final energy

      Pm_thrown = sqrt( pow(nu_thrown + MD - Ep_thrown, 2) - MN*MN  );  //thrown missing momentum
      En_thrown = sqrt( MN*MN + Pm_thrown*Pm_thrown);
      Kp_thrown = Ep_thrown - MP;
      Kn_thrown = En_thrown - MN;
      Em_thrown = Kp_thrown + Kn_thrown - nu_thrown;

      dPmiss = Pm_thrown - Pm;  //missing momentum resolution
      dEmiss = Em_thrown - Em;  //missing energy resolution

      //Fill variables
      res_hdelta->Fill(h_d_delta);
      res_hP->Fill(h_dP);

      res_edelta->Fill(e_d_delta);
      res_ekf->Fill(e_dP);
      res_pmiss->Fill(dPmiss);
      res_emiss->Fill(dEmiss);
      Emiss_v2->Fill(Em_v2);
      //---------------------------------------------------
      */

      //Define Kinematic Cuts
      Bool_t c_Em = Em>Em_min&&Em<Em_max;
      Bool_t c_Xbj = X>xbj_min&&X<xbj_max;
      Bool_t c_Q2 = Q2>Q2_min&&Q2<Q2_max;
      
      
      //-----------Define Acceptance Limit Cuts------------
      
      // e-arm
      Bool_t c_e_xptar = fabs(e_xptar) <= 0.05;
      Bool_t c_e_yptar = fabs(e_yptar) <= 0.025;
      Bool_t c_e_solid = c_e_xptar * c_e_yptar;
      
      // p-arm
      Bool_t c_p_xptar = fabs(h_xptar) <= 0.06;
      Bool_t c_p_yptar = fabs(h_yptar) <= 0.035;
      Bool_t c_p_solid = c_p_xptar * c_p_yptar;
      
      // momentum acceptance
      Bool_t c_e_delta = (-8 <= e_delta) && ( e_delta <= 4);
      Bool_t c_p_delta = (-8 <= h_delta) && ( h_delta <= 8);
      

      // acceptance
      Bool_t c_accept = c_e_solid * c_p_solid * c_e_delta * c_p_delta;
      
      
      
      //cout << "Ein:" << Ein << endl;
      
      //The events must be weighted properly, so that they represent true Yield, and
      //can be compare to actual data
      FullWeight = (Normfac*Weight*charge_factor*e_trk_eff*h_trk_eff)/nentries;

      //-----------DEBUGGING------------------
      //cout << "Normfac: " << Normfac << endl;
      //cout << "Weight: " << Weight << endl;
      //cout << "charge: " << charge_factor << endl;
      //cout << "nentries: " << nentries << endl;
      //cout << "FullWeght: " << FullWeight << endl;
      //--------------------------------------

      //ANALYSIS OF EVENT-BY-EVENT GOES HERE!!!!!!
      
      //APPLY CUTS: BEGIN CUTS LOOP
      if (c_Em&&c_Q2)
	{
	  //Kinematics
	  cut_Emiss->Fill(Em, FullWeight);
	  cut_Emiss->Sumw2(kFALSE);
		  
	  cut_pm->Fill(Pm, FullWeight);
	  cut_pm->Sumw2(kFALSE);
	  
	  cut_Q_2->Fill(Q2, FullWeight);
	  cut_omega->Fill(nu, FullWeight);
	  cut_W_inv->Fill(W, FullWeight);
	  cut_theta_elec->Fill(theta_e/dtr, FullWeight);
	  cut_theta_prot->Fill(theta_p/dtr, FullWeight);

	  cut_Q_2->Sumw2(kFALSE);
	  cut_omega->Sumw2(kFALSE);
	  

	  //Additional Kinematics Variables
	  cut_W_2->Fill(W2, FullWeight);
	  cut_xbj->Fill(X, FullWeight); 
	  cut_P_f->Fill(Pf, FullWeight); 
	  cut_k_i->Fill(ki, FullWeight);
	  cut_k_f->Fill(kf, FullWeight); 
	  cut_E_n->Fill(En, FullWeight); 
	  cut_theta_nq->Fill(th_nq/dtr, FullWeight);
	  cut_theta_q->Fill(th_q/dtr, FullWeight);

	  cut_xbj->Sumw2(kFALSE);
	  cut_theta_nq->Sumw2(kFALSE);
	  
	  //Reconstructed Target Quantities (Lab Frame)
	  cut_x_tar->Fill(tar_x, FullWeight);
	  cut_y_tar->Fill(tar_y, FullWeight);
	  cut_z_tar->Fill(tar_z, FullWeight);
	  
	  
	  //Hadron-Arm Target Reconstruction 
	  cut_hytar->Fill(h_ytar, FullWeight);
	  cut_hxptar->Fill(h_xptar, FullWeight);
	  cut_hyptar->Fill(h_yptar, FullWeight);
	  cut_hdelta->Fill(h_delta, FullWeight);
	  
	  //Hadron-Arm Focal Plane
	  cut_hxfp->Fill(h_xfp, FullWeight);
	  cut_hyfp->Fill(h_yfp, FullWeight);
	  cut_hxpfp->Fill(h_xpfp, FullWeight);
	  cut_hypfp->Fill(h_ypfp, FullWeight);
	  
	  //Electron-Arm Target Reconstruction
	  cut_eytar->Fill(e_ytar, FullWeight);
	  cut_exptar->Fill(e_xptar, FullWeight);
	  cut_eyptar->Fill(e_yptar, FullWeight);
	  cut_edelta->Fill(e_delta, FullWeight);
	  
	  //Electron-Arm Focal Plane
	  cut_exfp->Fill(e_xfp, FullWeight);
	  cut_eyfp->Fill(e_yfp, FullWeight);
	  cut_expfp->Fill(e_xpfp, FullWeight);
	  cut_eypfp->Fill(e_ypfp, FullWeight);


	  //Focal Plane Quantities
	  cut_h_xfp_vs_yfp->Fill(h_yfp, h_xfp, FullWeight);
	  cut_e_xfp_vs_yfp->Fill(e_yfp, e_xfp, FullWeight);

	  cut_emiss_vs_pmiss->Fill(Pm, Em, FullWeight);

	  //2D theta_nq correlations with other kinematics
	  cut_Q2_vs_thnq->Fill(th_nq/dtr, Q2, FullWeight); 
	  cut_xbj_vs_thnq->Fill(th_nq/dtr, X, FullWeight);  
	  cut_pm_vs_thnq->Fill(th_nq/dtr, Pm, FullWeight);  
	  cut_Em_vs_thnq->Fill(th_nq/dtr, Em, FullWeight); 
	  
	  //2D HMS v. SHMS Acceptance Correlations
	  cut_hxptar_vs_exptar->Fill(e_xptar, h_xptar, FullWeight); 
	  cut_hyptar_vs_eyptar->Fill(e_yptar, h_yptar, FullWeight); 
	  cut_hdelta_vs_edelta->Fill(e_delta, h_delta, FullWeight);

	}//End CUTS LOOP
         


      //Kinematics
      Emiss->Fill(Em, FullWeight);
      Emiss->Sumw2(kFALSE);         //Set error calculated by weight false (use sqrt(bin_content) by default.)

      pm->Fill(Pm, FullWeight);
      pm->Sumw2(kFALSE);

      Q_2->Fill(Q2, FullWeight);
      omega->Fill(nu, FullWeight);
      W_inv->Fill(W, FullWeight);
      theta_elec->Fill(theta_e/dtr, FullWeight);
      theta_prot->Fill(theta_p/dtr, FullWeight);

      Q_2->Sumw2(kFALSE);
      omega->Sumw2(kFALSE);
      
      //Additinal Kinematics
      W_2->Fill(W2, FullWeight);
      xbj->Fill(X, FullWeight);
      P_f->Fill(Pf, FullWeight);
      k_i->Fill(ki, FullWeight);
      k_f->Fill(kf, FullWeight);
      E_n->Fill(En, FullWeight);
      theta_nq->Fill(th_nq/dtr, FullWeight);
      theta_q->Fill(th_q/dtr, FullWeight);

      xbj->Sumw2(kFALSE);
      theta_nq->Sumw2(kFALSE);

      
      //Reconstructed Target Quantities (Lab Frame)
      x_tar->Fill(tar_x, FullWeight);
      y_tar->Fill(tar_y, FullWeight);
      z_tar->Fill(tar_z, FullWeight);

      
      //Hadron-Arm Target Reconstruction 
      hytar->Fill(h_ytar, FullWeight);
      hxptar->Fill(h_xptar, FullWeight);
      hyptar->Fill(h_yptar, FullWeight);
      hdelta->Fill(h_delta, FullWeight);
      
      //Hadron-Arm Focal Plane
      hxfp->Fill(h_xfp, FullWeight);
      hyfp->Fill(h_yfp, FullWeight);
      hxpfp->Fill(h_xpfp, FullWeight);
      hypfp->Fill(h_ypfp, FullWeight);
      
      //Electron-Arm Target Reconstruction
      eytar->Fill(e_ytar, FullWeight);
      exptar->Fill(e_xptar, FullWeight);
      eyptar->Fill(e_yptar, FullWeight);
      edelta->Fill(e_delta, FullWeight);
      
      //Electron-Arm Focal Plane
      exfp->Fill(e_xfp, FullWeight);
      eyfp->Fill(e_yfp, FullWeight);
      expfp->Fill(e_xpfp, FullWeight);
      eypfp->Fill(e_ypfp, FullWeight);

      
      //Fill 2D HMS Focal Plane Quantities
      h_xfp_vs_yfp->Fill(h_yfp, h_xfp, FullWeight);
      e_xfp_vs_yfp->Fill(e_yfp, e_xfp, FullWeight);

      emiss_vs_pmiss->Fill(Pm, Em, FullWeight);
      
      Q2_vs_thnq->Fill(th_nq/dtr, Q2, FullWeight);
      xbj_vs_thnq->Fill(th_nq/dtr, X, FullWeight);
      pm_vs_thnq->Fill(th_nq/dtr, Pm, FullWeight);
      Em_vs_thnq->Fill(th_nq/dtr, Em, FullWeight);

      hxptar_vs_exptar->Fill(e_xptar, h_xptar, FullWeight);
      hyptar_vs_eyptar->Fill(e_yptar, h_yptar, FullWeight);
      hdelta_vs_edelta->Fill(e_delta, h_delta, FullWeight);

      hdelta_vs_thnq->Fill(th_nq/dtr, h_delta, FullWeight);
      edelta_vs_thnq->Fill(th_nq/dtr, e_delta, FullWeight);

      // if (Cut(ientry) < 0) continue;
   }

   /*
 //----Spectrometer resolution calculation-----

   //hDdelta->Fit(hfit, "R");
   //h_sigma = hfit->GetParameter(2);
   //h_P =  h_sigma/100. * hP0 * 1000.;

   //Get Standard deviation from histograms
   h_sigma = res_hdelta->GetStdDev();
   h_Psigma = res_hP->GetStdDev();

   e_sigma = res_edelta->GetStdDev();
   e_Psigma = res_ekf->GetStdDev();

   Pm_sigma = res_pmiss->GetStdDev();
   Em_sigma = res_emiss->GetStdDev();
   */
   //Open a data file to store spec. resolution, estimated yields, rates, and statistical uncertainties
   simc_file.ReplaceAll(".root", ".report");   // 5 = length( $name )
 
   ofstream data;
   data.open(simc_file); 

   
   /*
   data << "HMS Delta Resolution: " << h_sigma << " %" << endl;
   data << "HMS Momentum Resolution: " << h_Psigma*1000. << " MeV" << endl;
   data << "  " << endl;
   data << "SHMS Delta Resolution: " << e_sigma << " %" << endl;
   data << "SHMS Momentum Resolution: " << e_Psigma*1000. << " MeV" << endl;


   data << "Missing Momentum Resolution: " << Pm_sigma*1000. << " MeV" << endl;
   data << "Missing Energy Resolution: " << Em_sigma*1000. << " MeV" << endl;
   data << "  " << endl;
   //data << "HMS Momentum Resolution " << h_dP << " MeV" << endl;
   */
   //Estimate the Yield and rates for missing momentum
   Double_t Yield;
   Double_t Yield_cut;
   Double_t Rates;
   Double_t Rates_cut;
   Double_t counts_per_charge;
   
   Yield = pm->Integral();
   Yield_cut = cut_pm->Integral();
   Rates = Yield /( time );
   Rates_cut = Yield_cut /( time  );

   data << "Yield:     " << Yield << endl;
   data << "Yield w/ Cuts: " << Yield_cut << endl;
   data << "   " << endl;
   data << "Rate: " << Rates << " / hr" << endl;
   data << "Rate /w Cuts: " << Rates_cut << " / hr" << endl;
   data << "  " << endl;
   data << "Counts / Charge: " << Yield / (Ib*time*3600./1000.) << " Counts/mC" << endl;
   data << "   " << endl;
   data << "Missing Momentum " << "               " <<  "Counts " << "     " << "Rel_err(%) " << "     " << "Counts w/cuts " << "     " <<  "Rel_err w/cuts (%) " << endl;


   //Calculate Statistical Uncertainties of missing momentum,


   Double_t miss_p;   //missing momentum
   Int_t bin;   //bin to store bin corresponding to x-value of histo
   Int_t content;    //store bin content
   Int_t cut_content;     //store bin content for histos with a cut
   Double_t err;    //store statistical error (relative error 1/sqrt(N)) of bin
   Double_t cut_err;    // store error of histogram with a cut

   
   for(miss_p = 0.3; miss_p < 1.2; miss_p = miss_p + 0.01)
     {

       bin = pm->GetXaxis()->FindBin(miss_p);

       content = pm->GetBinContent(bin);
       cut_content = cut_pm->GetBinContent(bin);
       
       err = 1. / sqrt(content)*100.;
       cut_err = 1. / sqrt(cut_content)*100.;
       
       data << miss_p*1000. << "     " << content << "     " << err << "    " <<  cut_content << "     " << cut_err << "    " << endl;
       
     }
   data.close();

   outfile->Write();

}
