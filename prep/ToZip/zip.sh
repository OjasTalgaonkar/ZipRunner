#!/bin/bash

set -u

ls -l filesToTest/input.txt filesToTest/output.bin | awk '{print $9 ": " $5 " bytes"}'