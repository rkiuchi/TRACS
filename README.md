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

### 4a. (Optional) Output root files. -- after successfully run "DoTracsOnly"  . 

You can check several distribution in the ROOT files. 
Notice that those are bi-products during development/debugging procedures, 
thus could be changed in future. 

user@cepcvtx:Somewhere/TRACS$ root wf120V  
root>  h_w_u->Draw();          // Weighting potential  
root>  h_w_f_grad->Draw();     // Weighting field  
root>  h_d_f_grad->Draw();     // E-field  
root>  h_d_f_grad_Y->Draw();   // E-field along with Z-axis  

### 4b. (Optional) "Edge_tree" . -- after successfully run "DoTracsOnly" .   
user@cepcvtx:Somewhere/TRACS$ ../../myApp/Edge_tree NOirrad_dt0ps_4pF_tNOtrappingns_dz5um_dy5dV20V_0nns_bottom_0_rc.hetct  
user@cepcvtx:Somewhere/TRACS$ root NOirrad_dt0ps_4pF_tNOtrappingns_dz5um_dy5dV20V_0nns_bottom_0_rc.hetct.root  
  
root> .x loadlib.c  
root> edge->StartViewer();  
or   
root> TBrowser a;  


- ###### The file name "NOirrad...." would be different, depending on the setting parameters in "MyConfigTRACS"   
- ###### The functionality/usage is not fully tested and that's why it is marked as "Optional" now. (09/02/2019)

### 5. Config File
Here, newly introduced parameters in the config file ("MyConfigTRACS" in the template) are described.  

- ###### SetAvalanche = yes   # yes: set this doping profile.  no: turn-off, even though parameters are given bellow.  

The shape of "Gain Layer" is now assumed as a simple Gaussian for which we need to specify some parameters:  
- ###### DopingProfile_PeakHeight   = 3.0e16       # unit in  cm^-3  
- ###### DopingProfile_PeakPosition = 1.5          # Z (vertical) position from the top. unit in micron-meter   
- ###### DopingProfile_GaussSigma  = 0.3           # unit in micron-meter  

The (carrier loop)calculation time scales with the number of carriers, including the secondary generated ones due to the Avalanche effect.
Thus, stopping the loop calculation iteration, if the number of generated carriers reaches or exceeds the ratio bellow. The ratio
is defined as the number between the total number of carriers generated and the number of initial carriers read from a carrier file.  
- ###### MaxMultiplicationRatio = 10.0         # no unit.   

In addion to above, the effective doping level in the bulk except the "gain layer" is also important.
This is determined from the detector thickness and the full depletion voltage, which is already used in the original TRACS.
Therefore, you need to set the full depletion voltage correctly. ( In fact, the impact ionization effect happens only 
at the high doping area, and less effect if one sets the full depletion voltage == nominal doping level wrongly )   
One of point is that this full depletion voltage is that one without the "gain layer", to estimate normal doping level correctly.
- ###### DepletionVoltage = 10.0 # in volts   


### ChangeLog (from the original repo.)

