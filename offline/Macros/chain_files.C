void chain_files()
{

  TString file_path =  "../../../ROOTfiles/";
 
  TChain ch("T");

  for (int run = 3341; run <= 3356; run++)
    {
      TString file_name = Form("coin_replay_production_%d_-1.root", run);                       
      ch.Add(file_path + file_name);
      cout << "chaining " << file_name << endl;
    }
  
  ch.Merge("~/cyero/hallc_replay/ROOTfiles/Pm580round2.root");

}
