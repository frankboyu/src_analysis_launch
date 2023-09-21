#!/bin/bash

VERSION=$1

if [ ${VERSION} == "test" ]
then
    rm -r /volatile/halld/home/boyu/src_analysis_launch/launch
    rm -r /volatile/halld/home/boyu/src_analysis_launch/merge_trees
    mkdir /volatile/halld/home/boyu/src_analysis_launch/launch
    mkdir /volatile/halld/home/boyu/src_analysis_launch/merge_trees
    
    swif2 cancel -delete -workflow src_analysis_launch
    swif2 cancel -delete -workflow src_analysis_launch_merge
    swif2 create -workflow src_analysis_launch
    swif2 create -workflow src_analysis_launch_merge    
    
else    
    mkdir /cache/halld/RunPeriod-2021-11/analysis/ver${VERSION}
    
    mkdir /volatile/halld/analysis/RunPeriod-2021-11/ver${VERSION}
    mkdir /volatile/halld/analysis/RunPeriod-2021-11/ver${VERSION}/batch01
    mkdir /volatile/halld/analysis/RunPeriod-2021-11/ver${VERSION}/batch02
    mkdir /volatile/halld/analysis/RunPeriod-2021-11/ver${VERSION}/batch03
    
    mkdir /work/halld2/analysis/RunPeriod-2021-11/ver${VERSION}
    mkdir /work/halld2/analysis/RunPeriod-2021-11/ver${VERSION}/batch01    
    mkdir /work/halld2/analysis/RunPeriod-2021-11/ver${VERSION}/batch02
    mkdir /work/halld2/analysis/RunPeriod-2021-11/ver${VERSION}/batch03
    
    swif2 create -workflow analysis_2021-11_ver${VERSION}_batch01
    swif2 create -workflow analysis_2021-11_ver${VERSION}_batch02
    swif2 create -workflow analysis_2021-11_ver${VERSION}_batch03
    swif2 create -workflow analysis_2021-11_ver${VERSION}_batch01_merge   
    swif2 create -workflow analysis_2021-11_ver${VERSION}_batch02_merge   
    swif2 create -workflow analysis_2021-11_ver${VERSION}_batch03_merge   
fi