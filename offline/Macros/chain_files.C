void chain_files()
{
//pm = 580: 3290-3305                 
//pm = 750: 3306-3340
  TString file_path =  "../../../ROOTfiles/";
 
  TChain ch("T");

  for (int run = 3290; run <= 3305; run++)
    {
	if(run==3291 || run==3303 || run==3304) {continue;}
      TString file_name = Form("coin_replay_production_%d_-1.root", run);                       
      ch.Add(file_path + file_name);
      cout << "chaining " << file_name << endl;
    }
  
  ch.Merge("~/work_dir/hallc_replay/ROOTfiles/Pm580set2.root");

}
