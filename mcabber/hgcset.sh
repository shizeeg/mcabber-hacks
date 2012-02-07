#! /bin/sh

if [ ! -f logprint.h ]; then
  echo "You are not in the mcabber directory" >&2
  exit 1
fi

GIT_COMMIT=`git log -1 --abbrev-commit | sed "s/commit //g" | head -1`
GIT_DATE=`git log -1 --date=iso | grep Date: | sed -E "s/Date: +//g"`
echo "#define HGCSET \"GIT $GIT_COMMIT ($GIT_DATE)\"" > hgcset.h

