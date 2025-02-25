This Section is tests out exe/bin file reconstruction.

reader.cc reads out binary files and outputs them in 1s and 0s

unreader.cc takes the output of reader.cc and reconstructs an exe based on it.

Purpose - This was mostly just a fun test, but it also helps me understand a bit more about binary files , that will be used in the ziprunner, possibly to recreate file that run on a zipVM(the runner that will executes zip files)

procedure - index.cc is read by reader and then output to the console. I redirect that output to hello.txt for storage. unreader then goes ahead and reconstructs a binary file based on it, which gets written to output.exe.

End result- output.exe performs the exact same program index.exe does
