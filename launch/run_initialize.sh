#!/bin/bash

VERSION=$1

if [ ${VERSION} == "test" ]
then
    rm -r /volatile/halld/home/boyu/src_analysis_launch/launch
    rm -r /volatile/halld/home/boyu/src_analysis_launch/merge_trees
    mkdir /volatile/halld/home/boyu/src_analysis_launch/launch
    mkdir /volatile/halld/home/boyu/src_analysis_launch/merge_trees
    
    rm -r /farm_out/boyu/src_analysis_launch/launch/test
    rm -r /farm_out/boyu/src_analysis_launch/merge_trees/test
    mkdir /farm_out/boyu/src_analysis_launch/launch/test
    mkdir /farm_out/boyu/src_analysis_launch/merge_trees/test

    swif2 cancel -delete -workflow src_analysis_launch
    swif2 cancel -delete -workflow src_analysis_launch_merge
    swif2 create -workflow src_analysis_launch
    swif2 create -workflow src_analysis_launch_merge    
else    
    mkdir /volatile/halld/analysis/RunPeriod-2021-11/ver${VERSION}
    mkdir /volatile/halld/analysis/RunPeriod-2021-11/ver${VERSION}/batch01
    mkdir /volatile/halld/analysis/RunPeriod-2021-11/ver${VERSION}/batch02
    mkdir /volatile/halld/analysis/RunPeriod-2021-11/ver${VERSION}/batch03

    mkdir /cache/halld/RunPeriod-2021-11/analysis/ver${VERSION}
    
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