#!/bin/bash

VERSION="ver08_batch01"

date
source /work/halld2/home/boyu/src_analysis_launch/merge_trees/env.sh
export PATH=/site/bin:${PATH} #because .login isn't executed, and need this path for SWIF
python /work/halld2/home/boyu/src_analysis_launch/merge_trees/merge_trees.py /work/halld2/home/boyu/src_analysis_launch/merge_trees/configs/jobs_merge/jobs_merge_2021-11_${VERSION}.cfg 0
