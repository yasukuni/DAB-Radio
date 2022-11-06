#pragma once

#include <stdint.h>
#include "../observable.h"

typedef int16_t viterbi_bit_t;

class ViterbiDecoder;
class AdditiveScrambler;

// Decodes the convolutionally encoded, scrambled and CRC16 group of FIGs
class FIC_Decoder 
{
private:
    ViterbiDecoder* vitdec;
    AdditiveScrambler* scrambler;
    uint8_t* decoded_bytes;

    const int nb_fibs_per_group;

    const int nb_encoded_bits;
    const int nb_decoded_bytes;
    const int nb_decoded_bits;

    // fib buffer, length of fib in bytes
    Observable<const uint8_t*, const int> obs_on_fib;
public:
    // number of bits in FIB (fast information block) group per CIF (common interleaved frame)
    FIC_Decoder(const int _nb_encoded_bits, const int _nb_fibs_per_group);
    ~FIC_Decoder();
    void DecodeFIBGroup(const viterbi_bit_t* encoded_bits, const int cif_index);
    auto& OnFIB(void) { return obs_on_fib; }
};