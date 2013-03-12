#ifndef CONTINUOUS_H
#define CONTINUOUS_H

#include <sphinxbase/ad.h>
#include <sphinxbase/cont_ad.h>

#include <pocketsphinx.h>

typedef struct {
    ps_decoder_t *ps;
    ad_rec_t *ad;
    cont_ad_t *cont;
} mic_recognizer_t;

#endif // CONTINUOUS_H