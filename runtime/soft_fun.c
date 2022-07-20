/*Copyright [2022-07-17] <wumeng>*/
#include <stdio.h>
#include <stdlib.h>
#include "soft_fun.h"

int average_pooling(int *img, int *out, int Nif, int Nir, int Nic) {
  int outH = (Nir + 2 * padY - KR) / SR + 1;
  int outW = (Nic + 2 * padX - KC) / SC + 1;
  printf("input: channel:%d\theight:%d\twidth:%d\t\n", Nif, Nir, Nic);
  for (int i = 0; i < Nir; i++) {
    for (int j = 0; j < Nic; j++) {
      for (int l = 0; l < Nif; l++) {
        printf("input: %d\t", *(img + i * Nif * Nic + j * Nif + l));
      }
    }
  }
  printf("\n");
  for (int i = 0; i < outH; i++) {
    for (int j = 0; j < outW; j++) {
      for (int l = 0; l < Nif; l++) {
        *(out + i * Nif * outW + j * Nif + l) = 0;
      }
    }
  }
  int nor = 0;
  for (int r = 0; r < (Nir + 2 * padY); r += SR) {
    int noc = 0;
    for (int c = 0; c < (Nic + 2 * padX); c += SC) {
      int *value = (int *)malloc(Nif * sizeof(int));
      for (int v = 0; v < Nif; v++) {
        value[v] = 0;
      }
      for (int kr = 0; kr < KR; kr++) {
        for (int kc = 0; kc < KC; kc++) {
          for (int j = 0; j < Nif; j++) {
            int xr = r + kr - padY;
            int xc = c + kc - padX;
            value[j] += 0;
            if ((kc + noc * SC - padX) > -1 && (kr + nor * SR - padY) > -1 &&
            (kc + noc * SC - padX) <= Nic && (kr + nor * SR - padY)
             <= Nir && xr < Nir && xc < Nic)
              value[j] += *(img + xr * Nif * Nic + xc * Nif + j);
          }
        }
      }
      for (int m = 0; m < Nif; m++) {
        if (nor < outH && noc < outW) {
          *(out + nor * Nif * outW + noc * Nif + m) = value[m] / KR / KC;
        }
      }
      noc += 1;
      if (noc >= outW) {
        break;
      }
    }
    nor += 1;
    if (nor >= outH) {
      break;
    }
  }
  printf("output: channel:%d\theight:%d\twidth:%d\t\n", Nif, outH, outW);
  for (int i = 0; i < outH; i++) {
    for (int j = 0; j < outW; j++) {
      for (int l = 0; l < Nif; l++) {
        printf("output:%d\t", *(out + i * Nif * outW + j * Nif + l));
      }
    }
  }
  printf("\n");
  return 0;
}
