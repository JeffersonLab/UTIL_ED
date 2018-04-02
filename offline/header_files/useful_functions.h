#ifndef USEFUL_FUNCS
#define USEFUL_FUNCS

//Header file containing definitions of useful functions to use.


/*
  Funtion1: 
  Description: Searched for specified variable, and returns either its
  value or error. The line format for this function to work is restricted to
 --->  variable_name : value +- error 
*/

Double_t getVal(TString report_file, string variable="", string return_value="")
{

  ifstream myfile;
  myfile.open(report_file);

  string line;
  Int_t counter = 0;
  
  string del1 = ":";
  string del2 = "+";
  size_t pos1;    //delimiter 1 position
  size_t pos2;    //delimiter 2 position
  
  //line number of desried variable (-1 means no-valid position)
  size_t var_pos;   
 
  //values and error of desired variable
  string val; 
  string val_err;
 
  Double_t value;
  Double_t value_err;
  
  if (report_file=="" || variable=="" || return_value=="")
    {
      cout << "**********************************************" << endl;
      cout << "*** Missing Arguments in Function getVal() ***" << endl;
      cout << "**********************************************" << endl;
      cout << "" << endl;
      cout << "Function Reference:: " << endl;
      cout << "getVal(string report_file, string variable, string return_value)" << endl;
      cout << "" << endl;
      cout << "Function Usage: " << endl;
      cout << "1) <report_file>: Name of the file you wish to open." << endl;
      cout << "2) <variable>: Name of the variable to search in report_file." << endl;
      cout << "3) <return_value>: Enter either, \"val\" or \"err\" to return " << endl;
      cout << "   the value or error of the varibale." << endl;
      cout << "" << endl;
      cout << "Example: " << endl;
      cout << "getVal(\"report.data\", \"SHMS E SING FID TRACK EFFIC \", \"val\")" << endl;
      cout << "" << endl;
      cout << "**********************************************" << endl;
      

    }
  
  while (getline(myfile, line))
    {
      
      //var_pos value of zero means that it found the line
      var_pos = line.find(variable);
      
      if (var_pos == 0)
	{
	  //cout << line << endl;
	  
	  //fing delimiter positions
	  pos1 = line.find(del1);
	  pos2 = line.find(del2);
	  
	  //extract value/err that is between two delimiters
	  val = line.substr(pos1+1, pos2-pos1-1);
	  val_err = line.substr(pos2+2);

   
	}

    }

  value = atof(val.c_str());
  value_err = atof(val_err.c_str());


  //Return value or error, based on user input
  if (return_value=="val")
    {
      return value;
    }
  else if(return_value == "err")
    {
      return value_err;
    }
  

  myfile.close();

} //end getVal() function

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


#endif
