## Note

 - still in development
 - only support linux now

## dependencies

```
# automation deps:
sudo apt install wget git gcc g++ make cmake qtdeclarative5-dev doxygen ninja-build

# manual deps:
# bazelisk

# post process
ldconfig
```

## compile

```
bazelisk build //:main
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
