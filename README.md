> [!WARNING]
> This project is for educational and informational purposes only. The author does not condone and is not liable for misuse of code in this repository, whether in part or its entirety.

# Payload Template Showcase
## Description
This repository contains a basic payload template originally designed to demonstrate antivirus evasion techniques. 

Please note: This template is no longer effective against the latest version of Windows Defender as of August 23, 2025. This version also intentionally contains multiple detectable elements such as hardcoded strings, residual memory artifacts that persist in the heap after execution, etc. These characteristics make it unsuitable for stealth or real-world evasion scenarios, so please don't test it on systems without explicit permission.

## Features
- Sleep timing to bypass simple heuristics evasion. 
- XOR encryption to evade static analysis.
- Process injection to migrate shellcode into remote processes to reduce suspicion.

## Compilation
To compile, please ensure that you have `x86_64-w64-mingw32-gcc`, `i686-w64-mingw32-gcc`, or equivalent compilers installed. 

x64:
```
make
```

x86:
```
make ARCH=x86
```