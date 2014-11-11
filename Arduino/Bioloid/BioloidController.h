/*
  BioloidController.h - arbotiX Library for Bioloid Pose Engine
  Copyright (c) 2008,2009 Michael E. Ferguson.  All right reserved.
*/

#ifndef BioloidController_h
#define BioloidController_h

/* poses:
 *  PROGMEM prog_uint16_t name[ ] = {4,512,512,482,542}; // first number is # of servos
 * sequences:
 *  PROGMEM transition_t name[] = {{NULL,count},{pose_name,1000},...} 
 */

#include "ax12.h"

/* pose engine runs at 30Hz (33ms between frames) 
   recommended values for interpolateSetup are of the form X*BIOLOID_FRAME_LENGTH - 1 */
#define BIOLOID_FRAME_LENGTH      33
/* we need some extra resolution, use 13 bits, rather than 10, during interpolation */
#define BIOLOID_SHIFT             3

/** a structure to hold transitions **/
typedef struct{
    unsigned int * pose;    // addr of pose to transition to 
    int time;               // time for transition
} transition_t; 

/** Bioloid Controller Class for mega324p/644p clients. **/
class BioloidController
{
  public:
    /* YOU SHOULD NOT USE Serial1 */
    BioloidController(long baud);               // baud usually 1000000

    /* Pose Manipulation */
    void loadPose( const unsigned int * addr ); // load a named pose from FLASH  
    void readPose();                            // read a pose in from the servos  
    void writePose();                           // write a pose out to the servos
    int getCurPose(int id);                     // get a servo value in the current pose
    int getNextPose(int id);                    // get a servo value in the next pose
    void setNextPose(int id, int pos);          // set a servo value in the next pose
    
    /* Pose Engine */
    void interpolateSetup(int time);            // calculate speeds for smooth transition
    void interpolateStep();                     // move forward one step in current interpolation  
    unsigned char interpolating;                // are we in an interpolation? 0=No, 1=Yes
    unsigned char runningSeq;                   // are we running a sequence? 0=No, 1=Yes 
    int poseSize;                               // how many servos are in this pose, used by Sync()

    /* to interpolate:
     *  bioloid.loadPose(myPose);
     *  bioloid.interpolateSetup(67);
     *  while(bioloid.interpolating > 0){
     *      bioloid.interpolateStep();
     *      delay(1);
     *  }
     */

    /* Sequence Engine */
    void playSeq( const transition_t * addr );  // load a sequence and play it from FLASH
    void play();                                // keep moving forward in time
    unsigned char playing;                      // are we playing a sequence? 0=No, 1=Yes

    /* to run the sequence engine:
     *  bioloid.playSeq(walk);
     *  while(bioloid.playing){
     *      bioloid.play();
     *  }
     */
    
  private:  
    unsigned int pose[AX12_MAX_SERVOS];         // the current pose, updated by Step(), set out by Sync()
    unsigned int nextpose[AX12_MAX_SERVOS];     // the destination pose, where we put on load
    int speed[AX12_MAX_SERVOS];                 // speeds for interpolation 

    unsigned long lastframe;                    // time last frame was sent out  
    
    transition_t * sequence;                    // sequence we are running
    int transitions;                            // how many transitions we have left to load
   
};
#endif
