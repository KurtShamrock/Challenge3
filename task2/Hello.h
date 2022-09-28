#pragma once

#ifdef HELLOLIBRARY_EXPORTS
#define HELLOLIBRARY_API __declspec(dllexport)
#else
#define HELLOLIBRARY_API __declspec(dllimport)
#endif
extern "C" HELLOLIBRARY_API void Hello();