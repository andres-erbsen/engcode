#!/bin/sh

# Yet Another Word List
# by Mendel Cooper and Alan Beale
# Public Domain
# Last modified 12-Oct-2008
wget -O yawl.txt http://gtoal.com/wordgames/yawl/word.list

# 2^18 shortest words in alphabetical order. This is /almost/ the whole list.
cat yawl.txt | awk '{print length"\t"$0}' | sort -k1,1n -k2 | head -262144 | cut -f2- | sort > words.txt

md5=$( md5sum words.txt )
case "$md5" in
    *4e0766283a0b1892b2ecbc28691e64b7*) rm yawl.txt ;;
    *) echo "MD5 sum does not match! $md5" >&2 ;;
esac

