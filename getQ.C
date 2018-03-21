Double_t getQ(string var1, string var2, string var3="" )
{

  //NOTE: var1 --> "HMS" or "SHMS" 
  //var2 --> "charge" or "time"
  //var3 --> if var2="charge", then var3 --> "BCM1", "BCM2", "BCM4A", "BCM4B", "BCM17"

  //gROOT->SetBatch(1);

  TString file_path = "../ROOTfiles/coin_replay_production_1851_-1.root";

  TFile *data_file = new TFile(file_path, "READ");
  //TTree *TSH = (TTree*)data_file->Get("TSH");	\

  
  Double_t time;    //in sec.
  Double_t charge;    //in uC

  /*
  if (var1=="HMS")
    {
      //Get HMS Scaler Tree
      //      TTree *TSH = (TTree*)data_file->Get("TSH");
      
      //Cut is > 5 uA current
      
      if (var2=="charge")
	{
	  //  TTree *TSH = (TTree*)data_file->Get("TSH");                                                                                                                                                                          

	  if (var3=="BCM1") { 

	    //	    TTree *TSH = (TTree*)data_file->Get("TSH");                                                                          
	    charge = TSH->GetMaximum("H.BCM1.scalerChargeCut"); 
	  }
	  
	  else if (var3=="BCM2") { TTree *TSH = (TTree*)data_file->Get("TSH");  charge = TSH->GetMaximum("H.BCM2.scalerChargeCut"); }                                                                              	  
	  else if (var3=="BCM4A") { charge = TSH->GetMaximum("H.BCM4A.scalerChargeCut"); }                                                                            
	  else if (var3=="BCM4B") { charge = TSH->GetMaximum("H.BCM4B.scalerChargeCut"); }                                                                           
	  else if (var3=="BCM17") { charge = TSH->GetMaximum("H.BCM17.scalerChargeCut"); } 
     	
  return charge;
	}
 
      else if (var2=="time")
	{
	  time = TSH->GetMaximum("H.1Mhz.scalerTimeCut");
	  return time;
	}

    }
  */
   if (var1=="SHMS")
    {
      //Get SHMS Scaler Tree                                                                                                           
       TTree *TSP = (TTree*)data_file->Get("TSP");                                                                                 
      
      if (var2=="charge")                                                                                                          
        {                                                                                                                          
	  if (var3=="BCM1") { charge = TSH->GetMaximum("P.BCM1.scalerChargeCut"); }                                               
                                                                                                                                  
          else if (var3=="BCM2") { charge = TSH->GetMaximum("P.BCM2.scalerChargeCut"); }                                          
                                                                                                                                  
          else if (var3=="BCM4A") { charge = TSH->GetMaximum("P.BCM4A.scalerChargeCut"); }                                       
                                                                                                                                  
          else if (var3=="BCM4B") { charge = TSH->GetMaximum("P.BCM4B.scalerChargeCut"); }                                
                                                                                       
          else if (var3=="BCM17") { charge = TSH->GetMaximum("P.BCM17.scalerChargeCut"); }                                                                                                                                                                      
	  return charge;
	}                                                                                                                          
                                                                                                                                   
      else if (var2=="time")                                                                                                       
        {                                                                                                                          
          time = TSH->GetMaximum("P.1Mhz.scalerTimeCut");                                                                          
	  return time;
	}                                                                                                                          
                                                                                                                                   
    }  
       
}


