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

using namespace std;
using namespace CGL;

#define msg(s) cerr << "[Main] " << s << endl;


// SVG *loadFile( const char* path ) {

//   SVG* svg = new SVG();

//   if( SVGParser::load( path, svg ) < 0) {
//     delete svg;
//     return NULL;
//   }
  
//   return svg;
// }

// vector<SVG*> loadDirectory( const char* path ) {

//   DIR *dir = opendir (path);
//   vector<SVG*> svgs;
//   if(dir) {
    
//     struct dirent *ent; size_t n = 0;
    
//     // load files
//     string pathname = path; 
//     if (pathname[pathname.size()-1] != '/') pathname.push_back('/');
//     while (((ent = readdir (dir)) != NULL) && (n < 9)) {

//       string filename = ent->d_name;
//       string filesufx = filename.substr(filename.find_last_of(".") + 1, 3);
//       if (filesufx == "svg" ) {
//         cerr << "[Drawer] Loading " << filename << "... "; 
//         SVG *svg = loadFile((pathname + filename).c_str());
//         if (!svg) {
//           cerr << "Failed (Invalid SVG file)" << endl;
//         } else {
//           cerr << "Succeeded" << endl;
//           svgs.push_back(svg);
//           n++;
//         }
//       }
//     }

//     closedir (dir);

//     if (n) {
//       msg("Successfully Loaded " << n << " files from " << path);
//       return svgs;
//     }

//     msg("No valid svg files found in " << path);
//     return svgs;
//   } 

//   msg("Could not open directory" << path);
//   return svgs;
// }

// vector<SVG*> loadPath( const char* path ) {

//   struct stat st;

//   // file exist?
//   if(stat(path, &st) < 0 ) {
//     msg("File does not exit: " << path);
//     return vector<SVG*>();
//   }

//   // load directory
//   if( st.st_mode & S_IFDIR ) {
//     return loadDirectory(path);
//   } 

//   // load file
//   if( st.st_mode & S_IFREG ) {
//     return vector<SVG*>(1,loadFile(path));
//   }

//   msg("Invalid path: " << path);
//   return vector<SVG*>();
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

  if (path_str.compare(path_str.length()-4,4,".wav") == 0 ){
       cout << "YES" << endl;
   } else {
       msg("Must input .wav file");
       return 0;
   }

  Aquila::WaveFile wav(argv[1]);




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
