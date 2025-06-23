#!/bin/bash

MODE=$1
TARGET=$2

source /group/halld/Software/build_scripts/gluex_env_boot_jlab.sh
gxenv /work/halld2/home/boyu/src_software_builds/halld_versions_srcct/analysis-2021_11-ver11.xml

if   [ "${MODE}" == "get" ]
then
    if   [ "${TARGET}" == "2H"  ]
    then
        jcache get /mss/halld/RunPeriod-2021-11/recon/ver01/REST/090213/dana_rest_090213_000.hddm
    elif [ "${TARGET}" == "4He" ]
    then
        jcache get /mss/halld/RunPeriod-2021-11/recon/ver01/REST/090061/dana_rest_090061_000.hddm
    elif [ "${TARGET}" == "12C" ]
    then
        jcache get /mss/halld/RunPeriod-2021-11/recon/ver01/REST/090290/dana_rest_090290_000.hddm
    fi
elif [ "${MODE}" == "check" ]
then
    if   [ "${TARGET}" == "2H"  ]
    then
        ls -lh /cache/halld/RunPeriod-2021-11/recon/ver01/REST/090213
    elif [ "${TARGET}" == "4He" ]
    then
        ls -lh /cache/halld/RunPeriod-2021-11/recon/ver01/REST/090061
    elif [ "${TARGET}" == "12C" ]
    then
        ls -lh /cache/halld/RunPeriod-2021-11/recon/ver01/REST/090290
    fi
elif [ "${MODE}" == "run" ]
then
    if   [ "${TARGET}" == "2H"  ]
    then
        hd_root --loadconfigs test.cfg /cache/halld/RunPeriod-2021-11/recon/ver01/REST/090213/dana_rest_090213_000.hddm
    elif [ "${TARGET}" == "4He" ]
    then
        hd_root --loadconfigs test.cfg /cache/halld/RunPeriod-2021-11/recon/ver01/REST/090061/dana_rest_090061_000.hddm
    elif [ "${TARGET}" == "12C" ]
    then
        hd_root --loadconfigs test.cfg /cache/halld/RunPeriod-2021-11/recon/ver01/REST/090290/dana_rest_090290_000.hddm
    fi
elif [ "${MODE}" == "clear" ]
then
    rm *.root
fi