#define NPLANES 12
#define NFILES 1

void dc_calib_draw()
{

  gROOT->SetBatch(1);

     

  TString file[NFILES];
  size_t size = 0;
  
  TString file1;
  //TString file2;
  //TString file3;
  //TString file4;
  
  
  //file1 = "./ROOTfiles/hms_replay_production_all_1856_10000005of6andcerelec.root";
  file1 = "./ROOTfiles/shms_replay_production_all_1791_1000000.root";
  //file2 = "./ROOTfiles/hms_replay_production_all_1856_1000000_neg10nsoffset.root";  
  //file3 = "./ROOTfiles/hms_replay_production_all_1856_1000000_neg5nsoffset.root";
  //file4 = "./ROOTfiles/hms_replay_production_all_1856_1000000_nooffset.root";

  //append files to array
  file[size++] = file1;
  //file[size++] = file2;
  //file[size++] = file3;
  //  file[size++] = file4;
  
 
  TFile *data_file[NFILES];
  
  //Open ROOT files
  for (int file_num = 0; file_num < NFILES; file_num++)
    {
      data_file[file_num] = new TFile(file[file_num], "READ"); 
    }

  

  //HMS
  string hplane_names[NPLANES]={"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
  Int_t hnwires[NPLANES] = {96, 96, 102, 102, 96, 96, 96, 96, 102, 102, 96, 96};

  //SHMS
  string splane_names[NPLANES]={"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2v2", "2v1", "2x2", "2x1", "2u2", "2u1"};
  Int_t snwires[NPLANES] = {107, 107, 79, 79, 107, 107, 107, 107, 79, 79, 107, 107};



  Int_t bins = 100;
   
   




   data_file[0]->cd();
   TTree *T = (TTree*)data_file[0]->Get("T");

   TFile *outfile = new TFile("drift_dist.root", "recreate");
  
   //Define PID Cuts
   
   TCut p_cer = "H.cer.npeSum>1.0";
   TCut p_cal = "H.cal.etot>0.1";
   Bool_t p_elec;

  //outfile->cd();

   //Plane Drift Distances
   TH1F *ddist_1u1 = new TH1F("ddist_1u1", "1U1 Plane Drift Distance", 100, -0.05, 0.55);
   TH1F *ddist_1u2 = new TH1F("ddist_1u2", "1U2 Plane Drift Distance", 100, -0.05, 0.55);
   TH1F *ddist_1x1 = new TH1F("ddist_1x1", "1X1 Plane Drift Distance", 100, -0.05, 0.55);
   TH1F *ddist_1x2 = new TH1F("ddist_1x2", "1X2 Plane Drift Distance", 100, -0.05, 0.55);
   TH1F *ddist_1v1 = new TH1F("ddist_1v1", "1V1 Plane Drift Distance", 100, -0.05, 0.55);
   TH1F *ddist_1v2 = new TH1F("ddist_1v2", "1V2 Plane Drift Distance", 100, -0.05, 0.55);
 
   TH1F *ddist_2v2 = new TH1F("ddist_2v2", "2V2 Plane Drift Distance", 100, -0.05, 0.55);
   TH1F *ddist_2v1 = new TH1F("ddist_2v1", "2V1 Plane Drift Distance", 100, -0.05, 0.55);
   TH1F *ddist_2x2 = new TH1F("ddist_2x2", "2X2 Plane Drift Distance", 100, -0.05, 0.55);
   TH1F *ddist_2x1 = new TH1F("ddist_2x1", "2X1 Plane Drift Distance", 100, -0.05, 0.55);
   TH1F *ddist_2u2 = new TH1F("ddist_2u2", "2U2 Plane Drift Distance", 100, -0.05, 0.55);
   TH1F *ddist_2u1 = new TH1F("ddist_2u1", "2U1 Plane Drift Distance", 100, -0.05, 0.55);

   //Plane Drift Times
   TH1F *dtime_1u1 = new TH1F("dtime_1u1", "1U1 Plane Drift Time", 400, -50, 350);
   TH1F *dtime_1u2 = new TH1F("dtime_1u1", "1U2 Plane Drift Time", 400, -50, 350);
   TH1F *dtime_1x1 = new TH1F("dtime_1x1", "1X1 Plane Drift Time", 400, -50, 350);
   TH1F *dtime_1x2 = new TH1F("dtime_1x2", "1X2 Plane Drift Time", 400, -50, 350);
   TH1F *dtime_1v1 = new TH1F("dtime_1v1", "1V1 Plane Drift Time", 400, -50, 350);
   TH1F *dtime_1v2 = new TH1F("dtime_1v2", "1V2 Plane Drift Time", 400, -50, 350);

   TH1F *dtime_2u1 = new TH1F("dtime_2u1", "2U1 Plane Drift Time", 400, -50, 350);
   TH1F *dtime_2u2 = new TH1F("dtime_2u1", "2U2 Plane Drift Time", 400, -50, 350);
   TH1F *dtime_2x1 = new TH1F("dtime_2x1", "2X1 Plane Drift Time", 400, -50, 350);
   TH1F *dtime_2x2 = new TH1F("dtime_2x2", "2X2 Plane Drift Time", 400, -50, 350);
   TH1F *dtime_2v1 = new TH1F("dtime_2v1", "2V1 Plane Drift Time", 400, -50, 350);
   TH1F *dtime_2v2 = new TH1F("dtime_2v2", "2V2 Plane Drift Time", 400, -50, 350);


   //Plane Drift Residuals
   TH1F *res_1u1 = new TH1F("res_1u1", "1U1 Plane Residuals", 100, -0.1, 0.1);
   TH1F *res_1u2 = new TH1F("res_1u1", "1U2 Plane Residuals", 100, -0.1, 0.1);
   TH1F *res_1x1 = new TH1F("res_1x1", "1X1 Plane Residuals", 100, -0.1, 0.1);
   TH1F *res_1x2 = new TH1F("res_1x2", "1X2 Plane Residuals", 100, -0.1, 0.1);
   TH1F *res_1v1 = new TH1F("res_1v1", "1V1 Plane Residuals", 100, -0.1, 0.1);
   TH1F *res_1v2 = new TH1F("res_1v2", "1V2 Plane Residuals", 100, -0.1, 0.1);

   TH1F *res_2u1 = new TH1F("res_2u1", "2U1 Plane Residuals", 100, -0.1, 0.1);
   TH1F *res_2u2 = new TH1F("res_2u1", "2U2 Plane Residuals", 100, -0.1, 0.1);
   TH1F *res_2x1 = new TH1F("res_2x1", "2X1 Plane Residuals", 100, -0.1, 0.1);
   TH1F *res_2x2 = new TH1F("res_2x2", "2X2 Plane Residuals", 100, -0.1, 0.1);
   TH1F *res_2v1 = new TH1F("res_2v1", "2V1 Plane Residuals", 100, -0.1, 0.1);
   TH1F *res_2v2 = new TH1F("res_2v2", "2V2 Plane Residuals", 100, -0.1, 0.1);


   TH2F *dt_v_wire_1u1 = new TH2F("dt_v_wire_1u1","1U1 Plane Drift Time vs. Wire", 96, -0.5, 95.5, 400, -50, 350);
   

   T->Draw("H.dc.1u1.dist>>ddist_1u1");
   T->Draw("H.dc.1u2.dist>>ddist_1u2");
   T->Draw("H.dc.1x1.dist>>ddist_1x1");
   T->Draw("H.dc.1x2.dist>>ddist_1x2");
   T->Draw("H.dc.1v1.dist>>ddist_1v1");
   T->Draw("H.dc.1v2.dist>>ddist_1v2");
 
   T->Draw("H.dc.2u1.dist>>ddist_2u1");
   T->Draw("H.dc.2u2.dist>>ddist_2u2");
   T->Draw("H.dc.2x1.dist>>ddist_2x1");
   T->Draw("H.dc.2x2.dist>>ddist_2x2");
   T->Draw("H.dc.2v1.dist>>ddist_2v1");
   T->Draw("H.dc.2v1.dist>>ddist_2v2");
   
   //HMS Chamber 1 Drift Distance vs. WireNumber 
   T->Draw("H.dc.1u1.time:H.dc.1u1.wirenum>>dt_v_wire_1u1", "", "colz");
   //T->Draw("H.dc.1u2.time:H.dc.1u2.wirenum>>(96, 0, 96, 400, -50, 350)", "", "colz");
   //T->Draw("H.dc.1x1.time:H.dc.1x1.wirenum>>(102, 0, 102, 400, -50, 350)", "", "colz");
   //T->Draw("H.dc.1x2.time:H.dc.1x2.wirenum>>(102, 0, 102, 400, -50, 350)", "", "colz");   
   //T->Draw("H.dc.1v1.time:H.dc.1v1.wirenum>>(96, 0, 96, 400, -50, 350)", "", "colz");   
   //T->Draw("H.dc.1v2.time:H.dc.1v2.wirenum>>(96, 0, 96, 400, -50, 350)", "", "colz");   
   //T->Draw("H.dc.2u1.time:H.dc.2u1.wirenum>>(96, 0, 96, 400, -50, 350)", "", "colz");   
   //T->Draw("H.dc.2u2.time:H.dc.2u2.wirenum>>(96, 0, 96, 400, -50, 350)", "", "colz");   
   //T->Draw("H.dc.2x1.time:H.dc.2x1.wirenum>>(102, 0, 102, 400, -50, 350)", "", "colz");   
   //T->Draw("H.dc.2x2.time:H.dc.2x2.wirenum>>(102, 0, 102, 400, -50, 350)", "", "colz");   
   //T->Draw("H.dc.2v1.time:H.dc.2v1.wirenum>>(96, 0, 96, 400, -50, 350)", "", "colz");
   //T->Draw("H.dc.2v2.time:H.dc.2v2.wirenum>>(96, 0, 96, 400, -50, 350)", "", "colz");
   


   outfile->Write();

}
