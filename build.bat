pushd %dp0
cmake --preset Win64
cmake --build --preset Win64 --target install
popd
