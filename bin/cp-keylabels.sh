#!/bin/bash
#
#   cp-keylabels.sh. Copies the keylabels files of each module to the specified directory
#
#   Copyright (C) 2023 Free Software Foundation, Inc.
#
#   Author:  Luis Alejandro Bernal Romero <aztlek@gmail.com>
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU General Public License
#   as published by the Free Software Foundation; either version 3
#   of the License, or (at your option) any later version.
#
#   You should have received a copy of the GNU General Public
#   License along with this library; see the file COPYING.
#   If not, write to the Free Software Foundation,
#   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.


base=$1
dir=keyLabels
mkdir -p $base/$dir
for i in modules/*
do
   module=$(basename $i)
   pdf=$i/images/ModuleKeyLabels.pdf
   if test -a $pdf
   then
   file_name=$(basename $pdf)
      cp $pdf $base/${dir}/${module}_KeyLabels.pdf
   fi
done
