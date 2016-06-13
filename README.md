# funtracker
A fun music tracker. Linux-oriented, Windows/OSX maybe later.

### Concept
Funtracker is a way for me to learn SDL and C, and to make an 8-bit style tracker.

The biggest ideas:
 - No instruments, just channel-persistent parameters as data
 - Channels act as pairs, so stereo makes sense and the pairs can interact
 - Fun stuff such as phase modulation (think OPL/FM) is possible for a variety of sounds
 - Crunchy/ugly chip sound, but still capable of multiple synthesis techniques

### What it is not
 - Funtracker does not emulate other trackers, and will not support .mod or .xm, except maybe imported.
 - Funtracker does not use precise math or expensive operations. Fixed-point math is fun!
 - Funtracker is made for fun, and more or less for me.

### waveedit
A way to bring waves together into a .pcmlib file, which acts as a library of waves or "samples" for tracking with.

Format details in src/read.c.
PCMlib is likely to be extended into the final tracker format.

### Micro goals
 1. Improve error handling. Stereo samples. Wav/RIFF/AIFF support.
 2. Graphical pcmlib builder. [break into goals]
 3. Actual modfiles [break aswell]
