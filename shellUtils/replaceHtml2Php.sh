#!/bin/bash

for file in `ls *.html`
do
  mv $file ${file/html/php}
done
