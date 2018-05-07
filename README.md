# OpenFlightReader :airplane:

## Yet Another OpenFlight Reader 

[![Build status](https://ci.appveyor.com/api/projects/status/jcvjftfpicwg7xas/branch/master?svg=true)](https://ci.appveyor.com/project/jbltx/openflightreader/branch/master)

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
:: go to the compiled generator directory
cd bin\generators\csharp

:: generate the CSharp bindings files
OpenFlightReader.CSharp.exe ^
 -L ..\..\dll ^
 -l OpenFlightReader.lib ^
 -I ..\..\include ^
 -i OpenFlightReader.h ^
 -o generated

```
This will generate `.cs` and `.cpp` files inside a folder named "FLT".

For the STD library bindings (std::string), you will need to compile a separated dll

```bat
cd generated
cl.exe /LD /EHsc Std-symbols.cpp
```

OpenFlightReader in your project:

| File                       | Location                               |
| -------------------------- | -------------------------------------- |
|  OpenFlightReader.dll      |  next to your compiled lib/executable  |
|  Std-symbols.dll           |  next to your compiled lib/executable  |
|  OpenFlightReader.cs       |  use it directly inside your project   |
|  Std.cs                    |  use it directly inside your project   |
