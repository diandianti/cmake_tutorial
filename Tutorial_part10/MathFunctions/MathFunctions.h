#ifndef _MATHFUNCTION_H_
#define _MATHFUNCTION_H_

#if defined(_WIN32)
#  if defined(EXPORTING_MYMATH)
#    define DECLSPEC __declspec(dllexport)
#  else
#    define DECLSPEC __declspec(dllimport)
#  endif
#else // non windows
#  define DECLSPEC
#endif

namespace mathfunctions {
	double DECLSPEC sqrt(double x);
}

#endif /* _MATHFUNCTION_H_*/

