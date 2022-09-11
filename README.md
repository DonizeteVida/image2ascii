# Setup environment

## Clone
``git clone --recurse-submodules https://github.com/DonizeteVida/image2ascii.git``

## Build

Install [Meson](https://mesonbuild.com/) \
Install [CMake](https://snapcraft.io/cmake)

``meson setup builddir`` \
``meson compile -C builddir`` \
``./builddir/main``