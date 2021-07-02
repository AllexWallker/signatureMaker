signatureMaker is a program that makes file signature chunk by chunk with default chunk size
1000000 bites(because in macOS 1 mb is 1000000 bites),then writes the result to a file with name
"*file_name*_signature.txt" and saves it in the same with input file directory.

Use command "cmake . -Bbuild", than "cd build" and than "make" to build and compile program.
It's necessary to have installed Boost 1.76 library on a computer, because cmake searchs it
automatically. The program is supposed to run in UNIX systems (tested on macOS).