#!/bin/bash
#
#   cp-one-engrave.sh. Copies the module's engraving file to the specified directory
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


base=$2
module=$1
module=$(basename $1)
engrave_dir=engrave
mkdir -p $base$engrave_dir
pdf=$1/images/engrave/engrave_VectorizedText.pdf
if test -a $pdf
then
   cp $pdf $base$engrave_dir/$module.pdf
fi
