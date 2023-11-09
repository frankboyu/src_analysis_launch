## src_analysis_launch

Scripts to run data skim for the SRC/CT experiment

JLab: /work/halld2/home/boyu/src_analysis_launch

GitHub: https://github.com/frankboyu/src_analysis_launch

### Usage

1.  Test the reactions with one REST file

    Go to the test folder. Edit the jana config file test.cfg with the reactions to test
    
    Then run the test using run.sh
    
    `sh run.sh MODE TARGET`
    
    where MODE can be one of:
    
    get: fetch one REST file from the tape to cache
    
    check: check if the file fetching is done
    
    run: run the reaction filter with the fetched REST file
    
    clear: delete the output root files
    
    and TARGET can be one of 2H, 4He or 12C
    
    Based on the output files and sizes. Estimate the total disk usage for the later steps

2.  Start the launch

    Go to the launch folder. Edit the jana config file with the reactions to run and jobs config file with the job resources and version control
    
    To create the directories and swif2 workflows used by the launch:
    
    `sh run_initialze.sh VERSION`
    
    where VERSION can be one of:
    
    test: use the test configs and personal directories to do some quick tests
    
    01, 02, 03...: the version of the official launch, have to be two digits

    To launch the jobs:
    
    `sh run_launch.sh VERSION BATCH`
    
    BATCH can be 2H, 4He, 12C if VERSION is test. Or 01, 02... if it's the official launch
    
3.  Start the merge

    Go to the merge_trees folder. Edit cron_exec.sh with the currently running VERSION and the jobs config file with the job resources and version control

    If startup_C.so is missing, recompile it using:

    `sh run_compile.sh`

    Then edit line 54 in script.sh to the newly compiled one
    
    To set up the merge:
    
    `sh run_merge.sh`
    
    crontab will run the merge scripts every 15 mins at back stage, which will check the jobs in the launch workflow and submit a new job to merge the files if all jobs in one run have finished.
    
    Check merge_progress.log for the newest updates
    
### Notes

1.  For a list of reactions in all previous analysis launches and more details: https://halldweb.jlab.org/wiki/index.php/SRC/CT_Physics_Analysis

2.  The original version of the code: https://github.com/JeffersonLab/hd_utilities/tree/master/launch_scripts