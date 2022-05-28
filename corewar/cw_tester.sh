#!/bin/bash

FILE1=$1
diff <(./corewar -show d $FILE1) <(./vm_champs/corewar -v 8 $FILE1)
