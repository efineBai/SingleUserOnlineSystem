{
  "targets": [

    {
      "target_name": "libsingleuser",
      "type": "shared_library",
      "dependencies": [
        "deps/djinni/support-lib/support_lib.gyp:djinni_jni",
        "deps/grpc/grpc.gyp:grpc++"
      ],
      "ldflags" : [ "-llog", "-Wl,--build-id,-Wno-unused-parameter,--gc-sections,--exclude-libs,ALL" ],
      "sources": [
        "./deps/djinni/support-lib/jni/djinni_main.cpp",
        "<!@(python deps/djinni/example/glob.py generated-src/jni   '*.cpp')",
        "<!@(python deps/djinni/example/glob.py generated-src/cpp   '*.cpp')",
        "<!@(python deps/djinni/example/glob.py SingleUserOnlineClient '*.cpp')"
      ],
      "include_dirs": [
        "generated-src/jni",
        "generated-src/cpp",
        "SingleUserOnlineClient",
        "generated-src/",
        "deps/include",
        "deps/grpc/include"

      ],
    },
  ],
}