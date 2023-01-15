#!/bin/bash

commit=
info=`date | awk '{print $1,$2,$3,$4}'`
read -r commit
res=${commit}' | '${info}
export res