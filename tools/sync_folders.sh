#/!/bin/bash

#this is mostly here so I don't forget the stupid syntax. 
#this func could probably be made useful at some point.
sync_source_files()
{
    echo "Copy files from $1 to $2?"
    find $1 -iname '*h' -exec cp --target-directory $2 {} \;
}