/* Author: Victor M. de Araujo Oliveira 
   This is the implementation of the visual descriptor
   presented in "A Compact and Efficient Image Retrieval Approach Based
   on Border/Interior Pixel Classification" by Stehling et al.
*/

#ifndef __BIC_H__
#define __BIC_H__

#define BIN 4

#define BINS (BIN*BIN*BIN)

void bic_extract (unsigned char *image, int w, int h, double *d);
double bic_distance (double *d1, double *d2);

#endif
