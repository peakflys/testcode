#!/bin/bash
count=0
for f in `find . -type f -name "*.cpp" -o -name "*.h" -o -name "*.c"` ; do 
coding=`file -bi $f | awk -F "=" '{print $2}'`;
if [ "$coding" = "iso-8859-1" ]; then
    iconv -f CP936 -t UTF8 $f -o /tmp/iconv.tmp;
    mv /tmp/iconv.tmp $f;
    count=`expr $count + 1`
fi
done
echo "convert $count files!"
