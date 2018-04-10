void run_multiple()
{

  
 
  for (int runNUM = 3290; runNUM<=3301; runNUM++ )
    {
     
      gSystem->Exec(Form("./run_full_deep.sh %d", runNUM));
    
    }

}
