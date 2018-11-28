This repository contains an example of a protoc plugin written in C++.

This example plugin generates text files that list the messages defined in proto files.

To build the plugin you will need to have a compiler (such as clang++) locally installed.

1. Install Google Protobuf from source by following [the instructions here](https://github.com/protocolbuffers/protobuf/blob/master/src/README.md).

   You should know the locations where header files, libprotoc and libprotobuf got installed.


2. Clone this repository:

```
git clone http://github.com/thesamet/protoc-plugin-in-cpp

cd protoc-plugin-in-cpp
```

3. Build the plugin

```
clang++ my_protoc_plugin.cc -o my_protoc_plugin  -lprotoc -lprotobuf
```

(pass `-I` and `-L` as necessary to point at the external include files and
libraries)

4. Try it out!

```
protoc --plugin=protoc-gen-example=my_protoc_plugin  \              
       protos/a.proto protos/b.proto -I protos \
       --example_out=protos
```
