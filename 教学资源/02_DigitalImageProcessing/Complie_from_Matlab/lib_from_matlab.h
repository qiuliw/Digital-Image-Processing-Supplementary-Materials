/*
 * MATLAB Compiler: 4.10 (R2009a)
 * Date: Fri May 14 10:01:44 2010
 * Arguments: "-B" "macro_default" "-B" "csharedlib:lib_from_matlab" "-W"
 * "lib:lib_from_matlab" "-T" "link:lib" "fft_matrix.m" "ifft_matrix.m"
 * "dct_matrix.m" "idct_matrix.m" 
 */

#ifndef __lib_from_matlab_h
#define __lib_from_matlab_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_lib_from_matlab
#define PUBLIC_lib_from_matlab_C_API __global
#else
#define PUBLIC_lib_from_matlab_C_API /* No import statement needed. */
#endif

#define LIB_lib_from_matlab_C_API PUBLIC_lib_from_matlab_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_lib_from_matlab
#define PUBLIC_lib_from_matlab_C_API __declspec(dllexport)
#else
#define PUBLIC_lib_from_matlab_C_API __declspec(dllimport)
#endif

#define LIB_lib_from_matlab_C_API PUBLIC_lib_from_matlab_C_API


#else

#define LIB_lib_from_matlab_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_lib_from_matlab_C_API 
#define LIB_lib_from_matlab_C_API /* No special import/export declaration */
#endif

extern LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV lib_from_matlabInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                                        mclOutputHandlerFcn print_handler);

extern LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV lib_from_matlabInitialize(void);

extern LIB_lib_from_matlab_C_API 
void MW_CALL_CONV lib_from_matlabTerminate(void);



extern LIB_lib_from_matlab_C_API 
void MW_CALL_CONV lib_from_matlabPrintStackTrace(void);


extern LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV mlxFft_matrix(int nlhs, mxArray *plhs[],
                                int nrhs, mxArray *prhs[]);

extern LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV mlxIfft_matrix(int nlhs, mxArray *plhs[],
                                 int nrhs, mxArray *prhs[]);

extern LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV mlxDct_matrix(int nlhs, mxArray *plhs[],
                                int nrhs, mxArray *prhs[]);

extern LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV mlxIdct_matrix(int nlhs, mxArray *plhs[],
                                 int nrhs, mxArray *prhs[]);

extern LIB_lib_from_matlab_C_API 
long MW_CALL_CONV lib_from_matlabGetMcrID() ;



extern LIB_lib_from_matlab_C_API bool MW_CALL_CONV mlfFft_matrix(int nargout
                                                                 , mxArray** a
                                                                 , mxArray* b);

extern LIB_lib_from_matlab_C_API bool MW_CALL_CONV mlfIfft_matrix(int nargout
                                                                  , mxArray** a
                                                                  , mxArray* b);

extern LIB_lib_from_matlab_C_API bool MW_CALL_CONV mlfDct_matrix(int nargout
                                                                 , mxArray** a
                                                                 , mxArray* b);

extern LIB_lib_from_matlab_C_API bool MW_CALL_CONV mlfIdct_matrix(int nargout
                                                                  , mxArray** a
                                                                  , mxArray* b);

#ifdef __cplusplus
}
#endif

#endif
