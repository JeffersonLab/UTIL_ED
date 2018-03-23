#!/usr/bin/env python
import sys
runNo = sys.argv[1]
evenNo = sys.argv[2]

#Create reduced report output file
out_filename = './UTIL_ED/CHARGE_REPORTS/heep_report_%s.report'% (runNo)

#Read REPORT File Name
report_filename = './REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_%s_%s.report'% (runNo, evenNo)

line_no=0

f = open(report_filename)
fout = open(out_filename,'w')


for line in f:
    data = line.split(':')
    if ('Run #' in data[0])  or ('SHMS BCM4a Beam Cut Charge'in data[0]) or ('SHMS BCM4b Beam Cut Charge'in data[0]) or('ROC2 Pre-Scaled Ps1 ROC2 Computer Live Time' in data[0]) or('E SING FID TRACK EFFIC'in data[0]or('HADRON SING FID TRACK EFFIC'in data[0])):
    
        line_no = line_no+1
        
        if line_no == 5:
            fout.write('SHMS ' + data[0]+ ': '+data[1])

        elif line_no == 6:
            fout.write('')
        elif line_no == 7:
            fout.write('')
        elif line_no == 8:
            fout.write('HMS ' + data[0]+ ': '+ data[1])
        else: 
            fout.write(data[0]+ ': '+ data[1])
        
fout.close()
f.close()



#reopen output file to rename some variables
