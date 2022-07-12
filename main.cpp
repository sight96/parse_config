
#include "./inc/paesr_config.h"
#include "Myffmpeg/Myffmpeg.h"



int main()
{
  
    Utils utils;
    CMyffmpeg myffmpeg;
    string filename = "setup.config";

    ConfigParser configParser;

    configParser.ParseConfig(filename);

    std::string itemCfgStr = "streamPath";
    configParser.GetStringValue(itemCfgStr, myffmpeg.setParam.streamPath);
    itemCfgStr = "omModelPath";
    configParser.GetStringValue(itemCfgStr, myffmpeg.setParam.omModelPath);
    itemCfgStr = "max_cosine_distance";
    configParser.GetFloatValue(itemCfgStr, myffmpeg.setParam.max_cosine_distance);
    itemCfgStr = "max_iou_distance";
    configParser.GetFloatValue(itemCfgStr, myffmpeg.setParam.max_iou_distance);
    itemCfgStr = "max_age";
    configParser.GetIntValue(itemCfgStr, myffmpeg.setParam.max_age);
    itemCfgStr = "max_dist";
    configParser.GetIntValue(itemCfgStr, myffmpeg.setParam.max_dist);
    itemCfgStr = "n_init";
    configParser.GetIntValue(itemCfgStr, myffmpeg.setParam.n_init);
    itemCfgStr = "tracklet";
    configParser.GetIntValue(itemCfgStr, myffmpeg.setParam.tracklet);
    itemCfgStr = "m_strTrackDisplay";
    configParser.GetStringValue(itemCfgStr, myffmpeg.setParam.m_strTrackDisplay);
    itemCfgStr = "deep_path";
    configParser.GetStringValue(itemCfgStr, myffmpeg.setParam.deep_path);
    itemCfgStr = "cameraType";
    configParser.GetIntValue(itemCfgStr, myffmpeg.setParam.cameraType);
    itemCfgStr = "missionType";
    configParser.GetIntValue(itemCfgStr, myffmpeg.setParam.missionType);
    itemCfgStr = "selfmodel";
    configParser.GetIntValue(itemCfgStr, myffmpeg.setParam.selfmodel);
    itemCfgStr = "MODEL_INPUT_WIDTH";
    configParser.GetIntValue(itemCfgStr, myffmpeg.setParam.WIDTH);
    itemCfgStr = "MODEL_INPUT_HEIGHT";
    configParser.GetIntValue(itemCfgStr, myffmpeg.setParam.HEIGHT);
    itemCfgStr = "Label";
    configParser.GetVectorStringValue(itemCfgStr, myffmpeg.setParam.LABEL);
    itemCfgStr = "m_camWidth";
    configParser.GetIntValue(itemCfgStr, myffmpeg.setParam.camWidth);
    itemCfgStr = "m_camHeight";
    configParser.GetIntValue(itemCfgStr, myffmpeg.setParam.camHeight);
    itemCfgStr = "m_interval_time";
    configParser.GetIntValue(itemCfgStr, myffmpeg.setParam.inter_time);
    configParser.GetStringValue("m_output_addr", myffmpeg.setParam.url);
    configParser.GetIntValue("m_objectsType", myffmpeg.setParam.m_objectsType);
    configParser.GetIntValue("m_iCameraID", myffmpeg.setParam.m_iCameraID);

    std::cout << "streamPath = " << myffmpeg.setParam.streamPath << std::endl
              << "omModelPath = " << myffmpeg.setParam.omModelPath << std::endl
              << "m_output_adrr = " << myffmpeg.setParam.url <<std::endl;
    if (myffmpeg.setParam.selfmodel == 0)
    {
        if (myffmpeg.setParam.cameraType == 1)
        {
            myffmpeg.MODEL_INPUT_WIDTH = 1344;
            myffmpeg.MODEL_INPUT_HEIGHT = 768;
        }
        else if (myffmpeg.setParam.cameraType == 2 && myffmpeg.setParam.missionType == 1)
        {
            myffmpeg.MODEL_INPUT_WIDTH = 640;
            myffmpeg.MODEL_INPUT_HEIGHT = 480;
        }
        else if (myffmpeg.setParam.cameraType == 2 && myffmpeg.setParam.missionType == 2)
        {
            myffmpeg.MODEL_INPUT_WIDTH = 1280;
            myffmpeg.MODEL_INPUT_HEIGHT = 736;
        }
        else
        {
            ERROR_LOG("error cameraType, Proceed with the light camera");
            myffmpeg.MODEL_INPUT_WIDTH = 1344;
            myffmpeg.MODEL_INPUT_HEIGHT = 768;
        }

        if (myffmpeg.setParam.missionType == 1 && myffmpeg.setParam.cameraType == 1)
        {
            myffmpeg.Label1 = {"lorry", "car", "person", "bus"};
            //['person', 'lorry', 'car', 'bigbus', 'midbus']
        }
        else if (myffmpeg.setParam.missionType == 2 && myffmpeg.setParam.cameraType == 1)
        {
            myffmpeg.Label1 = {"sail", "guard", "container", "freighter", "motor", "speed", "cruise", "rowing", "passenger"};
            //['sail', 'guard', 'container', 'freighter', 'motor', 'speed', 'cruise', 'rowing', 'passenger']
        }
        else if (myffmpeg.setParam.missionType == 1 && myffmpeg.setParam.cameraType == 2)
        {
            // ['lorry', 'car', 'person', 'midbus', 'bigbus']
            myffmpeg.Label1 = {"lorry", "car", "person", "midbus", "bigbus"};
        }
        else if (myffmpeg.setParam.missionType == 2 && myffmpeg.setParam.cameraType == 2)
        {
            //['sail', 'guard', 'container', 'freighter', 'motor', 'speed', 'cruise', 'rowing', 'passenger']
            myffmpeg.Label1 = {"sail", "guard", "container", "freighter", "motor", "speed", "cruise", "rowing", "passenger"};
        }
        else
        {
            ERROR_LOG("error cameraType, Proceed with the light camera");
            myffmpeg.Label1 = {"person", "lorry", "car", "bigbus", "midbus"};
        }
    }
    else
    {
        myffmpeg.MODEL_INPUT_WIDTH = myffmpeg.setParam.WIDTH;
        myffmpeg.MODEL_INPUT_HEIGHT = myffmpeg.setParam.HEIGHT;
        myffmpeg.Label1 = myffmpeg.setParam.LABEL;
        myffmpeg.m_camWidth = myffmpeg.setParam.camWidth;
        myffmpeg.m_camHeight = myffmpeg.setParam.camHeight;

        // ret = encoder_.InitResource(m_camWidth, m_camHeight);
        myffmpeg.m_interval_time = myffmpeg.setParam.inter_time;
    }
	myffmpeg.work();
   
    return 0;
}
