/* Author: Victor M. de Araujo Oliveira 
   This is the implementation of the visual descriptor
   presented in "A Compact and Efficient Image Retrieval Approach Based
   on Border/Interior Pixel Classification" by Stehling et al.
*/

#ifndef __BIC_H__
#define __BIC_H__

#define BIN 4

#define BINS (BIN*BIN*BIN)

struct bic_t
{
  unsigned char hist_low  [BINS];
  unsigned char hist_high [BINS];
};

void bic_extract (double *image, int w, int h, struct bic_t *d);
int bic_distance (struct bic_t *d1, struct bic_t *d2);

#endif
