#pragma once

#include <string>
//#include <RDP/UserJoint.h>
#include <RDP/UserPose.h>
#include <vector>
#include <map>

namespace nui{

typedef std::map<unsigned int, RDP::UserPose> PoseTable;

class Motion
{
	PoseTable m_poses;
	unsigned int m_motionId;
	bool poseIsExist(unsigned int poseId){ return m_poses.find(poseId) != m_poses.end(); }

public:
	static const int MAX_JOINT_NUM = 15;
	Motion();
	bool saveAs(const std::string &file);
	bool loadFrom(const std::string &file);
	bool setPose(unsigned int poseId, const RDP::UserPose &pose);
	//const RDP::UserPose& pose(unsigned int poseId);
	bool pose(unsigned int poseId, RDP::UserPose &pose);
	bool addPose(unsigned int poseId,const RDP::UserPose &pose);
	bool erasePose(unsigned int poseId);
	unsigned int id(){ return m_motionId; }

};

} //namespace nui

