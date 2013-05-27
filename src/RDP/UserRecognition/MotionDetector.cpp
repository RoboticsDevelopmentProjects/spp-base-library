#include "MotionDetector.h"
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <iostream>

using namespace std;
using namespace boost::filesystem;

namespace nui{

MotionDetector::MotionDetector() 
{

}

void MotionDetector::loadFromMotionFiles(const string &dirpath){
    vector<path> fileVec;
    path dir(dirpath);
    directory_iterator end;

    if(exists(dir)){
        m_motions.clear();
        copy(directory_iterator(dir), directory_iterator(), back_inserter(fileVec));

        for(int i=0; i < (int)fileVec.size(); i++){
            path &p = fileVec[i];
            if(is_directory(p)){

            }else{
                string fleaf = p.filename().string();
                string ext = p.extension().string();

                if(ext == ".txt"){
                    Motion motion;
                    motion.loadFrom(p.filename().string());
                    m_motions.push_back(PoseManager(motion));
                }
            }
        }
    }
}

void MotionDetector::toDetect(const RDP::UserStatus &user, unsigned int elapsedTime){
    for(int i=0; i < m_motions.size(); i++){
    }
}

void MotionDetector::updateUsers(const std::vector<RDP::UserStatus> &users, unsigned int elapsedTime){

    for(int i=0; i < users.size(); i++){
        toDetect(users[i], elapsedTime);
    }

}

} //namespace nui
