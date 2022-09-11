project('image2ascii', 'c')

cmake = import('cmake')

subdir('src')

jpeg_static = cmake.subproject('libjpeg-turbo').dependency('jpeg-static')

executable(
    'main', 
    'main.c',
    sources,
    dependencies: [
        jpeg_static
    ]
)