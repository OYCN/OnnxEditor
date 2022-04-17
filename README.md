## Note

 - still in development
 - only support linux now
 - using cmake is experimental

## dependencies

```
# automation deps:
sudo apt install wget git gcc g++ make cmake qtdeclarative5-dev doxygen ninja-build

# if using cmake, you need protobuf

# manual deps if using bazel:
# bazelisk

# post process
ldconfig
```

## compile

### by bazel

```
bazelisk build //:main
```

### by cmake

```
mkdir build
cd build
# using Ninja
cmake .. -G Ninja
ninja
# also you can using Makefile
cmake ..
make
```

## TODO LIST

- [ ] About Gui
  - [ ] Display attrs on Node
  - [ ] Display shapes on Edge
  - [ ] Using the best layout method
  - [ ] Gen the best curve
- [ ] Design the editor widget about node and edge
  - [ ] Edit the node
    - [ ] Node name
    - [ ] Node attrs
    - [ ] Node io
  - [ ] Edit the edge
  - [ ] Edit Initializers
- [ ] Support to save onnx
- [ ] Project
  - [ ] Support Win
  - [ ] Support MacOS
