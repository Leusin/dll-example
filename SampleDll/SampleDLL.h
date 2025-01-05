#ifndef INDLL_H
#define INDLL_H

#ifdef EXPORTING_DLL
extern "C" __declspec(dllexport) void HelloWorld();
#else
extern "C" __declspec(dllimport) void HelloWorld();
#endif

#endif // INDLL_H