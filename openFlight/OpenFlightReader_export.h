#pragma once

#ifdef OPENFLIGHTREADER_USE_DLL

    // Some classes uses std::string as membler and warning are generated
    // when exporting the dll interface.
    //
    // It seems it can be ignored:
    //  https://stackoverflow.com/questions/8976617/when-exporting-stl-stdbasic-string-template-from-dll-i-get-a-lnk2005-error
    //
    #pragma warning( disable : 4251)

    //compiled as dll, define declspec accoringly
    #ifdef OPENFLIGHTREADER_DLL_EXPORT 
	    #define OFR_API _declspec(dllexport)
    #else
	    #define OFR_API _declspec(dllimport)
    #endif
#endif

#ifndef OFR_API 
    #define OFR_API 
#endif // !OFR_API 