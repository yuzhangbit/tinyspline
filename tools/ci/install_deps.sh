#!/bin/bash
set -e

# Directory where this script is located.
SCRIPT_DIR=$( cd $(dirname $0); pwd -P)

# Directory where external dependencies will be handled.
DEPS_DIR="$SCRIPT_DIR/deps"
mkdir -p "$DEPS_DIR"

pushd "$DEPS_DIR"
	# Install dependencies from package manager.
	if [ "$TRAVIS_OS_NAME" == "linux" ]; then
		sudo apt-get -qq update
		sudo apt-get install --no-install-recommends \
			doxygen             \
			graphviz            \
			python-dev          \
			ruby-dev            \
			php-dev             \
			liblua5.3-dev       \
			octave-pkg-dev      \
			openjdk-8-jdk       \
			r-base              \
			r-cran-rcpp         \
			-y;
	fi
	if [ "$TRAVIS_OS_NAME" == "osx" ]; then
		brew update
		brew install \
			lua
	fi
	if [ "$CIRCLECI" == "true" ]; then
	sudo apt-get -qq update
	sudo apt-get install --no-install-recommends \
		doxygen             \
		graphviz            \
		python-dev          \
		php5-dev            \
		liblua5.2-dev       \
		octave-pkg-dev      \
		r-base              \
		r-cran-rcpp         \
		-y;
	fi

	# Install CMake-3.11.0 from binary package.
	if [ "$TRAVIS_OS_NAME" == "osx" ]; then
		wget https://cmake.org/files/v3.11/cmake-3.11.0-Darwin-x86_64.tar.gz
		sudo tar xf cmake-3.11.0-Darwin-x86_64.tar.gz --strip 3 -C /usr/local
	else
		wget https://cmake.org/files/v3.11/cmake-3.11.0-Linux-x86_64.tar.gz
		sudo tar xf cmake-3.11.0-Linux-x86_64.tar.gz --strip 1 -C /usr/local
	fi

	# Compile and install Swig-3.0.12 from source.
	wget https://github.com/swig/swig/archive/rel-3.0.12.tar.gz
	tar xf rel-3.0.12.tar.gz
	pushd swig-rel-3.0.12
		./autogen.sh
		./configure
		make
		sudo make install
	popd
popd
