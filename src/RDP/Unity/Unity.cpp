#include "Unity.h"
#include <std_msgs/Empty.h>
#include <iostream>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>

Unity::Unity(int argc, char *argv[]){
    ros::init(argc, argv, "Unity");
    
    m_node = boost::shared_ptr<ros::NodeHandle>(new ros::NodeHandle());
    
    m_speechRecog = boost::shared_ptr<nui::SpeechRecognitionClient>(new nui::SpeechRecognitionClient(*m_node));
    m_speechRecog->setResultCallback(boost::bind(&Unity::speechRetCb, this, boost::lambda::_1));
        
    m_userRecog = boost::shared_ptr<nui::UserRecognitionClient>(new nui::UserRecognitionClient(*m_node));
    m_userRecog->setDetectMotionCb(boost::bind(&Unity::detectMotionCb, this, boost::lambda::_1));

    m_cmd = boost::shared_ptr<spp::CommandSenderClient>(new spp::CommandSenderClient(*m_node));
}

void Unity::speechRetCb(const std_msgs::StringConstPtr &ret){
    std::cout << "speechRetCb = " << ret->data << std::endl;
}

void Unity::detectMotionCb(const RDP::DetectMotionConstPtr &motion){
    std::cout << "detectMotionCb = " << motion->id << std::endl;
    for(int i=0; i < m_detectMotionId.size(); i++){
        if(m_detectMotionId[i] == motion->id) return;
    }

    m_detectMotionId.push_back(motion->id);
}

void Unity::startSpeechRecognition(){
    m_speechRecog->startRecognition();
}

void Unity::lcdPuts(const std::string &str){
    m_cmd->lcdPuts(str);
}

void Unity::lcdClear(){
    m_cmd->lcdClear();
}

void Unity::motor(int rDuty, int lDuty){
    m_cmd->motor(rDuty, lDuty);
}

void Unity::statusUpdate(){
    ros::spinOnce();
    sleep(1);
}

