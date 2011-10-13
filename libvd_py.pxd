# includes

cdef extern from "bic.h":

    cdef struct bic_t:
      pass

    void bic_extract (double *image, int w, int h, bic_t *d)
    int bic_distance (bic_t *d1, bic_t *d2)
