Double_t getCharge(string spec, string bcm, TString filename)
{
   /*Brief: Get the accumulated charge if beam current was above threhsold (typically > 5 uA)
   */

  /*PARAMETERS: 
    spec --> "HMS" or "SHMS"
    bcm --> "BCM1", "BCM2", "BCM4A", "BCM4B", "BCM17"
    filename --> "/path/to/ROOTfile/file.root"
  */
  
  TFile *data_file = new TFile(filename, "READ");
  Double_t charge;    //in uC

  if (spec=="HMS")
    {

      TTree *TSH = (TTree*)data_file->Get("TSH");		
      
      if (bcm=="BCM1") { charge = TSH->GetMaximum("H.BCM1.scalerChargeCut"); }
      else if (bcm=="BCM2") { charge = TSH->GetMaximum("H.BCM2.scalerChargeCut"); }                                     
      else if (bcm=="BCM4A") { charge = TSH->GetMaximum("H.BCM4A.scalerChargeCut"); }                                       
      else if (bcm=="BCM4B") { charge = TSH->GetMaximum("H.BCM4B.scalerChargeCut"); }    
      else if (bcm=="BCM17") { charge = TSH->GetMaximum("H.BCM17.scalerChargeCut"); }                        
      return charge;
      
    }
	  
  else if (spec=="SHMS")
    {
      
      TTree *TSP = (TTree*)data_file->Get("TSP");		
      
      if (bcm=="BCM1") { charge = TSP->GetMaximum("P.BCM1.scalerChargeCut"); }
      else if (bcm=="BCM2") { charge = TSP->GetMaximum("P.BCM2.scalerChargeCut"); }                                     
      else if (bcm=="BCM4A") { charge = TSP->GetMaximum("P.BCM4A.scalerChargeCut"); }                                       
      else if (bcm=="BCM4B") { charge = TSP->GetMaximum("P.BCM4B.scalerChargeCut"); }    
      else if (bcm=="BCM17") { charge = TSP->GetMaximum("P.BCM17.scalerChargeCut"); }                        
      return charge;
      
    }
}

Double_t get_runtime(string spec, TString filename)
{

  /*Brief: Get the run time (in sec.) if beam current was above threhsold (typically > 5 uA)
   */

  /*PARAMETERS: 
    spec --> "HMS" or "SHMS"
    filename --> "/path/to/ROOTfile/file.root"
  */
  
  TFile *data_file = new TFile(filename, "READ");
  Double_t time;    //in uC

  if (spec=="HMS")
    {
      TTree *TSH = (TTree*)data_file->Get("TSH");		
      time = TSH->GetMaximum("H.1Mhz.scalerTimeCut");                         
      return time;
    }
	  
  else if (spec=="SHMS")
    {
      TTree *TSP = (TTree*)data_file->Get("TSP");		
      time = TSP->GetMaximum("P.1Mhz.scalerTimeCut");
      return time;
    }
}
   

int main()
{
  TString file_path = "../ROOTfiles/coin_replay_production_1851_-1.root";


  cout << get_runtime("HMS", file_path) << endl;
  cout << get_runtime("SHMS", file_path) << endl;

  //append to file
  ofstream outfile;
  outfile.open("test.txt", std::ios_base::app);
  outfile << "Data";
  outfile.close();


  return 0;
}
