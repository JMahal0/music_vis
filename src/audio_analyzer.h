/**
 * @author Jaskirat Mahal
 * Handles most of the communication with the Aquila library
 */

#include "aquila/source/WaveFile.h"

namespace Aquila {

class AudioAnalyzer {
 public:
 	static void FFT(WaveFile wav, Aquila::SpectrumType* spectrum);

};

}
