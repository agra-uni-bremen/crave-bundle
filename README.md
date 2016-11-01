**NEWS** We are preparing to release CRAVE 2.x code on GitHub. The new version does not need crave-bundle.
Meanwhile, please visit http://systemc-verification.org/crave for a preview of CRAVE 2.x including an integration with 
[UVM-SystemC](http://accellera.org/activities/working-groups/systemc-verification/uvm-systemc-faq).  

Constrained RAndom Verification Enviroment - CRAVE
====================================================

For feedback and bug reports: crave@informatik.uni-bremen.de

 Preparations
--------------

When installing directly from the git repository some additional steps are
required. These are not necessary when using the packaged source code. Both
require some packages to be installed on the system.

To get CRAVE from the git repository execute the following commands:

    git clone https://github.com/agra-uni-bremen/crave-bundle.git
    cd crave-bundle
    git submodule update --init

This will download crave and its direct dependencies. External dependencies
will be downloaded by the bootstrap script when executing make.

Please install the following packages to ensure the external packages will
build correctly:

* zlib and bzip2 development libraries (e.g. zlib1g-dev, libbz2-dev)
* CMake
* Python development libraries


 Build and install CRAVE
-------------------------

1. Call 'make' to build CRAVE, the dependencies should
   automatically download and build.
2. Call 'make test', all tests should pass.
3. Call 'make install'.

 Examples
----------

You will find several examples in the examples/ directory. These will
demonstrate how to build applications that use CRAVE as well as some core
features of CRAVE as listed below:

  * ex1_seed_dist              : global seed and simple distribution.
  * ex2_constr_ref             : constraints and references.
  * ex3_inh_soft_next          : constraint inheritance, soft constraints and custom next().
  * ex4_constr_mng             : enable/disable constraints.
  * ex5_vec_constr             : vector constraints.
  * ex6_inline_gen             : inline generator.
  * ex7_randv_enum             : constraints on enumeration types.

to execute these examples look into the build/examples directory.
See also the test cases in crave/tests which cover all implemented features.

 SystemC Support
-----------------

For the build system to build and test the SystemC testcases you need to
provide a SystemC config file for CMake. Place this file in your SystemC
installation directory (check that the include and library path are correct).

    # SystemCConfig.cmake
    set(SystemC_VERSION 2.2.0)

    ## alternative:
    # set(SystemC_DIRECTORY /path/to/systemC)
    get_filename_component(SystemC_DIRECTORY ${CMAKE_CURRENT_LIST_FILE} PATH)

    set(SystemC_INCLUDE_DIR  ${SystemC_DIRECTORY}/include )
    set(SystemC_INCLUDE_DIRS ${SystemC_INCLUDE_DIR} )
    set(SystemC_LIBRARIES    ${SystemC_DIRECTORY}/lib/libsystemc.a)

and point cmake to your SystemC directory:

    cmake -DSystemC_DIR=/path/to/systemc build/


 External dependencies
-----------------------

CRAVE uses the following external dependencies:

* [Boost]
* [CUDD]
* [SWORD]


 Known issues
--------------

In the default configuration CRAVE will use SWORD for its SMT-based
constraint-solver. SWORD is provided as binary program for Linux x86 and x86_64
platforms. However this version of SWORD is incompatible with RHEL 5 or derived
operating systems (e.g. CentOS 5).




[Boost]: http://www.boost.org
[CUDD]:  http://vlsi.colorado.edu/~fabio/CUDD/
[SWORD]: http://www.informatik.uni-bremen.de/agra/eng/sword.php
