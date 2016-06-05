# File format
First, there's the HEADER. Then, each wave has its own data, one for each wave.

The format for all data is: MssssDDDDD.....
 - M = magic number
 - ssss = size of data (32-bits)
 - DDDDD... = data

## pcmlib
### HEADER PARAMS
    SamPLE  magic number
    <needed>
    N       number of waves
    <optional>
    t       text (message)
    \0      padding
### EACH WAVE PARAMS
    <needed>
    w       wave data
    <optional>
    s       sample rate
    t       text (name)
    \0      padding


