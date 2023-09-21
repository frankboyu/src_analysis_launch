#!/bin/bash

VERSION=$1
BATCH=$2

source env.sh

if   [ ${VERSION} == "test" ]
then
    if   [ ${BATCH} == "2H"  ]
    then
        python launch.py jobs_analysis_2021-11_test.cfg 90213 90213  # diamond,   164 evio files
        python launch.py jobs_analysis_2021-11_test.cfg 90578 90578  # amorphous, 148 evio files
        swif2 run -workflow src_analysis_launch -maxconcurrent 1000
    elif [ ${BATCH} == "4He" ]
    then
        python launch.py jobs_analysis_2021-11_test.cfg 90061 90061  # diamond,   172 evio files
        python launch.py jobs_analysis_2021-11_test.cfg 90062 90062  # amorphous, 184 evio files
        swif2 run -workflow src_analysis_launch -maxconcurrent 1000
    elif [ ${BATCH} == "12C" ]
    then
        python launch.py jobs_analysis_2021-11_test.cfg 90290 90290  # diamond,   184 evio files
        python launch.py jobs_analysis_2021-11_test.cfg 90288 90288  # amorphous, 196 evio files
        swif2 run -workflow src_analysis_launch -maxconcurrent 1000
    fi
else    
    python launch.py jobs_analysis_2021-11_ver${VERSION}_batch${BATCH}.cfg 90001 90662
    swif2 run -workflow analysis_2021-11_ver${VERSION}_batch${BATCH} -maxconcurrent 1000    
fi    