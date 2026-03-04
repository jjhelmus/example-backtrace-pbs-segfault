## Setup

```
uv venv --python 3.14 --managed-python --seed
source .venv/bin/activate
python -m pip install .
```

## Run

```
python bug.py
```

## Results from gdb

```
gdb python
...
(gdb) set args bug.py
(gdb) run
...
In boom

Program received signal SIGSEGV, Segmentation fault.
0x00007ffff7bf3a10 in ?? () from /lib/x86_64-linux-gnu/libgcc_s.so.1
(gdb) bt
#0  0x00007ffff7bf3a10 in ?? () from /lib/x86_64-linux-gnu/libgcc_s.so.1
#1  0x00007ffff7bf591e in _Unwind_Backtrace () from /lib/x86_64-linux-gnu/libgcc_s.so.1
#2  0x00007ffff7d35eb3 in __GI___backtrace (array=array@entry=0x7fffffffd3e0, size=size@entry=50) at ./debug/backtrace.c:78
#3  0x00007ffff7fac297 in boom () at example_module.c:10
#4  0x00007ffff7fac2ef in Thing_inplace_or (self=0x7ffff7519b30, other=<optimized out>) at example_module.c:34
#5  0x0000000001ada8a2 in PyNumber_InPlaceOr.warm ()
#6  0x0000000000000014 in ?? ()
#7  0x0000000000000014 in ?? ()
#8  0x00007ffff7408e30 in ?? ()
#9  0x00007ffff7519b30 in ?? ()
#10 0x00007ffff7fb0020 in ?? ()
#11 0x0000000001801394 in _TAIL_CALL_BINARY_OP.llvm.10362591704542007599 ()
#12 0x00000000018890ed in _PyEval_Vector ()
#13 0x0000000001888de7 in PyEval_EvalCode ()
#14 0x00000000018e4c73 in run_mod.llvm ()
#15 0x0000000001a3b9c7 in pyrun_file ()
#16 0x0000000001a3979b in _PyRun_SimpleFileObject ()
#17 0x0000000001a39682 in _PyRun_AnyFileObject ()
#18 0x0000000001a391f6 in pymain_run_file_obj ()
#19 0x0000000001a390f4 in pymain_run_file ()
#20 0x00000000019b0f91 in Py_RunMain ()
#21 0x00000000019ae9c3 in pymain_main.llvm ()
#22 0x00000000019ae7ad in main ()
```







