#!/bin/bash

for b in `find . -name BUILD`
do
             buildifier $b
done

for b in `find . -name "*.bzl"`
do
             buildifier $b
done

for b in `find . -name BUILD`
do
             buildifier --lint=warn $b
done
