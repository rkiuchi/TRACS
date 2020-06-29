#!/usr/bin/env bash

# Main driver to submit jobs 
# Created [2020-06-29 Mon 17:00]

usage() {
	printf "NAME\n\tsubmit.sh - Main driver to submit jobs\n"
	printf "\nSYNOPSIS\n"
	printf "\n\t%-5s\n" "./submit.sh [OPTION]" 
	printf "\n\n" 
	printf "\nOPTIONS\n" 
    printf "\n\t%-9s  %-40s"  "1"      "run TRACS Simulation"
    printf "\n\t%-9s  %-40s"  "2"      "convert raw measurement file"    
    printf "\n\t%-9s  %-40s"  "3"      "run TRACS Simulation and Fitting"
    printf "\n\n"
	printf "\nDATE\n"
	printf "\n\t%-5s\n" "June 2020" 
}

usage_1() {
        printf "\n\t%-9s  %-40s"  "1.1"      "  "
}

usage_2() {
        printf "\n\t%-9s  %-40s"  "2.1"      "  "
}

usage_3() {
        printf "\n\t%-9s  %-40s"  "3.1"      "  "
}

usage_1_1() { 
	printf "\n\t%-9s  %-40s"  "1.1"      "[run TRACS Simulation]" 
	printf "\n\t%-9s  %-40s"  "1.1.1"    "Start run" 
	printf "\n\t%-9s  %-40s"  "1.1.2"    "Make plots" 
}

usage_2_1() {
        printf "\n\t%-9s  %-40s"  "2.1"      "[convert raw measurement file]"
        printf "\n\t%-9s  %-40s"  "2.1.1"    "Convert the measurement file"
        printf "\n\t%-9s  %-40s"  "2.1.2"    "Make plots"
}

usage_3_1() {
        printf "\n\t%-9s  %-40s"  "3.1"      "[run TRACS Simulation and Fitting]"
        printf "\n\t%-9s  %-40s"  "3.1.1"    "Start simulation and fitting"
        printf "\n\t%-9s  %-40s"  "3.1.2"    "Make plots"
}


if [[ $# -eq 0 ]]; then
    usage
    echo "Please enter your option: "
    read option
else
    option=$1    
fi

    # --------------------------------------------------------------------------
    #  1.1 run TRACS Simulation (only)
    # --------------------------------------------------------------------------

sub_1_1(){
case $option in 

    1.1) echo "Running TRACS Simulation..."
         ;;

    1.1.1) echo "Start run..."
           cd  ./run/template.20200629/

           # > DoTracsOnly [number of Threads] [configration file name == "MyConfigTRACS"]
           ../../myApp/DoTracsOnly  1  MyConfigTRACS
           ;;

    1.1.2) echo "Make plots..."
           # reserved ... 
           ;;

    esac
}


    # --------------------------------------------------------------------------
    #  2.1 Convert a measurement data file to the format which TRACS handls
    # --------------------------------------------------------------------------

sub_2_1(){
case $option in

    2.1) echo "Running TRACS Simulation for Fitting process..."
         ;;

    2.1.1) echo "Convert the measurement data to the format which TRACS handles..."
           cd  ./run/template.20200629/

           # > Edge_tree [inpur measurement file name]
           ../../myApp/Edge_tree   2019_09_28_15_28_11_HPK-EPI-W13-200-DS-SE2-01.txt
           ;;

    2.1.2) echo "Make plots..."
           cd  ./run/template.20200629/

           # Event No.:120 is arbitrarily chosen and written in the macro script
           root -l -q  'plot_data.c("2019_09_28_15_28_11_HPK-EPI-W13-200-DS-SE2-01.txt.root")'
           ;;
  esac
}


    # --------------------------------------------------------------------------
    #  3.1 run TRACS Simulation and Fitting (to the measument data)
    # --------------------------------------------------------------------------

sub_3_1(){
case $option in

    3.1) echo "Running TRACS Simulation for Fitting process..."
         ;;

    3.1.1) echo "Start running the fitting procedure..."
           cd  ./run/template.20200629/

           mkdir -p ./out/

           # In the following, event No.12 of the measured data is arbitrarily selected. Note that, TRACS simulation can also contain multiple events (=scan)
           # but current setting (MyConfigTRACS) is for one scan point. If the simulation contains multiple events,
           # and try to fit all of those with the measurement,  the source code has to be updated.
           
           # >MfgTRACSFit  [number of Threads]  [input measurement file(converted)]  [configration file name == "MyConfigTRACS"]  [optional condition]           
           ../../myApp/MfgTRACSFit   1   2019_09_28_15_28_11_HPK-EPI-W13-200-DS-SE2-01.txt.root  MyConfigTRACS  event==120
           ;;

    3.1.2) echo "Make plots..."
           # Very temporal !!! not studied well.s
           cd  ./run/template.20200629/
           
           root -l -q plot_sim_data.c           
           ;;
    
  esac

}




sub_1(){
case $option in 
# sample: 1.1 is print detail information about each step and then you can run the step you want.
#         1.1.* is directly running the step. 

    1.1) echo "  "
        usage_1_1
        echo "Please enter your option: " 
        read option 
        sub_1_1 option 
        ;;
    1.1.*) echo "  "
        sub_1_1 option
        ;;       
esac
}

sub_2(){
case $option in

    2.1) echo "  "
        usage_2_1
        echo "Please enter your option: " 
        read option
        sub_2_1 option
        ;;
    2.1.*) echo "  "
        sub_2_1 option
        ;;
esac
}

sub_3(){
case $option in

    3.1) echo "  "
        usage_3_1
        echo "Please enter your option: " 
        read option
        sub_3_1 option
        ;;
    3.1.*) echo "  "
        sub_3_1 option
        ;;
esac
}


case $option in
    1) echo "run TRACS Simulation"
       usage_1
       echo "Please enter your option: "
       read option
       sub_1 option
        ;;
    1.*) echo "run TRACS Simulation"
       sub_1 option
        ;;

    2) echo "convert measurement data file"
       usage_2
       echo "Please enter your option: "
       read option
       sub_2 option
        ;;
    2.*) echo "convert measurement data file"
       sub_2 option
       ;;

    3) echo "run TRACS Simulation and Fitting"
       usage_3
       echo "Please enter your option: "
       read option
       sub_3 option
        ;;
    3.*) echo "run TRACS Simulation and Fitting"
       sub_3 option
        ;;    

esac
