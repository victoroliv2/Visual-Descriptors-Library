# code

cimport libvd_py
import numpy as np
cimport numpy as np

cdef class BIC:
  cdef libvd_py.bic_t desc

  def __cinit__ (self, np.ndarray[np.float64_t, ndim=2, mode='c'] img):
    bic_extract (<double*>img.data, <int>img.shape[1], <int>img.shape[0], &(self.desc))

  def distance (self, BIC desc2):
    return bic_distance (&(self.desc), &(desc2.desc))
