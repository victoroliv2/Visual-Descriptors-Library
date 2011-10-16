# includes

cdef extern from "bic.h":

    void bic_extract (unsigned char *image, int w, int h, double *d)
    double bic_distance (double *d1, double *d2)
