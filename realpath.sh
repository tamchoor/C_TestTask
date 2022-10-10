#! /bin/sh

for arg in $@; do
  echo "$(cd "$(dirname "$arg")"; pwd -P)/$(basename "$arg")"
done
