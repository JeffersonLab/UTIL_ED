#define NPLANES 12

void dc_calib_draw()
{

  gROOT->SetBatch(1);


  TString file = "./ROOTfiles/shms_replay_production_all_1791_dccalib_ndata1cut.root"; 
  TFile *data_file = new TFile(file, "READ"); 
  TTree *T = (TTree*)data_file->Get("T");

  //Create output root file
  TFile *outfile = new TFile("dc_results.root", "recreate");

  string spec;
  string spec_name;

  //Create Histogram Arrays
  TH1F *ddist[NPLANES];    //drift distance
  TH1F *dtime[NPLANES];    //drift times
  TH1F *res[NPLANES];     //residuals
  TH2F *res_vs_wire[NPLANES];   //residuals vs. wirenumber


  //spec = "H";
  spec = "P";
  
  if (spec=="H")
    {
      spec_name = "HMS ";
      //HMS
      //plane[NPLANES]={"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
      //nwires[NPLANES] = {96, 96, 102, 102, 96, 96, 96, 96, 102, 102, 96, 96};
    }

  else if (spec=="P")
    {

    
      //Define TCuts
      TCut dc_hit;
      TCut dc_time;

      spec_name = "SHMS ";
      //SHMS
      string plane[NPLANES]={"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2v2", "2v1", "2x2", "2x1", "2u2", "2u1"};
      Int_t nwires[NPLANES] = {107, 107, 79, 79, 107, 107, 107, 107, 79, 79, 107, 107};
    
      Double_t nplanes[NPLANES] = {1,2,3,4,5,6,7,8,9,10,11,12};

      //Define Fit Functions
      TF1 *fit_line;
      TF1 *fit_gaus;

      //Define Residuals mean/st. dev
      Double_t mean, std;
      Double_t sigma[NPLANES];   //array to store fit param sigma (residuals)
      Double_t sigma_err[NPLANES];

      //Loop over Planes
      for (int ip = 0; ip < NPLANES; ip++)
	{
	  
	  gStyle->SetOptFit();
	  
	  //Define Cuts to be applied
	  dc_hit = Form("P.dc.%s.nhit==1", plane[ip].c_str());
	  dc_time = Form("P.dc.%s.time>0", plane[ip].c_str());

	  //Draw Drift Distance
	  ddist[ip] = new TH1F(Form("ddist_%s", plane[ip].c_str()), Form("Plane %s Drift Distance", plane[ip].c_str()), 100, -0.05, 0.55);
	  T->Draw(Form("P.dc.%s.dist>>ddist_%s", plane[ip].c_str(), plane[ip].c_str() ), dc_hit&&dc_time);
	  
	  //Fit Drift Distance
	  fit_line = new TF1("fit_line", "pol1", 0.01, 0.495);
	  ddist[ip]->Fit("fit_line", "R");
	    
	  	  
	  //Residuals
	  res[ip] = new TH1F(Form("res_%s", plane[ip].c_str()), Form("Plane %s Residuals", plane[ip].c_str()), 100, -0.1, 0.1);
	  T->Draw(Form("P.dc.residual[%d]>>res_%s", ip, plane[ip].c_str()), dc_hit&&dc_time);
	 
	  //Fit Residuals
	  //Get Mean/Standard deviation from histo
	  mean = res[ip]->GetMean();
	  std = res[ip]->GetStdDev();
	  
	  fit_gaus = new TF1("fit_gaus", "gaus", mean-std, mean+std);
	  res[ip]->Fit("fit_gaus", "R");
	  

	  sigma[ip] = fit_gaus->GetParameter(2);
	  sigma_err[ip] = fit_gaus->GetParError(2);

	  res_vs_wire[ip] = new TH2F(Form("%s_res_vs_wire", plane[ip].c_str()), Form("%s Residuals vs. Wire", plane[ip].c_str()), nwires[ip], 0, nwires[ip],  100, -0.5, 0.5);
	  T->Draw(Form("P.dc.residual[%d]:P.dc.%s.wirenum>>%s_res_vs_wire", ip, plane[ip].c_str(), plane[ip].c_str()), dc_hit&&dc_time, "colz");


	}

      //Plot TGraph of Residuals
      	TCanvas *gr_canv = new TCanvas("gr1", "", 2000, 500);
	gr_canv->SetGrid();

	TGraphErrors *gr = new TGraphErrors(12, nplanes, sigma, 0, sigma_err);
      	
	gr->SetTitle("Residuals vs. SHMS DC Planes");
	gr->SetMarkerStyle(20);
	gr->SetMarkerColor(1);
	
	gr->GetXaxis()->SetLimits(0., NPLANES+0.5);
	gr->GetXaxis()->SetTitle("Plane Number");
	gr->GetXaxis()->CenterTitle();
	gr->GetYaxis()->SetTitle("Residuals (cm)");
	gr->GetYaxis()->CenterTitle();
	//gr->GetYaxis()->SetRangeUser(-50.0, 50.0);
	
	gr->Draw("AP");
	gr_canv->Update();
	gr_canv->Write("FittedRes_v_Plane");   //write to a root file

	
    } //end else if statement for "P"
  




  outfile->Write();

  /*

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
  */
   

   /*
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
   */
   /*

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
   */

   //HMS Chamber 1 Drift Distance vs. WireNumber 
   // T->Draw("H.dc.1u1.time:H.dc.1u1.wirenum>>dt_v_wire_1u1", "", "colz");
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
   



}
