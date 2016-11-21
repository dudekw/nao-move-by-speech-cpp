// Import the RAPP Robot API
#include <rapp-robots-api/navigation/navigation.hpp>
#include <rapp-robots-api/localization/localization.hpp>
#include <rapp-robots-api/vision/vision.hpp>
#include <rapp-robots-api/communication/communication.hpp>
// Include string
#include <string>

// Create objects in order to call the desired functions
rapp::robot::navigation rapp_navigation;
rapp::robot::communication rapp_communication(0, NULL);
// Store current robot posture
std::string current_posture;


int main(int argc, char** argv){
    // Ask for instructions. The valid commands are "get up" and "sit"
    rapp_communication.text_to_speech("Hello there! What do you want me to do? I can sit or get up.");
    std::string res = rapp_communication.word_spotting({"sit","get up"});
    //if no word from the dictionary ({"sit","get up"}) was recognized:
    if (res == ""){
        rapp_communication.text_to_speech("Excuse me, I dont understand. Could you repeat? Evaliable words are:");
        rapp_communication.text_to_speech("sit");
        rapp_communication.text_to_speech("get up");
    }
    // Check which command was dictated by the human
    if (res == "sit"){
        // NAO sits with 75% of its maximum speed
        rapp_navigation.take_predefined_posture("Sit", 0.75);
        current_posture = "Sit";
    }
    if (res == "get up"){
        // NAO stands with 75% of its maximum speed
        rapp_navigation.take_predefined_posture("Stand", 0.75);
        current_posture = "Stand";
    }
    // Ask the human what movement to do: move the arms or the head?
    rapp_communication.text_to_speech("Do you want me to move my arms or my head?");

    res = rapp_communication.word_spotting({"arms", "head"});
    //if no word from the dictionary ({"arms", "head"}) was recognized:
    if (res == ""){
        rapp_communication.text_to_speech("Excuse me, I dont understand. Could you repeat? Evaliable words are:");
        rapp_communication.text_to_speech("arms");
        rapp_communication.text_to_speech("head");
    }
    // Check which command was dictated by the human
    if (res == "arms"){
        rapp_communication.text_to_speech("Do you want me to move the left or right arm?");
        res = rapp_communication.word_spotting({"left","right"});
        //if no word from the dictionary ({"arms", "head"}) was recognized:        
        if (res == ""){
            rapp_communication.text_to_speech("Excuse me, I dont understand. Could you repeat? Evaliable words are:");
            rapp_communication.text_to_speech("left");
            rapp_communication.text_to_speech("right");
        }
        // Check which command was dictated by the human
        if (res == "left")
            // Move left shoulder joint in pitch direction
            rapp_navigation.move_joint({"LShoulderPitch"}, {0}, 0.5);
        else if (res == "right")
            // Move right shoulder joint in pitch direction
            rapp_navigation.move_joint({"RShoulderPitch"}, {0}, 0.5);
        // return to the previous posture
        rapp_communication.text_to_speech("I will lower my arm now");
        rapp_navigation.take_predefined_posture(current_posture, 0.75);
    // Check which command was dictated by the human    
    }else if (res == "head"){
        rapp_communication.text_to_speech("Do you want me to turn my head left or right?");
        res = rapp_communication.word_spotting({"left","right"});
        //if no word from the dictionary ({"left","right"}) has  recognized:
        if (res == ""){
            rapp_communication.text_to_speech("Excuse me, I dont understand. Could you repeat? Evaliable words are:");
            rapp_communication.text_to_speech("left");
            rapp_communication.text_to_speech("right");
        }
        // The head moves by 0.4 rads left or right with 50% of its maximum speed
        if (res == "left")
            rapp_navigation.move_joint({"HeadYaw"}, {0.4f}, 0.5);
        else if (res == "right")
            rapp_navigation.move_joint({"HeadYaw"}, {-0.4f}, 0.5);
        // move head to init position 
        rapp_communication.text_to_speech("I will look straight now");
        rapp_navigation.move_joint({"HeadYaw"}, {0}, 0.5);
    }
    // sit down and rest
    rapp_communication.text_to_speech("And now I will sit down and sleep!");
    rapp_navigation.rest("Sit");
}