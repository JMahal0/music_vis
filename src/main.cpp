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
#include "visualization.h"
#include "drawrend.h"
#include "CGL/color.h"

using namespace std;
using namespace CGL;

#define msg(s) cerr << "[Main] " << s << endl;

void monoFile(Aquila::WaveFile wav) {
  Aquila::SpectrumType m_data;
  Aquila::AudioAnalyzer::FFT(wav, &m_data);

  CGL::Visualization vis = CGL::Visualization(Color::fromHex("faff3d"), Color::fromHex("beff00"),
                        Color::fromHex("ff8c1a"), Color::fromHex("ff2d14"),
                        Color::fromHex("b3ffff"), Color::fromHex("80ffbf"));

  CGL::DrawRend renderer = CGL::DrawRend(640, 480);


  for (int i = 0; i < m_data.size(); ++i) {
    
    double intensity = sqrt(m_data[i].real()*m_data[i].real() + m_data[i].imag()*m_data[i].imag());


  }


}

void stereoFile(Aquila::WaveFile wav_left, Aquila::WaveFile wav_right) {
  Aquila::SpectrumType m_data_left;
  Aquila::SpectrumType m_data_right;
  Aquila::AudioAnalyzer::FFT(wav_left, &m_data_left);
  Aquila::AudioAnalyzer::FFT(wav_right, &m_data_right);

  // double pow_left = Aquila::power(wav_left);
  // double pow_right = Aquila::power(wav_right);

  // cout << "Left mean" << Aquila::mean(wav_left) << endl;  
  // cout << "Right mean" << Aquila::mean(wav_right) << endl;

  // cout << "Left energy" << Aquila::energy(wav_left) << endl;  
  // cout << "Right energy" << Aquila::energy(wav_right) << endl;

  // cout << "Left RMS" << Aquila::rms(wav_left) << endl;  
  // cout << "Right RMS" << Aquila::rms(wav_right) << endl;

  // cout << "Left pow" << pow_left << endl;  
  // cout << "Right pow" << pow_right << endl;

  CGL::Visualization vis = CGL::Visualization(Color::fromHex("faff3d"), Color::fromHex("beff00"),
                        Color::fromHex("ff8c1a"), Color::fromHex("ff2d14"),
                        Color::fromHex("b3ffff"), Color::fromHex("80ffbf"));

  CGL::DrawRend renderer = CGL::DrawRend(640, 480);

  int length = m_data_left.size();

  double avg_left = 0;
  double avg_right = 0;

    for (int i = 0; i < length; ++i) {
    
    avg_left += sqrt(m_data_left[i].real()*m_data_left[i].real() + m_data_left[i].imag()*m_data_left[i].imag());
    
    avg_right += sqrt(m_data_right[i].real()*m_data_right[i].real() + m_data_right[i].imag()*m_data_right[i].imag());

    // printf("Int L %f R %f\n", intensity_left/Aquila::rms(wav_left), intensity_right/Aquila::rms(wav_right));
  }
  avg_left /= length;
  avg_right /= length;

  for (int i = 0; i < length; ++i) {

    if (i != 0) {
      // return;
    }
    // cout << i << endl;
    vis.vshapes.clear(); // temp
    // cout << "ere" << endl;
    
    vis.visualizeStereo(m_data_left[i], m_data_right[i], i, length, avg_left, avg_right);
    // cout << "iri" << endl;
    

    renderer.write_frame_shot(i, &(vis.vshapes));
    // cout << "[main]Seg fault before this" << endl;
    

  }

}


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
  cout << "# of Channels: " << wav.getChannelsNum() << endl;
  if (wav.isStereo()) {
    Aquila::WaveFile wav_right(argv[1], Aquila::StereoChannel::RIGHT);
    stereoFile(wav, wav_right);
    // cout << "stereoFile" << endl;
  } else {
    monoFile(wav);
  }


  // cout << "Loaded file: " << wav.getFilename() << " (" << wav.getBitsPerSample() << "bits/sample)" << endl;

  // cout << "Sample Freq: " << wav.getBytesPerSec()/wav.getBytesPerSample() << endl;
  // cout << "Audio Length: " << wav.getAudioLength() << "ms" << endl;

  // for (int i = 0; i < m_data.size(); ++i) {
    
  //   // printf("Real %f, Imaginary %f\n", m_data[i].real(), m_data[i].imag());
  //   double intensity = sqrt(m_data[i].real()*m_data[i].real() + m_data[i].imag()*m_data[i].imag());
  //   // printf("Int %f\t", intensity);
  // }



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
