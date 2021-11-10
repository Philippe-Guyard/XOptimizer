#include "interaction_service.h"
#include "utils/downloader/downloader.cpp"


// istream constructor
#include <iostream>     // std::ios, std::istream, std::cout
#include <fstream>      // std::filebuf

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

namespace XOptimiser::interaction_service{
//DOWNLOAD FUNCTIONS
bool is_downloader_data_valid(){
    //Check that region exists:

    //Check that department exists

    //Check that filename is valid.

    };

//IF TRUE ALLOWED TO CALL DOWNLOAD ELSE ERROR.

//PARSE FUNCTIONS

void interaction_service::interaction_service::Download_Parse(){
    //DOWNLOAD
    bool validdowndata;
    Downloader D = Downloader();

    D.download(Region,Department,"map.pbf");

    //if (success == true);


    //Parse: convert pbf file
    std::filebuf map;
      if (map.open ("map.pbf",std::ios::in))
      {
        std::istream is(&map);

        while (is)  {
           std::shared_ptr<std::istream> inputStream;
           inputStream = std::make_shared<std::istream>(&is);


           PBFParser parsingfile = PBFParser(inputStream);
        }

        std::shared_ptr<std::istream> GraphInputStream = parsingfile.getInputStream() const;

        map.close();
      }




};

};






