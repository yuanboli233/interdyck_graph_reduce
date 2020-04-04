#!/usr/bin/env bash
cp current.dot orig.dot
python3 graphgen_forfilter.py current.dot
./graph_simp.py
python3 recover_single_direction.py orig.dot current.dot > result.dot
mv result.dot current.dot
rm orig.dot
rm tmp.dot
