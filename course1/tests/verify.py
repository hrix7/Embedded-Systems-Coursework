#!/usr/bin/env python3
"""Build-switch checks plus independent C tests with ASan/UBSan."""
import os
from pathlib import Path
import subprocess
import tempfile
p=Path(__file__).resolve().parents[1]
def run(args, **kwargs):
    r=subprocess.run(args, cwd=p, text=True, capture_output=True, **kwargs)
    print(r.stdout, end='')
    if r.returncode:
        print(r.stderr)
        raise SystemExit(r.returncode)
    return r.stdout
run(['make','clean'])
for verbose in (1,0):
    run(['make','build','PLATFORM=HOST',f'VERBOSE={verbose}'])
    out=run(['./src/course1.out'])
    assert 'PASSED: 8 / 8' in out
    assert ('0 1 2 3 4 5 6 7' in out) == bool(verbose)
run(['make','build','PLATFORM=HOST','COURSE1=0'])
assert run(['./src/course1.out']) == ''
run(['make','build','PLATFORM=HOST','COURSE1=1'])
assert 'PASSED: 8 / 8' in run(['./src/course1.out'])
with tempfile.TemporaryDirectory() as d:
    exe=str(Path(d)/'edge')
    run(['gcc','-std=c99','-Wall','-Wextra','-Werror','-g','-O1',
         '-fsanitize=address,undefined','-fno-omit-frame-pointer','-no-pie',
         '-DHOST','-Iinclude/common','tests/edge_cases.c',
         'src/memory.c','src/data.c','src/stats.c','-o',exe])
    run([exe],env=dict(os.environ,ASAN_OPTIONS='detect_leaks=0',UBSAN_OPTIONS='halt_on_error=1'))
print('PASS: VERBOSE and COURSE1 switches, including rebuilds without cleaning.')
