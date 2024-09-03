/*
 * MATLAB Compiler: 4.10 (R2009a)
 * Date: Fri May 14 10:01:44 2010
 * Arguments: "-B" "macro_default" "-B" "csharedlib:lib_from_matlab" "-W"
 * "lib:lib_from_matlab" "-T" "link:lib" "fft_matrix.m" "ifft_matrix.m"
 * "dct_matrix.m" "idct_matrix.m" 
 */

#include <stdio.h>
#define EXPORTING_lib_from_matlab 1
#include "lib_from_matlab.h"
#ifdef __cplusplus
extern "C" {
#endif

extern mclComponentData __MCC_lib_from_matlab_component_data;

#ifdef __cplusplus
}
#endif


static HMCRINSTANCE _mcr_inst = NULL;


#if defined( _MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__) || defined(__LCC__)
#ifdef __LCC__
#undef EXTERN_C
#endif
#include <windows.h>

static char path_to_dll[_MAX_PATH];

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, void *pv)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        if (GetModuleFileName(hInstance, path_to_dll, _MAX_PATH) == 0)
            return FALSE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
    }
    return TRUE;
}
#endif
#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultPrintHandler(const char *s)
{
  return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultErrorHandler(const char *s)
{
  int written = 0;
  size_t len = 0;
  len = strlen(s);
  written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
  if (len > 0 && s[ len-1 ] != '\n')
    written += mclWrite(2 /* stderr */, "\n", sizeof(char));
  return written;
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_lib_from_matlab_C_API 
#define LIB_lib_from_matlab_C_API /* No special import/export declaration */
#endif

LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV lib_from_matlabInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler
)
{
  if (_mcr_inst != NULL)
    return true;
  if (!mclmcrInitialize())
    return false;
  if (!GetModuleFileName(GetModuleHandle("lib_from_matlab"), path_to_dll, _MAX_PATH))
    return false;
  if (!mclInitializeComponentInstanceWithEmbeddedCTF(&_mcr_inst,
                                                     &__MCC_lib_from_matlab_component_data,
                                                     true, NoObjectType,
                                                     LibTarget, error_handler,
                                                     print_handler, 81817, path_to_dll))
    return false;
  return true;
}

LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV lib_from_matlabInitialize(void)
{
  return lib_from_matlabInitializeWithHandlers(mclDefaultErrorHandler,
                                               mclDefaultPrintHandler);
}

LIB_lib_from_matlab_C_API 
void MW_CALL_CONV lib_from_matlabTerminate(void)
{
  if (_mcr_inst != NULL)
    mclTerminateInstance(&_mcr_inst);
}

LIB_lib_from_matlab_C_API 
long MW_CALL_CONV lib_from_matlabGetMcrID() 
{
  return mclGetID(_mcr_inst);
}

LIB_lib_from_matlab_C_API 
void MW_CALL_CONV lib_from_matlabPrintStackTrace(void) 
{
  char** stackTrace;
  int stackDepth = mclGetStackTrace(_mcr_inst, &stackTrace);
  int i;
  for(i=0; i<stackDepth; i++)
  {
    mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
    mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
  }
  mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV mlxFft_matrix(int nlhs, mxArray *plhs[],
                                int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "fft_matrix", nlhs, plhs, nrhs, prhs);
}

LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV mlxIfft_matrix(int nlhs, mxArray *plhs[],
                                 int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "ifft_matrix", nlhs, plhs, nrhs, prhs);
}

LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV mlxDct_matrix(int nlhs, mxArray *plhs[],
                                int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "dct_matrix", nlhs, plhs, nrhs, prhs);
}

LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV mlxIdct_matrix(int nlhs, mxArray *plhs[],
                                 int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "idct_matrix", nlhs, plhs, nrhs, prhs);
}

LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV mlfFft_matrix(int nargout, mxArray** a, mxArray* b)
{
  return mclMlfFeval(_mcr_inst, "fft_matrix", nargout, 1, 1, a, b);
}

LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV mlfIfft_matrix(int nargout, mxArray** a, mxArray* b)
{
  return mclMlfFeval(_mcr_inst, "ifft_matrix", nargout, 1, 1, a, b);
}

LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV mlfDct_matrix(int nargout, mxArray** a, mxArray* b)
{
  return mclMlfFeval(_mcr_inst, "dct_matrix", nargout, 1, 1, a, b);
}

LIB_lib_from_matlab_C_API 
bool MW_CALL_CONV mlfIdct_matrix(int nargout, mxArray** a, mxArray* b)
{
  return mclMlfFeval(_mcr_inst, "idct_matrix", nargout, 1, 1, a, b);
}
