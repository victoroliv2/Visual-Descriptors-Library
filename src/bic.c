#include "bic.h"

static inline int bin (unsigned char v)
{
  int i, b;
  unsigned char bin [BIN+1] = { 0, 64, 128, 192, 255 };

  for (b=0; b < BIN; b++)
    if (v >= bin[b] && v <= bin[b+1])
      {
        i = b;
        break;
      }

  return i;
}

static inline int bin_rgb (unsigned char *v)
{
  int r_bin, g_bin, b_bin;

  r_bin = bin(v[0]);
  g_bin = bin(v[1]);
  b_bin = bin(v[2]);

  return (r_bin << 4) + (g_bin << 2) + (b_bin << 0);
}

void bic_extract (unsigned char *image, int w, int h, double *d)
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
      d[b]      = (hist_low[b]  * 255.0) / (w*h);
      d[b+BINS] = (hist_high[b] * 255.0) / (w*h);
    }
}

static inline double func (double k)
{
  if      (k == 0.0)   return 0.0;
  else if (k <= 1.0)   return 1.0;
  /* [log2(x)]+1 */
  else if (k <= 2.0)   return 2.0;
  else if (k <= 4.0)   return 3.0;
  else if (k <= 8.0)   return 4.0;
  else if (k <= 16.0)  return 5.0;
  else if (k <= 32.0)  return 6.0;
  else if (k <= 64.0)  return 7.0;
  else if (k <= 128.0) return 8.0;
  else                 return 9.0;
}

double bic_distance (double *d1, double *d2)
{
  int b;
  int sum = 0;

  for (b=0; b < BINS; b++)
    {
      int k = func (d1[b]) - func (d2[b]);
      sum += (k < 0.0)? -k : k;
    }

  return sum;
}
