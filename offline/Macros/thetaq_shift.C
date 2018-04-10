//Calculate the shift in theta_q from the change in shms momentum

void thetaq_shift(double data_kf)
{

  double dtr = TMath::Pi() / 180.;

  double data_q, simc_q;
  double data_q2, simc_q2;
  double data_ki, simc_ki;
  double simc_kf;
  double data_th_e, simc_th_e;
  double data_th_q, simc_th_q;

  //Known Quantities
  data_ki = 10.6;
  simc_ki = 10.6;

  data_th_e = 12.2;  //deg
  simc_th_e = 12.169;   //deg
  
  simc_kf = 8.5695;
  
  data_q2 = data_ki*data_ki + data_kf*data_kf - 2.*data_ki*data_kf*cos(data_th_e*dtr);
  simc_q2 = simc_ki*simc_ki + simc_kf*simc_kf - 2.*simc_ki*simc_kf*cos(simc_th_e*dtr);
  
  data_th_q = acos( (data_ki - (data_kf*cos(data_th_e*dtr) ) ) / sqrt(data_q2)  );

  simc_th_q = acos( (simc_ki - (simc_kf*cos(simc_th_e*dtr) ) ) / sqrt(simc_q2)  );

  double diff_thq = data_th_q/dtr - simc_th_q/dtr;

  cout << "*****************" << endl;
  cout << "data_q2: " << data_q2 << endl;
  cout << "simc_q2: " << simc_q2 << endl;
  cout << "*****************" << endl;

  cout << "" << endl;
  cout << "*****************" << endl;
  cout << "data_thq: " << data_q2 << endl;
  cout << "simc_thq: " << simc_q2 << endl;
  cout << "diff_thq: " << diff_thq << endl;
  cout << "*****************" << endl;

}
