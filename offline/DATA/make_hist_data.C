#include <TSystem.h>
#include <TString.h>
#include "TFile.h"
#include "TTree.h"
#include <TNtuple.h>
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1F.h"
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TROOT.h>
#include <TMath.h>
#include <TLegend.h>
#include <TPaveLabel.h>
#include <TProfile.h>
#include <TPolyLine.h>
#include <TObjArray.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <TRandom3.h>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <TDecompSVD.h>
//#include "../header_files/set_highdeep_histos.h"
#include "../header_files/set_lowdeep_histos.h"

using namespace std;

void make_hist_data (TString Pmiss){

  TString basename;
  TString alias;
  Double_t pmiss_set;

  TString inputroot;
  TString outputhist;


  if (Pmiss=="80")
    {
      //  basename="coin_replay_production_3267_-1";
      basename="coin_replay_production_3267_-1olddelta";

      pmiss_set=80.;
      alias = "Pm80_run3267_oldpdelta";
      inputroot="../../../ROOTfiles/"+basename+".root";
	    
    }
  
  else if (Pmiss=="580")
    {
      basename="Pm580round2";
      pmiss_set=580.;

      inputroot="./ROOTfiles/"+basename+".root";

    }

  else if (Pmiss=="750")
    {
      basename="Pm750";
      pmiss_set=750.;

      inputroot="./ROOTfiles/"+basename+".root";

    }

  
    if (basename=="") {
     cout << " Input the basename of the root file (assumed to be in cyero/hallc_replay/ROOTfiles/ )" << endl;
     cin >> basename;
   }
  

  outputhist= "DATA_ROOTfiles/"+alias+".root";
  
  TObjArray HList(0);
  
  TString hadron_arm;
  TString electron_arm;
  hadron_arm = "HMS";
  electron_arm = "SHMS";

//
 //
  TFile *fsimc = new TFile(inputroot); 
  TTree *tsimc = (TTree*) fsimc->Get("T");
// Define branches
   Double_t  shms_ThScat;
   tsimc->SetBranchAddress("P.kin.primary.scat_ang_rad",&shms_ThScat);
   Double_t  shms_etracknorm;
   tsimc->SetBranchAddress("P.cal.etracknorm",&shms_etracknorm);
   Double_t  shms_ngcer_npesum;
   tsimc->SetBranchAddress("P.ngcer.npeSum",&shms_ngcer_npesum);
   Double_t  shms_W;
   tsimc->SetBranchAddress("P.kin.primary.W",&shms_W);
   Double_t  shms_Q2;
   tsimc->SetBranchAddress("P.kin.primary.Q2",&shms_Q2);
   Double_t  shms_xbj;
   tsimc->SetBranchAddress("P.kin.primary.x_bj",&shms_xbj);
   Double_t  shms_nu;
   tsimc->SetBranchAddress("P.kin.primary.nu",&shms_nu);
   Double_t  shms_q3m;
   tsimc->SetBranchAddress("P.kin.primary.q3m",&shms_q3m);
   Double_t  shms_thq;
   tsimc->SetBranchAddress("P.kin.primary.th_q",&shms_thq);
   Double_t  shms_kf;
   tsimc->SetBranchAddress("P.gtr.p",&shms_kf);
   Double_t  shms_reactz;
   tsimc->SetBranchAddress("P.react.z",&shms_reactz);
   Double_t  shms_xfp;
   tsimc->SetBranchAddress("P.dc.x_fp",&shms_xfp);
   Double_t  shms_xpfp;
   tsimc->SetBranchAddress("P.dc.xp_fp",&shms_xpfp);
   Double_t  shms_yfp;
   tsimc->SetBranchAddress("P.dc.y_fp",&shms_yfp);
   Double_t  shms_ypfp;
   tsimc->SetBranchAddress("P.dc.yp_fp",&shms_ypfp);
   Double_t  shms_ytar;
   tsimc->SetBranchAddress("P.gtr.y",&shms_ytar);
   Double_t  shms_yptar;
   tsimc->SetBranchAddress("P.gtr.ph",&shms_yptar);
   Double_t  shms_xptar;
   tsimc->SetBranchAddress("P.gtr.th",&shms_xptar);
   Double_t  shms_delta;
   tsimc->SetBranchAddress("P.gtr.dp",&shms_delta);
   //
   Double_t  hms_pf;
   tsimc->SetBranchAddress("H.gtr.p",&hms_pf);
   Double_t  hms_xfp;
   tsimc->SetBranchAddress("H.dc.x_fp",&hms_xfp);
   Double_t  hms_xpfp;
   tsimc->SetBranchAddress("H.dc.xp_fp",&hms_xpfp);
   Double_t  hms_yfp;
   tsimc->SetBranchAddress("H.dc.y_fp",&hms_yfp);
   Double_t  hms_ypfp;
   tsimc->SetBranchAddress("H.dc.yp_fp",&hms_ypfp);
   Double_t  hms_ytar;
   tsimc->SetBranchAddress("H.gtr.y",&hms_ytar);
   Double_t  hms_yptar;
   tsimc->SetBranchAddress("H.gtr.ph",&hms_yptar);
   Double_t  hms_xptar;
   tsimc->SetBranchAddress("H.gtr.th",&hms_xptar);
   Double_t  hms_delta;
   tsimc->SetBranchAddress("H.gtr.dp",&hms_delta);
   Double_t  hms_emiss;
   tsimc->SetBranchAddress("H.kin.secondary.emiss_nuc",&hms_emiss);
   Double_t  hms_pmiss;
   tsimc->SetBranchAddress("H.kin.secondary.pmiss",&hms_pmiss);
   Double_t  hms_thbq;
   tsimc->SetBranchAddress("H.kin.secondary.th_bq",&hms_thbq);
   Double_t  hms_thxq;
   tsimc->SetBranchAddress("H.kin.secondary.th_xq",&hms_thxq);
   // branches for cointime calc
    Double_t TcoinpTRIG1_ROC1_tdcTimeRaw;
    Double_t TcoinpTRIG4_ROC1_tdcTimeRaw;
    Double_t TcoinpTRIG1_ROC2_tdcTimeRaw;
    Double_t TcoinpTRIG4_ROC2_tdcTimeRaw;
    
    Double_t TcoinhTRIG1_ROC1_tdcTimeRaw;
    Double_t TcoinhTRIG4_ROC1_tdcTimeRaw;
    Double_t TcoinhTRIG1_ROC2_tdcTimeRaw;
    Double_t TcoinhTRIG4_ROC2_tdcTimeRaw;
    //Hodoscope start time 
    Double_t HhodStartTime;
    Double_t PhodStartTime;
    Double_t PhodfpHitsTime;
    Double_t HhodfpHitsTime;
    Double_t PhodoStartTimeMean=30.;
    Double_t HhodoStartTimeMean=30.;
    tsimc->SetBranchAddress("H.hod.starttime", &HhodStartTime);    
    tsimc->SetBranchAddress("H.hod.fpHitsTime", &HhodfpHitsTime);
    tsimc->SetBranchAddress("P.hod.starttime", &PhodStartTime);
    tsimc->SetBranchAddress("P.hod.fpHitsTime", &PhodfpHitsTime);
    tsimc->SetBranchAddress("T.coin.pTRIG1_ROC1_tdcTimeRaw", &TcoinpTRIG1_ROC1_tdcTimeRaw);
    tsimc->SetBranchAddress("T.coin.pTRIG4_ROC1_tdcTimeRaw", &TcoinpTRIG4_ROC1_tdcTimeRaw);
    tsimc->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTimeRaw", &TcoinpTRIG1_ROC2_tdcTimeRaw);
    tsimc->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcTimeRaw", &TcoinpTRIG4_ROC2_tdcTimeRaw);
    Double_t pOffset = 11.5;  // in ns
    Double_t hOffset = 335.;
    Double_t speedOfLight = 29.9792; // in cm/ns
    
    Double_t SHMScentralPathLen = 18.1*100;  // SHMS Target to focal plane path length converted to cm
    Double_t SHMSpathLength = 18.1*100;      // For now assume that it's same as SHMScentralPathLen
    Double_t HMScentralPathLen = 22*100;     // HMS Target to focal plane path length converted to cm
    Double_t DeltaHMSpathLength;    
    Double_t DeltaSHMSpathLength;    
    Double_t SHMSpartMass=0.510998/1000.0; 
    Double_t HMSpartMass= 938.27208/1000.0;
  
   //
    // Define histograms
   TH1F *data_Emiss = new TH1F("data_Emiss","missing energy", Em_nbins, Em_xmin, Em_xmax);   
   HList.Add(data_Emiss);
   TH1F *data_pm = new TH1F("data_pm","missing momentum", Pm_nbins, Pm_xmin, Pm_xmax); 
   HList.Add(data_pm);
   TH1F *data_Q2 = new TH1F("data_Q2","Q2", Q2_nbins, Q2_xmin, Q2_xmax);
   HList.Add(data_Q2);
   TH1F *data_omega = new TH1F("data_omega","Energy Transfer, #omega", om_nbins, om_xmin, om_xmax);
   HList.Add(data_omega);
   TH1F *data_W_inv = new TH1F("data_W_inv", "Invariant Mass, W", W_nbins, W_xmin, W_xmax);     
    HList.Add(data_W_inv);
   TH1F *data_theta_elec = new TH1F("data_theta_elec", "Electron Scatt. Angle", the_nbins, the_xmin, the_xmax);
    HList.Add(data_theta_elec);
   TH1F *data_theta_prot = new TH1F("data_theta_prot", "Proton Scatt. Angle", thp_nbins, thp_xmin, thp_xmax);
    HList.Add(data_theta_prot);
   TH1F *data_W2 = new TH1F("data_W2", "Invariant Mass W2", W2_nbins, W2_xmin, W2_xmax);
    HList.Add(data_W2);
   TH1F *data_xbj = new TH1F("data_xbj", "x-Bjorken", xbj_nbins, xbj_xmin, xbj_xmax);
   HList.Add(data_xbj);
   TH1F *data_Pf = new TH1F("data_Pf", "Final Proton Momentum", Pf_nbins, Pf_xmin, Pf_xmax);
   HList.Add(data_Pf);
   TH1F *data_kf = new TH1F("data_kf", "Final e^{-} Momentum", kf_nbins, kf_xmin, kf_xmax);
   HList.Add(data_kf);
   TH1F *data_q = new TH1F("data_q", "|q|, 3-vector Magnitude ", q_nbins, q_xmin, q_xmax);
   HList.Add(data_q);
   TH1F *data_theta_nq = new TH1F("data_theta_nq", "Neutron Angle, #theta_{nq}", thnq_nbins, thnq_xmin, thnq_xmax);
   HList.Add(data_theta_nq);
   TH1F *data_theta_q = new TH1F("data_theta_q", "q-vector Angle, #theta_{q}", thq_nbins, thq_xmin, thq_xmax);
   HList.Add(data_theta_q);
   TH1F *data_theta_pq = new TH1F("data_theta_pq", "Proton Angle, #theta_{pq}", thpq_nbins, thpq_xmin, thpq_xmax);
   HList.Add(data_theta_pq);
  //Target Reconstruction Variables
   TH1F *data_x_tar = new TH1F("data_x_tar", "x_Target", xtar_nbins, xtar_xmin, xtar_xmax);
   HList.Add(data_x_tar);
   TH1F *data_y_tar = new TH1F("data_y_tar", "y_Target", ytar_nbins, ytar_xmin, ytar_xmax);
   HList.Add(data_y_tar);
   TH1F *data_z_tar = new TH1F("data_z_tar", "z_Target", ztar_nbins, ztar_xmin, ztar_xmax);
   HList.Add(data_z_tar);
   //Hadron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
   TH1F *data_hytar = new TH1F("data_hytar", hadron_arm + " Y_{tar}", hytar_nbins, hytar_xmin, hytar_xmax);
  TH1F *data_hxptar = new TH1F("data_hxptar", hadron_arm + " X'_{tar}", hxptar_nbins, hxptar_xmin, hxptar_xmax);
   TH1F *data_hyptar = new TH1F("data_hyptar", hadron_arm + " Y'_{tar}", hyptar_nbins, hyptar_xmin, hyptar_xmax );
   TH1F *data_hdelta = new TH1F("data_hdelta", hadron_arm + " Momentum Acceptance, #delta", hdelta_nbins, hdelta_xmin, hdelta_xmax);
    HList.Add(data_hytar);
    HList.Add(data_hyptar);
    HList.Add(data_hxptar);
    HList.Add(data_hdelta);

   //Hadron arm Focal Plane Quantities
   TH1F *data_hxfp = new TH1F("data_hxfp", hadron_arm + " X_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax);
   TH1F *data_hyfp = new TH1F("data_hyfp", hadron_arm + " Y_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax);
   TH1F *data_hxpfp = new TH1F("data_hxpfp", hadron_arm + " X'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax );
   TH1F *data_hypfp = new TH1F("data_hypfp", hadron_arm + " Y'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax);
   HList.Add(data_hxfp);;
    HList.Add(data_hyfp);
    HList.Add(data_hxpfp);
    HList.Add(data_hypfp);

      
   //Electron Arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
   TH1F *data_eytar = new TH1F("data_eytar", electron_arm + " Y_{tar}", eytar_nbins, eytar_xmin, eytar_xmax);
   TH1F *data_exptar = new TH1F("data_exptar", electron_arm + " X'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax);
   TH1F *data_eyptar = new TH1F("data_eyptar", electron_arm + " Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax);
   TH1F *data_edelta = new TH1F("data_edelta", electron_arm + " Momentum Acceptance, #delta", edelta_nbins, edelta_xmin, edelta_xmax);
    HList.Add(data_eytar);
    HList.Add(data_eyptar);
    HList.Add(data_exptar);
    HList.Add(data_edelta);

   //Electron Arm Focal Plane Quantities
   TH1F *data_exfp = new TH1F("data_exfp", electron_arm + " X_{fp}", exfp_nbins, exfp_xmin, exfp_xmax);
   TH1F *data_eyfp = new TH1F("data_eyfp", electron_arm + " Y_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax);
   TH1F *data_expfp = new TH1F("data_expfp", electron_arm + " X'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax);
   TH1F *data_eypfp = new TH1F("data_eypfp", electron_arm + " Y'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax);
   HList.Add(data_exfp);;
    HList.Add(data_eyfp);
    HList.Add(data_expfp);
    HList.Add(data_eypfp);

   //Cross-Check correlations
   TH2F *data_emiss_vs_pmiss = new TH2F("data_emiss_vs_pmiss", " E_{miss} vs. P_{miss}", Pm_nbins, Pm_xmin, Pm_xmax, Em_nbins, Em_xmin, Em_xmax);
   TH2F *data_edelta_vs_eyptar = new TH2F("data_edelta_vs_eyptar", electron_arm + " #delta vs. Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, edelta_nbins, edelta_xmin, edelta_xmax);
   
   TH2F *data_emiss_vs_exptar = new TH2F("data_emiss_vs_exptar", " E_{miss} vs. X'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax, Em_nbins, Em_xmin, Em_xmax);
   TH2F *data_emiss_vs_eyptar = new TH2F("data_emiss_vs_eyptar", " E_{miss} vs. Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, Em_nbins, Em_xmin, Em_xmax);
   HList.Add(data_emiss_vs_pmiss);
   HList.Add(data_edelta_vs_eyptar);
   HList.Add(data_emiss_vs_exptar);
   HList.Add(data_emiss_vs_eyptar);

   //Create 2D Histograms at the Focal Plane Quantities
   TH2F *data_hxfp_vs_hyfp = new TH2F("data_hxfp_vs_hyfp", "X_{fp} vs Y_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, hxfp_nbins, hxfp_xmin, hxfp_xmax);
   TH2F *data_exfp_vs_eyfp = new TH2F("data_exfp_vs_eyfp", "X_{fp} vs Y_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, exfp_nbins, exfp_xmin, exfp_xmax);
   HList.Add(data_hxfp_vs_hyfp);
   HList.Add(data_exfp_vs_eyfp);

   //2D HMS v. SHMS Acceptance Correlations
   TH2F *data_hxptar_vs_exptar = new TH2F("data_hxptar_vs_exptar", "HMS vs. SHMS, X'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);
   TH2F *data_hyptar_vs_eyptar = new TH2F("data_hyptar_vs_eyptar", "HMS vs. SHMS, Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, hyptar_nbins, hyptar_xmin, hyptar_xmax);
   TH2F *data_hdelta_vs_edelta = new TH2F("data_hdelta_vs_edelta", "HMS vs. SHMS, #delta", edelta_nbins, edelta_xmin, edelta_xmax, hdelta_nbins, hdelta_xmin, hdelta_xmax);
   HList.Add(data_hxptar_vs_exptar);
   HList.Add(data_hyptar_vs_eyptar);
   HList.Add(data_hdelta_vs_edelta);
   //
   TH1F *SHMSROC1cointime = new TH1F("SHMSROC1cointime"," ; SHMS ROC1 Cointime",240,-30,30);
   TH1F *SHMSROC2cointime = new TH1F("SHMSROC2cointime"," ; SHMS ROC2 Cointime",240,-30,30);
   HList.Add(SHMSROC1cointime);
   HList.Add(SHMSROC2cointime);
   Double_t SHMScoinCorr;
   Double_t HMScoinCorr;
   Double_t SHMScorrCoinTimeROC1;
   Double_t SHMScorrCoinTimeROC2;
 // loop over entries
   Double_t th_cent=20.;
   if (pmiss_set == 80.) th_cent=38.89;
   if (pmiss_set == 580.) th_cent=55.0;
   if (pmiss_set == 750.) th_cent=58.4;
   Double_t cos_ts=TMath::Cos(th_cent/180*3.14159);
   Double_t sin_ts=TMath::Sin(th_cent/180*3.14159); 
 Long64_t nentries = tsimc->GetEntries();
	for (int i = 0; i < nentries; i++) {
      		tsimc->GetEntry(i);
                if (i%10000==0) cout << " Entry = " << i << endl;
		Bool_t shms_pid_cut = shms_etracknorm > .85 && shms_ngcer_npesum > 1.;
		Bool_t shms_delta_cut = shms_delta > -5. && shms_delta < 10.;
		Bool_t hms_delta_cut = hms_delta > -10. && hms_delta < 10.;
		Bool_t em_cut = hms_emiss >=-0.15 && hms_emiss <=0.2;
		SHMScorrCoinTimeROC1=-1000;
		SHMScorrCoinTimeROC2=-1000;
		//
		if (hms_delta_cut && shms_delta_cut && shms_pid_cut)  {               
	            DeltaHMSpathLength = 12.462*hms_xpfp + 0.1138*hms_xpfp*hms_xfp - 0.0154*hms_xfp - 72.292*hms_xpfp*hms_xpfp - 0.0000544*hms_xfp*hms_xfp - 116.52*hms_yfp*hms_ypfp;
	            DeltaSHMSpathLength = -0.11*atan2(shms_xptar,1)*1000; //- 0.057*shms_delta;  // See elog entry: 3517525
	            Double_t PgtrBetaCalc = shms_kf/sqrt(shms_kf*shms_kf + SHMSpartMass*SHMSpartMass);
	            Double_t HgtrBetaCalc = hms_pf/sqrt(hms_pf*hms_pf + HMSpartMass*HMSpartMass);
	            SHMScoinCorr = SHMScentralPathLen / (speedOfLight*PgtrBetaCalc) + DeltaSHMSpathLength / speedOfLight*PgtrBetaCalc + (PhodoStartTimeMean - PhodfpHitsTime); 
	            HMScoinCorr = HMScentralPathLen / (speedOfLight*HgtrBetaCalc) + DeltaHMSpathLength / speedOfLight*HgtrBetaCalc + (HhodoStartTimeMean - HhodfpHitsTime); 	
	            SHMScorrCoinTimeROC1 = (TcoinpTRIG1_ROC1_tdcTimeRaw*0.1 - SHMScoinCorr) - (TcoinpTRIG4_ROC1_tdcTimeRaw*0.1 - HMScoinCorr) - pOffset; // 0.1 to convert to ns
	            SHMScorrCoinTimeROC2 = (TcoinpTRIG1_ROC2_tdcTimeRaw*0.1 - SHMScoinCorr) - (TcoinpTRIG4_ROC2_tdcTimeRaw*0.1 - HMScoinCorr) - pOffset; 
	            SHMSROC1cointime->Fill(SHMScorrCoinTimeROC1);
	            SHMSROC2cointime->Fill(SHMScorrCoinTimeROC2);
		}
	//
 		Bool_t cointime_cut = SHMScorrCoinTimeROC1 >=-3. && SHMScorrCoinTimeROC1 <=3.;
		if (hms_delta_cut && shms_delta_cut && shms_pid_cut && cointime_cut)  {
                    data_Emiss->Fill(hms_emiss);
		  data_emiss_vs_pmiss->Fill(hms_pmiss,hms_emiss);
		  data_emiss_vs_exptar->Fill(shms_xptar,hms_emiss);
		  data_emiss_vs_eyptar->Fill(shms_yptar,hms_emiss);
		}
		if (/*hms_delta_cut && shms_delta_cut && */shms_pid_cut && cointime_cut && em_cut)  {
		  data_pm->Fill(hms_pmiss);
		  data_Q2->Fill(shms_Q2);
		  data_omega->Fill(shms_nu);
		  data_W_inv->Fill(shms_W);
		  data_xbj->Fill(shms_xbj);
		  data_kf->Fill(shms_kf);
		  data_q->Fill(shms_q3m);
		  data_theta_q->Fill(shms_thq*180./3.14159);
		  data_theta_nq->Fill(hms_thbq*180./3.14159);
		  data_theta_pq->Fill(hms_thxq*180./3.14159);
		  data_Pf->Fill(hms_pf);
		  data_theta_elec->Fill(shms_ThScat*180./3.14159);
		  Double_t hms_ThScat = TMath::ACos((cos_ts + hms_yptar * sin_ts) / TMath::Sqrt( 1. + (hms_xptar) * (hms_xptar) + hms_yptar * hms_yptar ));
		  data_theta_prot->Fill(hms_ThScat*180./3.14159);
		  data_edelta->Fill(shms_delta);
		  data_eytar->Fill(shms_ytar);
		  data_eyptar->Fill(shms_yptar);
		  data_exptar->Fill(shms_xptar);
		  data_hdelta->Fill(hms_delta);
		  data_hytar->Fill(hms_ytar);
		  data_hyptar->Fill(hms_yptar);
		  data_hxptar->Fill(hms_xptar);
		  data_exfp->Fill(shms_xfp);
		  data_eyfp->Fill(shms_yfp);
		  data_expfp->Fill(shms_xpfp);
		  data_eypfp->Fill(shms_ypfp);
		  data_hxfp->Fill(hms_xfp);
		  data_hyfp->Fill(hms_yfp);
		  data_hxpfp->Fill(hms_xpfp);
		  data_hypfp->Fill(hms_ypfp);
 		  data_z_tar->Fill(shms_reactz);
		  data_edelta_vs_eyptar->Fill(shms_yptar,shms_delta);
		  data_hxfp_vs_hyfp->Fill(hms_yfp,hms_xfp);
		  data_exfp_vs_eyfp->Fill(shms_yfp,shms_xfp);
		  data_hxptar_vs_exptar->Fill(shms_xptar,hms_xptar);
		  data_hyptar_vs_eyptar->Fill(shms_yptar,hms_yptar);
 		  data_hdelta_vs_edelta->Fill(shms_delta,hms_delta);
               }
	}
	//
 TFile hsimc(outputhist,"recreate");
	HList.Write();
//
}
