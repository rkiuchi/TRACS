# TRACS

### Note

### 1. Install
user@mylocal:---$ ssh -X cepcvtx.ihep.ac.cn  
  
user@cepcvtx:~$ cd {some directory under which you want to setup the code = Somewhere}  
user@cepcvtx:Somewhere$ git clone https://github.com/rkiuchi/TRACS  
user@cepcvtx:Somewhere$ cd TRACS   

### 2. Setup
user@cepcvtx:Somewhere/TRACS$ ./setup.sh

### 3. Build Code
user@cepcvtx:Somewhere/TRACS$ make

### 4. Run Template 
user@cepcvtx:Somewhere/TRACS$ cd ./run/template.IR_Bottom.20190901/   
user@cepcvtx:Somewhere/TRACS$ ../../myApp/DoTracsOnly 1 MyConfigTRACS  

### 4b. (Optional) -- after successfully run "DoTracsOnly" .   
user@cepcvtx:Somewhere/TRACS$ ../../myApp/Edge_tree   NOirrad_dt0ps_4pF_tNOtrappingns_dz5um_dy5dV20V_0nns_bottom_0_rc.hetct  
  
#### The file name "NOirrad...." differs reflecting the setting parameters in "MyConfigTRACS"   

user@cepcvtx:Somewhere/TRACS$ root NOirrad_dt0ps_4pF_tNOtrappingns_dz5um_dy5dV20V_0nns_bottom_0_rc.hetct.root  
  
root> .x loadlib.c  
root> edge->StartViewer();  

or   

root> TBrowser a;  


### 5. Config File
  
### ChangeLog (from the original repo.)

