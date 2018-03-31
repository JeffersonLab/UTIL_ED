#ifndef SET_LOWPm_HISTOS_H
#define SET_LOWPm_HISTOS_H

//Header file designed to set global histogram ranges that would apply
//to both simc/data histogram declarations. This way, one makes a single
//configuration of this file, and it will set the histogram ranges of multiple
//files simultaneosuly, if included as a header in that file.

//Units in GeV, degrees

//Default binning
Int_t nbins = 65;


//----------Kinematic Quantities---------
//Emiss
Double_t Em_nbins = 32;
Double_t Em_xmin = -0.1;
Double_t Em_xmax = 0.7;

//Pmiss
Double_t Pm_nbins = 24;
Double_t Pm_xmin = -0.1;
Double_t Pm_xmax = 0.5;

//Q2
Double_t Q2_nbins = nbins;
Double_t Q2_xmin = 1.5;
Double_t Q2_xmax = 5.5;

//omega (E-E')
Double_t om_nbins = nbins;
Double_t om_xmin = 1.5.;
Double_t om_xmax = 3.3;

//W_inv
Double_t W_nbins = nbins;
Double_t W_xmin = 0.0;
Double_t W_xmax = 2.3;

//theta_elec
Double_t the_nbins = nbins;
Double_t the_xmin = 8.;
Double_t the_xmax = 15.;

//theta_prot
Double_t thp_nbins = nbins;
Double_t thp_xmin = 35.;
Double_t thp_xmax = 45.;

//-------Additional Kinematic Variables----------

//W2
Double_t W2_nbins = nbins;
Double_t W2_xmin = 0.0;
Double_t W2_xmax = 2.3;

//xBj
Double_t xbj_nbins = nbins;
Double_t xbj_xmin = 0.5;
Double_t xbj_xmax = 1.5;

//Pf
Double_t Pf_nbins = nbins;
Double_t Pf_xmin = 2.0;
Double_t Pf_xmax = 3.5;

//kf
Double_t kf_nbins = nbins;
Double_t kf_xmin = 7.0;
Double_t kf_xmax = 9.5;

//------Target Reconstruction Variables----------
Double_t xtar_nbins = nbins;
Double_t xtar_xmin = -0.25;
Double_t xtar_xmax = 0.25;

Double_t ytar_nbins = nbins;
Double_t ytar_xmin = -0.25;
Double_t ytar_xmax = 0.25;

Double_t ztar_nbins = nbins;
Double_t ztar_xmin = -5.5;
Double_t ztar_xmax = 5.5;

//Hadron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
Double_t hytar_nbins = nbins;
Double_t hytar_xmin = -5.;
Double_t hytar_xmax = 5.;

Double_t hxptar_nbins = nbins;
Double_t hxptar_xmin = -0.1;
Double_t hxptar_xmax = 0.1;

Double_t hyptar_nbins = nbins;
Double_t hyptar_xmin = -0.05;
Double_t hyptar_xmax = 0.05;

Double_t hdelta_nbins = nbins;
Double_t hdelta_xmin = -15.;
Double_t hdelta_xmax = 15.;

//Hadron arm Focal Plane Quantities
//X-focal plane
Double_t hxfp_nbins = nbins;
Double_t hxfp_xmin = -60.;
Double_t hxfp_xmax = 60.;
//Y-focal plane
Double_t hyfp_nbins = nbins;
Double_t hyfp_xmin = -25.;
Double_t hyfp_xmax = 25.;
//X'-focal plane
Double_t hxpfp_nbins = nbins;
Double_t hxpfp_xmin = -0.08;
Double_t hxpfp_xmax = 0.08;
//Y'-focal plane
Double_t hypfp_nbins = nbins;
Double_t hypfp_xmin = -0.04;
Double_t hypfp_xmax = 0.04;

//Electron Arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
Double_t eytar_nbins = nbins;
Double_t eytar_xmin = -3.;
Double_t eytar_xmax = 3.;

Double_t exptar_nbins = nbins;
Double_t exptar_xmin = -0.06;
Double_t exptar_xmax = 0.06;

Double_t eyptar_nbins = nbins;
Double_t eyptar_xmin = -0.04;
Double_t eyptar_xmax = 0.04;

Double_t edelta_nbins = nbins;
Double_t edelta_xmin = -15.;
Double_t edelta_xmax = 8.;

//Electron Arm Focal Plane Quantities
Double_t exfp_nbins = nbins;
Double_t exfp_xmin = -35.;
Double_t exfp_xmax = 10.;

Double_t eyfp_nbins = nbins;
Double_t eyfp_xmin = -20.;
Double_t eyfp_xmax = 20.;

Double_t expfp_nbins = nbins;
Double_t expfp_xmin = -0.08;
Double_t expfp_xmax = 0.04;

Double_t eypfp_nbins = nbins;
Double_t eypfp_xmin = -0.04;
Double_t eypfp_xmax = 0.04;





#endif

    
