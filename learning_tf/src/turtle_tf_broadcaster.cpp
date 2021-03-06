/*
 * turtle_tf_broadcaster.cpp
 *
 *  Created on: Aug 7, 2014
 *      Author: exbot
 */
#include<ros/ros.h>
#include<tf/transform_broadcaster.h>
#include<turtlesim/Pose.h>

std::string turtle_name;

void poseCallback(const turtlesim::PoseConstPtr& msg)
{
    static tf::TransformBroadcaster br;
    //创建了一个Transform对象，
//复制这个turtle图形的2D位置并转换为3D位置，添加了一个z系，但是设为0.0
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(msg->x,msg->y,0.0));
    tf::Quaternion q;
//设置方位
    q.setRPY(0,0,msg->theta);
    transform.setRotation(q);

    br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"world",turtle_name));
    //通过TransformBroadcaster来发布信息需要四个参数:
//1.首先需要transform
//2.需要给transform一个时间戳，这个时间戳是现在的时间
//3.将我们创建的父框架的名字传输过去，在这个例子中是world
//4.将我们创建的子框架的名字传输过去，在这里就是turtle本身

}

int main(int argc,char** argv){
   ros::init(argc,argv,"my_tf_broadcaster");
   if(argc != 2){
     ROS_ERROR("need turtle name as argument");
     return -1;

   }
   turtle_name = argv[1];
   ros::NodeHandle node;
////从master订阅某乌龟的“/pose”话题，当消息到来时，即当乌龟位置改变时产生新的消息时，ROS将会调用poseCallback 
   ros::Subscriber sub =node.subscribe(turtle_name+"/pose",10,&poseCallback);
   ros::spin();
   return 0;
};


