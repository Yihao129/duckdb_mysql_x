# duckdb v1.4.2 (v1.4-andium)

https://github.com/duckdb/duckdb-mysql/tree/v1.4-andium

## Compile Environment

Works in Google Colab:

```
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
```

### vcpkg Setup

```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
git checkout ce613c41372b23b1f51333815feb3edd87ef8a8b
./bootstrap-vcpkg.sh
export VCPKG_TOOLCHAIN_PATH=$(pwd)/scripts/buildsystems/vcpkg.cmake
```

### Dependencies

```bash
sudo apt-get update
sudo apt-get install -y \
  ninja-build \
  cmake \
  build-essential \
  make \
  ccache \
  curl \
  zip \
  unzip \
  tar \
  pkg-config \
  autoconf \
  autoconf-archive \
  mariadb-server
```

## Changes

- Attach with multiple databases and only scan those databases: `database=db1,db2,...`

## Build Steps

1. Pull code:
   ```bash
   cd /content/duckdb_mysql_x/ && git pull && rm -rf /content/duckdb-mysql/src/ && cp -r /content/duckdb_mysql_x/src/ /content/duckdb-mysql/ && cd /content/duckdb-mysql/
   ```

2. Load the extension:
   ```sql
   LOAD '/content/duckdb-mysql/build/release/extension/mysql_scanner/mysql_scanner.duckdb_extension';
   ```

3. Build:
   ```bash
   GEN=ninja make
   ```
