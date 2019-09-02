# TRACS

### Note

### 1. Install
> ssh -X cepcvtx.ihep.ac.cn  
> cd {some directory under which you want to setup the code}  
> git clone https://github.com/rkiuchi/TRACS  
> cd TRACS   

### 2. Setup
> ./setup.sh

### 3. Build Code
> make

### 4. Run Template 
> cd ./run/template.IR_Bottom.20190901/   
> ../../myApp/DoTracsOnly 1 MyConfigTRACS  

### 4b. (Optional) -- after successfully run "DoTracsOnly" .   
> ../../myApp/Edge_tree   NOirrad_dt0ps_4pF_tNOtrappingns_dz5um_dy5dV20V_0nns_bottom_0_rc.hetct  
  
The file name "NOirrad...." differs reflecting the setting parameters in "MyConfigTRACS"   

user@cepcvtx:Something/TRACS$ root NOirrad_dt0ps_4pF_tNOtrappingns_dz5um_dy5dV20V_0nns_bottom_0_rc.hetct.root  
  
root[]> .x loadlib.c  
root> edge->StartViewer();  

or   

root> TBrowser a;  


### 5. Config File
  
### ChangeLog (from the original repo.)

