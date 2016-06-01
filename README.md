# funtracker
The "un-tracker". A music tracker. Linux-oriented, Windows/OSX maybe later.

### What it is
Funtracker is a way for me to learn SDL and C, and to make a hopefully cool 8-bit tracker.
It is designed to be used on larger, multiple-track projects, to increase flexibility and reduce filesize.

The biggest ideas:
 - No instruments, just channel-persistent parameters
 - All samples, or "Waves" are stored in a .pcmlib and can be shared across multiple tracks
 - Channels act as pairs, allowing for cool stuff using multiple samples, and easier stereo

### What it is not
 - Funtracker does not emulate other trackers, and will not support .mod or .xm, except maybe imported.
 - Funtracker does not use precise math or expensive operations. I aim to keep things integer and LUT-based.

### goals
 1. Reading of waves, writing of pcmlib, with .au, .wav, maybe .aiff support. Graphical pcmlib builder?
 2. Development of module format
