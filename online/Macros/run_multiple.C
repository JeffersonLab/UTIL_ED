void run_multiple()
{

  
 
  for (int runNUM = 3306; runNUM<=3340; runNUM++ )
    {
     
      gSystem->Exec(Form("./run_full_deep.sh %d", runNUM));
    
    }

}
