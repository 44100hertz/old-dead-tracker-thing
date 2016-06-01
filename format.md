# File formats
 - one char = one byte
 - 16-bit (XX) offsets are in multiples of 4 bytes
 - all offsets are absolute
 - first letter is magic, X/Y/Z is binary data
 - [optional params bracketed]
 - "_" is a space (0x20)
## .pcmlib ##
### HEADER
    SamP    magic number
    n_XX    number of waves
    h_XX    offset of wave headers
    [c_XX]  offset of comment
    ...     rest of header
### WAVE HEADERS
    XXXX    wave offset (in data)
    [N_XX]  offset of next wave header
    [n_XX]  offset of wave name
    [s_XX]  sample rate
    ...     rest of header
### WAVE DATA
    <insert however-long stream of 8bit PCM here>


