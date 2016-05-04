/**
 * @author Jaskirat Mahal
 */

#include "audio_analyzer.h"
#include "aquila/transform/FftFactory.h"
#include <iostream>
#include "aquila/tools/TextPlot.h"


using namespace std;

namespace Aquila {

void AudioAnalyzer::FFT(WaveFile wav, Aquila::SpectrumType* spectrum) {
	
	const size_t SIZE = 32;

	auto fft = Aquila::FftFactory::getFft(SIZE);
	*spectrum = fft->fft(wav.toArray());

    // Aquila::TextPlot plot("Input signal");
    // plot.setTitle("Spectrum");
    // plot.plotSpectrum(*spectrum);	
}


}