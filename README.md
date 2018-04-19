# OpenFlightReader :airplane:

## Yet Another OpenFlight Reader 


### Requirements

##### OpenFlightReader

- C++11 Compatible Compiler

##### OpenFlightReader.CSharp Generator

- Microsoft .NET Framework 4.6
- Visual Studio 2015
- Nuget executable installed in *%PATH%*

> NOTE : You can always provide the path of nuget.exe using **NUGET** cmake option.

### Build

```bat
mkdir build
cd build
cmake -DBUILD_AS_SHARED_LIB=ON -DBUILD_CSHARP_GENERATOR=OFF -G"Visual Studio 14 2015 Win64" ..
cmake --build . --config Release --target INSTALL
```


### OpenFlightReader.CSharp Generator Usage

```bat
OpenFlightReader.CSharp.exe ^
 -L F:\Projects\Libs\OpenFlightReader\bin\dll ^
 -l OpenFlightReader.lib ^
 -I F:\Projects\Libs\OpenFlightReader\bin\include ^
 -i OpenFlightReader.h ^
 -o FLT
```
This will generate `.cs` and `.cpp` files inside a folder named "FLT".