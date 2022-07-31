export TVM_HOME=/work/sabre/tvm
export PYTHONPATH=$TVM_HOME/python:${PYTHONPATH}
export TVM_LIBRARY_PATH=$TVM_HOME/build_ninja
alias tvmc='python3 -m tvm.driver.tvmc'
