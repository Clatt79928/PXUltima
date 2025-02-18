# DEFLATE (v.1.3)<br>[RFC 1951]

## Info
Deflate is a compression format.<br>
It uses Huffmancoding, because of that, not bound to byte borders.<br>
For parsing, you need to view this format as a stream of bits, rather than bytes.

## Structure

### DEFLATE info block (2 Bits)
|Name|Length|Type| Description |
|:-:|:-:|:-:|:-|
|IsLastBlock | 1 Bit | bool | - |
|Type| 2 Bits | enum | 0b00 - no compression<br>0b01 - compressed with fixed Huffman codes<br>0b10 - compressed with dynamic Huffman codes<br>0b11 - reserved (error)|


#### Compression - None (0b00)
|Name|Length|Type| Description |
|:-|:-:|:-:|:-:|
|Length | 1 Byte | Int 8-Bit | - |
|Length (Bitwise inverted) | 1 Byte | Int 8-Bit | - |
|Data | x Bytes | Byte[] | Raw Pixeldata RGB |


#### Compression - Fixed Huffman codes (0b01)
ToDo

#### Compression - Dynamic Huffman codes (0b10)
ToDo

## Links
- https://en.wikipedia.org/wiki/Deflate
