void getQ()
{


  //gROOT->SetBatch(1);

  TString file_path = "../ROOTfiles/coin_replay_production_1851_-1.root";

  TFile *data_file = new TFile(file_path, "READ");

  
  Double_t time;
  Int_t binx;


  //Get HMS Scaler Tree
  TTree *TSH = (TTree*)data_file->Get("TSH");

  TH1F *htime = new TH1F("htime", "", 800, 0, 8000);
  

  htime->SetDefaultBufferSize();

  TCanvas *c1 = new TCanvas();
  TSH->Draw("H.1Mhz.scalerTimeCut>>htime");
  binx = htime->FindLastBinAbove(0);

  time = htime->GetXaxis()->GetBinUpEdge(binx);
  
}
