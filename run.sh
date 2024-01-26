#!/bin/bash

workdir=`dirname $0`
cd $workdir
workdir=`pwd`

uvicorn api:app --host 0.0.0.0 --port 8086 --reload