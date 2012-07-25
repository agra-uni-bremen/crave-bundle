#!/bin/bash
SRC_DIR=$( cd $(dirname $0) && pwd)

BUILD_DIR=$PWD/build

BOOST=boost-1_46_1
REQUIRES="
  SWORD-1.1
  cudd-2.4.2
"

CMAKE=cmake
BUILD_CMAKE="no"
CMAKE_PACKAGE=cmake-2.8.4

CMAKE_ARGS="
  -DmetaSMT_ENABLE_TESTS=off
  -DmetaSMT_ENABLE_TOOLBOX=off
"



if ! [[ "$1" ]]; then
  cat << EOF
$0 sets up a metaSMT build folder.
usage: $0 [--free] [--non-free] build
  --boost=/p/t/b  use this version of the Boost libraries
  --clean         delete build folder before creating a new one
  --deps <dir>    build dependencies in this folder
   -d <dir>       can be shared in different projects
  --install <dir> configure cmake to install to this directory
   -i <dir>
  --mode <type>   the CMake build type to configure, types are
   -m <type>      RELEASE, MINSIZEREL, RELWITHDEBINFO, DEBUG
   -Dvar=val      pass options to cmake
  --cmake=/p/t/c  use this version of cmake
  --cmake         build a custom cmake version
  <build>         the folder to setup the build environment in
EOF
  exit 1
fi


while [[ "$@" ]]; do
  case $1 in
    --boost=*)    BOOST=""; BOOST_ROOT="${1#--boost=}";;
    --deps|-d)    DEPS="$2"; shift;;
    --install|-i) INSTALL="$2"; shift;;
    --mode|-m)    CMAKE_ARGS="$CMAKE_ARGS -DCMAKE_BUILD_TYPE=$2"; shift;;
     -D*)         CMAKE_ARGS="$CMAKE_ARGS $1";;
    --clean|-c)   CLEAN="rm -rf";;
    --cmake=*)    CMAKE="${1#--cmake=}";;
    --cmake)      BUILD_CMAKE="yes";;
             *)   ## assume build dir
                  BUILD_DIR="$1" ;;
  esac
  shift;
done

if [[ "$CLEAN" ]]; then
  rm -rf $BUILD_DIR
fi

mk_and_abs_dir() {
  mkdir -p $1 &&
  cd $1 &>/dev/null &&
  pwd
}
BUILD_DIR=$(mk_and_abs_dir $BUILD_DIR) &&
INSTALL=$(mk_and_abs_dir ${INSTALL:-$BUILD_DIR/root}) &&
DEPS=$(mk_and_abs_dir ${DEPS:-$BUILD_DIR}) &&

if [ -z "$BOOST_ROOT" ]; then
  REQUIRES="$BOOST $REQUIRES"
  BOOST_ROOT="$DEPS/$BOOST"
fi


if ! [ -d dependencies ]; then 
  # packaged mode
  echo "could not find the dependency repository"
  exit 2
fi

cd dependencies
./build "$DEPS" $REQUIRES &&
if [ "$BUILD_CMAKE" = "yes" ]; then
  ./build "$DEPS" $CMAKE_PACKAGE &&
  CMAKE=$DEPS/$CMAKE_PACKAGE/bin/cmake
fi

cd $BUILD_DIR && 

PREFIX_PATH=$(echo $REQUIRES| sed "s@[ ^] *@;$DEPS/@g")

eval_echo() {
 $@
 echo "$@"
}



cd $BUILD_DIR
eval_echo $CMAKE $SRC_DIR \
  -DCMAKE_INSTALL_PREFIX="$INSTALL" \
  -DCMAKE_PREFIX_PATH="$PREFIX_PATH" \
  $CMAKE_ARGS \
  -DBOOST_ROOT="$BOOST_ROOT"

echo "finished bootstrap, you can now call make in $BUILD_DIR"
