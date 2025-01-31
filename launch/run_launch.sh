#!/bin/bash

VERSION=$1
BATCH=$2

source /group/halld/Software/build_scripts/gluex_env_boot_jlab.sh
gxenv $HALLD_VERSIONS/version.xml

if   [ ${VERSION} == "test" ]
then
    # Initialization
    rm -r /volatile/halld/home/boyu/src_analysis_launch/launch
    rm -r /volatile/halld/home/boyu/src_analysis_launch/merge_trees
    mkdir /volatile/halld/home/boyu/src_analysis_launch/launch
    mkdir /volatile/halld/home/boyu/src_analysis_launch/merge_trees

    swif2 cancel -delete -workflow analysis_2021-11_test
    swif2 cancel -delete -workflow analysis_2021-11_test_merge
    swif2 create -workflow analysis_2021-11_test
    swif2 create -workflow analysis_2021-11_test_merge

    # Launch the jobs
    if   [ ${BATCH} == "2H"  ]
    then
        python launch.py configs/jobs_analysis/jobs_analysis_2021-11_test.cfg 90213 90213  # diamond,   164 evio files
        python launch.py configs/jobs_analysis/jobs_analysis_2021-11_test.cfg 90578 90578  # amorphous, 148 evio files
        swif2 run -workflow analysis_2021-11_test
    elif [ ${BATCH} == "4He" ]
    then
        python launch.py configs/jobs_analysis/jobs_analysis_2021-11_test.cfg 90061 90061  # diamond,   172 evio files
        python launch.py configs/jobs_analysis/jobs_analysis_2021-11_test.cfg 90062 90062  # amorphous, 184 evio files
        swif2 run -workflow analysis_2021-11_test
    elif [ ${BATCH} == "12C" ]
    then
        python launch.py configs/jobs_analysis/jobs_analysis_2021-11_test.cfg 90290 90290  # diamond,   184 evio files
        python launch.py configs/jobs_analysis/jobs_analysis_2021-11_test.cfg 90288 90288  # amorphous, 196 evio files
        swif2 run -workflow analysis_2021-11_test
    fi
else
    # Initialization
    if [ ${BATCH} == "01" ]
    then
        mkdir /volatile/halld/analysis/RunPeriod-2021-11/ver${VERSION}
        mkdir /volatile/halld/analysis/RunPeriod-2021-11/ver${VERSION}/batch01
        mkdir /volatile/halld/analysis/RunPeriod-2021-11/ver${VERSION}/batch02
        mkdir /volatile/halld/analysis/RunPeriod-2021-11/ver${VERSION}/batch03

        mkdir /farm_out/boyu/src_analysis_launch/launch/ver${VERSION}
        mkdir /farm_out/boyu/src_analysis_launch/launch/ver${VERSION}/batch01
        mkdir /farm_out/boyu/src_analysis_launch/launch/ver${VERSION}/batch02
        mkdir /farm_out/boyu/src_analysis_launch/launch/ver${VERSION}/batch03

        mkdir /farm_out/boyu/src_analysis_launch/merge_trees/ver${VERSION}
        mkdir /farm_out/boyu/src_analysis_launch/merge_trees/ver${VERSION}/batch01
        mkdir /farm_out/boyu/src_analysis_launch/merge_trees/ver${VERSION}/batch02
        mkdir /farm_out/boyu/src_analysis_launch/merge_trees/ver${VERSION}/batch03

        swif2 create -workflow analysis_2021-11_ver${VERSION}_batch01
        swif2 create -workflow analysis_2021-11_ver${VERSION}_batch02
        swif2 create -workflow analysis_2021-11_ver${VERSION}_batch03

        swif2 create -workflow analysis_2021-11_ver${VERSION}_batch01_merge
        swif2 create -workflow analysis_2021-11_ver${VERSION}_batch02_merge
        swif2 create -workflow analysis_2021-11_ver${VERSION}_batch03_merge
    fi

    # Launch the jobs
    python launch.py configs/jobs_analysis/jobs_analysis_2021-11_ver${VERSION}_batch${BATCH}.cfg 90001 90662
    swif2 run -workflow analysis_2021-11_ver${VERSION}_batch${BATCH} -maxconcurrent 1500
fi
