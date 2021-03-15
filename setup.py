#!/usr/bin/env python

from distutils.core import setup
from distutils.core import Extension

setup(name='hidraw',
      version='0.2',
      description='Gathers Linux hidraw information',
      author='Danny Milosavljevic',
      author_email='dannym@friendly-machines.at',
      url='hutp://www.scratchpost.org/',
      packages=['hidraw'],
      ext_modules=[Extension('hidraw._hidraw', ['hidraw/hidrawmodule.c'])]
     )
