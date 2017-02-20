#!/usr/bin/python3

# ==============================================================================
# BEGIN template
# ==============================================================================
import sys
import time
import re
import pprint
import random

def dbg(x,y=None):
  if y is None: dbgout = pprint.pformat(x)
  else: dbgout = x+' = '+pprint.pformat(y)
  sys.stderr.write('>>> '+dbgout+'\n')
  sys.stderr.flush()

oo = 0x3f3f3f3f3f3f3f3f
# ==============================================================================
# END template
# ==============================================================================

def main():
  dbg('hello python')

main()
