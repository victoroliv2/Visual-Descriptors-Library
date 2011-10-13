#include "bic.h"

static inline int bin (double k)
{
  int i, b;
  unsigned char v = k * 255; /* k \in [0,1] */
  unsigned char bin [BIN+1] = { 0, 64, 128, 192, 255 };

  for (b=0; b < BIN; b++)
    if (v >= bin[b] && v <= bin[b+1])
      {
        i = b;
        break;
      }

  return i;
}

static inline int bin_rgb (double *v)
{
  int r_bin, g_bin, b_bin;

  r_bin = bin(v[0]);
  g_bin = bin(v[1]);
  b_bin = bin(v[2]);

  return (r_bin << 4) + (g_bin << 2) + (b_bin << 0);
}

void bic_extract (double *image, int w, int h, struct bic_t *d)
{
  int b, i, j;
  const int rw = 3*w; /* R G B */

  int hist_low  [BINS];
  int hist_high [BINS];

  for (b=0; b < BINS; b++)
    {
      hist_low[b]  = 0;
      hist_high[b] = 0;
    }

  for (i=0; i < h; i++)
    for (j=0; j < rw; j+=3)
      {
        int v = bin_rgb( &image[i*rw+j] );

        if (i == 0 || i == h-1 || j == 0 || j == rw-3) /* border */
          {
            hist_low[v]++;
          }
        else
          {
            if (v == bin_rgb( &image[(i-1)*rw+ j   ] ) &&
                v == bin_rgb( &image[(i+1)*rw+ j   ] ) &&
                v == bin_rgb( &image[ i   *rw+(j-3)] ) &&
                v == bin_rgb( &image[ i   *rw+(j+3)] ))
              {
                hist_low[v]++;
              }
            else
              {
                hist_high[v]++;
              }
          }
      }

  for (b=0; b < BINS; b++)
    {
      d->hist_low[b]  = (hist_low[b]  * 255) / (w*h);
      d->hist_high[b] = (hist_high[b] * 255) / (w*h);
    }
}

static inline int func (unsigned char k)
{
  if      (k == 0)   return 0;
  else if (k == 1)   return 1;
  /* [log2(x)]+1 */
  else if (k == 2)   return 2;
  else if (k <= 4)   return 3;
  else if (k <= 8)   return 4;
  else if (k <= 16)  return 5;
  else if (k <= 32)  return 6;
  else if (k <= 64)  return 7;
  else if (k <= 128) return 8;
  else               return 9;
}

int bic_distance (struct bic_t *d1, struct bic_t *d2)
{
  int b;
  int sum = 0;

  for (b=0; b < BINS; b++)
    {
      int k = func (d1->hist_low[b]) - func (d2->hist_low[b]);
      sum += (k < 0)? -k : k;
    }

  for (b=0; b < BINS; b++)
    {
      int k = func (d1->hist_high[b]) - func (d2->hist_high[b]);
      sum += (k < 0)? -k : k;
    }

  return sum;
}
