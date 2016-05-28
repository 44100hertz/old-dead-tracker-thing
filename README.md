# funtracker
A non-traditional music tracker. The "un-tracker".

## What it is
Funtracker is a way for me to learn SDL and C, and to make a hopefully cool 8-bit tracker.
It is designed to be both efficient and flexible, by reducing redundancy, and by allowing parameters to be changed on-the-fly.

The biggest things:
 - There are no instruments, just channel-persistent parameters to be saved and loaded
 - Samples are stored as a separate file and can be used in multiple tracks
 - Channels act as pairs, allowing for basic sound synthesis using samples, and easy stereo management
 - Limited by design to reduce overhead and to force creativity

## What it is not
Funtracker is not designed to emulate older trackers, and will not support .mod or .xm.
Funtracker does not use precise math or expensive operations. I aim to keep things integer and LUT-based.

# current goals
 1. Sample reading, playback, and manipulation
 2. Development of sample and track formats
 3. Reading and writing basic tracks
 4. An SDL UI and live playback
 5. ...
