#include "CGL/CGL.h"
#include "CGL/viewer.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#define TINYEXR_IMPLEMENTATION
#include "CGL/tinyexr.h"
// typedef uint32_t gid_t;
#include <iostream>

// #include "svg.h"
// #include "drawrend.h"
// #include "transforms.h"
// #include "svgparser.h"

#include "aquila/source/WaveFile.h"
#include "audio_analyzer.h"

using namespace std;
using namespace CGL;

#define msg(s) cerr << "[Main] " << s << endl;

// int analyze(double* sample_data, Aquila::WaveFile wav, double time) {
//   const size_t SIZE = 64;

//   auto fft = Aquila::FftFactory::getFft(SIZE);
//   Aquila::SpectrumType spectrum = fft->fft(wav.toArray());

//   cout << "stuff" << endl;


//   return 0;
// }


int main( int argc, char** argv ) {

  if (argc != 2) {
    msg("Wrong number of arguments. Pass in 1 .wav file");
    return 0;
  }

  // file exist?
  struct stat st;

  if(stat(argv[1], &st) < 0 ) {
    msg("File does not exit: " << argv[1]);
    return 0;
  }

  //argv[1] is actually a .wav file
  std::string path_str(argv[1]);
  if (path_str.compare(path_str.length()-4,4,".wav") != 0 ){
    msg("Must input .wav file");
    return 0;
   }

  Aquila::WaveFile wav(argv[1]);
  cout << "Loaded file: " << wav.getFilename() << " (" << wav.getBitsPerSample() << "bits/sample)" << endl;
  // cout << "# of Channels: " << wav.getChannelsNum() << endl;
  // cout << "Sample Freq: " << wav.getBytesPerSec()/wav.getBytesPerSample() << endl;
  // cout << "Audio Length: " << wav.getAudioLength() << "ms" << endl;

  cout << Aquila::AudioAnalyzer::analyze(wav) << endl;




  // // create viewer
  // Viewer viewer = Viewer();

  // create application
  // DrawRend app(wav);

  // // set renderer
  // viewer.set_renderer(&app);

  // // init viewer
  // viewer.init();

  // // start viewer
  // viewer.start();

  exit(EXIT_SUCCESS);

  return 0;

}
