
# duckdb v1.4.2 (v1.4-andium)

# compile env:
/content/duckdb-mysql# ldd --version
ldd (Ubuntu GLIBC 2.35-0ubuntu3.8) 2.35
Copyright (C) 2022 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
Written by Roland McGrath and Ulrich Drepper.
/content/duckdb-mysql# gcc --version
gcc (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
git checkout ce613c41372b23b1f51333815feb3edd87ef8a8b
./bootstrap-vcpkg.sh
export VCPKG_TOOLCHAIN_PATH=$(pwd)/scripts/buildsystems/vcpkg.cmake


# changes
1. attach with multiple databses and only scan thoses datanases. database=db1,db2...



