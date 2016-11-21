# cdisk
A small program for creating ram disks in OS X written in c.

## Usage
    cdisk X

where X is the size of the ram disk to be created in Gigabytes.
To create a ram disk with a size of 2GB, enter:

    cdisk 2

## Development
### Software requirements
* hdiutil
* diskutil

Both dependencies are command line utilities that comes preinstalled with OS X.

## Build
    make
