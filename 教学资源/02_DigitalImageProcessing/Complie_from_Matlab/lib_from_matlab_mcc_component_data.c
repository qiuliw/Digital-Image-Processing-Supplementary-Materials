/*
 * MATLAB Compiler: 4.10 (R2009a)
 * Date: Fri May 14 10:01:45 2010
 * Arguments: "-B" "macro_default" "-B" "csharedlib:lib_from_matlab" "-W"
 * "lib:lib_from_matlab" "-T" "link:lib" "fft_matrix.m" "ifft_matrix.m"
 * "dct_matrix.m" "idct_matrix.m" 
 */

#include "mclmcrrt.h"

#ifdef __cplusplus
extern "C" {
#endif
const unsigned char __MCC_lib_from_matlab_session_key[] = {
    '4', '6', '4', '7', '1', '7', '4', 'C', 'F', '6', 'A', '1', '3', 'B', 'D',
    'D', 'D', 'A', 'B', '7', 'A', '3', '2', 'F', '9', 'A', 'F', '2', 'E', '1',
    '7', 'B', 'C', '7', 'A', '8', '0', '8', '7', '8', 'C', '6', 'D', '6', '1',
    '5', 'A', '3', '5', '6', 'C', '4', '8', '1', '8', '9', '2', '0', '3', '2',
    'B', 'B', 'D', '3', '9', 'A', '4', '7', 'F', '8', '4', 'E', '4', '2', 'E',
    '5', 'E', '2', '3', '8', '4', '1', '8', '1', 'E', 'A', 'B', '6', '9', '1',
    'A', 'C', '5', '7', '9', '7', 'B', '8', 'D', 'C', '9', '1', 'E', '6', '8',
    '6', '6', '8', '5', 'A', 'A', '6', '6', 'F', '8', '3', '5', '0', 'A', '0',
    '1', 'F', 'D', 'F', 'F', '7', '8', 'B', 'F', '2', 'E', '8', 'F', 'C', '9',
    '1', 'D', '9', '9', '6', 'C', 'A', 'E', '4', '9', '6', 'D', 'C', '1', 'F',
    '4', 'D', 'B', '2', 'C', '7', '6', 'D', '6', 'F', '2', '0', '0', '9', '3',
    'F', '3', '4', 'B', '9', '1', '1', 'F', 'B', '9', '2', 'C', '8', 'A', '8',
    'E', '4', '3', '5', 'B', '7', 'B', '7', '8', '7', 'C', '2', 'A', '5', '3',
    'F', '9', 'A', 'D', 'C', 'C', 'F', '2', '3', '8', '2', '3', 'B', '1', '0',
    '8', '9', '8', '4', '0', '9', '0', 'C', 'F', '7', 'D', '7', 'D', 'D', 'A',
    'C', '0', 'A', 'F', '9', '6', '5', '7', '1', 'A', 'C', 'B', 'C', '6', '1',
    '0', 'E', 'D', '1', 'F', '1', '4', 'B', '0', 'E', '4', '1', '8', '2', '5',
    '3', '\0'};

const unsigned char __MCC_lib_from_matlab_public_key[] = {
    '3', '0', '8', '1', '9', 'D', '3', '0', '0', 'D', '0', '6', '0', '9', '2',
    'A', '8', '6', '4', '8', '8', '6', 'F', '7', '0', 'D', '0', '1', '0', '1',
    '0', '1', '0', '5', '0', '0', '0', '3', '8', '1', '8', 'B', '0', '0', '3',
    '0', '8', '1', '8', '7', '0', '2', '8', '1', '8', '1', '0', '0', 'C', '4',
    '9', 'C', 'A', 'C', '3', '4', 'E', 'D', '1', '3', 'A', '5', '2', '0', '6',
    '5', '8', 'F', '6', 'F', '8', 'E', '0', '1', '3', '8', 'C', '4', '3', '1',
    '5', 'B', '4', '3', '1', '5', '2', '7', '7', 'E', 'D', '3', 'F', '7', 'D',
    'A', 'E', '5', '3', '0', '9', '9', 'D', 'B', '0', '8', 'E', 'E', '5', '8',
    '9', 'F', '8', '0', '4', 'D', '4', 'B', '9', '8', '1', '3', '2', '6', 'A',
    '5', '2', 'C', 'C', 'E', '4', '3', '8', '2', 'E', '9', 'F', '2', 'B', '4',
    'D', '0', '8', '5', 'E', 'B', '9', '5', '0', 'C', '7', 'A', 'B', '1', '2',
    'E', 'D', 'E', '2', 'D', '4', '1', '2', '9', '7', '8', '2', '0', 'E', '6',
    '3', '7', '7', 'A', '5', 'F', 'E', 'B', '5', '6', '8', '9', 'D', '4', 'E',
    '6', '0', '3', '2', 'F', '6', '0', 'C', '4', '3', '0', '7', '4', 'A', '0',
    '4', 'C', '2', '6', 'A', 'B', '7', '2', 'F', '5', '4', 'B', '5', '1', 'B',
    'B', '4', '6', '0', '5', '7', '8', '7', '8', '5', 'B', '1', '9', '9', '0',
    '1', '4', '3', '1', '4', 'A', '6', '5', 'F', '0', '9', '0', 'B', '6', '1',
    'F', 'C', '2', '0', '1', '6', '9', '4', '5', '3', 'B', '5', '8', 'F', 'C',
    '8', 'B', 'A', '4', '3', 'E', '6', '7', '7', '6', 'E', 'B', '7', 'E', 'C',
    'D', '3', '1', '7', '8', 'B', '5', '6', 'A', 'B', '0', 'F', 'A', '0', '6',
    'D', 'D', '6', '4', '9', '6', '7', 'C', 'B', '1', '4', '9', 'E', '5', '0',
    '2', '0', '1', '1', '1', '\0'};

static const char * MCC_lib_from_matlab_matlabpath_data[] = 
  { "lib_from_mat/", "$TOOLBOXDEPLOYDIR/", "$TOOLBOXMATLABDIR/general/",
    "$TOOLBOXMATLABDIR/ops/", "$TOOLBOXMATLABDIR/lang/",
    "$TOOLBOXMATLABDIR/elmat/", "$TOOLBOXMATLABDIR/randfun/",
    "$TOOLBOXMATLABDIR/elfun/", "$TOOLBOXMATLABDIR/specfun/",
    "$TOOLBOXMATLABDIR/matfun/", "$TOOLBOXMATLABDIR/datafun/",
    "$TOOLBOXMATLABDIR/polyfun/", "$TOOLBOXMATLABDIR/funfun/",
    "$TOOLBOXMATLABDIR/sparfun/", "$TOOLBOXMATLABDIR/scribe/",
    "$TOOLBOXMATLABDIR/graph2d/", "$TOOLBOXMATLABDIR/graph3d/",
    "$TOOLBOXMATLABDIR/specgraph/", "$TOOLBOXMATLABDIR/graphics/",
    "$TOOLBOXMATLABDIR/uitools/", "$TOOLBOXMATLABDIR/strfun/",
    "$TOOLBOXMATLABDIR/imagesci/", "$TOOLBOXMATLABDIR/iofun/",
    "$TOOLBOXMATLABDIR/audiovideo/", "$TOOLBOXMATLABDIR/timefun/",
    "$TOOLBOXMATLABDIR/datatypes/", "$TOOLBOXMATLABDIR/verctrl/",
    "$TOOLBOXMATLABDIR/codetools/", "$TOOLBOXMATLABDIR/helptools/",
    "$TOOLBOXMATLABDIR/winfun/", "$TOOLBOXMATLABDIR/winfun/NET/",
    "$TOOLBOXMATLABDIR/demos/", "$TOOLBOXMATLABDIR/timeseries/",
    "$TOOLBOXMATLABDIR/hds/", "$TOOLBOXMATLABDIR/guide/",
    "$TOOLBOXMATLABDIR/plottools/", "toolbox/local/",
    "toolbox/shared/dastudio/", "$TOOLBOXMATLABDIR/datamanager/",
    "toolbox/compiler/", "toolbox/shared/spcuilib/", "toolbox/signal/signal/" };

static const char * MCC_lib_from_matlab_classpath_data[] = 
  { "" };

static const char * MCC_lib_from_matlab_libpath_data[] = 
  { "" };

static const char * MCC_lib_from_matlab_app_opts_data[] = 
  { "" };

static const char * MCC_lib_from_matlab_run_opts_data[] = 
  { "" };

static const char * MCC_lib_from_matlab_warning_state_data[] = 
  { "off:MATLAB:dispatcher:nameConflict" };


mclComponentData __MCC_lib_from_matlab_component_data = { 

  /* Public key data */
  __MCC_lib_from_matlab_public_key,

  /* Component name */
  "lib_from_matlab",

  /* Component Root */
  "",

  /* Application key data */
  __MCC_lib_from_matlab_session_key,

  /* Component's MATLAB Path */
  MCC_lib_from_matlab_matlabpath_data,

  /* Number of directories in the MATLAB Path */
  42,

  /* Component's Java class path */
  MCC_lib_from_matlab_classpath_data,
  /* Number of directories in the Java class path */
  0,

  /* Component's load library path (for extra shared libraries) */
  MCC_lib_from_matlab_libpath_data,
  /* Number of directories in the load library path */
  0,

  /* MCR instance-specific runtime options */
  MCC_lib_from_matlab_app_opts_data,
  /* Number of MCR instance-specific runtime options */
  0,

  /* MCR global runtime options */
  MCC_lib_from_matlab_run_opts_data,
  /* Number of MCR global runtime options */
  0,
  
  /* Component preferences directory */
  "lib_from_mat_97088E67AA29B893C4885536388B28EE",

  /* MCR warning status data */
  MCC_lib_from_matlab_warning_state_data,
  /* Number of MCR warning status modifiers */
  1,

  /* Path to component - evaluated at runtime */
  NULL

};

#ifdef __cplusplus
}
#endif


